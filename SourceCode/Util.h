#pragma once
#include <Windows.h>


//��Э������ʱ (UTC) ���ص�ǰϵͳ���ں�ʱ��
ULONGLONG GetSystemTime1970();

ULONGLONG GetSystemTimeToday1970();

ULONGLONG SystemTimeTo1970(LPSYSTEMTIME SystemTime);

SYSTEMTIME FileTimeToLocalSystemTime(LPFILETIME LocalTime);

BOOL  IsAppAlreadyRunning(LPCWSTR EventName);
