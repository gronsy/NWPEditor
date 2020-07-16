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
	namespace RenameSameLineTests
	{
		struct CppLanguageTestRenameSameLine : public ::testing::Test
		{
			std::string new_method_name;
			CppLanguage cpp_language;
		public:
			CppLanguageTestRenameSameLine(bool is_clang = false) :
				new_method_name("new_test_name"), cpp_language()
			{
			}
		};

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithOneNamespaceNoBrackets)
		{
			const std::string function_definition_line_cpp = "void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)";
			cpp_language.GenerateRegex(function_definition_line_cpp);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language)");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithOneNamespaceAndOpeningBracket)
		{
			const std::string function_definition_line_cpp = "void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language){";
			cpp_language.GenerateRegex(function_definition_line_cpp);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language){");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithTwoNamespacesAndNoBrackets)
		{
			const std::string function_definition_line_cpp = "void Namespace::ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)";
			cpp_language.GenerateRegex(function_definition_line_cpp);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void Namespace::ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language)");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithTwoNamespacesAndOpeningBracket)
		{
			const std::string function_definition_line_cpp = "void Namespace::ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language){";
			cpp_language.GenerateRegex(function_definition_line_cpp);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void Namespace::ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language){");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodDeclarationInOneLine)
		{
			const std::string function_definition_line_cpp = "void RenameVariableOrFunction(const CString& renameTo, int language);";
			cpp_language.GenerateRegex(function_definition_line_cpp);
			const std::string renamed_method_name =
                cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void " + new_method_name + "(const CString& renameTo, int language);");
		}
	}

	namespace RenameDifferentLinesBasedOnThePickedLineName
	{
		struct CppLanguageTestRenameDifferentLine : public ::testing::Test
		{
			std::string new_method_name;
			std::string line_to_change;
			CppLanguage cpp_language;
		public:
			CppLanguageTestRenameDifferentLine(std::string line_to_change, bool is_clang = false):
				line_to_change(line_to_change) ,new_method_name("new_method_name")
			{}
		};
	}
}