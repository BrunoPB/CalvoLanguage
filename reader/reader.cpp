#include "reader.h"

#include <fstream>
#include <vector>

vector<string> readFile(string fileName) {
    vector<string> code = {};
    ifstream file("./" + fileName);
    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            code.push_back(line);
        }
        file.close();
    } else {
        // throw "File not found.";
    }
    return code;
}

vector<lexer_rule> getLexerConfig() {
    ifstream file(LEXER_CONFIG_FILE);
    if (file.is_open()) {
        string line;
        vector<lexer_rule> rules = {};
        while (getline(file, line)) {
            if (line.length() < 1 || line[0] == '#') {
                continue;
            }
            line = treatLine(line);
            string lineRegex = "";
            string lineToken;
            int lineLength = line.length();
            for (int i = 0; i < lineLength; i++) {
                if (line[i] != '#') {
                    lineRegex += line[i];
                } else {
                    if (i < lineLength - 1) {
                        if (line[i + 1] != '#') {
                            i++;
                            lineRegex += line[i];
                        } else {
                            i += 2;
                            lineToken = line.substr(i, lineLength);
                            i = lineLength;
                        }
                    } else {
                        // throw "ERROR: Error in lexer configuration file";
                    }
                }
            }
            int tok_code = getTokenEnum(lineToken);
            lexer_rule token = make_tuple(lineRegex, tok_code);
            rules.push_back(token);
        }
        file.close();
        return rules;
    } else {
        return {};
        // throw "File not found.";
    }
}

inline string treatLine(string line) {
    bool quit = false;
    string treatingLine = line;
    while (!quit) {
        int index = treatingLine.find(" ");
        if (index >= 0) {
            treatingLine.replace(index, 1, "");
        } else {
            quit = true;
        }
    };
    return treatingLine;
}

inline int getTokenEnum(string s) {
    if (s == "commentstart") {
        return tok_comment_s;
    } else if (s == "commentend") {
        return tok_comment_e;
    } else if (s == "var") {
        return tok_var;
    } else if (s == "if") {
        return tok_if;
    } else if (s == "else") {
        return tok_else;
    } else if (s == "while") {
        return tok_while;
    } else if (s == ";") {
        return tok_semicolon;
    } else if (s == "{") {
        return tok_bracket_o;
    } else if (s == "}") {
        return tok_bracket_c;
    } else if (s == "(") {
        return tok_paren_o;
    } else if (s == ")") {
        return tok_paren_c;
    } else if (s == "=") {
        return tok_equal;
    } else if (s == "operator") {
        return tok_operator;
    } else if (s == "compare") {
        return tok_compare;
    } else if (s == "boolean") {
        return tok_boolean;
    } else if (s == "number") {
        return tok_number;
    } else if (s == "id") {
        return tok_id;
    } else {
        return tok_error;
    }
}