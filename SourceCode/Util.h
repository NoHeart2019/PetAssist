#pragma once
#include <Windows.h>


//以协调世界时 (UTC) 返回当前系统日期和时间
ULONGLONG GetSystemTime1970();

ULONGLONG GetSystemTimeToday1970();

ULONGLONG SystemTimeTo1970(LPSYSTEMTIME SystemTime);

SYSTEMTIME FileTimeToLocalSystemTime(LPFILETIME LocalTime);

BOOL  IsAppAlreadyRunning(LPCWSTR EventName);
