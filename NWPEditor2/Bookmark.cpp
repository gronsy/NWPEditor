#include "stdafx.h"
#include "Bookmark.h"

Bookmark::Bookmark(std::wstring name, int bm_line) :
	bookmark_name(name), line(bm_line)
{}

int Bookmark::GetBookmarkLine()
{
	return line;
}

std::wstring Bookmark::GetBookmarkName()
{
	return bookmark_name;
}