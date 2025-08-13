#include "console.h"
#include "backtracking.h"
#include "SimpleTest.h"
#include <iostream>
using namespace std;

/*
 * You are free to edit the main in any way that works
 * for your testing/debugging purposes.
 * We will supply our own main() during grading
 */

int main() {
    if (runSimpleTests(SELECTED_TESTS)) {
        return 0;
    }
    cout << endl << "main() completed." << endl;
    return 0;
}

// Do not remove or edit below this line. It is here to confirm that your code
// conforms to the expected function prototypes needed for grading
void confirmFunctionPrototypes() {
    string str;
    Set<string> s;
    Lexicon lex;
    predict(str, s, lex);

    Vector<blockT> b = {{"A", 10}};
    Map<string,int> m = computePowerIndexes(b);

    Grid<int> pg;
    canRedistrict(pg, 1);
}
