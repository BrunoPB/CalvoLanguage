#include <iostream>
#include <vector>

#include "lexer/lexer.h"
#include "shared/allincludes.h"

using std::cout;
using std::endl;
using std::string;
using std::vector;

int main(int argc, char *argv[]) {
    try {
        string fileName = argv[1];
        vector<token> tokens;
        tokens = getTokens(fileName);
    } catch (string error) {
        cout << "ERROR: " << error << endl;
    }
    return 0;
}