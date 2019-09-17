// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "dllmain.h"

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
		DialogBox(hModule, MAKEINTRESOURCE(IDD_MAIN_DLG), NULL, (DLGPROC)&Dlgproc);
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

INT_PTR Dlgproc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_INITDIALOG:
		// 初始化map
		InitPrevCityMap();
		break;
	case WM_CLOSE:
		EndDialog(hWnd, 0);
		break;
	case WM_COMMAND:
		if (wParam == IDC_BTN_READ)
		{
			ReadData(hWnd);
		}
		if (wParam == IDC_BTN_WRITE)
		{
			if (MessageBox(NULL, _T("向微信写入这些信息后，可能会导致微信崩溃，这些修改仅本次有效，确定要写入吗？"), _T("提示"), MB_ICONWARNING | MB_OKCANCEL) != IDOK)
			{
				break;
			}
			WriteData(hWnd);
		}
		break;
	}
	return 0;
}

