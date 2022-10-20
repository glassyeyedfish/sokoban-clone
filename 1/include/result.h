#ifndef RESULT_H
#define RESULT_H

/*
 * Result type inspired by the Rust programming language
 */

typedef enum { 
        RESULT_VOID,
        RESULT_INT, 
        RESULT_ERROR
} result_e;

typedef union {
        int i;
} result_ok_t;

typedef struct {
        result_e result;
        result_ok_t ok;
        char* err;
} result_t;

typedef result_t result_void_t;
typedef result_t result_int_t;

#endif