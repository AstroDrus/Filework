#include <iostream>
#include <string>
#include "MakeTask.h"

int main(int argc, char** argv)
{

	std::unique_ptr<Task> task = MakeTask(argc, argv);
	task->Exec();

}
