#include <memory>
#include <iostream>
#include <string>

std::unique_ptr<Task> MakeTask(int argc, char** argv)
{
	// Проверить, что вообще есть что-то, кроме имени программы
	if (argc <= 2 || argc > 4)
	{
		return std::make_unique<ErrorUsage>(argv[0]);
	}

	std::string firstOpt = argv[1];
	if (firstOpt[0] == '-')
	{
		if (!CheckExpansion(argv[2]) || !CheckFormat(argv[2]))
		{
			std::cerr << "Incorrect using!\n";
			return std::make_unique<ErrorUsage>(argv[0]);
		}

		if (firstOpt[1] == 'h')
		{
			return std::make_unique<Help>();
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
