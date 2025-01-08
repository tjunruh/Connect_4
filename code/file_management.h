#pragma once
#include <string>
#include <controls.h>

namespace connect_4_file_management
{
#ifdef _WIN32
	const std::string controls_path = "Connect_4_Controls\\";
#elif __linux__
	const std::string controls_path = "Connect_4_Controls/";
#endif
	int save_controls(std::string file_name, controls* game_controls);
	int load_controls(std::string file_name, controls* game_controls);
}