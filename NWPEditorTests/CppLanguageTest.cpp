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
				new_method_name("new_test_name")
			{
			}
		};

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithOneNamespaceNoBrackets)
		{
			const std::string function_definition_line_cpp = "void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)";
			cpp_language.GenerateRegex(function_definition_line_cpp, 25);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language)");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithOneNamespaceAndOpeningBracket)
		{
			const std::string function_definition_line_cpp = "void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language){";
			cpp_language.GenerateRegex(function_definition_line_cpp, 25);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language){");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithTwoNamespacesAndNoBrackets)
		{
			const std::string function_definition_line_cpp = "void Namespace::ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)";
			cpp_language.GenerateRegex(function_definition_line_cpp, 41);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void Namespace::ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language)");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithTwoNamespacesAndOpeningBracket)
		{
			const std::string function_definition_line_cpp = "void Namespace::ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language){";
			cpp_language.GenerateRegex(function_definition_line_cpp, 41);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void Namespace::ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language){");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodDeclarationInOneLine)
		{
			const std::string function_definition_line_cpp = "void RenameVariableOrFunction(const CString& renameTo, int language);";
			cpp_language.GenerateRegex(function_definition_line_cpp, 15);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "void " + new_method_name + "(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithTemplateMethodCallInOneLine)
		{
			const std::string function_definition_line_cpp = "RenameVariableOrFunction<int>(const CString& renameTo, int language);";
			cpp_language.GenerateRegex(function_definition_line_cpp, 7);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, new_method_name + "<int>(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithTemplateMethodCallInOneLineAndOneNamespace)
		{
			const std::string function_definition_line_cpp = "namespace::RenameVariableOrFunction<int>(const CString& renameTo, int language);";
			cpp_language.GenerateRegex(function_definition_line_cpp, 21);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "namespace::" + new_method_name + "<int>(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithTemplateMethodCallInOneLineAndTwoNamespaces)
		{
			const std::string function_definition_line_cpp = "namespace::one_more_namespace::RenameVariableOrFunction<int>(const CString& renameTo, int language);";
			cpp_language.GenerateRegex(function_definition_line_cpp, 37);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "namespace::one_more_namespace::" + new_method_name + "<int>(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithCallFromLocalClassObject)
		{
			const std::string function_definition_line_cpp = "my_class.RenameVariableOrFunction(const CString& renameTo, int language);";
			cpp_language.GenerateRegex(function_definition_line_cpp, 15);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "my_class." + new_method_name + "(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithCallFromLocalClassObjectPointer)
		{
			const std::string function_definition_line_cpp = "my_class->RenameVariableOrFunction(const CString& renameTo, int language);";
			cpp_language.GenerateRegex(function_definition_line_cpp, 15);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "my_class->" + new_method_name + "(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithCallFromLocalClassObjectTemplateMethodCall)
		{
			const std::string function_definition_line_cpp = "my_class.RenameVariableOrFunction<int>(const CString& renameTo, int language);";
			cpp_language.GenerateRegex(function_definition_line_cpp, 15);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "my_class." + new_method_name + "<int>(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithCallFromLocalClassPointerTemplateMethodCall)
		{
			const std::string function_definition_line_cpp = "my_class->RenameVariableOrFunction<int>(const CString& renameTo, int language);";
			cpp_language.GenerateRegex(function_definition_line_cpp, 15);
			const std::string renamed_method_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(function_definition_line_cpp, new_method_name);

			EXPECT_EQ(renamed_method_name, "my_class->" + new_method_name + "<int>(const CString& renameTo, int language);");
		}
	}

	namespace RenameDifferentLinesBasedOnThePickedLineName
	{
		struct CppLanguageTestRenameDifferentLine : public ::testing::Test
		{
			std::string new_method_name;
			CppLanguage cpp_language;
		public:
			CppLanguageTestRenameDifferentLine(bool is_clang = false) :
			new_method_name("new_method_name")
			{}
		};

		TEST_F(CppLanguageTestRenameDifferentLine, RenameCppMethodDeffinitionWithNameFromMethodCallWithDotOperator)
		{
			const std::string name_extraction_line = "RenameVariableOrFunction(const CString & renameTo, int language)";
			cpp_language.GenerateRegex(name_extraction_line, 13);
			
			const std::string line_to_swap_name = "my_class.RenameVariableOrFunction(const CString & renameTo, int language)";
			const std::string renamed_line_name =
				cpp_language.ReplaceCurrentLineNameIfMatched(line_to_swap_name, new_method_name);

			EXPECT_EQ(renamed_line_name, "my_class." + new_method_name + "RenameVariableOrFunction(const CString & renameTo, int language)");
		}
	}
}