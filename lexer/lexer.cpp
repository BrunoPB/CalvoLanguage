#include "lexer.h"

#include <iostream>
#include <regex>
#include <vector>

#include "../reader/reader.h"

vector<token> getTokens(string fileName) {
    // try {
    vector<string> fileLines = readFile(fileName);
    vector<lexer_rule> rules = getLexerConfig();
    vector<token> tokens = {};
    for (auto line : fileLines) {
        vector<token> line_tokens = tokenize(line, rules);
        tokens.insert(tokens.begin() + tokens.size(),
                      line_tokens.begin(),
                      line_tokens.begin() + line_tokens.size());
    }
    return tokens;
    //} catch (string error) {
    // throw error;
    //}
}

vector<token> tokenize(string code, vector<lexer_rule> rules) {
    vector<token> tokens = {};
    static bool inComment = false;
    for (int i = 0; i < code.size(); i++) {
        // Building lexeme
        string lexeme = code.substr(i, 1);

        if (isEmptySpace(lexeme[0])) {
            continue;
        }

        if (!inComment && !matchAnyRule(lexeme, rules)) {
            // throw "UNKNOWN LEXEME: " + lexeme;
        }

        // Getting largest sequence possible using lookahead

        bool lookaheaded = false;
        while (matchAnyRule(lexeme, rules) && i < code.length() - 1) {
            lookaheaded = true;
            i++;
            string c = code.substr(i, 1);
            lexeme += c;

            if (isEmptySpace(c[0])) {
                break;
            }
        }
        if (lookaheaded && !matchAnyRule(lexeme, rules)) {
            lexeme = lexeme.substr(0, lexeme.length() - 1);
            i--;
        }
        int cur_token = matchToken(lexeme, rules);
        if (cur_token == tok_comment_s) {
            inComment = true;
        } else if (cur_token == tok_comment_e) {
            if (inComment) {
                inComment = false;
            } else {
                // throw "ERROR IN LEXER: COMMENT ENDING WITHOUT STARTING.";
            }
        } else if (!inComment) {
            token t = make_tuple(cur_token, lexeme);
            tokens.push_back(t);
        }
    }
    return tokens;
}

bool isEmptySpace(char s) {
    if (s == ' ' || s == '\n' || s == '\0' || s == '\t') {
        return true;
    }
    return false;
}

bool matchAnyRule(string s, vector<lexer_rule> rules) {
    for (lexer_rule rule : rules) {
        regex re(get<0>(rule));
        if (regex_match(s, re) && get<1>(rule) != tok_error) {
            return true;
        }
    }
    return false;
}

int matchToken(string lexeme, vector<lexer_rule> rules) {
    for (lexer_rule rule : rules) {
        regex re(get<0>(rule));
        if (regex_match(lexeme, re)) {
            return get<1>(rule);
        }
    }
    return -1;
    // throw "UNKNOWN TOKEN: " + lexeme;
}