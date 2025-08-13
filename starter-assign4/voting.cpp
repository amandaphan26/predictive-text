/*
 * File: predict.cpp
 * Author: Amanda Phan (amandapt@stanford.edu)
 * Course/Section: CS 106B, Thorton 210
 * This file computes the voting power of the different blocks in a block-voting system.
 */
#include <iostream>    // for cout, endl
#include <string>      // for string class
#include "backtracking.h"
#include "SimpleTest.h"
using namespace std;

/*
 * The computerPowerIndexes helper function takes in a Vector of size N that contains all the blocks
 * in the system. The output returns a Map of size N, which assosicates each block ID with the
 * Banzhaf power index for that block.
 */
int computeCriticalVotes(int majority, Vector<blockT>& blocks, int chosen, int coalition, int index) {
    int result;

    if (coalition > majority){
        return 0;
    }

    if (index == blocks.size()){
        if (coalition + blocks[chosen].count > majority){
            return 1;
        }
    return 0;
    }

    if (index == chosen) {
        return computeCriticalVotes(majority, blocks, chosen, coalition, index + 1);
    }
    else {
        return computeCriticalVotes(majority, blocks, chosen, coalition + blocks[index].count, index + 1) +
        computeCriticalVotes(majority, blocks, chosen, coalition, index + 1);
    }

}

/* The computerPowerIndexes function takes in a Vector of blockTs. The output returns
 a map of string keys to integer values.*/
Map<string,int> computePowerIndexes(Vector<blockT>& blocks) {
    Map<string, int> result;

    int blocksCount = 0;
    for (int i = 0; i < blocks.size(); i++){
        blocksCount += blocks[i].count;
    }

    int majority = blocksCount / 2;
    int total = 0;

    for (int i = 0; i < blocks.size(); i++){
        // Calculates the critical vote for each block.
        int criticalVotes = computeCriticalVotes(majority, blocks, i, 0, 0);
        result[blocks[i].id] = criticalVotes;
        total += criticalVotes;
    }

    // Converting critical votes of each block to a percentage.
    for (string blocks : result) {
        result[blocks] = 100 * result[blocks] / total;
    }

    return result;
}


/* * * * * * Test Cases * * * * * */

STUDENT_TEST("Power indexes: lions-45 tigers-7 bears-48") {
    Vector<blockT> blocks = {{"Lions",45}, {"Tigers",7}, {"Bears",48}};
    Map<string,int> expected = {{"Lions",33}, {"Tigers",33}, {"Bears",33}};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}


PROVIDED_TEST("Power indexes: lions-50 tigers-49 bears-1") {
    Vector<blockT> blocks = {{"Lions",50}, {"Tigers",49}, {"Bears",1}};
    Map<string,int> expected = {{"Lions",60}, {"Tigers",20}, {"Bears",20}};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Power indexes: Hempshead 1-1-3-7-9-9") {
    Vector<blockT> blocks = {{"A",1}, {"B",1}, {"C",3}, {"D",7}, {"E",9}, {"F",9}};
    Map<string,int> expected = {{"A",0}, {"B",0}, {"C",0}, {"D",33}, {"E",33}, {"F",33}};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Power indexes: CA-55 TX-38 NY-29") {
    Vector<blockT> blocks = {{"CA",55}, {"TX",38}, {"NY",29}};
    Map<string,int> expected = {{"CA",33}, {"TX",33}, {"NY",33}};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Power indexes: CA-55 TX-38 GA-16") {
    Vector<blockT> blocks = {{"CA",55}, {"TX",38}, {"GA",16}};
    Map<string,int> expected = {{"CA",100}, {"TX",0}, {"GA",0}};
    EXPECT_EQUAL(computePowerIndexes(blocks), expected);
}

PROVIDED_TEST("Power indexes: time operation") {
    Vector<blockT> blocks;
    for (int i = 0; i < 24; i++) {
        blockT b = {charToString('A' + i), randomInteger(1, 10)};
        blocks.add(b);
    }
    TIME_OPERATION(blocks.size(), computePowerIndexes(blocks));
}
