#include "Gdiplus.h"
using namespace Gdiplus;

CString GetAppDirectory();
CString IntToString(int i);
Gdiplus::Font* SetFontStyle(Gdiplus::Font* f, FontStyle fs);
CString SecondToMinuteAndSecond(int nSecond);
void SplitString(CString str, TCHAR chr, CStringArray& arr);
void CopyArray(CStringArray& arrS, CStringArray& arrD);
void RecursiveDelete(CString szPath);
int GetEncoderClsid(const WCHAR* format, CLSID* pClsid);
void CopyFolder(CString strSrc, CString strDes, CString folderName);
CString MakeLower(CString str);
CString MakeKhongDau(CString str);
CString StringFromResource(UINT nID);