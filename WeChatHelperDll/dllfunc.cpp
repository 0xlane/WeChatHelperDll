#include "dllfunc.h"

VOID ReadData(HWND hWnd)
{
	char szWxid[0x100] = { 0 }, szPicPath[0x100] = { 0 }, szPhone[0x100] = { 0 }, szCity[0x100] = { 0 }, szPrev[0x100] = { 0 }, szCountry[0x100] = { 0 }, szEmail[0x100] = { 0 }, szDev[0x100] = { 0 };
	wchar_t szNickName[0x100] = { 0 };
	const TCHAR* lpszWxDllName = _T("WeChatWin.dll");

	//// �õ�WeChatWin.dll��ַ
	//HMODULE hWx = GetModuleHandle(lpszWxDllName);
	//if (!hWx)
	//{
	//	MessageBox(hWnd, _T("����WeChatWin.dll���ʧ�ܣ�"), _T("����"), MB_OK);
	//	return;
	//}

	//DWORD dwWxBase = (DWORD)hWx;

	//// ͨ��ƫ��������
	//sprintf_s(szWxid, "%s", (dwWxBase + dwOffsetOfWxid));
	//sprintf_s(szNickName, "%s", dwWxBase + dwOffsetOfNick);
	//sprintf_s(szPicPath, "%s", *(LPVOID*)(dwWxBase + dwOffsetOfLogo));
	
	// �õ�����ID
	HANDLE hProcess = GetCurrentProcess();
	if (!hProcess)
	{
		MessageBox(hWnd, _T("�޷����̾����"), _T("����"), MB_OK);
		return;
	}
	// �õ�ģ���ַ
	HMODULE hWx = GetModuleHandle(lpszWxDllName);
	if (!hWx)
	{
		MessageBox(hWnd, _T("�޷���ȡWeChatWin.dllģ�飡"), _T("����"), MB_OK);
		return;
	}
	DWORD dwWxBase = (DWORD)hWx;
	// ��ȡ�ڴ� wxid��Ҫ�ж��Ƿ���ָ��
	ReadProcessMemory(hProcess, (LPCVOID)(*(DWORD*)(dwWxBase + dwOffsetOfWxid)), szWxid, sizeof(szWxid), NULL);
	if (0 == szWxid[0])
		ReadProcessMemory(hProcess, (LPCVOID)(dwWxBase + dwOffsetOfWxid), szWxid, sizeof(szWxid), NULL);
	ReadProcessMemory(hProcess, (LPCVOID)(*((DWORD *)(dwWxBase + dwOffsetOfLogo))), szPicPath, sizeof(szPicPath), NULL);
	ReadProcessMemory(hProcess, (LPCVOID)(dwWxBase + dwOffsetOfCity), szCity, sizeof(szCity), NULL);
	ReadProcessMemory(hProcess, (LPCVOID)(dwWxBase + dwOffsetOfDev), szDev, sizeof(szDev), NULL);
	ReadProcessMemory(hProcess, (LPCVOID)(dwWxBase + dwOffsetOfPrev), szPrev, sizeof(szPrev), NULL);
	ReadProcessMemory(hProcess, (LPCVOID)(dwWxBase + dwOffsetOfCountry), szCountry, sizeof(szCountry), NULL);
	ReadProcessMemory(hProcess, (LPCVOID)(dwWxBase + dwOffsetOfPhone), szPhone, sizeof(szPhone), NULL);
	ReadProcessMemory(hProcess, (LPCVOID)(*(DWORD *)(dwWxBase + dwOffsetOfEmail)), szEmail, sizeof(szEmail), NULL);

	{
		char szBuff[0x100] = { 0 };
		ReadProcessMemory(hProcess, (LPCVOID)(dwWxBase + dwOffsetOfNick), szBuff, sizeof(szBuff), NULL);
		wcscpy_s(szNickName, wcslen(UTF8ToUnicode(szBuff)) + 1, UTF8ToUnicode(szBuff));
	}

	// ����������Ϣ
	char szPrevCity[0x200] = { 0 };
	std::map<const char*, const char*, ptrCmp>::iterator itPrev;
	std::map<const char*, const char*, ptrCmp>::iterator itCity;
	std::map<const char*, const char*, ptrCmp>::iterator itCountry;
	itPrev = mPrevMap.find(szPrev);
	itCity = mCityMap.find(szCity);
	itCountry = mCountryDomainMap.find(szCountry);
	if (itPrev != mPrevMap.end() && itCity != mCityMap.end())
	{
		sprintf_s(szPrevCity, "%s %s", itPrev->second, itCity->second);
	}
	else
	{
		sprintf_s(szPrevCity, "%s", itCountry->second);
	}
	//sprintf_s(szPrevCity, "%s %s", mPrevMap["Hebei"], mCityMap["Shijiazhuang"]);

	SendDlgItemMessageW(hWnd, IDC_EDIT_NICK, WM_SETTEXT, 0, (LPARAM)szNickName);
	SendDlgItemMessage(hWnd, IDC_EDIT_IMAGE, WM_SETTEXT, 0, (LPARAM)szPicPath);
	SendDlgItemMessage(hWnd, IDC_EDIT_WXID, WM_SETTEXT, 0, (LPARAM)szWxid);
	SendDlgItemMessage(hWnd, IDC_EDIT_PHONE, WM_SETTEXT, 0, (LPARAM)szPhone);
	SendDlgItemMessage(hWnd, IDC_EDIT_DEVICE, WM_SETTEXT, 0, (LPARAM)szDev);
	SendDlgItemMessage(hWnd, IDC_EDIT_EMAIL, WM_SETTEXT, 0, (LPARAM)szEmail);
	SendDlgItemMessage(hWnd, IDC_EDIT_CITY, WM_SETTEXT, 0, (LPARAM)szPrevCity);
}

VOID WriteData(HWND hWnd)
{
	char szWxid[0x100] = { 0 }, szNickName[0x100] = { 0 }, szPicPath[0x100] = { 0 };
	// �õ�����ID
	HANDLE hProcess = GetCurrentProcess();
	if (!hProcess)
	{
		MessageBox(hWnd, _T("�޷����̾����"), _T("����"), MB_OK);
		return;
	}
	// �õ�WeChatWin.dll��ַ
	const TCHAR* lpszWxDllName = _T("WeChatWin.dll");
	HMODULE hWx = GetModuleHandle(lpszWxDllName);
	if (!hWx)
	{
		MessageBox(hWnd, _T("����WeChatWin.dll���ʧ�ܣ�"), _T("����"), MB_OK);
		return;
	}

	DWORD dwWxBase = (DWORD)hWx;

	// ͨ��ƫ��д��ַ wxid��Ҫ�ж��Ƿ���ָ��
	ReadProcessMemory(hProcess, (LPCVOID)(*(DWORD*)(dwWxBase + dwOffsetOfWxid)), szWxid, sizeof(szWxid), NULL);
	if (0 == szWxid[0])
	{
		memset(szWxid, 0, sizeof(szWxid));
		SendDlgItemMessage(hWnd, IDC_EDIT_WXID, WM_GETTEXT, sizeof(szWxid), (LPARAM)szWxid);
		WriteProcessMemory(hProcess, (LPVOID)(dwWxBase + dwOffsetOfWxid), szWxid, sizeof(szWxid), NULL);
	}
	else
	{
		memset(szWxid, 0, sizeof(szWxid));
		SendDlgItemMessage(hWnd, IDC_EDIT_WXID, WM_GETTEXT, sizeof(szWxid), (LPARAM)szWxid);
		WriteProcessMemory(hProcess, (LPVOID)(*(DWORD*)(dwWxBase + dwOffsetOfWxid)), szWxid, sizeof(szWxid), NULL);
	}
	SendDlgItemMessage(hWnd, IDC_EDIT_NICK, WM_GETTEXT, sizeof(szNickName), (LPARAM)szNickName);
	WriteProcessMemory(hProcess, (LPVOID)(dwWxBase + dwOffsetOfNick), szNickName, sizeof(szNickName), NULL);
	SendDlgItemMessage(hWnd, IDC_EDIT_IMAGE, WM_GETTEXT, sizeof(szPicPath), (LPARAM)szPicPath); 
	WriteProcessMemory(hProcess, (LPVOID)(*(DWORD*)(dwWxBase + dwOffsetOfLogo)), szPicPath, sizeof(szPicPath), NULL);

	MessageBox(NULL, _T("д��ɹ���"), _T("���"), MB_OK);
}

//************************************************************
// ��������: UTF8ToUnicode
// ����˵��: ��UTF8����תΪUnicode(΢��Ĭ�ϱ���ΪUTF8)
// ��    ��: str ��Ҫת�����ַ���
// �� �� ֵ: wchar_t ���ص��ַ��� 
//************************************************************
wchar_t* UTF8ToUnicode(const char* str)
{
	int    textlen = 0;
	wchar_t* result;
	textlen = MultiByteToWideChar(CP_UTF8, 0, str, -1, NULL, 0);
	result = (wchar_t*)malloc((textlen + 1) * sizeof(wchar_t));
	memset(result, 0, (textlen + 1) * sizeof(wchar_t));
	MultiByteToWideChar(CP_UTF8, 0, str, -1, (LPWSTR)result, textlen);
	return    result;
}