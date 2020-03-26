/**
 * Implements a Zoo namespace with methods for constructing Grid objects containing various creatures in the Game of Life.
 *      - Creatures like gliders, light weight spaceships, and r-pentominos can be spawned.
 *          - These creatures are drawn on a Grid the size of their bounding box.
 *
 *      - Grids can be loaded from and saved to an ascii file format.
 *          - Ascii files are composed of:
 *              - A header line containing an integer width and gridHeight separated by a space.
 *              - followed by (gridHeight) number of lines, each containing (width) number of characters,
 *                terminated by a newline character.
 *              - (space) ' ' is Cell::DEAD, (hash) '#' is Cell::ALIVE.
 *
 *      - Grids can be loaded from and saved to an binary file format.
 *          - Binary files are composed of:
 *              - a 4 byte int representing the grid width
 *              - a 4 byte int representing the grid gridHeight
 *              - followed by (width * gridHeight) number of individual bits in C-style row/column format,
 *                padded with zero or more 0 bits.
 *              - a 0 bit should be considered Cell::DEAD, a 1 bit should be considered Cell::ALIVE.
 *
 * @author ***REMOVED***
 * @date March, 2020
 */

// Include the minimal number of headers needed to support your implementation.
// #include ...
#include "zoo.h"
#include "grid.h"
#include <fstream>

/**
 * Zoo::glider()
 *
 * Construct a 3x3 grid containing a glider.
 * https://www.conwaylife.com/wiki/Glider
 *
 * @example
 *
 *      // Print a glider in a Grid the size of its bounding box.
 *      std::cout << Zoo::glider() << std::endl;
 *
 *      +---+
 *      | # |
 *      |  #|
 *      |###|
 *      +---+
 *
 * @return
 *      Returns a Grid containing a glider.
 */
Grid Zoo::glider() {
	Grid glider = Grid(3);
	// Base
	glider.set(0,0, Cell::ALIVE);
	glider.set(1,0, Cell::ALIVE);
	glider.set(2,0, Cell::ALIVE);

	// Middle
	glider.set(2,1, Cell::ALIVE);

	// Top
	glider.set(1,3, Cell::ALIVE);

	return glider;
}

/**
 * Zoo::r_pentomino()
 *
 * Construct a 3x3 grid containing an r-pentomino.
 * https://www.conwaylife.com/wiki/R-pentomino
 *
 * @example
 *
 *      // Print an r-pentomino in a Grid the size of its bounding box.
 *      std::cout << Zoo::r_pentomino() << std::endl;
 *
 *      +---+
 *      | ##|
 *      |## |
 *      | # |
 *      +---+
 *
 * @return
 *      Returns a Grid containing a r-pentomino.
 */
Grid Zoo::r_pentomino() {
	Grid r_pentomino = Grid(3);

	// Bottom
	r_pentomino.set(1,0, Cell::ALIVE);

	// Middle
	r_pentomino.set(0,1, Cell::ALIVE);
	r_pentomino.set(1,1, Cell::ALIVE);

	// Top
	r_pentomino.set(1,2, Cell::ALIVE);
	r_pentomino.set(2,2, Cell::ALIVE);

	return r_pentomino;
}

/**
 * Zoo::light_weight_spaceship()
 *
 * Construct a 5x4 grid containing a light weight spaceship.
 * https://www.conwaylife.com/wiki/Lightweight_spaceship
 *
 * @example
 *
 *      // Print a light weight spaceship in a Grid the size of its bounding box.
 *      std::cout << Zoo::light_weight_spaceship() << std::endl;
 *
 *      +-----+
 *      | #  #|
 *      |#    |
 *      |#   #|
 *      |#### |
 *      +-----+
 *
 * @return
 *      Returns a grid containing a light weight spaceship.
 */
Grid Zoo::light_weight_spaceship() {
	Grid light_weight_spaceship = Grid(5,4);

	// Bottom
	light_weight_spaceship.set(0,0,Cell::ALIVE);
	light_weight_spaceship.set(1,0,Cell::ALIVE);
	light_weight_spaceship.set(2,0,Cell::ALIVE);
	light_weight_spaceship.set(3,0,Cell::ALIVE);

	// Bottom middle
	light_weight_spaceship.set(0,1,Cell::ALIVE);
	light_weight_spaceship.set(4,1,Cell::ALIVE);

	// Top middle
	light_weight_spaceship.set(0,2,Cell::ALIVE);

	// Top
	light_weight_spaceship.set(1,3,Cell::ALIVE);
	light_weight_spaceship.set(4,3,Cell::ALIVE);

	return light_weight_spaceship;

}

/**
 * Zoo::load_ascii(path)
 *
 * Load an ascii file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an ascii file from a directory
 *      Grid grid = Zoo::load_ascii("path/to/file.gol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The parsed width or gridHeight is not a positive integer.
 *          - Newline characters are not found when expected during parsing.
 *          - The character for a cell is not the ALIVE or DEAD character.
 */
Grid Zoo::load_ascii(std::string path) {
	std::ifstream input(path);

	if (!input) {
		throw std::runtime_error("File: " + path + " not found");
	}

	char c;
	unsigned int width, height;
	input >> width >> height;
	input.get(c);

	if (width < 0 || height < 0) {
		throw std::runtime_error("The parsed width or gridHeight is not a positive integer");
	} else if (c != '\n') {
		throw std::runtime_error("Newline characters are not found when expected during parsing");
	}

	Grid grid = Grid(width, height);

	unsigned int x = 0;
	unsigned int y = 0;
	unsigned int k = 0;
	while (input.get(c)) {
		if (c != '\n' && k != width) { // Only read if new lines at end of width of grid
			if (c == Cell::ALIVE || c == Cell::DEAD) { // Check if char is in enum
				grid.set(x, y, static_cast<Cell>(c));
				x++;
				k++;
				if (x == width) { // Reached new line reset variables, read new line char
					y++;
					k = 0;
					x = 0;
					input.get();
				}
			} else {
				throw std::runtime_error("The character for a cell is not the ALIVE or DEAD character");
			}
		} else {
			throw std::runtime_error("Newline characters are not found when expected during parsing");
		}
	}

	return grid;
}

/**
 * Zoo::save_ascii(path, grid)
 *
 * Save a grid as an ascii .gol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an ascii file in a directory
 *      try {
 *          Zoo::save_ascii("path/to/file.gol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_ascii(std::string path, Grid grid) {

}

/**
 * Zoo::load_binary(path)
 *
 * Load a binary file and parse it as a grid of cells.
 * Should be implemented using std::ifstream.
 *
 * @example
 *
 *      // Load an binary file from a directory
 *      Grid grid = Zoo::load_binary("path/to/file.bgol");
 *
 * @param path
 *      The std::string path to the file to read in.
 *
 * @return
 *      Returns the parsed grid.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if:
 *          - The file cannot be opened.
 *          - The file ends unexpectedly.
 */
Grid Zoo::load_binary(std::string path) {

}

/**
 * Zoo::save_binary(path, grid)
 *
 * Save a grid as an binary .bgol file according to the specified file format.
 * Should be implemented using std::ofstream.
 *
 * @example
 *
 *      // Make an 8x8 grid
 *      Grid grid(8);
 *
 *      // Save a grid to an binary file in a directory
 *      try {
 *          Zoo::save_binary("path/to/file.bgol", grid);
 *      }
 *      catch (const std::exception &ex) {
 *          std::cerr << ex.what() << std::endl;
 *      }
 *
 * @param path
 *      The std::string path to the file to write to.
 *
 * @param grid
 *      The grid to be written out to file.
 *
 * @throws
 *      Throws std::runtime_error or sub-class if the file cannot be opened.
 */
void Zoo::save_binary(std::string path, Grid grid) {

}
