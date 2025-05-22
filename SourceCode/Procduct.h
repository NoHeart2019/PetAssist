
/*
	产品类 
	包含，开始以下成员
	系统开始目录，是否是管理员， 32位还是64位程序。
	自身路径。自身目录，自身名称,快捷方式名称，快捷方式描述。

*/
#include <atlbase.h>
#include <atlconv.h>
#include <windows.h>
#include <shlobj.h>
#include <objbase.h>


class CProduct
{
public:
	// 构造函数，初始化成员变量
	CProduct()
	{
		// 初始化成员变量
		m_AutoRunDirectory.Empty();
		m_SelfDirectory.Empty();
		m_SystemDirectory.Empty();
		m_Wow64Directory.Empty();
		m_IsAdmin = FALSE;
		m_Is64Bit = FALSE;
		m_IsActiveLicense = TRUE;
		m_SelfPath.Empty();
		m_SelfProgramName.Empty();
		m_ShortcutName.Empty();
		m_ShortcutDescription.Empty();
		m_FileVersion.Empty();
		m_ProductVersion.Empty();
		m_ProductName.Empty();
		m_FileDescription.Empty();

		m_LanguageCode = GetUserDefaultUILanguage();

		// 获取开机自启动目录
		wchar_t startupPath[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, startupPath)))
		{
			m_AutoRunDirectory = startupPath;
		}
		
		// 获取当前进程的自身路径
		wchar_t szPath[MAX_PATH];
		if (GetModuleFileNameW(NULL, szPath, MAX_PATH))
		{
			m_SelfPath = szPath;
			// 提取自身目录
			int pos = m_SelfPath.ReverseFind(L'\\');
			if (pos != -1)
			{
				m_SelfDirectory = m_SelfPath.Left(pos);
				m_SelfProgramName = m_SelfPath.Mid(pos + 1);
				if (!m_SelfDirectory.IsEmpty())
					::SetCurrentDirectory(m_SelfDirectory);
			}
		} 
		
		// 获取系统目录，加上::
		wchar_t systemPath[MAX_PATH];
		if (::GetSystemDirectoryW(systemPath, MAX_PATH))
		{
			m_SystemDirectory = systemPath;
		}

		// 获取 WOW64 目录
		if (IsWow64Process(GetCurrentProcess(), &m_Is64Bit) && m_Is64Bit)
		{
			wchar_t wow64Path[MAX_PATH];
			if (GetSystemWow64DirectoryW(wow64Path, MAX_PATH))
			{
				m_Wow64Directory = wow64Path;
			}
		}

		// 检查是否是管理员权限
		m_IsAdmin = IsAdminInternal();

		// 检查是 32 位还是 64 位程序
		m_Is64Bit = Is64BitProcess();

		// 获取文件版本、产品版本、产品名称以及文件描述
		GetVersionInfo();
	}

	// 开机自启动目录的 Set 和 Get 方法
	void SetAutoRunDirectory(const CString& value)
	{
		m_AutoRunDirectory = value;
	}
	
	CString& GetAutoRunDirectory()
	{
		return m_AutoRunDirectory;
	}

	// 自身目录的 Set 和 Get 方法
	void SetSelfDirectory(const CString& value)
	{
		m_SelfDirectory = value;
	}
	CString& GetSelfDirectory()
	{
		return m_SelfDirectory;
	}

	// 系统目录的 Get 方法
	CString& GetSystemDirectory()
	{
		return m_SystemDirectory;
	}

	// WOW64 目录的 Get 方法
	CString& GetWow64Directory()
	{
		return m_Wow64Directory;
	}

	// 是否是管理员的 Set 方法和直接以成员变量名的获取方法
	void SetIsAdmin(BOOL value)
	{
		m_IsAdmin = value;
	}
	BOOL IsAdmin() const
	{
		return m_IsAdmin;
	}

	// 32 位还是 64 位程序的 Set 方法和直接以成员变量名的获取方法
	void SetIs64Bit(BOOL value)
	{
		m_Is64Bit = value;
	}
	BOOL Is64Bit() const
	{
		return m_Is64Bit;
	}

	// 自身路径的 Set 和 Get 方法
	void SetSelfPath(const CString& value)
	{
		m_SelfPath = value;
	}
	
	CString& GetSelfPath()
	{
		return m_SelfPath;
	}

	// 自身程序名的 Get 方法
	CString& GetSelfProgramName()
	{
		return m_SelfProgramName;
	}

	// 快捷方式名称的 Get 方法
	CString& GetShortcutName()
	{
		return m_ShortcutName;
	}

	// 快捷方式描述的 Get 方法
	CString& GetShortcutDescription()
	{
		return m_ShortcutDescription;
	}

	// 文件版本的 Get 方法
	CString& GetFileVersion()
	{
		return m_FileVersion;
	}

	// 产品版本的 Get 方法
	CString& GetProductVersion()
	{
		return m_ProductVersion;
	}

	// 产品名称的 Get 方法
	CString& GetProductName()
	{
		return m_ProductName;
	}

	// 文件描述的 Get 方法
	CString& GetFileDescription()
	{
		return m_FileDescription;
	}
	// 获取语言码
	LANGID GetLanguageCode() const
	{
		return m_LanguageCode;
	}

	LANGID SetLanguageCode() const
	{
		return m_LanguageCode;
	}

	// 创建快捷方式的方法，将 autoRunDirectory 改为 SaveDirectory
	BOOL CreateShortcut(const CString& shortcutName, const CString& shortcutDescription, const CString& SaveDirectory)
	{
		HRESULT hres;
		IShellLinkW* psl;

		// 初始化 COM 库
		hres = CoInitialize(NULL);
		if (FAILED(hres))
		{
			return FALSE;
		}

		// 创建 IShellLink 对象
		hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&psl);
		if (SUCCEEDED(hres))
		{
			IPersistFile* ppf;

			// 设置快捷方式的目标路径
			psl->SetPath(m_SelfPath);

			// 设置快捷方式的描述
			psl->SetDescription(shortcutDescription);

			// 获取 IPersistFile 接口
			hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

			if (SUCCEEDED(hres))
			{
				CString shortcutPath = SaveDirectory + L"\\" + shortcutName + L".lnk";

				// 保存快捷方式
				hres = ppf->Save(shortcutPath, TRUE);

				// 释放 IPersistFile 接口
				ppf->Release();
			}

			// 释放 IShellLink 对象
			psl->Release();
		}

		// 释放 COM 库
		CoUninitialize();

		if (SUCCEEDED(hres))
		{
			m_ShortcutName = shortcutName;
			m_ShortcutDescription = shortcutDescription;
			return TRUE;
		}

		return FALSE;
	}

	// 创建自启动快捷方式函数
	BOOL CreateAutoRunLink()
	{
		CString File;
		File = m_AutoRunDirectory + L"\\" + m_SelfProgramName +L".lnk";
		DWORD Attributes = GetFileAttributes(File);
		if (Attributes != INVALID_FILE_ATTRIBUTES)
			return TRUE;
				
		return CreateShortcut(m_SelfProgramName, m_FileDescription, m_AutoRunDirectory);
	}

	// 开机自启动函数
	BOOL SetAutoStart(BOOL enable)
	{
		HKEY hKey;
		LONG lResult;
		const wchar_t* subKey = L"Software\\Microsoft\\Windows\\CurrentVersion\\Run";

		if (enable)
		{
			lResult = RegOpenKeyExW(HKEY_CURRENT_USER, subKey, 0, KEY_SET_VALUE, &hKey);
			if (lResult == ERROR_SUCCESS)
			{
				lResult = RegSetValueExW(hKey, m_SelfProgramName, 0, REG_SZ, (BYTE*)m_SelfPath.GetBuffer(), (m_SelfPath.GetLength() + 1) * sizeof(wchar_t));
				RegCloseKey(hKey);
				return lResult == ERROR_SUCCESS;
			}
		}
		else
		{
			lResult = RegOpenKeyExW(HKEY_CURRENT_USER, subKey, 0, KEY_SET_VALUE, &hKey);
			if (lResult == ERROR_SUCCESS)
			{
				lResult = RegDeleteValueW(hKey, m_SelfProgramName);
				RegCloseKey(hKey);
				return lResult == ERROR_SUCCESS;
			}
		}
		return FALSE;
	}

private:
	// 封装检查是否是管理员权限的函数
	BOOL IsAdminInternal()
	{
		SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
		PSID AdministratorsGroup;
		if (AllocateAndInitializeSid(&NtAuthority, 2, SECURITY_BUILTIN_DOMAIN_RID, DOMAIN_ALIAS_RID_ADMINS, 0, 0, 0, 0, 0, 0, &AdministratorsGroup))
		{
			BOOL fIsAdmin = FALSE;
			CheckTokenMembership(NULL, AdministratorsGroup, &fIsAdmin);
			FreeSid(AdministratorsGroup);
			return fIsAdmin;
		}
		return FALSE;
	}

	// 封装判断是 32 位还是 64 位程序的函数
	BOOL Is64BitProcess()
	{
		BOOL bIsWow64 = FALSE;
		IsWow64Process(GetCurrentProcess(), &bIsWow64);
		return !bIsWow64;
	}

	// 获取文件版本、产品版本、产品名称以及文件描述
	// 尝试使用每个语言和代码页组合来获取产品名称和文件描述，优先使用与用户默认 UI 语言匹配的组合：
	
	void GetVersionInfo()
	{
		// 获取文件版本信息的大小
		DWORD dwHandle;
		DWORD dwLen = GetFileVersionInfoSizeW(m_SelfPath, &dwHandle);
		if (dwLen == 0)
		{
			// 文件版本信息大小获取失败，直接返回
			return;
		}

		// 分配内存用于存储文件版本信息
		CHeapPtr<BYTE> buffer;
		if (!buffer.Allocate(dwLen))
		{
			// 内存分配失败，直接返回
			return;
		}

		// 获取文件版本信息
		if (!GetFileVersionInfoW(m_SelfPath, dwHandle, dwLen, buffer))
		{
			// 文件版本信息获取失败，直接返回
			return;
		}

		// 获取固定文件信息
		VS_FIXEDFILEINFO* pFixedFileInfo;
		UINT uLen;
		if (!VerQueryValueW(buffer, L"\\", (LPVOID*)&pFixedFileInfo, &uLen))
		{
			// 固定文件信息获取失败，直接返回
			return;
		}

		// 构建文件版本字符串
		m_FileVersion.Format(L"%d.%d.%d.%d",
			HIWORD(pFixedFileInfo->dwFileVersionMS),
			LOWORD(pFixedFileInfo->dwFileVersionMS),
			HIWORD(pFixedFileInfo->dwFileVersionLS),
			LOWORD(pFixedFileInfo->dwFileVersionLS));

		// 构建产品版本字符串
		m_ProductVersion.Format(L"%d.%d.%d.%d",
			HIWORD(pFixedFileInfo->dwProductVersionMS),
			LOWORD(pFixedFileInfo->dwProductVersionMS),
			HIWORD(pFixedFileInfo->dwProductVersionLS),
			LOWORD(pFixedFileInfo->dwProductVersionLS));

		// 获取语言和代码页信息
		LPDWORD pLangAndCodePage;
		if (VerQueryValueW(buffer, L"\\VarFileInfo\\Translation", (LPVOID*)&pLangAndCodePage, &uLen))
		{
			UINT count = uLen / sizeof(DWORD);
			if (count == 0)
			{
				// 语言和代码页信息数组为空，直接返回
				return;
			}

			// 初始化匹配的语言代码为数组的第一个元素
			DWORD matchedLangCode = pLangAndCodePage[0];

			// 遍历数组，查找与用户默认语言码匹配的元素
			for (UINT i = 0; i < count; ++i)
			{
				WORD langCode = MAKEWORD(LOBYTE(pLangAndCodePage[i]), HIBYTE(HIWORD(pLangAndCodePage[i])));
				if (langCode == LOWORD(m_LanguageCode))
				{
					// 找到匹配的语言码，更新 matchedLangCode 并跳出循环
					matchedLangCode = pLangAndCodePage[i];
					break;
				}
			}

			// 获取产品名称和文件描述
			wchar_t subBlock[256];
			wchar_t* pProductName = nullptr;
			wchar_t* pFileDescription = nullptr;

			// 构建产品名称的子块路径并获取产品名称
			swprintf_s(subBlock, L"\\StringFileInfo\\%04x%04x\\ProductName", LOWORD(matchedLangCode), HIWORD(matchedLangCode));
			VerQueryValueW(buffer, subBlock, (LPVOID*)&pProductName, &uLen);

			// 构建文件描述的子块路径并获取文件描述
			swprintf_s(subBlock, L"\\StringFileInfo\\%04x%04x\\FileDescription", LOWORD(matchedLangCode), HIWORD(matchedLangCode));
			VerQueryValueW(buffer, subBlock, (LPVOID*)&pFileDescription, &uLen);

			// 如果成功获取到产品名称，将其赋值给成员变量
			if (pProductName)
			{
				m_ProductName = pProductName;
			}
			// 如果成功获取到文件描述，将其赋值给成员变量
			if (pFileDescription)
			{
				m_FileDescription = pFileDescription;
			}
		}
	}

	// 函数：递归创建多级目录（基于 ATL 的 CString）
	bool CreateWorkDirectory(const CString& path) {
		int pos = 0;
		do {
			// 找到下一个目录分隔符
			pos = path.Find(L"\\", pos + 1);

			// 提取当前层级的路径
			CString subPath = path.Left(pos == -1 ? path.GetLength() : pos);

			// 检查目录是否存在
			DWORD fileAttr = GetFileAttributes(subPath);
			if (fileAttr == INVALID_FILE_ATTRIBUTES) {
				// 目录不存在，尝试创建
				if (!CreateDirectory(subPath, NULL)) {
					return false;
				} 
			} else if (!(fileAttr & FILE_ATTRIBUTE_DIRECTORY)) {
				// 路径存在但不是目录
				return false;
			}
		} while (pos != -1);

		return true;
	}

	
public:
	CString m_AutoRunDirectory;  // 系统开机自启动目录
	CString m_SelfDirectory;     // 自身目录
	CString m_SystemDirectory;   // 系统目录
	CString m_Wow64Directory;    // WOW64 目录
	CString m_SelfPath;          // 自身路径
	CString m_SelfProgramName;   // 自身程序名
	CString m_ShortcutName;      // 快捷方式名称
	CString m_ShortcutDescription; // 快捷方式描述
	CString m_FileVersion;       // 文件版本
	CString m_ProductVersion;    // 产品版本
	CString m_ProductName;       // 产品名称
	CString m_FileDescription;   // 文件描述
	LANGID  m_LanguageCode;         // 语言码

	BOOL m_IsAdmin;              // 是否是管理员
	BOOL m_Is64Bit;              // 32 位还是 64 位程序
	BOOL m_IsActiveLicense;      //是否激活
};

extern CProduct theApp;


int CProductTest();