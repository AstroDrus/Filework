#include <iostream>
#include <string>
#include "MakeTask.h"

int main(int argc, char** argv)
{
try 
{
	std::unique_ptr<Task> task = MakeTask(argc, argv);
	task->Exec();
}
catch(const std::exception& error)
{
	std::cerr << error.what();
}


}
