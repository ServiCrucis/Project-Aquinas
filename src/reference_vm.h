//
// Created by ServusDei on 1/29/2020.
//

#ifndef PROJECT_AQUINAS_REFERENCE_VM_H
#define PROJECT_AQUINAS_REFERENCE_VM_H

#include <stdint.h>

// binary CPU instruction (IR reference)
// purpose: to facilitate inter-module communication
enum CPU {
    EXECUTE,
    EXE = EXECUTE
};

// EXECUTE opcode format:
// EXECUTE MODULE OPERATION [INPUT_STACK] [OUTPUT_STACK]
// execute (GPU, ADD, [OPERAND_STACK_ADDRESS])
// short-hand syntax:
// GPU.ADD([operand_stack])
// if the GPU is device 0:
// MODULE[0].ADD([operand_buffer], [return_buffer])

// binary ALU instructions only (no ADD, SUB, MUL, DIV, etc.)
// purpose: binary arithmetic operations
enum ALU {
    OR,
    NOT,
    NOR = NOT + OR,
    AND,
    NAND = NOT + AND,
    XOR,
    XNOR = NOT + XOR,
    LSH,
    RSH,
};

// logical binary Mathematical Computation Unit
// purpose: performs common mathematical operations
enum MCU {
    // elementary arithmetic
    ADD,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    // common functions
    SQUARE_ROOT,
    SQRT = SQUARE_ROOT,
    CUBE_ROOT,
    CBRT = CUBE_ROOT,
    NTH_ROOT,
    ROOTN = NTH_ROOT,
    LOG,
    LOG10,
    LOGE,
    POWER, // x to the n power function
    RECIPROCAL, // reciprocal function
    RCP = RECIPROCAL,
    INTERPOLATE, // linear interpolation
    LERP = INTERPOLATE,
    N_FACTORIAL,
    FACTORIAL = N_FACTORIAL,
    NFACT = N_FACTORIAL,
    // trigonometric functions
    SINE,
    SIN = SINE,
    SINEN,
    SINN = SINEN,
    COSINE,
    COS = COSINE,
    COSINEN,
    COSN = COSINEN,
    TANGENT,
    TAN = TANGENT,
    TANGENTN,
    TANN = TANGENTN,
    SECANT,
    SEC = SECANT,
    SECANTN,
    SECN = SECANTN,
    COSECANT,
    CSC = COSECANT,
    COSECANTN,
    CSCN = COSECANTN,
    COTANGENT,
    COT = COTANGENT,
    COTANGENTN,
    COTN = COTANGENTN,
    TO_RADIANS,
    TO_DEGREES,
    // calculus
    DIFFERENTIATE,
    INTEGRATE

};

// binary GPU instructions only
// purpose: image-specific computations
enum GPU {
    TRANSFORM,
    ROTATE,
};

// logical binary array module instructions
// purpose: state storage module
enum ARRAY {
    GET,
    SET
};

//logical binary stack module instructions
enum STACK {
    PUSH,
    POP
};

#endif //PROJECT_AQUINAS_REFERENCE_VM_H
