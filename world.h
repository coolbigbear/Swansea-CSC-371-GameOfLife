/**
 * Declares a class representing a 2d grid world for simulating a cellular automaton.
 * Rich documentation for the api and behaviour the World class can be found in world.cpp.
 *
 * The test suites provide granular BDD style (Behaviour Driven Development) test cases
 * which will help further understand the specification you need to code to.
 *
 * @author YOUR_STUDENT_NUMBER
 * @date March, 2020
 */
#pragma once

// Add the minimal number of includes you need in order to declare the class.
// #include ...

#include "grid.h"

/**
 * Declare the structure of the World class for representing a 2d grid world.
 *
 * A World holds two equally sized Grid objects for the current state and next state.
 *      - These buffers should be swapped using std::swap after each update step.
 */
class World {

private:
	Grid current_state;
	Grid next_state;

	unsigned int count_neighbours(unsigned int x, unsigned int y, bool toroidal);

public:
	World();
	World(unsigned int square_size);
	World(unsigned int width, unsigned int gridHeight);
	World(Grid initial_state);

	unsigned int get_width();
	unsigned int get_height();
	unsigned int get_total_cells();
	unsigned int get_alive_cells();
	unsigned int get_dead_cells();

	const Grid& get_state() const;
	void resize(unsigned int square_size);
	void resize(unsigned int new_width, unsigned int new_height);

	void step(bool toroidal = false);
	void advance(unsigned int steps, bool toroidal = false);
    // How to draw an owl:
    //      Step 1. Draw a circle.
    //      Step 2. Draw the rest of the owl.

};