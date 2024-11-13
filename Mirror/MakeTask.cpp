#include <fstream>
#include <string>
#include <vector>
#include <memory>
#include <iostream>
#include <string>
#include "MakeTask.h"
#include "Checker.h"

class Copy : public Task
{
public:
	Copy(const char* path2source, const char* path2dest);

public:
	void Exec() override;

private:
	const char* path2source_;
	const char* path2dest_;
};

class VerticalMirror : public Task
{
public:
	VerticalMirror(const char* path2source, const char* path2dest);

public:
	void Exec() override;

private:
	const char* path2source_;
	const char* path2dest_;
};

class HorizontalMirror : public Task
{
public:
	HorizontalMirror(const char* path2source, const char* path2dest);

public:
	void Exec() override;

private:
	const char* path2source_;
	const char* path2dest_;
};

class Rotate : public Task
{
public:
	Rotate(const char* path2source, const char* path2dest);

public:
	void Exec() override;

private:
	const char* path2source_;
	const char* path2dest_;
};

class ErrorUsage : public Task
{
public:
	ErrorUsage(const char* programname);

public:
	void Exec() override;

private:
	const char* programname_;
};

class Help : public Task
{
public:
	void Exec() override;
};
struct PbmSize
{
    int width = 0;
    int heigth = 0;
};


bool open_files_cheker (const std::ifstream& input, const std::ofstream& output);

std::unique_ptr<Task> MakeTask(int argc, char** argv)
{
	// Проверить, что вообще есть что-то, кроме имени программы
	if (argc < 2 || argc > 4)
	{
		return std::make_unique<ErrorUsage>(argv[0]);
	}

	std::string firstOpt = argv[1];
	if (firstOpt[0] == '-')
	{
		if (firstOpt[1] == 'h')
		{
			return std::make_unique<Help>();
		}
		if (!CheckExpansion(argv[2]) || !CheckFormat(argv[2]))
		{
			std::cerr << "Incorrect using!\n";
			return std::make_unique<ErrorUsage>(argv[0]);
		}
		else
		{
			switch (firstOpt[1])
			{
			case 'v':
				return std::make_unique<VerticalMirror>(argv[2], argv[3]);
				break;

			case 'g':
				return std::make_unique<HorizontalMirror>(argv[2], argv[3]);
				break;

			case 'r':
				return std::make_unique<Rotate>(argv[2], argv[3]);
				break;

			case 'c':
				return std::make_unique<Copy>(argv[2], argv[3]);
				break;

			default:
				return std::make_unique<ErrorUsage>(argv[0]);
				break;
			}
		}
	}
	else
	{
		if (argc == 3)
		{
			return std::make_unique<Copy>(argv[1], argv[2]);
		}
		else
		{
			return std::make_unique<ErrorUsage>(argv[0]);
		}
	}
}

bool open_files_cheker (const std::ifstream& input, const std::ofstream& output)
{
	
	if (!input.is_open())
	{
		throw "Incorrect source file name!\n";
	}
	if (!output.is_open())
	{
		throw "Incorrect dest file name!\n";
	}

	return 1;
}

Copy::Copy(const char* path2source, const char* path2dest) :
	path2source_(path2source),
	path2dest_(path2dest)
{}

VerticalMirror::VerticalMirror(const char* path2source, const char* path2dest) :
	path2source_(path2source),
	path2dest_(path2dest)
{}

HorizontalMirror::HorizontalMirror(const char* path2source, const char* path2dest) :
	path2source_(path2source),
	path2dest_(path2dest)
{}

Rotate::Rotate(const char* path2source, const char* path2dest) :
	path2source_(path2source),
	path2dest_(path2dest)
{}

ErrorUsage::ErrorUsage(const char* programname) :
	programname_(programname)
{}

void Copy::Exec()
{
	std::ifstream input(path2source_);
	std::ofstream output(path2dest_, std::ios_base::app);
	try
	{
	if (!open_files_cheker(input, output));
	}
	catch(const std::string& error)
	{
		std::cerr << error;
	}

	// перенос данных
	for (std::string line; std::getline(input, line); )
	{
		output << line << std::endl;
	}
}

void VerticalMirror::Exec()
{
	std::ifstream input(path2source_);
	std::ofstream output(path2dest_, std::ios_base::app);
	try
	{
	if (!open_files_cheker(input, output));
	}
	catch(const std::string& error)
	{
		std::cerr << error;
	}

	int counter = 0;
	// перенос данных и отзеркаливание   
	for (std::string line; std::getline(input, line); )
	{
		if (counter < 2 || line[0] == '#')
		{
			++counter;
			output << line << std::endl;
		}
		else
		{
			std::string reverseline(line.rbegin(), line.rend());
			output << reverseline << std::endl;
		}
	}
}

void HorizontalMirror::Exec()
{
	std::ifstream input(path2source_);
	std::ofstream output(path2dest_, std::ios_base::app);
	try
	{
	if (!open_files_cheker(input, output));
	}
	catch(const std::string& error)
	{
		std::cerr << error;
	}

	std::vector <std::string> picture;
	int counter = 0;
	std::string cols;
	for (std::string line; std::getline(input, line); )
	{

		if (line[0] != '#' && line != "P1" && counter < 3)
		{
			for (int i = 0; i < PBMmaxsize_; ++i)
			{
				if (line[i] == ' ')
				{
					break;
				}
				else
				{
					cols.insert(cols.end(), line[i]);
				}
			}
		}
		if (counter < 2 || line[0] == '#')
		{
			output << line << std::endl;
			++counter;
			continue;
		}
		std::string str(line.begin(), line.end());
		// меняем строки местами и вставляем их в вектор
		picture.insert(picture.begin(), str);
	}
	// вектор передаем в файл
	for (int i = 0; i < stoi(cols); ++i)
	{
		output << picture[i] << std::endl;
	}
}

void Rotate::Exec() // картинка должна быть квадратной
{
	PbmSize size;
	std::ifstream input(path2source_);
	std::ofstream output(path2dest_, std::ios_base::app);
	try
	{
	if (!open_files_cheker(input, output));
	}
	catch(const std::string& error)
	{
		std::cerr << error;
	}
	std::vector <std::vector<char>> Mtxofpicture;
	std::string colsize;
	std::string rowsize;
	int counter = 0;
	bool flag_for_cols_and_rows = 0;
	for (std::string line; std::getline(input, line); )
	{
		if (line[0] != '#')
		{
			++counter;
		}
		if (line[0] != '#' && line != "P1" && counter < 3)
		{
			output << line << std::endl;
			for (int i = 0; i < PBMmaxsize_; ++i)
			{
				if (line[i] == ' ')
				{
					flag_for_cols_and_rows = 1;
				}
				else if (flag_for_cols_and_rows == 0)
				{
					colsize.insert(colsize.end(), line[i]);
				}
				else
				{
					if (i < line.size())
					{
						rowsize.insert(rowsize.end(), line[i]);
					}
					else
					{
						break;
					}

				}
			}
		}
		else if (counter < 3)
		{
			output << line << std::endl;
		}
		else
		{
			if (stoi(colsize) != stoi(rowsize))
			{
				std::cerr << "Incorrect picture size!\n";
				return;
			}
			for (int rows = 0; rows < stoi(rowsize); ++rows)
			{
				for (int cols = 0; cols < stoi(colsize); ++cols)
				{

					for (int i = 0; line[i] != '\n'; ++i)
					{
						Mtxofpicture[rows][cols] = line[i];
					}

				}
			}
		}
	}

    size.width = stoi(colsize);
    size.heigth = stoi(rowsize);

	// переворачиваем на 90 градусов вправо
	std::vector <std::vector<std::string>> reverseMtxofpicture;

	for (int cols = 0; cols < size.width; ++cols)
	{
		for (int rows = 0; rows < size.heigth; ++rows)
		{
			reverseMtxofpicture[rows][cols] = Mtxofpicture[cols][stoi(colsize) - rows + 1];
		}
	}

	// передаем вектор в файл
	for (int cols = 0; cols < stoi(colsize); ++cols)
	{
		for (int rows = 0; rows < stoi(rowsize); ++rows)
		{
			output << reverseMtxofpicture[rows][cols];
		}
		output << std::endl;
	}
}

void ErrorUsage::Exec()
{
	std::cout << "Usage: " << programname_ << " <SOURCE_FILENAME.pbm> <DESTINATION_FILENAME.pbm> \n"
		"<SOURCE_FILENAME.pbm> - the path to the file to copy data their \n"
		"<DESTINATION_FILENAME.pbm> - the path to the file to put data from the SOURCE_FILENAME.pbm" << std::endl;

}

void Help::Exec()
{
	std::cout << "1) Просто скопировать           - ./pbm_worker src.pbm dst.pbm" << std::endl;
	std::cout << "2) Посмотреть справку           - ./pbm_worker -h" << std::endl;
	std::cout << "3) Отобразить по вертикали      - ./pbm_worker -v src.bm dst.pbm" << std::endl;
	std::cout << "4) Отобразить по горизонтали    - ./pbm_worker -g src.bm dst.pbm" << std::endl;
	std::cout << "5) Повернуть на 90 град         - ./pbm_worker -r src.bm dst.pbm" << std::endl;
	std::cout << "./program [option] [src file] [dst file]" << std::endl;
}
