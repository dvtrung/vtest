#include "stdafx.h"
#include "appfunc.h"

CString GetAppDirectory()
{
	CString strFilePath;

	//Get program file path
	TCHAR lpFileName[MAX_PATH+1];
	GetModuleFileName(NULL, lpFileName, MAX_PATH);
	strFilePath = lpFileName;

	//Get program folder
	int nLastIndex = strFilePath.ReverseFind('\\');
	if (nLastIndex!=-1) {
		strFilePath = strFilePath.Left(nLastIndex);
	} else {
		strFilePath = _T("\\");
	}

	return strFilePath;
}

CString IntToString( int i )
{
	char buffer[10];
	_itoa_s( i, buffer, 10, 10 );
	return CString(buffer);
}

Gdiplus::Font* SetFontStyle( Gdiplus::Font* f, FontStyle fs )
{
	FontFamily ff; f->GetFamily(&ff);
	Gdiplus::Font* font=new Gdiplus::Font(&ff,f->GetSize(),fs,f->GetUnit());
	return font;
}

CString SecondToMinuteAndSecond( int nSecond )
{
	CString m=IntToString(nSecond/60); if (m.GetLength()==1) m=L"0"+m;
	CString s=IntToString(nSecond%60); if (s.GetLength()==1) s=L"0"+s;
	return (m+L":"+s);
}

void SplitString(CString str, TCHAR chr, CStringArray& arr)
{
	int pos=str.Find(chr,0);
	int prevPos=-1;
	while (pos!=-1)
	{
		arr.Add(str.Mid(prevPos+1,pos-prevPos-1));
		prevPos=pos;
		pos=str.Find(chr,prevPos+1);
	}
	arr.Add(str.Mid(prevPos+1,str.GetLength()-prevPos+1));
}

void CopyArray( CStringArray& arrS, CStringArray& arrD )
{
	arrD.RemoveAll();
	for (int i=0;i<arrS.GetSize();i++) arrD.Add(arrS[i]);
}

void RecursiveDelete(CString szPath)
{
	CFileFind ff;
	CString path = szPath;

	if(path.Right(1) != "\\")
		path += "\\";

	path += "*.*";

	BOOL res = ff.FindFile(path);

	while(res)
	{
		res = ff.FindNextFile();
		if (!ff.IsDots() && !ff.IsDirectory())
			DeleteFile(ff.GetFilePath());
		else if (ff.IsDirectory())
		{
			path = ff.GetFilePath();
			CString s=ff.GetFileName();
			if (ff.GetFileName()!=L"." && ff.GetFileName()!=L"..")
			{
				RecursiveDelete(path);
				RemoveDirectory(path);
			}
		}
	}
	RemoveDirectory(szPath);
}

void CopyFolder(CString strSrc, CString strDes, CString folderName)
{
	CFileFind ff;
	CString path = strSrc;

	if(path.Right(1) != "\\")
		path += "\\";
	if (folderName=="")
	{
		int i=strSrc.GetLength()-2;
		while (strSrc[i]!='\\' && strSrc[i]!='/' && i>0) i--;
		folderName=strSrc.Mid(i+1,strSrc.GetLength()-i-1);
	}

	if(strDes.Right(1) != "\\")
		strDes += "\\";

	path += "*.*";

	BOOL res = ff.FindFile(path);
	CreateDirectory(strDes + folderName, NULL);
	while(res)
	{
		res = ff.FindNextFile();
		if (!ff.IsDots() && !ff.IsDirectory())
			CopyFile(ff.GetFilePath(),strDes + folderName + L"\\" + ff.GetFileName(),FALSE);
		else if (ff.IsDirectory())
		{
			if (ff.GetFileName()!=L"." && ff.GetFileName()!=L"..")
			{
				CopyFolder(ff.GetFilePath(),strDes + folderName,L"");
			}
		}
	}
}

int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
{
	UINT  num = 0;          // number of image encoders
	UINT  size = 0;         // size of the image encoder array in bytes

	ImageCodecInfo* pImageCodecInfo = NULL;

	GetImageEncodersSize(&num, &size);
	if(size == 0)
		return -1;  // Failure

	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
	if(pImageCodecInfo == NULL)
		return -1;  // Failure

	GetImageEncoders(num, size, pImageCodecInfo);

	for(UINT j = 0; j < num; ++j)
	{
		if( wcscmp(pImageCodecInfo[j].MimeType, format) == 0 )
		{
			*pClsid = pImageCodecInfo[j].Clsid;
			free(pImageCodecInfo);
			return j;  // Success
		}    
	}

	free(pImageCodecInfo);
	return -1;  // Failure
}

CString MakeLower( CString str )
{
	str.MakeLower();
	CString str1=L"ĂÂĐÊÔƠ";
	CString str2=L"ăâdêôơ";
	for (int i=0;i<str1.GetLength();i++) str.Replace(str1[i],str2[i]);
	return str;
}

CString MakeKhongDau(CString str)
{
	CString str1=	L"áàảãạăắằẳẵặâấầẩẫậđéèẻẽẹêếềểễệíìỉĩịóòỏõọôốồổỗộơớờởỡợúùủũụưứừửữự";
	CString str2=	L"aaaaaaaaaaaaaaaaadeeeeeeeeeeeiiiiiooooooooooooooooouuuuuuuuuuu";
	str1+=			L"ÁÀẢÃẠĂẮẰẲẴẶÂẤẦẨẪẬĐÉÈẺẼẸÊẾỀỂỄỆÍÌỈĨỊÓÒỎÕỌÔỐỒỔỖỘƠỚỜỞỠỢÚÙỦŨỤƯỨỪỬỮỰ";
	str2+=			L"AAaAAAAAAAAAAAAAADEEEEEEEEEEEIIIIIOOOOOOOOOOOOOOOOOUUUUUUUUUUU";
	for (int i=0;i<str1.GetLength();i++) str.Replace(str1[i],str2[i]);
	return str;
}

CString StringFromResource(UINT nID)
{
	CString str;
	str.LoadStringW(nID);
	return str;
}