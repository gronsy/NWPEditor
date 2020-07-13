//
// pch.cpp
// Include the standard header and generate the precompiled header.
//

#include "pch.h"

#include "../NWPEditor2/CppLanguage.h"
#include "../NWPEditor2/CppLanguage.cpp"
#include "../NWPEditor2/AbstractLanguage.h"
#include "../NWPEditor2/AbstractLanguage.cpp"

namespace CppUnitTests
{
	struct CppLanguageTest : public ::testing::Test
	{
		std::string new_method_name;
		CppLanguage cpp_language;
	public:
		CppLanguageTest(bool is_clang = false) :
			new_method_name("new_test_name"), cpp_language()
		{
		}
	};

	TEST_F(CppLanguageTest, RenameCppWithMethodImplementationWithOneNamespaceNoBrackets)
	{
		const std::string function_definition_line_cpp = "void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)";
		cpp_language.GenerateRegex(function_definition_line_cpp);
		const std::string renamed_method_name =
			cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

		EXPECT_EQ(renamed_method_name, "void ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language)");
	}

	TEST_F(CppLanguageTest, RenameCppWithMethodImplementationWithOneNamespaceAndOpeningBracket)
	{
		const std::string function_definition_line_cpp = "void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language){";
		cpp_language.GenerateRegex(function_definition_line_cpp);
		const std::string renamed_method_name =
			cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

		EXPECT_EQ(renamed_method_name, "void ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language){");
	}

	TEST_F(CppLanguageTest, RenameCppWithMethodImplementationWithTwoNamespacesAndNoBrackets)
	{
		const std::string function_definition_line_cpp = "void Namespace::ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)";
		cpp_language.GenerateRegex(function_definition_line_cpp);
		const std::string renamed_method_name =
			cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

		EXPECT_EQ(renamed_method_name, "void Namespace::ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language)");
	}

	TEST_F(CppLanguageTest, RenameCppWithMethodImplementationWithTwoNamespacesAndOpeningBracket)
	{
		const std::string function_definition_line_cpp = "void Namespace::ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language){";
		cpp_language.GenerateRegex(function_definition_line_cpp);
		const std::string renamed_method_name =
			cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

		EXPECT_EQ(renamed_method_name, "void Namespace::ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language){");
	}
}