#include "stdafx.h"
#include "C32Debug.h"


CDebugLogger theLog;


int CDebugLoggerTest() {
	setlocale(LC_ALL, "Chinese");

	CDebugLogger logger;
	// ������־����Ϊ INFO
	logger.SetLogLevel(LogLevelInfo);
	// �������ģʽΪ�ļ�
	logger.SetOutputMode(OutputModeFile);

	logger.Format("%ws", L"�й���������");

	// ʹ�����ص� OutputMessage ����
	logger.OutputMessage(LogLevelInfo, "Info message with string %s", "test");
	logger.OutputMessage(LogLevelError, "Error message with float %.2f", 3.14);

	// ������־���
	logger.SetLoggingEnabled(false);

	// ��Щ��־���������
	logger.OutputMessage(LogLevelDebug, "This debug message won't be logged", 0);
	logger.OutputMessage(LogLevelInfo, "This info message won't be logged", 0);
	logger.OutputMessage(LogLevelError, "This error message won't be logged", 0);

	return 0;
}