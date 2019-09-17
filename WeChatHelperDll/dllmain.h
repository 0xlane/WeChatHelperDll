#ifndef _DLL_MAIN_H
#define _DLL_MAIN_H

#if _MSC_VER > 1000
#pragma once
#endif

#include "resource.h"
#include "dllfunc.h"

INT_PTR Dlgproc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

#endif