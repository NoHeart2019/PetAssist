#include "stdafx.h"
#include "Procduct.h"

#pragma comment(lib, "version.lib")
//CProduct theProduct;

// 定义 ZxDebugEx 宏

CProduct theApp;

int CProductTest()
{
	CProduct product;

	// 创建自启动快捷方式
	if (product.CreateAutoRunLink())
	{
		ZxDebugEx(("Auto run shortcut created successfully.\n"));
	}
	else
	{
		ZxDebugEx(("Failed to create auto run shortcut.\n"));
	}

	// 设置开机自启动
	if (product.SetAutoStart(FALSE))
	{
		ZxDebugEx(("Set auto start successfully.\n"));
	}
	else
	{
		ZxDebugEx(("Failed to set auto start.\n"));
	}

	// 输出信息
	ZxDebugEx(("Auto Run Directory: %ls\n", product.GetAutoRunDirectory().GetBuffer()));
	ZxDebugEx(("Self Directory: %ls\n", product.GetSelfDirectory().GetBuffer()));
	ZxDebugEx(("System Directory: %ls\n", product.GetSystemDirectory().GetBuffer()));
	ZxDebugEx(("Wow64 Directory: %ls\n", product.GetWow64Directory().GetBuffer()));
	ZxDebugEx(("Is Admin: %s\n", product.IsAdmin() ? "Yes" : "No"));
	ZxDebugEx(("Is 64-bit: %s\n", product.Is64Bit() ? "Yes" : "No"));
	ZxDebugEx(("Self Path: %ls\n", product.GetSelfPath().GetBuffer()));
	ZxDebugEx(("Self Program Name: %ls\n", product.GetSelfProgramName().GetBuffer()));
	ZxDebugEx(("Shortcut Name: %ls\n", product.GetShortcutName().GetBuffer()));
	ZxDebugEx(("Shortcut Description: %ls\n", product.GetShortcutDescription().GetBuffer()));
	ZxDebugEx(("File Version: %ls\n", product.GetFileVersion().GetBuffer()));
	ZxDebugEx(("Product Version: %ls\n", product.GetProductVersion().GetBuffer()));
	ZxDebugEx(("Product Name: %ls\n", product.GetProductName().GetBuffer()));
	ZxDebugEx(("File Description: %ls\n", product.GetFileDescription().GetBuffer()));

	return 0;
}

