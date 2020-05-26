//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

#include "../NWPEditor2/CppLanguage.h"

struct CppLanguageTest : public ::testing::Test
{
public:
	CppLanguage cpp_language;
	CppLanguageTest(bool is_clang = false) :cpp_language(is_clang)
	{
	}
};

TEST_F(CppLanguageTest, ReturnsCorrectValueAfterRenameCpp)
{
}