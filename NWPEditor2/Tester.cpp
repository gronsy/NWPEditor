#include "stdafx.h"
#pragma once
#include "Tester.h"

void WriteToFile(std::string input)
{
	std::ofstream ofstream_file;
	ofstream_file.open("C:\\Users\\horva\\Desktop\\test.cpp");
	ofstream_file << input;
	ofstream_file.close();
}