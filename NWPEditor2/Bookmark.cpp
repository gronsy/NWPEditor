#include "stdafx.h"
#include "Bookmark.h"

Bookmark::Bookmark(std::wstring name, int bm_line):
	bookmark_name(name), line(bm_line)
{}


int Bookmark::get_bookmark_index(std::wstring bookmark_name)
{
	int index=FAIL_CODE;

	return index;
}