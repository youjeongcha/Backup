#pragma once

#include "resource.h"

SOCKET g_sock;
std::string g_strChat;
std::vector<std::string> g_vLog;

void AddLog(const char* str);
void ErrorQuit(const char* caption);
void ErrorDisplay(HWND hWnd, const char* caption);
void ErrorDisplay(HWND hWnd, const int& errorCode, const char* caption);
void SocketProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);