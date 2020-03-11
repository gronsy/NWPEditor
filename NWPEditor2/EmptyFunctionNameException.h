#pragma once
#include <string>
#include <exception>

public class EmptyFunctionNameException :std::exception
{
private:
	std::string error_message;
public:
	EmptyFunctionNameException(std::string message) :error_message(message) {};

	std::string GetErrorMessage() { return error_message; }
};