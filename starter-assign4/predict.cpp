/*
 * File: predict.cpp
 * Author: Amanda Phan (amandapt@stanford.edu)
 * Course/Section: CS 106B, Thorton 210
 * This file uses a T9-style prediction algorithm to suggest words that match a sequence of tapped digits.
 */
#include <iostream>
#include "backtracking.h"
#include "lexicon.h"
#include "set.h"
#include "SimpleTest.h"
using namespace std;



// keypad is a program-wide constant that stores the Map from digit char to
// its associated set of possible letters
static const Map<char, Set<char>> keypad = {
    {'2', {'a','b','c'} }, {'3', {'d','e','f'} }, {'4', {'g','h','i'} },
    {'5', {'j','k','l'} }, {'6', {'m','n','o'} }, {'7', {'p','q','r','s'} },
    {'8', {'t','u','v'} }, {'9', {'w','x','y','z'} } };


/* The predict helper function takes in a string of digits, a set of strings of suggestions, and a lexicon
 * to explore all the possible letter sequences formed by the tapped digits, storing those sequences
 * that are actual English words in a set of suggestions. */
void predict(string soFar, string digits, Set<string>& suggestions, Lexicon& lex){
    if (digits.length() == 0) {
        if (lex.contains(soFar)){
            suggestions.add(soFar);
        }
    }

    if (!lex.containsPrefix(soFar)) {
        return;
    }

    Set<char> firstValue = keypad[digits[0]];
    for (char ch : firstValue){
       predict(soFar + ch, digits.substr(1), suggestions, lex);

    }
}

/* The predict wrapper function takes in a string of digits, a set of strings of suggested words, and a lexicon.
 * It also calls the helper function, which takes in an empty string soFar, a string of digits, and set of strings
 * of suggestions, and a lexicon. */
void predict(string digits, Set<string>& suggestions, Lexicon& lex) {
    predict("", digits, suggestions, lex);
}



/* Test helper function to return shared copy of Lexicon. Use to
 * avoid (expensive) re-load of word list on each test case. */
static Lexicon& sharedLexicon() {
    static Lexicon lex("res/EnglishWords.txt");
    return lex;
}

/* * * * * * Test Cases * * * * * */

STUDENT_TEST("Predict intended words for digit sequence 22556667") {
    string digits = "22556667";
    Set<string> expected = {"balloons"};
    Set<string> suggestions;

    predict(digits, suggestions, sharedLexicon());
    EXPECT_EQUAL(suggestions, expected);
}


STUDENT_TEST("Predict intended words for digit sequence 8378464") {
    string digits = "8378464";
    Set<string> expected = {"testing", "vesting"};
    Set<string> suggestions;

    predict(digits, suggestions, sharedLexicon());
    EXPECT_EQUAL(suggestions, expected);
}


PROVIDED_TEST("Predict intended words for digit sequence 6263, example from writeup") {
    string digits = "6263";
    Set<string> expected = {"name", "mane", "oboe"};
    Set<string> suggestions;

    predict(digits, suggestions, sharedLexicon());
    EXPECT_EQUAL(suggestions, expected);
}

PROVIDED_TEST("What words can I spell from my phone number?") {
    string digits = "3228679";  // my old phone number :-)
    Set<string> expected = {"factory"};
    Set<string> suggestions;

    predict(digits, suggestions, sharedLexicon());
    EXPECT_EQUAL(suggestions, expected);
}
