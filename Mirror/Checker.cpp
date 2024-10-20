#include <fstream>
#include <iostream>
#include <string>


bool CheckFormat(const std::string& SourceFile)
{
	const unsigned PBMmaxsize = 65535;
	std::ifstream input(SourceFile);
	if (!input.is_open())
	{
		std::cerr << "Incorrect source file name!\n";
		return false;
	}

	std::string colsnum;
	std::string rowsnum;
	bool flag = 0;

	int checkparametrs = 0;
	int checkhelper = 0;

	for (std::string line; std::getline(input, line); ++checkhelper)
	{

		if (checkhelper == 1 && flag == 0)
		{
			for (int i = 0; i < line.size(); ++i)
			{
				if (line[i] == ' ')
				{
					flag = true;
				}
				else if (flag == 0)
				{
					colsnum += line[i];
				}
				else if (flag == 1)
				{
					rowsnum += line[i];
				}
				else
				{
					return false;
				}
			}
		}

		if (line[0] == '#')
		{
			--checkhelper;
		}
		else if (checkhelper == 0 && line == "P1")
		{
			++checkparametrs;
		}
		else if (checkhelper == 1 && stoi(colsnum) <= PBMmaxsize && stoi(rowsnum) <= PBMmaxsize)
		{
			++checkparametrs;
			break;
		}
		else
		{
			return false;
		}
	}

	if (checkparametrs == 2)
	{
		return true;
	}
	else
	{
		return false;
	}

}

bool CheckExpansion(const std::string& SourceFile)
{
	const std::string expectedExtension = ".bpm";
	auto idxLastExtOccur = std::string(SourceFile).rfind(expectedExtension);
	if (idxLastExtOccur == std::string::npos)
	{
		return false;
	}
	return (std::string(SourceFile).size() - idxLastExtOccur) == expectedExtension.size();
}
