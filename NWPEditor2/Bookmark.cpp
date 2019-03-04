#include "stdafx.h"
#include "Bookmark.h"

int Bookmark::get_bookmark_index(std::wstring bookmark_name)
{
	int index=FAIL_CODE;

	return index;
}

int Bookmark::add_bookmark(std::wstring bookmark_name, int line)
{
	if (!bookmark_index.at(bookmark_name))
		//return FAIL_CODE;

	return bookmark_index.at(bookmark_name);
}