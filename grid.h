/**
 * Declares a class representing a 2d grid of cells.
 * Rich documentation for the api and behaviour the Grid class can be found in grid.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author ***REMOVED***
 * @date March, 2020
 */
#pragma once

#include <vector>
#include <iostream>

// Add the minimal number of includes you need in order to declare the class.
// #include ...

/**
 * A Cell is a char limited to two named values for Cell::DEAD and Cell::ALIVE.
 */
enum Cell : char {
    DEAD = ' ',
    ALIVE = '#'
};

/**
 * Declare the structure of the Grid class for representing a 2d grid of cells.
 */
class Grid {
private:
    std::vector<Cell> grid;
    unsigned int gridHeight;
    unsigned int gridWidth;

    unsigned int get_index(unsigned int x, unsigned int y) const;
	void check_if_in_bounds(int x, int y) const;

public:
    Grid();
    explicit Grid(unsigned int gridSize);
    explicit Grid(unsigned int width, unsigned int height);

    const unsigned int &get_width() const;
    const unsigned int &get_height() const;
    unsigned int get_total_cells() const;
    unsigned int get_alive_cells() const;
    unsigned int get_dead_cells() const;

	Cell get(int x, int y) const;
	void set(unsigned int x, unsigned int y, Cell value);

	void resize(unsigned int square_size);
    void resize(unsigned int width, unsigned int height);

    Cell & operator()(int x, int y);
    const Cell operator()(int x, int y) const;

	Grid crop(int x0, int y0, int x1, int y1) const;
	void merge(const Grid& other, int x0, int y0, bool alive_only = false);
	Grid rotate(int rotation) const;

	friend std::ostream & operator<<(std::ostream & output_stream, const Grid& grid);
};