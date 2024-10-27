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
	if (!input.is_open())
	{
		std::cerr << "Incorrect source file name!\n";
		return;
	}

	std::ofstream output(path2dest_, std::ios_base::app);
	if (!output.is_open())
	{
		std::cerr << "Incorrect dest file name!\n";
		return;
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
	if (!input.is_open())
	{
		std::cerr << "Incorrect source file name!\n";
		return;
	}

	std::ofstream output(path2dest_, std::ios_base::app);
	if (!output.is_open())
	{
		std::cerr << "Incorrect dest file name!\n";
		return;
	}

	int num = 0;
	// перенос данных и отзеркаливание   
	for (std::string line; std::getline(input, line); )
	{
		if (num < 2 || line[0] == '#')
		{
			++num;
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
	const unsigned PBMmaxsize = 65535;
	std::ifstream input(path2source_);
	if (!input.is_open())
	{
		std::cerr << "Incorrect source file name!\n";
		return;
	}

	std::ofstream output(path2dest_, std::ios_base::app);
	if (!output.is_open())
	{
		std::cerr << "Incorrect dest file name!\n";
		return;
	}

	std::vector <std::string> picture;
	int num = 0;
	std::string cols;
	for (std::string line; std::getline(input, line); )
	{

		if (line[0] != '#' && line != "P1" && num < 3)
		{
			for (int i = 0; i < PBMmaxsize; ++i)
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
		if (num < 2 || line[0] == '#')
		{
			output << line << std::endl;
			++num;
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
	const unsigned PBMmaxsize = 65535;
	std::ifstream input(path2source_);
	if (!input.is_open())
	{
		std::cerr << "Incorrect source file name!\n";
		return;
	}

	std::ofstream output(path2dest_, std::ios_base::app);
	if (!output.is_open())
	{
		std::cerr << "Incorrect dest file name!\n";
		return;
	}

	std::vector <std::vector<char>> Mtxofpicture;
	std::string colsize;
	std::string rowsize;
	int num = 0;
	bool flag = 0;

	for (std::string line; std::getline(input, line); )
	{
		if (line[0] != '#')
		{
			++num;
		}
		if (line[0] != '#' && line != "P1" && num < 3)
		{
			output << line << std::endl;
			for (int i = 0; i < PBMmaxsize; ++i)
			{
				if (line[i] == ' ')
				{
					flag = 1;
				}
				else if (flag == 0)
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
		else if (num < 3)
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

	// переворачиваем на 90 градусов вправо
	std::vector <std::vector<std::string>> reverseMtxofpicture;

	for (int cols = 0; cols < stoi(colsize); ++cols)
	{
		for (int rows = 0; rows < stoi(rowsize); ++rows)
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
