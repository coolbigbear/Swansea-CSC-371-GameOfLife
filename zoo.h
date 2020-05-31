/**
 * Declares a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 * Rich documentation for the api and behaviour the Zoo namespace can be found in zoo.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author **REMOVED**
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the namespace.
// #include ...
#include "grid.h"

/**
 * Declare the interface of the Zoo namespace for constructing lifeforms and saving and loading them from file.
 */
namespace Zoo {

	// Errors
	const std::string file_cannot_be_opened_error = "File cannot be opened: ";
	const std::string newline_characters_not_found_error = "Newline characters are not found when expected during parsing";
	const std::string file_ends_unexpectedly_error = "File ends unexpectedly";
	const std::string char_not_in_cell_enum_error = "The character for a cell is not the ALIVE or DEAD character";
	const std::string height_or_width_not_positive_error = "The parsed grid width or grid height is not a positive integer:";

	Grid glider();
	Grid r_pentomino();
	Grid light_weight_spaceship();
	Grid load_ascii(const std::string& path);
	void save_ascii(const std::string& path, const Grid& grid);
	Grid load_binary(const std::string& path);
	void save_binary(const std::string& path, const Grid& grid);
};
