//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

#include "../NWPEditor2/CppLanguage.h"
#include "../NWPEditor2/CppLanguage.cpp"
#include "../NWPEditor2/AbstractLanguage.h"
#include "../NWPEditor2/AbstractLanguage.cpp"

struct CppLanguageTest : public ::testing::Test
{
	std::string new_method_name;
public:
	CppLanguage cpp_language;
	CppLanguageTest(bool is_clang = false) :
	cpp_language(is_clang), new_method_name("new_test_name")
	{
	}
};

TEST_F(CppLanguageTest, ReturnsCorrectValueAfterRenameCpp)
{
	std::string function_definition_line_cpp="void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)";
	cpp_language.GenerateRegex(function_definition_line_cpp);
	const std::string renamed_method_name=
		cpp_language.ReplaceInstances(function_definition_line_cpp, new_method_name);

	EXPECT_EQ(renamed_method_name, "void ScintillaCtrl::"+new_method_name+"(const CString& renameTo, int language)");
}