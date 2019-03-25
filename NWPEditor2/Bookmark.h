#pragma once
#include <string>

class Bookmark {
private:
	std::wstring bookmark_name;
	int line;
public:
	Bookmark(std::wstring name, int bm_line);
	int GetBookmarkLine();
};