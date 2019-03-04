#pragma once
#include <map>
#include <string>

#define FAIL_CODE -1

class Bookmark {
private:
	std::map<std::wstring, int> bookmark_index;
public:
	int get_bookmark_index(std::wstring bookmark_name);
	int add_bookmark(std::wstring bookmark_name, int line);
};