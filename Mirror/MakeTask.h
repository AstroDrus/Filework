#pragma once
#ifndef MakeTask_HPP
#define MakeTask_HPP

#include <memory>

std::unique_ptr<Task> MakeTask(int argc, char** argv);

#endif
