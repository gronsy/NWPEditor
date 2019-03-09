#pragma once
#include <string>

#define FAIL_CODE -1

class Bookmark {
private:
	std::wstring bookmark_name;
	int line;
public:
	Bookmark(std::wstring name, int bm_line);
	int get_bookmark_index(std::wstring bookmark_name);
};