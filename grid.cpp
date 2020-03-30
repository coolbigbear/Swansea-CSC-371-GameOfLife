/**
 * Implements a class representing a 2d grid of cells.
 *      - New cells are initialized to Cell::DEAD.
 *      - Grids can be resized while retaining their contents in the remaining area.
 *      - Grids can be rotated, cropped, and merged together.
 *      - Grids can return counts of the alive and dead cells.
 *      - Grids can be serialized directly to an ascii std::ostream.
 *
 * You are encouraged to use STL container types as an underlying storage mechanism for the grid cells.
 *
 * @author ***REMOVED***
 * @date March, 2020
 */
#include "grid.h"
#include <sstream>
#include <vector>
#include <stdexcept>

// Include the minimal number of headers needed to support your implementation.
// #include ...

/**
 * Grid::Grid()
 *
 * Construct an empty grid of size 0x0.
 * Can be implemented by calling Grid::Grid(square_size) constructor.
 *
 * @example
 *
 *      // Make a 0x0 empty grid
 *      Grid grid;
 *
 */
Grid::Grid() : Grid(0) {
}

/**
 * Grid::Grid(square_size)
 *
 * Construct a grid with the desired size filled with dead cells.
 * Single value constructors should be marked "explicit" to prevent them
 * being used to implicitly cast ints to grids on construction.
 *
 * Can be implemented by calling Grid::Grid(width, height) constructor.
 *
 * @example
 *
 *      // Make a 16x16 grid
 *      Grid x(16);
 *
 *      // Also make a 16x16 grid
 *      Grid y = Grid(16);
 *
 *      // This should be a compiler error! We want to prevent this from being allowed.
 *      Grid z = 16;
 *
 * @param square_size
 *      The edge size to use for the width and height of the grid.
 */
Grid::Grid(const unsigned int gridSize) : Grid(gridSize, gridSize) {
}

/**
 * Grid::Grid(width, height)
 *
 * Construct a grid with the desired size filled with dead cells.
 *
 * @example
 *
 *      // Make a 16x9 grid
 *      Grid grid(16, 9);
 *
 * @param width
 *      The width of the grid.
 *
 * @param height
 *      The height of the grid.
 */
Grid::Grid(const unsigned int width, const unsigned int height) : gridHeight(height), gridWidth(width) {
    std::vector<Cell> tempGrid(width * height, Cell::DEAD);
    this->grid = tempGrid;
}

/**
 * Grid::get_width()
 *
 * Gets the current width of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the width of the grid to the console
 *      std::cout << grid.get_width() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the width of the grid to the console
 *      std::cout << read_only_grid.get_width() << std::endl;
 *
 * @return
 *      The width of the grid.
 */
const unsigned int &Grid::get_width() const {
    return this->gridWidth;
}

/**
 * Grid::get_height()
 *
 * Gets the current height of the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the height of the grid to the console
 *      std::cout << grid.get_height() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the height of the grid to the console
 *      std::cout << read_only_grid.get_height() << std::endl;
 *
 * @return
 *      The height of the grid.
 */
const unsigned int &Grid::get_height() const {
    return this->gridHeight;
}

/**
 * Grid::get_total_cells()
 *
 * Gets the total number of cells in the grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << grid.get_total_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the total number of cells on the grid to the console
 *      std::cout << read_only_grid.get_total_cells() << std::endl;
 *
 * @return
 *      The number of total cells.
 */
unsigned int Grid::get_total_cells() const {
    return this->grid.size();
}

/**
 * Grid::get_alive_cells()
 *
 * Counts how many cells in the grid are alive.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of alive cells to the console
 *      std::cout << grid.get_alive_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of alive cells to the console
 *      std::cout << read_only_grid.get_alive_cells() << std::endl;
 *
 * @return
 *      The number of alive cells.
 */
unsigned int Grid::get_alive_cells() const {
	unsigned int total = 0;
    for (char i : this->grid) {
        if (i == Cell::ALIVE) {
            total += 1;
        }
    }
    return total;
}

/**
 * Grid::get_dead_cells()
 *
 * Counts how many cells in the grid are dead.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Print the number of dead cells to the console
 *      std::cout << grid.get_dead_cells() << std::endl;
 *
 *      // Should also be callable in a constant context
 *      const Grid &read_only_grid = grid;
 *
 *      // Print the number of dead cells to the console
 *      std::cout << read_only_grid.get_dead_cells() << std::endl;
 *
 * @return
 *      The number of dead cells.
 */
unsigned int Grid::get_dead_cells() const {
    return this->get_total_cells() - this->get_alive_cells();
}

/**
 * Grid::resize(square_size)
 *
 * Resize the current grid to a new width and height that are equal. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 8x8
 *      grid.resize(8);
 *
 * @param square_size
 *      The new edge size for both the width and height of the grid.
 */
void Grid::resize(const unsigned int square_size) {
    resize(square_size, square_size);
}

/**
 * Grid::resize(width, height)
 *
 * Resize the current grid to a new width and height. The content of the grid
 * should be preserved within the kept region and padded with Grid::DEAD if new cells are added.
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Resize the grid to be 2x8
 *      grid.resize(2, 8);
 *
 * @param new_width
 *      The new width for the grid.
 *
 * @param new_height
 *      The new height for the grid.
 */
void Grid::resize(const unsigned int width, const unsigned int height) {

	// Create new grid to copy old grid in to
	const unsigned int new_grid_size = width * height;
    std::vector<Cell > grid2;
    grid2.assign(new_grid_size, Cell::DEAD);

    unsigned int grid_width;
    unsigned int grid_height;

    // Set variables depending if grid is being made smaller or bigger
    if (this->gridWidth < width) {	// Making bigger than original
        grid_width = this->gridWidth;
        grid_height = this->gridHeight;
    } else {						// Making grid smaller
        grid_height = height;
		grid_width = width;
    }

    // Loop over new grid and copy elements from old grid to new grid
    // First check if grid is size 0
    if (this->gridWidth != 0 && this->gridHeight != 0) {
        for (int y = 0; y < grid_height; y++) {
        	for (int x = 0; x < grid_width; x++) {
				grid2[y * width + x] = this->get(x, y);
			}
        }
    }

    // Assign grid and update height and width
    this->grid = grid2;
    this->gridHeight = height;
    this->gridWidth = width;
}

/**
 * Grid::get_index(x, y)
 *
 * Private helper function to determine the 1d index of a 2d coordinate.
 * Should not be visible from outside the Grid class.
 * The function should be callable from a constant context.
 *
 * @param x
 *      The x coordinate of the cell.
 *
 * @param y
 *      The y coordinate of the cell.
 *
 * @return
 *      The 1d offset from the start of the data array where the desired cell is located.
 */
unsigned int Grid::get_index(unsigned int x, unsigned int y) const {
    return (y * this->get_width()) + x;
}

/**
 * Grid::get(x, y)
 *
 * Returns the value of the cell at the desired coordinate.
 * Specifically this function should return a cell value, not a reference to a cell.
 * The function should be callable from a constant context.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Read the cell at coordinate (1, 2)
 *      Cell cell = grid.get(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @return
 *      The value of the desired cell. Should only be Grid::ALIVE or Grid::DEAD.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell Grid::get(const int x, const int y) const {
	check_if_in_bounds(x, y);
    return (*this)(x, y);
}

/**
 * Grid::set(x, y, value)
 *
 * Overwrites the value at the desired coordinate.
 * Should be implemented by invoking Grid::operator()(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Assign to a cell at coordinate (1, 2)
 *      grid.set(1, 2, Cell::ALIVE);
 *
 * @param x
 *      The x coordinate of the cell to update.
 *
 * @param y
 *      The y coordinate of the cell to update.
 *
 * @param value
 *      The value to be written to the selected cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
void Grid::set(unsigned int x, unsigned int y, Cell value) {
	check_if_in_bounds(x, y);
	Grid::operator()(x, y) = value;
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a modifiable reference to the value at the desired coordinate.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = grid(1, 2);
 *
 *      // Directly assign to a cell at coordinate (1, 2)
 *      grid(1, 2) = Cell::ALIVE;
 *
 *      // Extract a reference to an individual cell to avoid calculating it's
 *      // 1d index multiple times if you need to access the cell more than once.
 *      Cell &cell_reference = grid(1, 2);
 *      cell_reference = Cell::DEAD;
 *      cell_reference = Cell::ALIVE;
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A modifiable reference to the desired cell.
 *
 * @throws
 *      std::runtime_error or sub-class if x,y is not a valid coordinate within the grid.
 */
Cell & Grid::operator()(const int x, const int y) {
	check_if_in_bounds(x, y);
	return this->grid[Grid::get_index(x, y)];
}

/**
 * Grid::operator()(x, y)
 *
 * Gets a read-only reference to the value at the desired coordinate.
 * The operator should be callable from a constant context.
 * Should be implemented by invoking Grid::get_index(x, y).
 *
 * @example
 *
 *      // Make a grid
 *      Grid grid(4, 4);
 *
 *      // Constant reference to a grid (does not make a copy)
 *      const Grid &read_only_grid = grid;
 *
 *      // Get access to read a cell at coordinate (1, 2)
 *      Cell cell = read_only_grid(1, 2);
 *
 * @param x
 *      The x coordinate of the cell to access.
 *
 * @param y
 *      The y coordinate of the cell to access.
 *
 * @return
 *      A read-only reference to the desired cell.
 *
 * @throws
 *      std::exception or sub-class if x,y is not a valid coordinate within the grid.
 */
const Cell Grid::operator()(const int x, const int y) const {
	check_if_in_bounds(x, y);
	return this->grid[Grid::get_index(x, y)];
}

/**
 * Grid::crop(x0, y0, x1, y1)
 *
 * Extract a sub-grid from a Grid.
 * The cropped grid spans the range [x0, x1) by [y0, y1) in the original grid.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a grid
 *      Grid y(4, 4);
 *
 *      // Crop the centre 2x2 in y, trimming a 1 cell border off all sides
 *      Grid x = y.crop(x, 1, 1, 3, 3);
 *
 * @param x0
 *      Left coordinate of the crop window on x-axis.
 *
 * @param y0
 *      Top coordinate of the crop window on y-axis.
 *
 * @param x1
 *      Right coordinate of the crop window on x-axis (1 greater than the largest index).
 *
 * @param y1
 *      Bottom coordinate of the crop window on y-axis (1 greater than the largest index).
 *
 * @return
 *      A new grid of the cropped size containing the values extracted from the original grid.
 *
 * @throws
 *      std::exception or sub-class if x0,y0 or x1,y1 are not valid coordinates within the grid
 *      or if the crop window has a negative size.
 */
Grid Grid::crop(const int x0, const int y0, const int x1, const int y1) const {

	check_if_in_bounds(x0, y0);
	check_if_in_bounds(x1, y1);

	if (y0 > y1 || x0 > x1) {
		std::stringstream ss;
		ss << "Crop window has a negative size:"<<
		" x0 = "<< x0 <<
		" y0 = " << y0 <<
		" x1 = " << x1 <<
		" y1 = " << y1;
		throw std::invalid_argument(ss.str());
	}

	const unsigned int new_grid_width = x1 - x0;
	const unsigned int new_grid_height = y1 - y0;
	unsigned int old_grid_index = 0;
	unsigned int cells_in_row = 0;

	// Figure out if 0's are passed and where to start the grid
	if (x0 == 0 || y0 == 0) {
		if (x0 + y0 == 0) {
			old_grid_index = 0;	// Cropping starts in top left corner
		} else if (x0 == 0) {
			old_grid_index = y0 * this->gridWidth; // Cropping starts at start of row y0
		} else {
			old_grid_index = x0; // Cropping starts on first row at offset x0
		}
	} else {
		old_grid_index = (this->gridWidth * y0) + x0; // Find row and add offset
	}

	Grid temp = Grid(new_grid_width, new_grid_height);
	// Loop over selected portion of grid and copy from old to new Grid.
	for (unsigned int new_grid_index = 0; new_grid_index < temp.get_total_cells(); new_grid_index++) {
		if (cells_in_row >= new_grid_width) {
			cells_in_row = 0;
			old_grid_index += this->gridWidth - new_grid_width;
		}
		temp.grid[new_grid_index] = this->grid[old_grid_index];
		old_grid_index++;
		cells_in_row++;
	}

	return temp;
}

/**
 * Grid::merge(other, x0, y0, alive_only = false)
 *
 * Merge two grids together by overlaying the other on the current grid at the desired location.
 * By default merging overwrites all cells within the merge reason to be the value from the other grid.
 *
 * Conditionally if alive_only = true perform the merge such that only alive cells are updated.
 *      - If a cell is originally dead it can be updated to be alive from the merge.
 *      - If a cell is originally alive it cannot be updated to be dead from the merge.
 *
 * @example
 *
 *      // Make two grids
 *      Grid x(2, 2), y(4, 4);
 *
 *      // Overlay x as the upper left 2x2 in y
 *      y.merge(x, 0, 0);
 *
 *      // Overlay x as the bottom right 2x2 in y, reading only alive cells from x
 *      y.merge(x, 2, 2, true);
 *
 * @param other
 *      The other grid to merge into the current grid.
 *
 * @param x0
 *      The x coordinate of where to place the top left corner of the other grid.
 *
 * @param y0
 *      The y coordinate of where to place the top left corner of the other grid.
 *
 * @param alive_only
 *      Optional parameter. If true then merging only sets alive cells to alive but does not explicitly set
 *      dead cells, allowing whatever value was already there to persist. Defaults to false.
 *
 * @throws
 *      std::exception or sub-class if the other grid being placed does not fit within the bounds of the current grid.
 */
void Grid::merge(const Grid& other, const int x0, const int y0, bool alive_only) {

	check_if_in_bounds(x0, y0);

	const unsigned int other_grid_width = other.get_width();
	const unsigned int other_grid_height = other.get_height();

	if (other_grid_width + x0 > this->get_width() || other_grid_height + y0 > this->get_height()) {
		std::stringstream ss;
		ss << "Grid being placed does not fit within the bounds of the current grid:"<<
		   " x0 = "<< x0 <<
		   " y0 = " << y0;
		throw std::invalid_argument(ss.str());
	}

	unsigned int current_grid_index;
	unsigned int cells_in_row = 0;

	// Figure out if 0's are passed and where to start the grid
	if (x0 == 0 || y0 == 0) {
		if (x0 + y0 == 0) {
			current_grid_index = 0; // Merge starts from top left corner
		} else if (x0 == 0) {
			current_grid_index = y0 * this->get_width(); // Merge starts at the start of row y0
		} else {
			current_grid_index = x0; // Merge starts on first row with x0 offset
		}
	} else {
		current_grid_index = (this->gridWidth * y0) + x0; // Find row and add offset
	}

	// Loop over selected portion of grid and copy from other grid to current.
	for (unsigned int other_grid_index = 0; other_grid_index < other.get_total_cells(); other_grid_index++) {
		if (cells_in_row >= other_grid_width) {
			cells_in_row = 0;
			current_grid_index += this->gridWidth - other_grid_width;
		}
		if (alive_only) {
			Cell &cell = this->grid[current_grid_index];
			if (cell == Cell::DEAD) {
				cell = other.grid[other_grid_index];
			}
		} else {
			this->grid[current_grid_index] = other.grid[other_grid_index];
		}
		current_grid_index++;
		cells_in_row++;
	}
}

/**
 * Grid::rotate(rotation)
 *
 * Create a copy of the grid that is rotated by a multiple of 90 degrees.
 * The rotation can be any integer, positive, negative, or 0.
 * The function should take the same amount of time to execute for any valid integer input.
 * The function should be callable from a constant context.
 *
 * @example
 *
 *      // Make a 1x3 grid
 *      Grid x(1,3);
 *
 *      // y is size 3x1
 *      Grid y = x.rotate(1);
 *
 * @param _rotation
 *      An positive or negative integer to rotate by in 90 intervals.
 *
 * @return
 *      Returns a copy of the grid that has been rotated.
 */
Grid Grid::rotate(const int rotation) const {

	Grid g = (*this);

	int rotation_direction = abs(rotation % 4 + 4) % 4;

	if (rotation_direction == 0) {
		//Grid doesn't change
	} else if (rotation_direction == 3) {
		// Original top of grid facing to the left
		// Reading from top left corner
		//      +-----------+
		// -->  | 3 | 6 | 9 |  Read last index of each row, then second index of each row, then third etc.
		//    T |---|---|---|
		//    O | 2 | 5 | 8 |
		//    P |---|---|---|
		//      | 1 | 4 | 7 |
		//      +-----------+
		//
		unsigned int offset = 1;
		unsigned int new_grid_index = 0;
		for (unsigned int current_row = 1; current_row <= this->get_height(); current_row++) {
			g.grid[new_grid_index] = this->grid[(this->gridWidth * current_row) - offset];
			new_grid_index++;
			if(new_grid_index != this->get_total_cells() && current_row == get_height()) {
				current_row = 0;
				offset++;
			}
		}
		// Re-assign width's and heights
		const unsigned int temp = g.gridWidth;
		g.gridWidth = g.gridHeight;
		g.gridHeight = temp;

	} else if (rotation_direction == 2) {
		// Original top of grid facing down
		// Reading from top left corner
		//      +-----------+
		// -->  | 9 | 8 | 7 |  Read grid upside down.
		//      |---|---|---|
		//      | 6 | 5 | 4 |
		//      |---|---|---|
		//      | 3 | 2 | 1 |
		//      +-----------+
		// 			T O P
		unsigned int j = 0;
		for (auto i = this->grid.crbegin(); i != this->grid.crend(); ++i) {
			g.grid[j] = *i;
			j++;
		}
	} else {
		// Original top of grid facing to the right
		// Reading from top left corner
		//      +-----------+
		// -->  | 7 | 4 | 1 |  Read (starting from last row) first index of each row, then second index of each row etc.
		//      |---|---|---| T
		//      | 8 | 5 | 2 | O
		//      |---|---|---| P
		//      | 9 | 6 | 3 |
		//      +-----------+
		//
		unsigned int offset = this->get_width() * - 1;
		unsigned int new_grind_index = 0;
		for (unsigned int current_row = this->get_height(); current_row >= 1 ; current_row--) {
			g.grid[new_grind_index] = this->grid[(this->gridWidth * current_row) + offset];
			new_grind_index++;
			if(new_grind_index != this->get_total_cells() && current_row == 1) {
				current_row = this->get_height() + 1;
				offset++;
			}
		}
		const unsigned int temp = g.gridWidth;
		g.gridWidth = g.gridHeight;
		g.gridHeight = temp;
	}

	return g;
}

/**
 * operator<<(output_stream, grid)
 *
 * Serializes a grid to an ascii output stream.
 * The grid is printed wrapped in a border of - (dash), | (pipe), and + (plus) characters.
 * Alive cells are shown as # (hash) characters, dead cells with ' ' (space) characters.
 *
 * The function should be callable on a constant Grid.
 *
 * @example
 *
 *      // Make a 3x3 grid with a single alive cell
 *      Grid grid(3);
 *      grid(1, 1) = Cell::ALIVE;
 *
 *      // Print the grid to the console
 *      std::cout << grid << std::endl;
 *
 *      // The grid is printed with a border of + - and |
 *
 *      +---+
 *      |   |
 *      | # |
 *      |   |
 *      +---+
 *
 * @param os
 *      An ascii mode output stream such as std::cout.
 *
 * @param grid
 *      A grid object containing cells to be printed.
 *
 * @return
 *      Returns a reference to the output stream to enable operator chaining.
 */
std::ostream & operator<<(std::ostream & output_stream, const Grid& grid) {

	std::string padding = "+" + std::string(grid.get_width(), '-') + "+";
	output_stream << padding << std::endl; 	// Top row

	for (int y = 0; y < grid.get_height(); y++) {
		output_stream << "|"; 				// Start of row
		for (int x = 0; x < grid.get_width(); x++) {
			output_stream << (char) grid.get(x, y);
		}
		output_stream << "|" << std::endl; 	// End of row
	}
	output_stream << padding << std::endl; 	// Bottom row

	return output_stream;
}

/**
 * Check whether passed coordinates are in grid.
 * @param x - The x coordinate.
 * @param y - The y coordinate.
 *
 * @throws 	- out_of_range exception if point (x,y) not in grid.
 */
void Grid::check_if_in_bounds(const int x, const int y) const {
	if (x > this->get_width() || y > this->get_height() || x < 0 || y < 0) {
		std::stringstream ss;
		ss << x  << ", " << y << " is not a valid coordinate within the grid";
		throw std::out_of_range(ss.str());
	}
}