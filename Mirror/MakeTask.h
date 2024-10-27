#pragma once
#ifndef MakeTask_HPP
#define MakeTask_HPP

#include <memory>

class Task
{
public:
	virtual ~Task() = default;
	virtual void Exec() = 0;
};

std::unique_ptr<Task> MakeTask(int argc, char** argv);

#endif
