#include "mbed.h"
#include "DHT22.h"
#include "motordriver.h"
#include "Adafruit_GFX_lib/Adafruit_SSD1306.h"
#include <string.h>


//LED
#define GREEN_LED_PIN       PA_13
#define YELLOW_LED_PIN      PB_10
#define RED_LED_PIN         PA_4
//BTN
#define FIRST_BTN_PIN       PA_14
#define SECOND_BTN_PIN      PB_7
#define THIRD_BTN_PIN       PC_4
//MOTER
#define MOTOR_A_PWN_PIN 	PA_7
#define MOTOR_A_DIR_PIN 	PC_8
//DHT22
#define DHT22_DATA_PIN		PB_2
//JOYSICK
#define JS_X_AXIS			PC_2
#define JS_Y_AXIS			PC_3
#define NEUTRAL_VALUE		73
//BUZZER
#define BUZZER_PIN      PC_9
//BUZZER-SOUND TODO::enum change
#define C_NOTE_HALF_PERIOD  1915 //usec
#define NOTE_c  0
#define NOTE_d  1
#define NOTE_e  2
#define NOTE_f  3
#define NOTE_g  4
#define NOTE_a  5
#define NOTE_b  6
#define NOTE_C  7
//PWD length
#define PASSWORD_LENGTH		4 

const int PASSWORD[PASSWORD_LENGTH] = { 1, 0, 0, 0 }; // PWD


enum LED
{
	GREEN_LED,
	YELLOW_LED,
	RED_LED,
	COUNT_LED,

	NONE_LED,
};
enum BTN
{
	BTN_FIRST,
	BTN_SECOND,
	BTN_THIRD,
	BTN_COUNT
};
enum DIRECTION
{
	DIRECTION_FORWARD,
	DIRECTION_BACKWARD,
};
enum DoorState
{
	DOOR_CLOSED,
	DOOR_OPENED
};
enum OperatingMode
{
	MODE_NORMAL,
	MODE_INPUT
};

enum TIME
{
	TIME_YELLOW_LED_BLINK = 1000,
	TIME_RED_GREEN_LED_BLINK = 2000,


	TIME_SLOW = 500,
	TIME_GAP = 50,
	TIME_SLOWEST = 900,
	TIME_FASTEST = 50,
};

enum MELODY_TYPE
{
	MELODY_OPEN,
	MELODY_CLOSE,
	MELODY_WRONG,
};

enum edge_t
{
	NO_EDGE = 0,
	RISING_EDGE,
	FALLING_EDGE,
};



//LED
DigitalOut greenLed(GREEN_LED_PIN);
DigitalOut yellowLed(YELLOW_LED_PIN);
DigitalOut redLed(RED_LED_PIN);
DigitalOut* leds[COUNT_LED];
bool bLedActive = false;
int ledTime = 0;
Timer ledTm;

//BTN
DigitalIn firstBtn(FIRST_BTN_PIN);
DigitalIn secondBtn(SECOND_BTN_PIN);
DigitalIn thirdBtn(THIRD_BTN_PIN);
DigitalIn* btns[BTN_COUNT];

//MOTOR
Motor motorA(MOTOR_A_PWN_PIN, MOTOR_A_DIR_PIN);
bool bMotorActive = false;
int motorTime = 0;
Timer motorTm;

//DHT
DHT22 dht22(DHT22_DATA_PIN);

//OLED
I2C i2cMaster(I2C_SDA, I2C_SCL);		//D14, D15
Adafruit_SSD1306_I2c myOled(i2cMaster, D13, 0x78, 64, 128);

//JOYSICK
Serial pc(USBTX, USBRX, 9600);
AnalogIn xAxis(JS_X_AXIS);
AnalogIn yAxis(JS_Y_AXIS);
Ticker ctrTicker;
Ticker jsTicker;
int x;

//BUZZER
PwmOut buzzer(BUZZER_PIN);
int note_periods[] = {
	3830, 3400, 3038, 2864, 2550, 2272, 2028, 1912
};
int melody[] = {
	NOTE_c, NOTE_d, NOTE_e, NOTE_f, NOTE_g, NOTE_a, NOTE_b,
	NOTE_C, NOTE_C, NOTE_b, NOTE_a, NOTE_g, NOTE_f, NOTE_e,
	NOTE_d, NOTE_c
};
int melody_open[] = {
	NOTE_a, NOTE_b, NOTE_c
};
int melody_close[] = {
	NOTE_c, NOTE_b, NOTE_a
};
int melody_wrong[] = {
	NOTE_f
};

Timer BuzzerTm;
Ticker toneTicker;
int sound_index = 0;
MELODY_TYPE nowSoundType;


//LED Blink
void blinkLed(enum LED led, int sec)
{
	if (bLedActive == true) //prevent double show LED
	{
		for (int i = 0; i < COUNT_LED; i++)
		{
			*leds[i] = 0;
		}
	}

	bLedActive = true;
	ledTm.reset();
	*leds[led] = 1;
}



//LockON
bool verifyPassword(const int* input)
{
	for (int i = 0; i < PASSWORD_LENGTH; i++)
	{
		if (input[i] != PASSWORD[i])
			return false; //not open
	}

	return true; //open
}

//doorOPEN
void Door_Open(enum DoorState* doorState)
{
	if (*doorState == DOOR_CLOSED)
	{
		*doorState = DOOR_OPENED;
		printf("Door Opened\n");
	}
}

//BUZZER
void stopPlaying() {
	toneTicker.detach();  // Detach the ticker to stop the melody
	buzzer = 0;
}

void playTone(MELODY_TYPE sound_TYPE) {
	nowSoundType = sound_TYPE;

	switch (sound_TYPE) {
	case MELODY_OPEN:
		buzzer.period_us(note_periods[melody_open[sound_index++]]);
		break;

	case MELODY_CLOSE:
		buzzer.period_us(note_periods[melody_close[sound_index++]]);
		break;

	case MELODY_WRONG:
		buzzer.period_us(note_periods[melody_wrong[sound_index++]]);
		break;

	default:
		return;
	}
	BuzzerTm.start();
	buzzer = 0.5;
}


void Door_AutoLock(enum DoorState* doorState)
{
	static time_t startTime = 0; //door open time
	const int lockDuration = 30;//Debug::3. Defualt::30

	if (*doorState == DOOR_OPENED)
	{
		if (startTime == 0)
		{
			startTime = time(NULL); //set open time
		}
		else
		{
			time_t currentTime = time(NULL); //set now time

			if (currentTime - startTime >= lockDuration)
			{
				*doorState = DOOR_CLOSED;
				//BUZZER
				playTone(MELODY_CLOSE); //buzzer
				motorTime = 1000; //moter clock
				bMotorActive = true;
				motorTm.reset();
				motorTm.start();
				motorA.forward(250);
				startTime = 0; //initialize
			}
		}
	}
}


void displayOLED_NormalMode(enum DoorState doorState, float temperature, float humidity) {
	myOled.clearDisplay();

	//Draw rectangles for display
	myOled.drawRect(0, 5, 127, 30, WHITE);


	//Display door state
	char doorStateBuffer[20] = "Door "; 
	strcat(doorStateBuffer, (doorState == DOOR_OPENED) ? "Open" : "Close");

	myOled.setTextSize(2);
	myOled.setTextCursor(5, 15);

	for (int i = 0; i < strlen(doorStateBuffer); i++) {
		myOled.writeChar(doorStateBuffer[i]);
	}


	//Display temperature
	char tempBuffer[20] = "Temperature: ";
	char tempString[10];

	//float data change String/ and save temperatureString
	snprintf(tempString, sizeof(tempString), "%.2f", temperature);
	strcat(tempBuffer, tempString);

	myOled.setTextSize(1);
	myOled.setTextCursor(10, 45);

	//OLED
	for (int i = 0; i < strlen(tempBuffer); i++) {
		myOled.writeChar(tempBuffer[i]);
	}


	// Display humidity
	char humBuffer[20] = "humidity: ";  // ??? ??? ??? ??
	char humString[10];  // ??? ???? ???? ??? ??

	//float data change String/ and save temperatureString
	snprintf(humString, sizeof(humString), "%.2f", humidity);
	strcat(humBuffer, humString);

	myOled.setTextSize(1);
	myOled.setTextCursor(10, 55);

	// tempBuffer? ? ??? OLED? ??
	for (int i = 0; i < strlen(humBuffer); i++) {
		myOled.writeChar(humBuffer[i]);
	}

	myOled.display();
}


void displayOLED_InputMode(const int* passwordInput, int password_Index) {
	myOled.clearDisplay();

	// Draw rectangles for display
	myOled.drawRect(0, 10, 30, 50, WHITE);
	myOled.drawRect(30, 10, 30, 50, WHITE);
	myOled.drawRect(60, 10, 30, 50, WHITE);
	myOled.drawRect(90, 10, 30, 50, WHITE); 

	myOled.setTextSize(4);

	myOled.setTextCursor(5, 20); 
	myOled.writeChar(0x30 + (passwordInput[0])); 

	myOled.setTextCursor(35, 20);
	myOled.writeChar(0x30 + (passwordInput[1])); 

	myOled.setTextCursor(65, 20); 
	myOled.writeChar(0x30 + (passwordInput[2]));

	myOled.setTextCursor(95, 20);
	myOled.writeChar(0x30 + (passwordInput[3]));

	//now Cursor show
	myOled.drawFastHLine(password_Index * 30, 62, 30, WHITE);

	myOled.display();
}

//JOYSTICK > password_Index change
int readJoystick(int password_Index)
{
	x = xAxis * 100;

	//Normalization
	x = NEUTRAL_VALUE - x;
	if (abs(x) <= 1)
		x = 0;

	// Modify passwordInput index based on joystick input
	if ((x > 0) && (password_Index > 0))
	{ //joystick => (left == x++)
		password_Index--;
	}
	else if ((x < 0) && (password_Index < PASSWORD_LENGTH - 1))
	{ //joystick => (right == x--)
		password_Index++;
	}

	return password_Index;
}


//edge
edge_t detectBtnEdge(int btn)
{
	static int prevState[BTN_COUNT] = { 1, 1, 1 };
	edge_t edge = NO_EDGE;

	//edge now state disticnt
	int currState = (btn == BTN_FIRST ? firstBtn : ((btn == BTN_SECOND) ? secondBtn : thirdBtn));

	if (currState != prevState[btn])
	{
		wait_ms(50); //debouncing delay 50miliseconed
		currState = (btn == BTN_FIRST ? firstBtn : ((btn == BTN_SECOND) ? secondBtn : thirdBtn));

		if (currState != prevState[btn])
		{
			if (currState == 1)
				edge = RISING_EDGE;
			else
				edge = FALLING_EDGE;

			prevState[btn] = currState;
		}
	}

	return edge;
}



void setup()
{
	//MOTOR
	motorA.stop();

	//LED
	leds[GREEN_LED] = &greenLed;
	leds[YELLOW_LED] = &yellowLed;
	leds[RED_LED] = &redLed;

	btns[BTN_FIRST] = &firstBtn;
	btns[BTN_SECOND] = &secondBtn;
	btns[BTN_THIRD] = &thirdBtn;

	buzzer.period_us(C_NOTE_HALF_PERIOD + 2);
	buzzer = 0;
}



int main() {
	edge_t edge[BTN_COUNT] = { NO_EDGE , NO_EDGE , NO_EDGE };

	//LED
	int time = TIME_YELLOW_LED_BLINK; //blicking time
	LED nowLed = YELLOW_LED; //first show led

	//MOTOR
	DIRECTION directionCheck = DIRECTION_FORWARD;
	double speed = 1.0; //Motor Speed

	//OLED
	int cnt = 0;
	bool inverted = false;
	int textSize = 1;
	wait(3.0);		// wait to display splash image
	myOled.clearDisplay();

	myOled.setTextSize(textSize);
	myOled.printf("%ux%u OLED Display\r\n", myOled.width(), myOled.height());
	myOled.display();


	//DOOR
	enum DoorState doorState = DOOR_CLOSED; //inital door state
	enum OperatingMode operatingMode = MODE_NORMAL; //inital Mode

	int passwordInput[PASSWORD_LENGTH] = { 0, 0, 0, 0, };
	int password_Index = 0; //PWD seat change
	int prev_Index = password_Index;
	int passwordCorrect = 0;

	setup();

	//BUZZER
	int current_note_index = 0;



	while (1)
	{
		//========= Timer ==========
		//Buzer
		if (BuzzerTm.read() > 1.0)
		{
			BuzzerTm.reset();
			BuzzerTm.stop();
			stopPlaying(); 
		}

		if ((bMotorActive) && (motorTm.read_ms() >= motorTime)) //motor active stop
		{
			bMotorActive = false;

			motorTm.reset();
			motorTm.stop();
			motorA.stop();
		}


		if ((bLedActive) && (ledTm.read_ms() >= ledTime)) //LED active stop
		{
			bLedActive = false;

			for (int i = 0; i < COUNT_LED; i++)
			{
				*leds[i] = 0;
			}

			ledTm.reset();
			ledTm.stop();
		}


		edge[BTN_FIRST] = detectBtnEdge(BTN_FIRST); 			//check isPress btn1?
		edge[BTN_SECOND] = detectBtnEdge(BTN_SECOND); 		//check isPress btn2?


		//door is closer > input pwd
		if (doorState == DOOR_CLOSED) {
			//====== processButton1() ======
			//pressed btn1 
			if (edge[BTN_FIRST] == FALLING_EDGE)
			{

				operatingMode = MODE_INPUT;
				blinkLed(YELLOW_LED, time);

				//PWD++
				passwordInput[password_Index]++;

				if (passwordInput[password_Index] > 9)
					passwordInput[password_Index] = 9;

				//OLED
				displayOLED_InputMode(passwordInput, password_Index);
			}


			//====== processButton2() ======
			//pressed btn2
			if (edge[BTN_SECOND] == FALLING_EDGE)
			{

				operatingMode = MODE_INPUT;
				blinkLed(YELLOW_LED, time);

				//PWD--
				passwordInput[password_Index]--;

				if (passwordInput[password_Index] < 0)
					passwordInput[password_Index] = 0;

				//OLED
				displayOLED_InputMode(passwordInput, password_Index);
			}
		}




		if (operatingMode == MODE_NORMAL)
		{
			//OLED - Normal Mode
			if (dht22.sample())
			{
				displayOLED_NormalMode(doorState, dht22.getTemperature() / 10.0, dht22.getHumidity() / 10.0);
			}

			//if Mode is normal > close door 30s
			Door_AutoLock(&doorState);

		}
		else if (operatingMode == MODE_INPUT)
		{ //pwd input mode

			password_Index = readJoystick(password_Index);

			if (password_Index != prev_Index)
			{
				prev_Index = password_Index;
				//OLED - now cusor show
				displayOLED_InputMode(passwordInput, password_Index);
			}

			//===== check isPress btn3? =======
			edge[BTN_THIRD] = detectBtnEdge(BTN_THIRD);

			//pressed btn3
			if (edge[BTN_THIRD] == FALLING_EDGE)
			{
				operatingMode = MODE_NORMAL; //turn mode_normal
				time = TIME_RED_GREEN_LED_BLINK;

				//pwd check
				if (verifyPassword(passwordInput))
				{
					//open door
					Door_Open(&doorState);

					//BUZZER
					playTone(MELODY_OPEN); //buzzer

					bMotorActive = true; //Moter active start;
					motorTime = 1000;
					motorTm.reset();
					motorTm.start();
					motorA.backward(250);

					operatingMode = MODE_NORMAL;

					blinkLed(GREEN_LED, time);
				}
				else
				{ //not open door
					playTone(MELODY_WRONG); //buzzer
					blinkLed(RED_LED, time);
				}

				//password[] init
				password_Index = 0;
				for (int i = 0; i < PASSWORD_LENGTH; i++)
				{
					passwordInput[i] = 0;
				}
			}
		}

		wait(1.0); //humidity realtive //Delete if not reauired
	}
	return 0;
}
