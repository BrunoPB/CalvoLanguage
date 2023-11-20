#ifndef ENUMS_H
#define ENUMS_H

enum Token {

    // Error
    tok_error = -1,

    // Comments
    tok_comment_s = -2,
    tok_comment_e = -3,

    // Keywords
    tok_if = -4,
    tok_else = -5,
    tok_while = -6,

    // Special Chars
    tok_bracket_o = -7,
    tok_bracket_c = -8,
    tok_paren_o = -9,
    tok_paren_c = -10,
    tok_semicolon = -11,
    tok_equal = -12,

    // Operators
    tok_compare = -13,
    tok_boolean = -14,
    tok_operator = -15,

    // Values
    tok_number = -16,

    // Ids
    tok_id = -17,
};

enum NonTerminals {
    nt_S = 0,
    nt_CODE = 1,
    nt_ATRIB = 2,
    nt_EXPRESSION = 3,
    nt_OPERATION = 4,
    nt_BOOL = 5,
    nt_BOOLOP = 6,
    nt_COND = 7,
    nt_ELSE = 8,
    nt_REP = 9,
    nt_CALL = 10,
    nt_PARAM = 11
};

#endif