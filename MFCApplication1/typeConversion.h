#pragma once

#ifndef TYPE_CONV
#define TYPE_CONV
#endif

#include <afxwin.h>
#include <afxext.h>
#include <afxdisp.h>
#include <string>
#include <sstream>

typedef char* CP;
typedef CString CS;
typedef BSTR BS;
typedef std::string STR;
typedef std::wstring WS;
typedef std::stringstream SS;

// Reference
// BSTR <-> STR
// https://stackoverflow.com/questions/6284524/bstr-to-stdstring-stdwstring-and-vice-versa

CS CP_CS(CP str) { return STR_CS(STR(str)); }
BS CP_BS(CP str) { return STR_BS(STR(str)); }
STR CS_STR(CS cs) { return STR(CT2CA(cs)); }
CS STR_CS(STR str) { return (LPCWSTR)STR_BS(str); }
STR BS_STR(BS bs) { return CS_STR((LPCWSTR)bs); }

BSTR STR_BS(const std::string& str)
{
    int wslen = ::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
        str.data(), str.length(),
        NULL, 0);

    BSTR wsdata = ::SysAllocStringLen(NULL, wslen);
    ::MultiByteToWideChar(CP_ACP, 0 /* no flags */,
        str.data(), str.length(),
        wsdata, wslen);
    return wsdata;
}

WS BS_WS(BS bs) { return WS(bs, SysStringLen(bs)); }
BSTR WS_BS(WS ws) { return SysAllocStringLen(ws.data(), ws.size()); }