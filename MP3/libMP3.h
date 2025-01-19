#pragma once
#include <fstream>

namespace MP3
{
//give to the main.cpp the head of the MP3_file
std::string GetHeading( std::ifstream& source_file);
} // namespace MP3
