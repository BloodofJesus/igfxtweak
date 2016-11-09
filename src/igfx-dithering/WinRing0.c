﻿#include "WinRing0.h"

FindPciDeviceByClass_t FindPciDeviceByClass = NULL;
ReadPciConfigDwordEx_t ReadPciConfigDwordEx = NULL;
ReadPciConfigWordEx_t ReadPciConfigWordEx = NULL;

static BOOL initialized = FALSE;
static HANDLE hWinRing0 = NULL;

static void WinRing0Reset(void)
{
    if (hWinRing0)
        FreeLibrary(hWinRing0);
    hWinRing0 = NULL;
    FindPciDeviceByClass = NULL;
    ReadPciConfigDwordEx = NULL;
    ReadPciConfigWordEx = NULL;
}

BOOL WinRing0Initialize(void)
{
    if (initialized)
        return TRUE;
    do
    {
#if defined(_M_X64) || defined(__amd64__)
        hWinRing0 = LoadLibrary("WinRing0x64.dll");
#else
        hWinRing0 = LoadLibrary("WinRing0.dll");
#endif
        if (!hWinRing0)
            break;
        if (!(FindPciDeviceByClass = GetProcAddress(hWinRing0, "FindPciDeviceByClass")))
            break;
        if (!(ReadPciConfigDwordEx = GetProcAddress(hWinRing0, "ReadPciConfigDwordEx")))
            break;
        if (!(ReadPciConfigWordEx = GetProcAddress(hWinRing0, "ReadPciConfigWordEx")))
            break;
        initialized = 1;
        return TRUE;
    } while (0);
    WinRing0Reset();
    return FALSE;
}

BOOL WinRing0Deinitialize(void)
{
    if (!initialized)
        return TRUE;
    WinRing0Reset();
    initialized = 0;
    return TRUE;
}