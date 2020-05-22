#pragma once
#include <string>
#include <vector>

/*
 * Application launch args
 */
using LaunchArgs = std::vector<std::string>;

/*
 * Class Application
 * Manage render thread, event thread and multithread
 */
class Application
{
public:
	void Launch(LaunchArgs args);
};