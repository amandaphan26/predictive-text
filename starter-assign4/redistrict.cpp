/*
 * File: redistrict.cpp
 * Author: Amanda Phan (amandapt@stanford.edu)
 * Course/Section: CS 106B, Thorton 210
 * This file implements horizontal-vertical spitline (HVS) to determine whether a population density
 * can be redistricted.
 */

#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "backtracking.h"
#include "grid.h"
#include "gridgraphics.h"
#include "SimpleTest.h"
using namespace std;

/* The subgridSum function takes in a grid of integers and a GridLocationRange.
* The output returns the total population count. */
int subgridSum(Grid<int>& g, GridLocationRange range) {
    int totalPopCount = 0;
    for (GridLocation loc: range){
        totalPopCount += g[loc];
    }
    return totalPopCount;
}


/* The divideHorizontal function takes in a GridLocationRange, a top End Row (specifies where the horizontal
 * slice is), and two subranges: top and bottom.*/
void divideHorizontal(GridLocationRange range, int topEndRow, GridLocationRange& top, GridLocationRange& bottom) {
    top = GridLocationRange(range.startRow(), range.startCol(), topEndRow, range.endCol());
    bottom = GridLocationRange(topEndRow + 1, range.startCol(), range.endRow(), range.endCol());
}


/* The divideVertical function takes in a GridLocationRange, a left end column (specifies where the vertical
 * slice is), and two subranges: left and a splits a rectangular range vertically */
void divideVertical(GridLocationRange range, int leftEndCol, GridLocationRange& left, GridLocationRange& right) {
    left = GridLocationRange(range.startRow(), range.startCol(), range.endRow(), leftEndCol);
    right = GridLocationRange(range.startRow(), leftEndCol + 1, range.endRow(), range.endCol());
}


/* The canRedistrictHelper function takes in three parameters: a grid of integers, a range, and a target size.
 The output returns a true/false value based on wehether the districts can be split horizontally or vertically. */
bool canRedistrictHelper(Grid<int>& populationGrid, GridLocationRange range, int targetSize) {
    int pop = subgridSum(populationGrid, range);

    if (pop % targetSize != 0){
        return false;
    }
    else if (pop == targetSize){
        return true;
    }

    GridLocationRange top;
    GridLocationRange bottom;
    // Loops through the start to end row and checks to see if the two subranges (top and bottom) can be divided horizontally.
    for (int i = range.startRow(); i < range.endRow(); i++){
        divideHorizontal(range, i, top, bottom);
        bool result = canRedistrictHelper(populationGrid, top, targetSize) && canRedistrictHelper(populationGrid, bottom, targetSize);
        if (result){
            return true;
        }
    }

    GridLocationRange left;
    GridLocationRange right;
    // Loops through the start to end column and checks to see if the two subranges (left and right) can be divided vertically.
    for (int j = range.startCol(); j < range.endCol(); j++){
        divideVertical(range, j, left, right);
        bool result = canRedistrictHelper(populationGrid, left, targetSize) && canRedistrictHelper(populationGrid, right, targetSize);
        if (result){
            return true;
        }
    }
    return false;
}

/* The canRedistrictfunction takes in two arguments: a population density grid and
 * the number of districts. The output returns a true/false value based in the HVS strategy,
 * determining whether there is a valid redistricting of the state's population.
 */
bool canRedistrict(Grid<int>& populationGrid, int nDistricts) {
    GridLocationRange range = GridLocationRange(0, 0, populationGrid.numRows() - 1, populationGrid.numCols() - 1);
    int totalSize = subgridSum(populationGrid, range);
    // Checks to see if the total population size can be evenly split into the specified number of districts.
    if (totalSize % nDistricts != 0){
        return false;
    }
    int targetSize = totalSize / nDistricts;
    return canRedistrictHelper(populationGrid, range, targetSize);
}


/* * * * * * Test Cases * * * * * */

STUDENT_TEST("subgridSum sums values in grid range") {
    // This is an example test of helper function subgridSum
    Grid<int> grid = { {24, 26, 4}, {9, 7, 83}, {42, 7, 5} };
    GridLocationRange all = grid.locations();
    GridLocationRange firstColumn = GridLocationRange(0, 0, 2, 0);
    GridLocationRange bottomCorner = GridLocationRange(2, 2, 2, 2);

    EXPECT_EQUAL(subgridSum(grid, firstColumn), 75);
    EXPECT_EQUAL(subgridSum(grid, bottomCorner), 5);
    EXPECT_EQUAL(subgridSum(grid, all), 207);
}

STUDENT_TEST("subgridSum sums values in grid range") {
    // This is an example test of helper function subgridSum
    Grid<int> grid = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9} };
    GridLocationRange all = grid.locations();
    GridLocationRange firstColumn = GridLocationRange(0, 0, 2, 0);
    GridLocationRange bottomCorner = GridLocationRange(2, 2, 2, 2);

    EXPECT_EQUAL(subgridSum(grid, firstColumn), 12);
    EXPECT_EQUAL(subgridSum(grid, bottomCorner), 9);
    EXPECT_EQUAL(subgridSum(grid, all), 45);
}


PROVIDED_TEST("subgridSum sums values in grid range") {
    // This is an example test of helper function subgridSum
    Grid<int> grid = { {1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 10, 10} };
    GridLocationRange all = grid.locations();
    GridLocationRange firstColumn = GridLocationRange(0, 0, 3, 0);
    GridLocationRange bottomCorner = GridLocationRange(3, 2, 3, 2);

    EXPECT_EQUAL(subgridSum(grid, firstColumn), 22);
    EXPECT_EQUAL(subgridSum(grid, bottomCorner), 10);
    EXPECT_EQUAL(subgridSum(grid, all), 75);
}



PROVIDED_TEST("nevada example from writeup can be divided into 4 districts") {
    Grid<int> nevada = { {20, 31, 20},
                         { 5, 19, 30},
                         {25, 25, 25} };

    initForPopulationGrid(nevada); // you can remove if you don't wish to animate this test case
    EXPECT(canRedistrict(nevada, 4));
    waitForCloseWindow();
}

PROVIDED_TEST("wyoming example from writeup cannot be divided into 2 districts") {
    Grid<int> wyoming = { {10, 15},
                          { 5, 10} };

    initForPopulationGrid(wyoming); // you can remove if you don't wish to animate this test case
    EXPECT(!canRedistrict(wyoming, 2));
    waitForCloseWindow();
}

PROVIDED_TEST("small example, 5 districts") {
    Grid<int> small = { {3, 7, 10},
                        {6, 3, 1},
                        {1, 10, 9} };
    initForPopulationGrid(small);  // you can remove if you don't wish to animate this test case
    EXPECT(canRedistrict(small, 5));
    waitForCloseWindow();
}

PROVIDED_TEST("medium example, 12 districts") {
    Grid<int> medium = { {10, 1,  2, 5, 1, 4},
                          {1, 1,  8, 2, 1, 7},
                          {9, 8, 10, 3, 3, 4},
                          {5, 2,  2, 8, 7, 3},
                          {2, 1,  1, 7, 1, 1} };
    initForPopulationGrid(medium);  // you can remove if you don't wish to animate this test case
    EXPECT(canRedistrict(medium, 12));
    waitForCloseWindow();
}

PROVIDED_TEST("large example can be divided into 25 districts") {
    Grid<int> large = { { 5,  2, 2,  1,  6, 4, 8, 2},
                        {10, 10, 2,  1,  3, 4, 2, 3},
                        { 1,  1, 4,  5,  1, 9, 1, 4},
                        { 9,  5, 5, 10, 10, 3, 3, 4},
                        { 3,  1, 1,  1,  2, 8, 6, 2},
                        { 2,  1, 1,  7,  3, 5, 1, 1},
                        { 1,  1, 2,  2,  7, 5, 1, 9},
                        { 4,  1, 2, 10,  1, 9, 5, 5} };
    initForPopulationGrid(large); // you can remove if you don't wish to animate this test case
    EXPECT(canRedistrict(large, 25));
    waitForCloseWindow();
}
