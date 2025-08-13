#pragma once

/* Needed for predict.cpp */
#include "set.h"
#include "lexicon.h"
#include <string>
void predict(std::string digits, Set<std::string>& suggestions, Lexicon& lex);


/* Needed for voting.cpp */
#include "vector.h"

/* The blockT struct is stores the data for one voting block.
 * The id field is the string name/id for the block and the count
 * is the number of votes cast for this block.
 */
struct blockT {
    std::string id;
    int count;
};

Map<std::string,int> computePowerIndexes(Vector<blockT>& blocks);


/* Needed for redistrict.cpp */
#include "grid.h"
bool canRedistrict(Grid<int>& populationGrid, int nDistricts);
