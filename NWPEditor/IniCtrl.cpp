#include "ChildView.h"
#include "stdafx.h"
#include "IniCtrl.h"

IniCtrl::IniCtrl()
{
	buffer = nullptr;
}

IniCtrl::~IniCtrl()
{
	delete[] buffer;
	buffer = nullptr;
}

void IniCtrl::SendIni(int lang, bool clang) 
{
	switch (lang) {
	case SCLEX_CPP:
		if (clang) {
			keywords = c_keywords;
			key = _T("c");
			break;
		}
		key = _T("cpp");
		keywords = cpp_keywords;
		break;
	case SCLEX_PYTHON:
		key = _T("python");
		keywords = py_keywords;
		break;
	default:
		keywords = NULL;
	}
	
	LoadKeywords();
	LoadColours();
}

void IniCtrl::LoadColours()
{
}

void IniCtrl::LoadKeywords()
{
	int buffer_len = _tcslen(keywords) * 2;
	if (PathFileExists(_T("config/keywords.ini")))
		WriteKeywords();

	if (buffer != nullptr) delete[] buffer;

	buffer = new TCHAR[buffer_len];
	GetPrivateProfileString(_T("keywords"), key, keywords, buffer, buffer_len, _T("config/keywords.ini"));

	delete[] buffer; buffer = nullptr;
}

void IniCtrl::WriteKeywords() 
{
	WritePrivateProfileString(_T("keywords"), _T("cpp"), cpp_keywords, _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("c"), c_keywords, _T("config/keywords.ini"));
	WritePrivateProfileString(_T("keywords"), _T("python"), py_keywords, _T("config/keywords.ini"));
}

void IniCtrl::WriteColours() 
{

}

TCHAR* IniCtrl::GetKeywords() { return keywords; }