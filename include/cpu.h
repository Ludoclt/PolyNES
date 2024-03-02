#ifndef CPU_H
#define CPU_H

#include <cstdint>

#define STACK_OFFSET 0x0100

class Bus;

class CPU
{
public:
    CPU(Bus *bus);

    struct Instruction
    {
        uint8_t (CPU::*operation)(void) = nullptr;
        uint8_t (CPU::*addrmode)(void) = nullptr;
        uint8_t cycles = 0;

        Instruction(uint8_t (CPU::*operation)(), uint8_t (CPU::*addrmode)(), uint8_t cycles) : operation(operation), addrmode(addrmode), cycles(cycles) {}
    };

    enum FLAGS
    {
        N = (1 << 7), // Negative
        V = (1 << 6), // Overflow
        U = (1 << 5), // Unused
        B = (1 << 4), // Break
        D = (1 << 3), // Decimal
        I = (1 << 2), // Interrupt Disable
        Z = (1 << 1), // Zero
        C = (1 << 0), // Carry
    };

    void onClock();

    // Interrupts
    void reset();
    void irq();
    void nmi();

    // Adressing Modes
    uint8_t ACC();
    uint8_t IMP();
    uint8_t IMM();
    uint8_t ZPG();
    uint8_t ZPX();
    uint8_t ZPY();
    uint8_t REL();
    uint8_t ABS();
    uint8_t ABX();
    uint8_t ABY();
    uint8_t IND();
    uint8_t IZX();
    uint8_t IZY();

    // Instructions https://en.wikibooks.org/wiki/6502_Assembly
    //              https://www.masswerk.at/6502/6502_instruction_set.html
    //              https://www.gladir.com/CODER/ASM6502/reference.htm
    // Load and Store
    uint8_t LXX(uint8_t &reg); // CUSTOM
    uint8_t LDA();
    uint8_t LDX();
    uint8_t LDY();
    uint8_t STA();
    uint8_t STX();
    uint8_t STY();

    // Arithmetic
    uint8_t ADCOp();
    uint8_t SBC();

    // Increment and Decrement
    uint8_t INC();
    uint8_t INX();
    uint8_t INY();
    uint8_t DEC();
    uint8_t DEX();
    uint8_t DEY();

    // Shift and Rotate
    uint8_t ASL();
    uint8_t LSR();
    uint8_t ROL();
    uint8_t ROR();

    // Logic
    uint8_t AND();
    uint8_t ORA();
    uint8_t EOR();

    // Compare and Test Bit
    void CXX(uint8_t &reg); // CUSTOM
    uint8_t CMP();
    uint8_t CPX();
    uint8_t CPY();
    uint8_t BIT();

    // Branch
    uint8_t BXX(FLAGS f, bool v); // CUSTOM
    uint8_t BCC();
    uint8_t BCS();
    uint8_t BNE();
    uint8_t BEQ();
    uint8_t BPL();
    uint8_t BMI();
    uint8_t BVC();
    uint8_t BVS();

    // Transfer
    uint8_t TXX(uint8_t &reg, uint8_t value); // CUSTOM
    uint8_t TAX();
    uint8_t TXA();
    uint8_t TAY();
    uint8_t TYA();
    uint8_t TSX();
    uint8_t TXS();

    // Stack
    uint8_t PHA();
    uint8_t PLA();
    uint8_t PHP();
    uint8_t PLP();

    // Subroutines and Jump
    uint8_t JMP();
    uint8_t JSR();
    uint8_t RTS();
    uint8_t RTI();

    // Set and Clear
    uint8_t CLC();
    uint8_t SEC();
    uint8_t CLD();
    uint8_t SED();
    uint8_t CLI();
    uint8_t SEI();
    uint8_t CLV();

    // Miscellaneous
    uint8_t BRK();
    uint8_t NOP();

    // catch illegal opcodes
    uint8_t XXX();

private:
    Bus *bus = nullptr;

    uint8_t accu = 0x00;
    uint8_t xReg = 0x00;
    uint8_t yReg = 0x00;
    uint16_t pc = 0x0000;
    uint8_t stackptr = 0xFD;
    uint8_t status = 0x00;

    uint8_t cycles = 0;
    uint8_t opcode = 0x00;
    uint16_t absAddr = 0x0000;
    uint16_t relAddr = 0x0000;
    uint8_t data = 0x00;

    Instruction instructionTable[256];

    uint8_t getFlag(FLAGS f);
    void setFlag(FLAGS f, bool v);
    void fetchData();
};

#endif