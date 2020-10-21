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

			std::string ExecuteTest(const std::string& name_extract_line, const int cursor_index)
			{
				cpp_language.GenerateRegex(name_extract_line, cursor_index);
				const std::string new_name_line =
					cpp_language.ReplaceCurrentLineNameIfMatched(name_extract_line, new_method_name);

				return new_name_line;
			}
		};

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithOneNamespaceNoBrackets)
		{
			const std::string new_name_line = ExecuteTest("void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)", 25);

			EXPECT_EQ(new_name_line, "void ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language)");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithOneNamespaceAndOpeningBracket)
		{
			const std::string new_name_line = ExecuteTest("void ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language){", 25);

			EXPECT_EQ(new_name_line, "void ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language){");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithTwoNamespacesAndNoBrackets)
		{
			const std::string new_name_line = ExecuteTest("void Namespace::ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language)", 41);

			EXPECT_EQ(new_name_line, "void Namespace::ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language)");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodImplementationWithTwoNamespacesAndOpeningBracket)
		{
			const std::string new_line_name = ExecuteTest("void Namespace::ScintillaCtrl::RenameVariableOrFunction(const CString& renameTo, int language){", 41);

			EXPECT_EQ(new_line_name, "void Namespace::ScintillaCtrl::" + new_method_name + "(const CString& renameTo, int language){");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithMethodDeclarationInOneLine)
		{
			std::string new_line_name = ExecuteTest("void RenameVariableOrFunction(const CString& renameTo, int language);", 15);

			EXPECT_EQ(new_line_name, "void " + new_method_name + "(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithTemplateMethodCallInOneLine)
		{
			const std::string new_line_name = ExecuteTest("RenameVariableOrFunction<int>(const CString& renameTo, int language);", 7);

			EXPECT_EQ(new_line_name, new_method_name + "<int>(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithTemplateMethodCallInOneLineAndOneNamespace)
		{
			const std::string new_line_name = ExecuteTest("namespace::RenameVariableOrFunction<int>(const CString& renameTo, int language);", 21);

			EXPECT_EQ(new_line_name, "namespace::" + new_method_name + "<int>(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithTemplateMethodCallInOneLineAndTwoNamespaces)
		{
			const std::string new_line_name = ExecuteTest("namespace::one_more_namespace::RenameVariableOrFunction<int>(const CString& renameTo, int language);", 37);

			EXPECT_EQ(new_line_name, "namespace::one_more_namespace::" + new_method_name + "<int>(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithCallFromLocalClassObject)
		{
			const std::string new_line_name = ExecuteTest("my_class.RenameVariableOrFunction(const CString& renameTo, int language);", 15);

			EXPECT_EQ(new_line_name, "my_class." + new_method_name + "(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithCallFromLocalClassObjectPointer)
		{
			const std::string new_line_name = ExecuteTest("my_class->RenameVariableOrFunction(const CString& renameTo, int language);", 15);

			EXPECT_EQ(new_line_name, "my_class->" + new_method_name + "(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithCallFromLocalClassObjectTemplateMethodCall)
		{
			const std::string new_line_name = ExecuteTest("my_class.RenameVariableOrFunction<int>(const CString& renameTo, int language);", 15);

			EXPECT_EQ(new_line_name, "my_class." + new_method_name + "<int>(const CString& renameTo, int language);");
		}

		TEST_F(CppLanguageTestRenameSameLine, RenameCppWithCallFromLocalClassPointerTemplateMethodCall)
		{
			const std::string new_line_name = ExecuteTest("my_class->RenameVariableOrFunction<int>(const CString& renameTo, int language);", 15);

			EXPECT_EQ(new_line_name, "my_class->" + new_method_name + "<int>(const CString& renameTo, int language);");
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