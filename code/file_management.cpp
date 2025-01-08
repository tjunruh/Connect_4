#include "file_management.h"
#include <filesystem>

int connect_4_file_management::save_controls(std::string file_name, controls* game_controls)
{
	if (!std::filesystem::exists(controls_path))
	{
		std::filesystem::create_directory(controls_path);
	}

	int status = game_controls->save_controls(controls_path + file_name);
	return status;
}

int connect_4_file_management::load_controls(std::string file_name, controls* game_controls)
{
	if (!std::filesystem::exists(controls_path))
	{
		std::filesystem::create_directory(controls_path);
	}

	int status = game_controls->load_controls(controls_path + file_name);
	return status;
}