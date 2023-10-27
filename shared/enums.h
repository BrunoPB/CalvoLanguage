#ifndef ENUMS_H
#define ENUMS_H

enum Token {
    // Error
    tok_error = 0,

    // Comments
    tok_comment_s = -1,
    tok_comment_e = -2,

    // Keywords
    tok_var = -3,
    tok_if = -4,
    tok_else = -5,
    tok_while = -6,

    // Special Chars
    tok_semicolon = -7,
    tok_bracket_o = -8,
    tok_bracket_c = -9,
    tok_paren_o = -10,
    tok_paren_c = -11,
    tok_equal = -12,

    // Operators
    tok_operator = -13,
    tok_compare = -14,
    tok_boolean = -15,

    // Values
    tok_number = -16,

    // Ids
    tok_id = -17,
};

#endif