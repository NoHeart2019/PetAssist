#include "stdafx.h"
#include "Util.h"
#include <time.h>

ULONGLONG GetSystemTime1970()
{
	//return ::_time64(NULL);
	// 获取当前系统时间
	SYSTEMTIME st;
	GetSystemTime(&st);
	
	// 转换为系统文件时间格式
	FILETIME ft;
	SystemTimeToFileTime(&st, &ft);

	// 将 FILETIME 转换为 ULONGLONG
	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;
	ui.QuadPart =((ui.QuadPart - 116444736000000000ULL) / 10000000U);
	return ui.QuadPart;
}

ULONGLONG GetSystemTimeToday1970()
{
	SYSTEMTIME st;
	GetSystemTime(&st);
	st.wHour = 0;
	st.wMinute = 0;
	st.wSecond = 0;
	st.wMilliseconds = 0;

	// 转换为系统文件时间格式
	FILETIME ft;
	SystemTimeToFileTime(&st, &ft);
	// 将 FILETIME 转换为 ULONGLONG
	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;
	//ui.QuadPart =((ui.QuadPart - 116444736000000000ULL) / 10000000U);

	return ui.QuadPart;

}

ULONGLONG SystemTimeTo1970(LPSYSTEMTIME SystemTime)
{
	SYSTEMTIME St = {};
	FILETIME ft={};
	TzSpecificLocalTimeToSystemTime(NULL, SystemTime, &St);

	SystemTimeToFileTime(&St, &ft);
	// 将 FILETIME 转换为 ULONGLONG
	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;
	ui.QuadPart =((ui.QuadPart - 116444736000000000ULL) / 10000000U);

	return ui.QuadPart;
}

SYSTEMTIME FileTimeToLocalSystemTime(LPFILETIME LocalTime)
{
	FILETIME LocalTime32={};
	SYSTEMTIME SystemTime={};
	FileTimeToLocalFileTime(LocalTime, &LocalTime32);
	FileTimeToSystemTime(&LocalTime32, &SystemTime);

	return SystemTime;
}


BOOL  IsAppAlreadyRunning(LPCWSTR EventName)
{
	 if(theOnlyRun.Create(FALSE, EventName) == TRUE && theOnlyRun.IsOpen())
		return TRUE;

	return FALSE;
}
