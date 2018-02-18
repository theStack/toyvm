//
// Created by Stefan on 17.02.2018.
//

#ifndef HUNGERBYTE_EMU_H
#define HUNGERBYTE_EMU_H

#include <cstdint>

#define PC_START 0x0100
#define SP_START 0xEEEE
#define MEM_SIZE 0x10000
#define REG_SIZE 16

#define SB 0xC
#define SR 0xD
#define SP 0xE
#define PC 0xF

// denotes a single word
typedef uint16_t word_t;
typedef int16_t sword_t;

// status reg
typedef struct {
    word_t rem_bits :12;
    word_t c :1; // carry bit
    word_t z :1; // zero bit
    word_t n :1; // negative bit
    word_t v :1; // overflow bit
} status_reg_t;

// dual operand instruction

#define IS_DUAL_IS(IS) ((IS) & 0x8000)

enum class Dual_OPC : uint8_t {
    MOV, ADD, SUB, MUL, AND, OR, XOR, SHR
};
typedef struct {
    word_t src :4;
    word_t dst :4;
    word_t as  :2;
    word_t ad  :2;
    word_t opc :3;
    word_t id  :1;
} dual_instr_layout_t;

// branch instruction

#define IS_BRANCH_IS(IS) (((IS) & 0xC000) == 0x4000)

enum class Branch_OPC : uint8_t {
    JMP, JN, JGE, JL, JNE, JEQ, JNC, JC
};
typedef struct {
    word_t offset      :10;
    word_t v           :1;
    word_t condition   :3;
    word_t id          :2;
} branch_instr_layout_t;

// single operand instruction

#define IS_SINGLE_IS(IS) (((IS) & 0xC000) == 0x0000)

enum class Single_OPC : uint8_t {
    HLT, PUSH, POP, CALL, RET, //Stack operations
    INC, DEC,
    INV, TST, SHR, SHL,
    OUT, IN,
};
typedef struct {
    word_t src  :4;
    word_t as   :2;
    word_t port :4;
    word_t opc  :4;
    word_t id   :2;
} single_instr_layout_t;
#endif //HUNGERBYTE_EMU_H
