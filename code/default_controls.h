#pragma once
#include <string>
#include <ascii_io.h>
#include <format_tools.h>

struct control_mapping
{
	std::string name = "";
	int key = ascii_io::undefined;
};

const std::vector<control_mapping> default_control_names =
{
	{"up", ascii_io::up},
	{"down", ascii_io::down},
	{"right", ascii_io::right},
	{"left", ascii_io::left},
	{"select", ascii_io::enter},
	{"quit", ascii_io::q},
	{"delete", ascii_io::DEL},
	{"help", ascii_io::h},
	{"enable line drawing", 0},
	{"enable color", 0},
	{"background color", format_tools::black},
	{"foreground color", format_tools::white},
	{"x color", format_tools::blue},
	{"o color", format_tools::red},
	{"mark color", format_tools::yellow},
	{"bold foreground", 0}
};