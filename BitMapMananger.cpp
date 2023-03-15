//#include "BitMapMananger.h"
//
//BitMapMananger* BitMapMananger::m_hThis = NULL;
//
//HBITMAP MyCreateDIBSection(HDC hdc, int width, int height)
//{
//    BITMAPINFO bm_info;
//    ZeroMemory(&bm_info.bmiHeader, sizeof(BITMAPINFOHEADER));
//
//    bm_info.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
//    //color bits : 1, 4, 8, 16, 24, 32
//    //1:흑백, 4:16색, 8:256색, 16:2^15색, 24,31:2^24색
//    bm_info.bmiHeader.biBitCount = 24;
//    bm_info.bmiHeader.biWidth = width; //너비, 비트맵의 가로 픽셀 수
//    bm_info.bmiHeader.biHeight = height; //높이, 비트맵의 세로 픽셀 수
//    bm_info.bmiHeader.biPlanes = 1; //1로 고정, 반드시 1이어야 한다
//
//    LPVOID pBits;
//    return CreateDIBSection(hdc, &bm_info, DIB_RGB_COLORS, (void**)&pBits, NULL, 0);
//}
//
//void Draw(HWND hWnd, HDC hdc)
//{
//    //RECT clientRect;
//    //GetClientRect(hWnd, &clientRect);
//
//    //HBITMAP backBitmap = MyCreateDIBSection(hdc, clientRect.right + 1, clientRect.bottom + 1);
//    //HDC backDC = CreateCompatibleDC(hdc);
//    //SelectObject(backDC, backBitmap);
//
//    //HDC memDC = CreateCompatibleDC(hdc);
//    ///*HBITMAP oldBitmap = (HBITMAP)SelectObject(memDC, Chess);
//    //TransparentBlt(backDC, 100 + g_nX, 100, 125, 125, memDC, 0, 0, 125, 125, RGB(255, 0, 255));
//    //SelectObject(memDC, oldBitmap);
//    //oldBitmap = (HBITMAP)SelectObject(memDC, Dog);*/
//
//    //BitBlt(backDC, 0, 0, 145, 245, memDC, 0, 0, SRCCOPY);
//    //StretchBlt(backDC, 200, 200, 245, 345, memDC, 0, 0, 145, 245, SRCCOPY);
//    //SelectObject(memDC, oldBitmap);
//    //DeleteDC(memDC);
//
//    //BitBlt(hdc, 0, 0, 145, 245, memDC, 0, 0, SRCCOPY);
//    //DeleteObject(backDC);
//    //DeleteObject(backBitmap);
//}