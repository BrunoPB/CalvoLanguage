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
    tok_var = -6,
    tok_while = -7,

    // Special Chars
    tok_bracket_o = -8,
    tok_bracket_c = -9,
    tok_paren_o = -10,
    tok_paren_c = -11,
    tok_semicolon = -12,
    tok_equal = -13,

    // Operators
    tok_compare = -14,
    tok_boolean = -15,
    tok_operator = -16,

    // Values
    tok_number = -17,

    // Ids
    tok_id = -18,
};

enum NonTerminals {
    nt_S = 0,
    nt_CODE = 1,
    nt_DECLARATION = 2,
    nt_ATRIB = 3,
    nt_EXPRESSION = 4,
    nt_OPERATION = 5,
    nt_BOOL = 6,
    nt_BOOLOP = 7,
    nt_COND = 8,
    nt_ELSE = 9,
    nt_REP = 10,
    nt_CALL = 11,
    nt_PARAM = 12
};

#endif