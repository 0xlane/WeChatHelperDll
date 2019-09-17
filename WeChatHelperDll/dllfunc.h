#ifndef _DLL_FUNC_H

#if _MSC_VER > 1000
#pragma once
#endif

#include "pch.h"
#include "resource.h"
#include "citymap.h"

//#ifndef IMPORT_DLL
//#define IMPORT_DLL extern "C" _declspec(dllimport)         // ��������ⲿʹ��
//#endif

/* v: 2.6.8.51 */
//nickname: WeChatWin.dll + 0126D91C(�ַ���)
//wxid : WeChatWin.dll + 0126D8A4(ָ����ַ���)
//email : WeChatWin.dll + 0126D938(ָ��)
//phone : WeChatWin.dll + 0126D950(�ַ���)
//device : WeChatWin.dll + 0126DD48(�ַ���)
//prevent�� WeChatWin.dll + 0126DA08(�ַ���)
//city : WeChatWin.dll + 0126DA20(�ַ���)
//logo : WeChatWin.dll + 0126DBE4(�ַ���)

/* v: 2.6.8.65 */
//nickname: WeChatWin.dll + 0126D8FC(�ַ���)
//wxid : WeChatWin.dll + 0126D884(ָ����ַ���)
//email : WeChatWin.dll + 0126D918(ָ��)
//phone : WeChatWin.dll + 0126D930(�ַ���)
//country : WeChatWin.dll + 0126DAD8(�ַ���)
//device : WeChatWin.dll + 0126DD38(�ַ���)
//prevent�� WeChatWin.dll + 0126D9E8(�ַ���)
//city : WeChatWin.dll + 0126DA00(�ַ���)
//logo : WeChatWin.dll + 0126DBC4(�ַ���)

static const DWORD dwOffsetOfNick = 0x0126D8FC;
static const DWORD dwOffsetOfWxid = 0x0126D884;
static const DWORD dwOffsetOfLogo = 0x0126DBC4;
static const DWORD dwOffsetOfEmail = 0x0126D918;
static const DWORD dwOffsetOfPhone = 0x0126D930;
static const DWORD dwOffsetOfCity = 0x0126DA00;
static const DWORD dwOffsetOfPrev = 0x0126D9E8;
static const DWORD dwOffsetOfCountry = 0x0126DAD8;
static const DWORD dwOffsetOfDev = 0x0126DD38;


VOID ReadData(HWND hWnd);
VOID WriteData(HWND hWnd);
wchar_t* UTF8ToUnicode(const char* str);

#endif