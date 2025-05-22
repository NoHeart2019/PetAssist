#pragma once

#include <atlbase.h>
#include <atlstr.h>
#include <windows.h>
#include <iostream>

// ������־����ö��
enum LogLevel {
	LogLevelDebug,
	LogLevelInfo,
	LogLevelError
};

// �������ģʽö��
enum OutputMode {
	OutputModeDebugger,
	OutputModeFile
};

// ��־��¼����
class CDebugLogger {
private:
	// ��Ա���������� m_X ��ʽ��_ ������ĸ��д
	LogLevel m_CurrentLevel;  // ��ǰ��־����
	OutputMode m_CurrentMode; // ��ǰ���ģʽ
	CString m_LogFilePath;   // ��־�ļ�·��
	bool m_IsLoggingEnabled;  // ������־�Ƿ�����ı�־
	ULONG m_IndexLog;
public:
	// ���캯������ʼ����־�������ģʽ����־�ļ�·������־����״̬
	CDebugLogger(LogLevel level = LogLevelDebug, OutputMode mode = OutputModeDebugger, 
		const CStringA& filePath = "debug.log", bool isLoggingEnabled = false)
		: m_CurrentLevel(level), 
		m_CurrentMode(mode), 
		m_LogFilePath(filePath), 
		m_IsLoggingEnabled(isLoggingEnabled) {
		m_IndexLog = 0;
		}

	// ������־����
	void SetLogLevel(LogLevel level) {
		m_CurrentLevel = level;
	}

	// �������ģʽ
	void SetOutputMode(OutputMode mode) {
		m_CurrentMode = mode;
	}

	// ������־�Ƿ����
	void SetLoggingEnabled(bool enabled) {
		m_IsLoggingEnabled = enabled;
	}


public:
	// �����Ϣ��������
	void OutputToDebugger(const CStringA& message) {
		if (m_IsLoggingEnabled) {
			OutputDebugStringA(message);
		}
	}

	// �����Ϣ���ļ�
	void OutputToFile(const CStringA& message) {
		if (m_IsLoggingEnabled) {
			HANDLE hFile = CreateFile(m_LogFilePath, GENERIC_WRITE, 0, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
			if (hFile == INVALID_HANDLE_VALUE) {
				return;
			}
			// ���ļ�ָ���ƶ����ļ�ĩβ
			SetFilePointer(hFile, 0, NULL, FILE_END);
			DWORD bytesWritten;

			CStringA nonConstMessage = message; // ����һ���� const �ĸ���
			const char* buffer = nonConstMessage.GetBuffer();
			int length = nonConstMessage.GetLength();

			// д����־��Ϣ
			WriteFile(hFile, buffer, length, &bytesWritten, NULL);

			nonConstMessage.ReleaseBuffer(); // �ͷŻ�����
			CloseHandle(hFile);
		}
	}

	// ����ģʽ�����Ϣ
	void OutputMessage(const CStringA& message) {
		if (m_IsLoggingEnabled) {
			switch (m_CurrentMode) {
			case OutputModeDebugger:
				OutputToDebugger(message);
				break;
			case OutputModeFile:
				OutputToFile(message);
				break;
			}
		}
	}

	// ���� OutputMessage ����������ɱ����
	void OutputMessage(const char* format, ...) {
		if (m_IsLoggingEnabled) {
			va_list args;
			va_start(args, format);
			CStringA message;
			message.FormatV(format, args);
			va_end(args);
			OutputMessage(message);
		}
	}

	// ���� OutputMessage ���������� LogLevel �Ϳɱ����
	void OutputMessage(LogLevel logLevel, const char* format, ...) {
		if (m_IsLoggingEnabled) {
			if ((logLevel == LogLevelDebug && m_CurrentLevel != LogLevelDebug) ||
				(logLevel == LogLevelInfo && m_CurrentLevel == LogLevelError)) {
					return;
			}

			va_list args;
			va_start(args, format);
			CStringA message;
			message.FormatV(format, args);
			va_end(args);

			CStringA logMessage;
			switch (logLevel) {
			case LogLevelDebug:
				logMessage.Format("[DEBUG] %s", message);
				break;
			case LogLevelInfo:
				logMessage.Format("[INFO] %s", message);
				break;
			case LogLevelError:
				logMessage.Format("[ERROR] %s", message);
				break;
			}

			OutputMessage(logMessage);
		}
	}


public:
	// ���������Ϣ
	void Debug(const CStringA& message) {
		if (m_IsLoggingEnabled && m_CurrentLevel == LogLevelDebug) {
			CStringA logMessage;
			logMessage.Format("[DEBUG] %s", message);
			OutputMessage(logMessage);
		}
	}

	// �����Ϣ
	void Info(const CStringA& message) {
		if (m_IsLoggingEnabled && (m_CurrentLevel == LogLevelDebug || m_CurrentLevel == LogLevelInfo)) {
			CStringA logMessage;
			logMessage.Format("[INFO] %d %s", m_IndexLog++, message);
			OutputMessage(logMessage);
		}
	}

	// ���������Ϣ
	void Error(const CStringA& message) {
		if (m_IsLoggingEnabled) {
			CStringA logMessage;
			logMessage.Format("[ERROR] %s", message);
			OutputMessage(logMessage);
		}
	}

	CStringA Format(const char* formats, ...)
	{
		ULONG n = 0;
		ULONG length = 4096;
		CStringA String = "";
		char* Ptr = new char[length];
		if (Ptr == NULL)
			return String;
		RtlZeroMemory(Ptr, length);
		va_list arglist = NULL;
		va_start(arglist, formats);
		n = vsprintf_s(Ptr, length, formats, arglist);
		va_end(arglist);

		String = Ptr;

		return String;
	}


};

extern CDebugLogger theLog;

#define ZxDebug(x) \
{\
	CStringA Str000;\
	Str000.Format x;\
	theLog.Debug(Str000);\
}
#define ZxDebugEx(x) \
{\
	CStringA Str000;\
	Str000.Format x;\
	theLog.Info(Str000);\
}


int CDebugLoggerTest();
