
/*
	��Ʒ�� 
	��������ʼ���³�Ա
	ϵͳ��ʼĿ¼���Ƿ��ǹ���Ա�� 32λ����64λ����
	����·��������Ŀ¼����������,��ݷ�ʽ���ƣ���ݷ�ʽ������

*/
#include <atlbase.h>
#include <atlconv.h>
#include <windows.h>
#include <shlobj.h>
#include <objbase.h>


class CProduct
{
public:
	// ���캯������ʼ����Ա����
	CProduct()
	{
		// ��ʼ����Ա����
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

		// ��ȡ����������Ŀ¼
		wchar_t startupPath[MAX_PATH];
		if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_STARTUP, NULL, 0, startupPath)))
		{
			m_AutoRunDirectory = startupPath;
		}
		
		// ��ȡ��ǰ���̵�����·��
		wchar_t szPath[MAX_PATH];
		if (GetModuleFileNameW(NULL, szPath, MAX_PATH))
		{
			m_SelfPath = szPath;
			// ��ȡ����Ŀ¼
			int pos = m_SelfPath.ReverseFind(L'\\');
			if (pos != -1)
			{
				m_SelfDirectory = m_SelfPath.Left(pos);
				m_SelfProgramName = m_SelfPath.Mid(pos + 1);
				if (!m_SelfDirectory.IsEmpty())
					::SetCurrentDirectory(m_SelfDirectory);
			}
		} 
		
		// ��ȡϵͳĿ¼������::
		wchar_t systemPath[MAX_PATH];
		if (::GetSystemDirectoryW(systemPath, MAX_PATH))
		{
			m_SystemDirectory = systemPath;
		}

		// ��ȡ WOW64 Ŀ¼
		if (IsWow64Process(GetCurrentProcess(), &m_Is64Bit) && m_Is64Bit)
		{
			wchar_t wow64Path[MAX_PATH];
			if (GetSystemWow64DirectoryW(wow64Path, MAX_PATH))
			{
				m_Wow64Directory = wow64Path;
			}
		}

		// ����Ƿ��ǹ���ԱȨ��
		m_IsAdmin = IsAdminInternal();

		// ����� 32 λ���� 64 λ����
		m_Is64Bit = Is64BitProcess();

		// ��ȡ�ļ��汾����Ʒ�汾����Ʒ�����Լ��ļ�����
		GetVersionInfo();
	}

	// ����������Ŀ¼�� Set �� Get ����
	void SetAutoRunDirectory(const CString& value)
	{
		m_AutoRunDirectory = value;
	}
	
	CString& GetAutoRunDirectory()
	{
		return m_AutoRunDirectory;
	}

	// ����Ŀ¼�� Set �� Get ����
	void SetSelfDirectory(const CString& value)
	{
		m_SelfDirectory = value;
	}
	CString& GetSelfDirectory()
	{
		return m_SelfDirectory;
	}

	// ϵͳĿ¼�� Get ����
	CString& GetSystemDirectory()
	{
		return m_SystemDirectory;
	}

	// WOW64 Ŀ¼�� Get ����
	CString& GetWow64Directory()
	{
		return m_Wow64Directory;
	}

	// �Ƿ��ǹ���Ա�� Set ������ֱ���Գ�Ա�������Ļ�ȡ����
	void SetIsAdmin(BOOL value)
	{
		m_IsAdmin = value;
	}
	BOOL IsAdmin() const
	{
		return m_IsAdmin;
	}

	// 32 λ���� 64 λ����� Set ������ֱ���Գ�Ա�������Ļ�ȡ����
	void SetIs64Bit(BOOL value)
	{
		m_Is64Bit = value;
	}
	BOOL Is64Bit() const
	{
		return m_Is64Bit;
	}

	// ����·���� Set �� Get ����
	void SetSelfPath(const CString& value)
	{
		m_SelfPath = value;
	}
	
	CString& GetSelfPath()
	{
		return m_SelfPath;
	}

	// ����������� Get ����
	CString& GetSelfProgramName()
	{
		return m_SelfProgramName;
	}

	// ��ݷ�ʽ���Ƶ� Get ����
	CString& GetShortcutName()
	{
		return m_ShortcutName;
	}

	// ��ݷ�ʽ������ Get ����
	CString& GetShortcutDescription()
	{
		return m_ShortcutDescription;
	}

	// �ļ��汾�� Get ����
	CString& GetFileVersion()
	{
		return m_FileVersion;
	}

	// ��Ʒ�汾�� Get ����
	CString& GetProductVersion()
	{
		return m_ProductVersion;
	}

	// ��Ʒ���Ƶ� Get ����
	CString& GetProductName()
	{
		return m_ProductName;
	}

	// �ļ������� Get ����
	CString& GetFileDescription()
	{
		return m_FileDescription;
	}
	// ��ȡ������
	LANGID GetLanguageCode() const
	{
		return m_LanguageCode;
	}

	LANGID SetLanguageCode() const
	{
		return m_LanguageCode;
	}

	// ������ݷ�ʽ�ķ������� autoRunDirectory ��Ϊ SaveDirectory
	BOOL CreateShortcut(const CString& shortcutName, const CString& shortcutDescription, const CString& SaveDirectory)
	{
		HRESULT hres;
		IShellLinkW* psl;

		// ��ʼ�� COM ��
		hres = CoInitialize(NULL);
		if (FAILED(hres))
		{
			return FALSE;
		}

		// ���� IShellLink ����
		hres = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLinkW, (LPVOID*)&psl);
		if (SUCCEEDED(hres))
		{
			IPersistFile* ppf;

			// ���ÿ�ݷ�ʽ��Ŀ��·��
			psl->SetPath(m_SelfPath);

			// ���ÿ�ݷ�ʽ������
			psl->SetDescription(shortcutDescription);

			// ��ȡ IPersistFile �ӿ�
			hres = psl->QueryInterface(IID_IPersistFile, (LPVOID*)&ppf);

			if (SUCCEEDED(hres))
			{
				CString shortcutPath = SaveDirectory + L"\\" + shortcutName + L".lnk";

				// �����ݷ�ʽ
				hres = ppf->Save(shortcutPath, TRUE);

				// �ͷ� IPersistFile �ӿ�
				ppf->Release();
			}

			// �ͷ� IShellLink ����
			psl->Release();
		}

		// �ͷ� COM ��
		CoUninitialize();

		if (SUCCEEDED(hres))
		{
			m_ShortcutName = shortcutName;
			m_ShortcutDescription = shortcutDescription;
			return TRUE;
		}

		return FALSE;
	}

	// ������������ݷ�ʽ����
	BOOL CreateAutoRunLink()
	{
		CString File;
		File = m_AutoRunDirectory + L"\\" + m_SelfProgramName +L".lnk";
		DWORD Attributes = GetFileAttributes(File);
		if (Attributes != INVALID_FILE_ATTRIBUTES)
			return TRUE;
				
		return CreateShortcut(m_SelfProgramName, m_FileDescription, m_AutoRunDirectory);
	}

	// ��������������
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
	// ��װ����Ƿ��ǹ���ԱȨ�޵ĺ���
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

	// ��װ�ж��� 32 λ���� 64 λ����ĺ���
	BOOL Is64BitProcess()
	{
		BOOL bIsWow64 = FALSE;
		IsWow64Process(GetCurrentProcess(), &bIsWow64);
		return !bIsWow64;
	}

	// ��ȡ�ļ��汾����Ʒ�汾����Ʒ�����Լ��ļ�����
	// ����ʹ��ÿ�����Ժʹ���ҳ�������ȡ��Ʒ���ƺ��ļ�����������ʹ�����û�Ĭ�� UI ����ƥ�����ϣ�
	
	void GetVersionInfo()
	{
		// ��ȡ�ļ��汾��Ϣ�Ĵ�С
		DWORD dwHandle;
		DWORD dwLen = GetFileVersionInfoSizeW(m_SelfPath, &dwHandle);
		if (dwLen == 0)
		{
			// �ļ��汾��Ϣ��С��ȡʧ�ܣ�ֱ�ӷ���
			return;
		}

		// �����ڴ����ڴ洢�ļ��汾��Ϣ
		CHeapPtr<BYTE> buffer;
		if (!buffer.Allocate(dwLen))
		{
			// �ڴ����ʧ�ܣ�ֱ�ӷ���
			return;
		}

		// ��ȡ�ļ��汾��Ϣ
		if (!GetFileVersionInfoW(m_SelfPath, dwHandle, dwLen, buffer))
		{
			// �ļ��汾��Ϣ��ȡʧ�ܣ�ֱ�ӷ���
			return;
		}

		// ��ȡ�̶��ļ���Ϣ
		VS_FIXEDFILEINFO* pFixedFileInfo;
		UINT uLen;
		if (!VerQueryValueW(buffer, L"\\", (LPVOID*)&pFixedFileInfo, &uLen))
		{
			// �̶��ļ���Ϣ��ȡʧ�ܣ�ֱ�ӷ���
			return;
		}

		// �����ļ��汾�ַ���
		m_FileVersion.Format(L"%d.%d.%d.%d",
			HIWORD(pFixedFileInfo->dwFileVersionMS),
			LOWORD(pFixedFileInfo->dwFileVersionMS),
			HIWORD(pFixedFileInfo->dwFileVersionLS),
			LOWORD(pFixedFileInfo->dwFileVersionLS));

		// ������Ʒ�汾�ַ���
		m_ProductVersion.Format(L"%d.%d.%d.%d",
			HIWORD(pFixedFileInfo->dwProductVersionMS),
			LOWORD(pFixedFileInfo->dwProductVersionMS),
			HIWORD(pFixedFileInfo->dwProductVersionLS),
			LOWORD(pFixedFileInfo->dwProductVersionLS));

		// ��ȡ���Ժʹ���ҳ��Ϣ
		LPDWORD pLangAndCodePage;
		if (VerQueryValueW(buffer, L"\\VarFileInfo\\Translation", (LPVOID*)&pLangAndCodePage, &uLen))
		{
			UINT count = uLen / sizeof(DWORD);
			if (count == 0)
			{
				// ���Ժʹ���ҳ��Ϣ����Ϊ�գ�ֱ�ӷ���
				return;
			}

			// ��ʼ��ƥ������Դ���Ϊ����ĵ�һ��Ԫ��
			DWORD matchedLangCode = pLangAndCodePage[0];

			// �������飬�������û�Ĭ��������ƥ���Ԫ��
			for (UINT i = 0; i < count; ++i)
			{
				WORD langCode = MAKEWORD(LOBYTE(pLangAndCodePage[i]), HIBYTE(HIWORD(pLangAndCodePage[i])));
				if (langCode == LOWORD(m_LanguageCode))
				{
					// �ҵ�ƥ��������룬���� matchedLangCode ������ѭ��
					matchedLangCode = pLangAndCodePage[i];
					break;
				}
			}

			// ��ȡ��Ʒ���ƺ��ļ�����
			wchar_t subBlock[256];
			wchar_t* pProductName = nullptr;
			wchar_t* pFileDescription = nullptr;

			// ������Ʒ���Ƶ��ӿ�·������ȡ��Ʒ����
			swprintf_s(subBlock, L"\\StringFileInfo\\%04x%04x\\ProductName", LOWORD(matchedLangCode), HIWORD(matchedLangCode));
			VerQueryValueW(buffer, subBlock, (LPVOID*)&pProductName, &uLen);

			// �����ļ��������ӿ�·������ȡ�ļ�����
			swprintf_s(subBlock, L"\\StringFileInfo\\%04x%04x\\FileDescription", LOWORD(matchedLangCode), HIWORD(matchedLangCode));
			VerQueryValueW(buffer, subBlock, (LPVOID*)&pFileDescription, &uLen);

			// ����ɹ���ȡ����Ʒ���ƣ����丳ֵ����Ա����
			if (pProductName)
			{
				m_ProductName = pProductName;
			}
			// ����ɹ���ȡ���ļ����������丳ֵ����Ա����
			if (pFileDescription)
			{
				m_FileDescription = pFileDescription;
			}
		}
	}

	// �������ݹ鴴���༶Ŀ¼������ ATL �� CString��
	bool CreateWorkDirectory(const CString& path) {
		int pos = 0;
		do {
			// �ҵ���һ��Ŀ¼�ָ���
			pos = path.Find(L"\\", pos + 1);

			// ��ȡ��ǰ�㼶��·��
			CString subPath = path.Left(pos == -1 ? path.GetLength() : pos);

			// ���Ŀ¼�Ƿ����
			DWORD fileAttr = GetFileAttributes(subPath);
			if (fileAttr == INVALID_FILE_ATTRIBUTES) {
				// Ŀ¼�����ڣ����Դ���
				if (!CreateDirectory(subPath, NULL)) {
					return false;
				} 
			} else if (!(fileAttr & FILE_ATTRIBUTE_DIRECTORY)) {
				// ·�����ڵ�����Ŀ¼
				return false;
			}
		} while (pos != -1);

		return true;
	}

	
public:
	CString m_AutoRunDirectory;  // ϵͳ����������Ŀ¼
	CString m_SelfDirectory;     // ����Ŀ¼
	CString m_SystemDirectory;   // ϵͳĿ¼
	CString m_Wow64Directory;    // WOW64 Ŀ¼
	CString m_SelfPath;          // ����·��
	CString m_SelfProgramName;   // ���������
	CString m_ShortcutName;      // ��ݷ�ʽ����
	CString m_ShortcutDescription; // ��ݷ�ʽ����
	CString m_FileVersion;       // �ļ��汾
	CString m_ProductVersion;    // ��Ʒ�汾
	CString m_ProductName;       // ��Ʒ����
	CString m_FileDescription;   // �ļ�����
	LANGID  m_LanguageCode;         // ������

	BOOL m_IsAdmin;              // �Ƿ��ǹ���Ա
	BOOL m_Is64Bit;              // 32 λ���� 64 λ����
	BOOL m_IsActiveLicense;      //�Ƿ񼤻�
};

extern CProduct theApp;


int CProductTest();