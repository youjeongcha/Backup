#ifndef _CRUDETIMER_H
#define _CRUDETIMER_H

#pragma comment(lib, "winmm.lib")
#include <windows.h>

class CrudeTimer
{
private:
  //set to the time (in seconds) when class is instantiated
  double m_dStartTime;

  //set the start time
  CrudeTimer(){m_dStartTime = timeGetTime() * 0.001;}
  CrudeTimer(const CrudeTimer&);
  CrudeTimer& operator=(const CrudeTimer&);
  
public:
  static CrudeTimer* Instance();

  //returns how much time has elapsed since the timer was started
  double GetCurrentTime(){return timeGetTime() * 0.001 - m_dStartTime;}

};

#define Clock CrudeTimer::Instance()

#endif