#pragma once
#include <string>

#include "AbstractLanguage.h"
#include "EmptyFunctionNameException.h"

#define ITERATOR_CLANG_COLON_OFFSET 2
#define ITERATOR_SPACE_OFFSET 1
#define ERASE_OFFSET 1
#define STRING_BEGINNING 0

public class CppLanguage : public AbstractLanguage
{
protected:
	virtual void ExtractFunctionName(std::string line);
	void InitializeCLanguage();
	void InitializeCppLanguage();
public:
	CppLanguage(bool is_clang = false);
	virtual ~CppLanguage();
	
	virtual void GenerateRegex(std::string line);
};