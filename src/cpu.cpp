#include "cpu.h"

#include "bus.h"

CPU::CPU(Bus *bus) : bus(bus), instructionTable{
                                   {&CPU::BRK, &CPU::IMM, 7},
                                   {&CPU::ORA, &CPU::IZX, 6},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::NOP, &CPU::IMP, 3},
                                   {&CPU::ORA, &CPU::ZPG, 3},
                                   {&CPU::ASL, &CPU::ZPG, 5},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::PHP, &CPU::IMP, 3},
                                   {&CPU::ORA, &CPU::IMM, 2},
                                   {&CPU::ASL, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::ORA, &CPU::ABS, 4},
                                   {&CPU::ASL, &CPU::ABS, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::BPL, &CPU::REL, 2},
                                   {&CPU::ORA, &CPU::IZY, 5},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::ORA, &CPU::ZPX, 4},
                                   {&CPU::ASL, &CPU::ZPX, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::CLC, &CPU::IMP, 2},
                                   {&CPU::ORA, &CPU::ABY, 4},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::ORA, &CPU::ABX, 4},
                                   {&CPU::ASL, &CPU::ABX, 7},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::JSR, &CPU::ABS, 6},
                                   {&CPU::AND, &CPU::IZX, 6},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::BIT, &CPU::ZPG, 3},
                                   {&CPU::AND, &CPU::ZPG, 3},
                                   {&CPU::ROL, &CPU::ZPG, 5},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::PLP, &CPU::IMP, 4},
                                   {&CPU::AND, &CPU::IMM, 2},
                                   {&CPU::ROL, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::BIT, &CPU::ABS, 4},
                                   {&CPU::AND, &CPU::ABS, 4},
                                   {&CPU::ROL, &CPU::ABS, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::BMI, &CPU::REL, 2},
                                   {&CPU::AND, &CPU::IZY, 5},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::AND, &CPU::ZPX, 4},
                                   {&CPU::ROL, &CPU::ZPX, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::SEC, &CPU::IMP, 2},
                                   {&CPU::AND, &CPU::ABY, 4},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::AND, &CPU::ABX, 4},
                                   {&CPU::ROL, &CPU::ABX, 7},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::RTI, &CPU::IMP, 6},
                                   {&CPU::EOR, &CPU::IZX, 6},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::NOP, &CPU::IMP, 3},
                                   {&CPU::EOR, &CPU::ZPG, 3},
                                   {&CPU::LSR, &CPU::ZPG, 5},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::PHA, &CPU::IMP, 3},
                                   {&CPU::EOR, &CPU::IMM, 2},
                                   {&CPU::LSR, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::JMP, &CPU::ABS, 3},
                                   {&CPU::EOR, &CPU::ABS, 4},
                                   {&CPU::LSR, &CPU::ABS, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::BVC, &CPU::REL, 2},
                                   {&CPU::EOR, &CPU::IZY, 5},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::EOR, &CPU::ZPX, 4},
                                   {&CPU::LSR, &CPU::ZPX, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::CLI, &CPU::IMP, 2},
                                   {&CPU::EOR, &CPU::ABY, 4},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::EOR, &CPU::ABX, 4},
                                   {&CPU::LSR, &CPU::ABX, 7},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::RTS, &CPU::IMP, 6},
                                   {&CPU::ADCOp, &CPU::IZX, 6},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::NOP, &CPU::IMP, 3},
                                   {&CPU::ADCOp, &CPU::ZPG, 3},
                                   {&CPU::ROR, &CPU::ZPG, 5},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::PLA, &CPU::IMP, 4},
                                   {&CPU::ADCOp, &CPU::IMM, 2},
                                   {&CPU::ROR, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::JMP, &CPU::IND, 5},
                                   {&CPU::ADCOp, &CPU::ABS, 4},
                                   {&CPU::ROR, &CPU::ABS, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::BVS, &CPU::REL, 2},
                                   {&CPU::ADCOp, &CPU::IZY, 5},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::ADCOp, &CPU::ZPX, 4},
                                   {&CPU::ROR, &CPU::ZPX, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::SEI, &CPU::IMP, 2},
                                   {&CPU::ADCOp, &CPU::ABY, 4},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::ADCOp, &CPU::ABX, 4},
                                   {&CPU::ROR, &CPU::ABX, 7},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::STA, &CPU::IZX, 6},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::STY, &CPU::ZPG, 3},
                                   {&CPU::STA, &CPU::ZPG, 3},
                                   {&CPU::STX, &CPU::ZPG, 3},
                                   {&CPU::XXX, &CPU::IMP, 3},
                                   {&CPU::DEY, &CPU::IMP, 2},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::TXA, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::STY, &CPU::ABS, 4},
                                   {&CPU::STA, &CPU::ABS, 4},
                                   {&CPU::STX, &CPU::ABS, 4},
                                   {&CPU::XXX, &CPU::IMP, 4},
                                   {&CPU::BCC, &CPU::REL, 2},
                                   {&CPU::STA, &CPU::IZY, 6},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::STY, &CPU::ZPX, 4},
                                   {&CPU::STA, &CPU::ZPX, 4},
                                   {&CPU::STX, &CPU::ZPY, 4},
                                   {&CPU::XXX, &CPU::IMP, 4},
                                   {&CPU::TYA, &CPU::IMP, 2},
                                   {&CPU::STA, &CPU::ABY, 5},
                                   {&CPU::TXS, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::NOP, &CPU::IMP, 5},
                                   {&CPU::STA, &CPU::ABX, 5},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::LDY, &CPU::IMM, 2},
                                   {&CPU::LDA, &CPU::IZX, 6},
                                   {&CPU::LDX, &CPU::IMM, 2},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::LDY, &CPU::ZPG, 3},
                                   {&CPU::LDA, &CPU::ZPG, 3},
                                   {&CPU::LDX, &CPU::ZPG, 3},
                                   {&CPU::XXX, &CPU::IMP, 3},
                                   {&CPU::TAY, &CPU::IMP, 2},
                                   {&CPU::LDA, &CPU::IMM, 2},
                                   {&CPU::TAX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::LDY, &CPU::ABS, 4},
                                   {&CPU::LDA, &CPU::ABS, 4},
                                   {&CPU::LDX, &CPU::ABS, 4},
                                   {&CPU::XXX, &CPU::IMP, 4},
                                   {&CPU::BCS, &CPU::REL, 2},
                                   {&CPU::LDA, &CPU::IZY, 5},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::LDY, &CPU::ZPX, 4},
                                   {&CPU::LDA, &CPU::ZPX, 4},
                                   {&CPU::LDX, &CPU::ZPY, 4},
                                   {&CPU::XXX, &CPU::IMP, 4},
                                   {&CPU::CLV, &CPU::IMP, 2},
                                   {&CPU::LDA, &CPU::ABY, 4},
                                   {&CPU::TSX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 4},
                                   {&CPU::LDY, &CPU::ABX, 4},
                                   {&CPU::LDA, &CPU::ABX, 4},
                                   {&CPU::LDX, &CPU::ABY, 4},
                                   {&CPU::XXX, &CPU::IMP, 4},
                                   {&CPU::CPY, &CPU::IMM, 2},
                                   {&CPU::CMP, &CPU::IZX, 6},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::CPY, &CPU::ZPG, 3},
                                   {&CPU::CMP, &CPU::ZPG, 3},
                                   {&CPU::DEC, &CPU::ZPG, 5},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::INY, &CPU::IMP, 2},
                                   {&CPU::CMP, &CPU::IMM, 2},
                                   {&CPU::DEX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::CPY, &CPU::ABS, 4},
                                   {&CPU::CMP, &CPU::ABS, 4},
                                   {&CPU::DEC, &CPU::ABS, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::BNE, &CPU::REL, 2},
                                   {&CPU::CMP, &CPU::IZY, 5},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::CMP, &CPU::ZPX, 4},
                                   {&CPU::DEC, &CPU::ZPX, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::CLD, &CPU::IMP, 2},
                                   {&CPU::CMP, &CPU::ABY, 4},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::CMP, &CPU::ABX, 4},
                                   {&CPU::DEC, &CPU::ABX, 7},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::CPX, &CPU::IMM, 2},
                                   {&CPU::SBC, &CPU::IZX, 6},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::CPX, &CPU::ZPG, 3},
                                   {&CPU::SBC, &CPU::ZPG, 3},
                                   {&CPU::INC, &CPU::ZPG, 5},
                                   {&CPU::XXX, &CPU::IMP, 5},
                                   {&CPU::INX, &CPU::IMP, 2},
                                   {&CPU::SBC, &CPU::IMM, 2},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::SBC, &CPU::IMP, 2},
                                   {&CPU::CPX, &CPU::ABS, 4},
                                   {&CPU::SBC, &CPU::ABS, 4},
                                   {&CPU::INC, &CPU::ABS, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::BEQ, &CPU::REL, 2},
                                   {&CPU::SBC, &CPU::IZY, 5},
                                   {&CPU::XXX, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 8},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::SBC, &CPU::ZPX, 4},
                                   {&CPU::INC, &CPU::ZPX, 6},
                                   {&CPU::XXX, &CPU::IMP, 6},
                                   {&CPU::SED, &CPU::IMP, 2},
                                   {&CPU::SBC, &CPU::ABY, 4},
                                   {&CPU::NOP, &CPU::IMP, 2},
                                   {&CPU::XXX, &CPU::IMP, 7},
                                   {&CPU::NOP, &CPU::IMP, 4},
                                   {&CPU::SBC, &CPU::ABX, 4},
                                   {&CPU::INC, &CPU::ABX, 7},
                                   {&CPU::XXX, &CPU::IMP, 7}}
{
}

uint8_t CPU::getFlag(FLAGS f)
{
    return (status & f) > 0;
}

void CPU::setFlag(FLAGS f, bool v)
{
    v ? status |= f : status &= ~f;
}

void CPU::fetchData()
{
    if (instructionTable[opcode].addrmode != &CPU::IMP)
        data = bus->read(absAddr);
}

void CPU::onClock()
{
    if (cycles == 0)
    {
        opcode = bus->read(pc);
        pc++;
        cycles = instructionTable[opcode].cycles + ((this->*instructionTable[opcode].addrmode)() & (this->*instructionTable[opcode].operation)());
    }
    cycles--;
}

// Interrupts

void CPU::reset()
{
    accu = 0;
    xReg = 0;
    yReg = 0;
    stackptr = 0xFD;
    status = 0x00 | U;
    absAddr = 0xFFFC;
    uint16_t lo = bus->read(absAddr);
    uint16_t hi = bus->read(absAddr + 1);
    pc = (hi << 8) | lo;
    relAddr = 0x0000;
    absAddr = 0x0000;
    data = 0x00;

    cycles = 8;
}

void CPU::irq()
{
    if (getFlag(I) == 0)
    {
        bus->write(STACK_OFFSET + stackptr, (pc >> 8) & 0x00FF);
        stackptr--;
        bus->write(STACK_OFFSET + stackptr, pc & 0x00FF);
        stackptr--;

        setFlag(B, 0);
        setFlag(U, 1);
        setFlag(I, 1);
        bus->write(STACK_OFFSET + stackptr, status);
        stackptr--;

        absAddr = 0xFFFE;
        uint16_t lo = bus->read(absAddr);
        uint16_t hi = bus->read(absAddr + 1);
        pc = (hi << 8) | lo;

        cycles = 7;
    }
}

void CPU::nmi()
{
    bus->write(STACK_OFFSET + stackptr, (pc >> 8) & 0x00FF);
    stackptr--;
    bus->write(STACK_OFFSET + stackptr, pc & 0x00FF);
    stackptr--;

    setFlag(B, 0);
    setFlag(U, 1);
    setFlag(I, 1);
    bus->write(STACK_OFFSET + stackptr, status);
    stackptr--;

    absAddr = 0xFFFA;
    uint16_t lo = bus->read(absAddr);
    uint16_t hi = bus->read(absAddr + 1);
    pc = (hi << 8) | lo;

    cycles = 8;
}

// Adressing Modes

uint8_t CPU::IMP()
{
    data = accu;
    return 0;
}

uint8_t CPU::IMM()
{
    absAddr = pc++;
    return 0;
}

uint8_t CPU::ZPG()
{
    absAddr = bus->read(pc);
    pc++;
    absAddr &= 0xFF;
    return 0;
}

uint8_t CPU::ZPX()
{
    absAddr = bus->read(pc) + xReg;
    pc++;
    absAddr &= 0xFF;
    return 0;
}

uint8_t CPU::ZPY()
{
    absAddr = bus->read(pc) + yReg;
    pc++;
    absAddr &= 0xFF;
    return 0;
}

uint8_t CPU::ABS()
{
    uint16_t lo = bus->read(pc);
    pc++;
    uint16_t hi = bus->read(pc);
    pc++;
    absAddr = (hi << 8) | lo;
    return 0;
}

uint8_t CPU::ABX()
{
    uint16_t lo = bus->read(pc);
    pc++;
    uint16_t hi = bus->read(pc);
    pc++;
    absAddr = (hi << 8) | lo;
    absAddr += xReg;
    return (absAddr & 0xFF00) != (hi << 8) ? 1 : 0;
}

uint8_t CPU::ABY()
{
    uint16_t lo = bus->read(pc);
    pc++;
    uint16_t hi = bus->read(pc);
    pc++;
    absAddr = (hi << 8) | lo;
    absAddr += yReg;
    return (absAddr & 0xFF00) != (hi << 8) ? 1 : 0;
}

uint8_t CPU::IND()
{
    uint16_t ptr_lo = bus->read(pc);
    pc++;
    uint16_t ptr_hi = bus->read(pc);
    pc++;
    uint16_t ptr = (ptr_hi << 8) | ptr_lo;
    if (ptr_lo == 0xFF) // Simulate page boundary hardware bug
    {
        absAddr = (bus->read(ptr & 0xFF00) << 8) | bus->read(ptr + 0);
    }
    else // Behave normally
    {
        absAddr = (bus->read(ptr + 1) << 8) | bus->read(ptr + 0);
    }
    return 0;
}

uint8_t CPU::IZX()
{
    uint16_t t = bus->read(pc);
    pc++;
    uint16_t lo = bus->read((uint16_t)(t + (uint16_t)xReg) & 0xFF);
    uint16_t hi = bus->read((uint16_t)(t + (uint16_t)xReg + 1) & 0xFF);
    absAddr = (hi << 8) | lo;
    return 0;
}

uint8_t CPU::IZY()
{
    uint16_t t = bus->read(pc);
    pc++;
    uint16_t lo = bus->read(t & 0xFF);
    uint16_t hi = bus->read((t + 1) & 0xFF);
    absAddr = (hi << 8) | lo;
    absAddr += yReg;
    return (absAddr & 0xFF00) != (hi << 8);
}

uint8_t CPU::REL()
{
    relAddr = bus->read(pc);
    pc++;
    if (relAddr & 0x80)
        relAddr |= 0xFF00;
    return 0;
}

// Instructions

// Load and Store

uint8_t CPU::LXX(uint8_t &reg)
{
    fetchData();
    reg = data;
    setFlag(N, reg & 0x80);
    setFlag(Z, reg == 0x00);
    return 1;
}

uint8_t CPU::LDA()
{
    return LXX(accu);
}

uint8_t CPU::LDX()
{
    return LXX(xReg);
}

uint8_t CPU::LDY()
{
    return LXX(yReg);
}

uint8_t CPU::STA()
{
    bus->write(absAddr, accu);
    return 0;
}

uint8_t CPU::STX()
{
    bus->write(absAddr, xReg);
    return 0;
}

uint8_t CPU::STY()
{
    bus->write(absAddr, yReg);
    return 0;
}

// Arithmetic

uint8_t CPU::ADCOp()
{
    fetchData();
    uint16_t result = (uint16_t)accu + (uint16_t)data + (uint16_t)getFlag(C);
    setFlag(C, result > 255);
    setFlag(Z, (result & 0xFF) == 0);
    setFlag(N, result & 0x80);
    setFlag(V, (~((uint16_t)accu ^ (uint16_t)data) & ((uint16_t)accu ^ (uint16_t)result)) & 0x80);
    accu = result & 0xFF;
    return 1;
}

uint8_t CPU::SBC()
{
    fetchData();
    uint16_t value = ((uint16_t)data) ^ 0xFF;
    uint16_t result = (uint16_t)accu + value + (uint16_t)getFlag(C);
    setFlag(C, result & 0xFF00);
    setFlag(Z, ((result & 0xFF) == 0));
    setFlag(V, (result ^ (uint16_t)accu) & (result ^ value) & 0x80);
    setFlag(N, result & 0x80);
    accu = result & 0xFF;
    return 1;
}

// Increment and Decrement

uint8_t CPU::INC()
{
    fetchData();
    data++;
    setFlag(N, data & 0x80);
    setFlag(Z, data == 0x00);
    bus->write(absAddr, data);
    return 0;
}

uint8_t CPU::INX()
{
    xReg++;
    setFlag(N, xReg & 0x80);
    setFlag(Z, xReg == 0x00);
    return 0;
}

uint8_t CPU::INY()
{
    yReg++;
    setFlag(N, yReg & 0x80);
    setFlag(Z, yReg == 0x00);
    return 0;
}

uint8_t CPU::DEC()
{
    fetchData();
    data--;
    setFlag(N, data & 0x80);
    setFlag(Z, data == 0x00);
    bus->write(absAddr, data);
    return 0;
}

uint8_t CPU::DEX()
{
    xReg--;
    setFlag(N, xReg & 0x80);
    setFlag(Z, xReg == 0x00);
    return 0;
}

uint8_t CPU::DEY()
{
    yReg--;
    setFlag(N, yReg & 0x80);
    setFlag(Z, yReg == 0x00);
    return 0;
}

// Shift and Rotate

uint8_t CPU::ASL()
{
    fetchData();
    uint16_t result = (uint16_t)data << 1;
    setFlag(C, (result & 0xFF00) > 0);
    setFlag(N, result & 0x80);
    setFlag(Z, (result & 0xFF) == 0x00);
    if (instructionTable[opcode].addrmode == &CPU::IMP)
        accu = result & 0xFF;
    else
        bus->write(absAddr, result & 0xFF);
    return 0;
}

uint8_t CPU::LSR()
{
    fetchData();
    setFlag(C, data & 0x01);
    uint8_t result = data >> 1;
    setFlag(N, result & 0x80);
    setFlag(Z, result == 0x00);
    if (instructionTable[opcode].addrmode == &CPU::IMP)
        accu = result;
    else
        bus->write(absAddr, result);
    return 0;
}

uint8_t CPU::ROL()
{
    fetchData();
    uint16_t result = (uint16_t)(data << 1) | getFlag(C);
    setFlag(C, result & 0xFF00);
    setFlag(Z, (result & 0xFF) == 0x00);
    setFlag(N, result & 0x80);
    if (instructionTable[opcode].addrmode == &CPU::IMP)
        accu = result & 0xFF;
    else
        bus->write(absAddr, result & 0xFF);
    return 0;
}

uint8_t CPU::ROR()
{
    fetchData();
    uint16_t result = (uint16_t)(getFlag(C) << 7) | (data >> 1);
    setFlag(C, data & 0x01);
    setFlag(Z, (result & 0xFF) == 0x00);
    setFlag(N, result & 0x80);
    if (instructionTable[opcode].addrmode == &CPU::IMP)
        accu = result & 0xFF;
    else
        bus->write(absAddr, result & 0xFF);
    return 0;
}

// Logic

uint8_t CPU::AND()
{
    fetchData();
    accu &= data;
    setFlag(Z, accu == 0x00);
    setFlag(N, accu & 0x80);
    return 1;
}

uint8_t CPU::ORA()
{
    fetchData();
    accu |= data;
    setFlag(N, accu & 0x80);
    setFlag(Z, accu == 0x00);
    return 1;
}

uint8_t CPU::EOR()
{
    fetchData();
    accu ^= data;
    setFlag(N, accu & 0x80);
    setFlag(Z, accu == 0x00);
    return 1;
}

// Compare and Test Bit

void CPU::CXX(uint8_t &reg)
{
    fetchData();
    uint16_t result = (uint16_t)reg - (uint16_t)data;
    setFlag(N, result & 0x80);
    setFlag(Z, (result & 0xFF) == 0x00);
    setFlag(C, reg >= data);
}

uint8_t CPU::CMP()
{
    CXX(accu);
    return 1;
}

uint8_t CPU::CPX()
{
    CXX(xReg);
    return 0;
}

uint8_t CPU::CPY()
{
    CXX(yReg);
    return 0;
}

uint8_t CPU::BIT()
{
    fetchData();
    uint8_t result = accu & data;
    setFlag(N, data & (1 << 7));
    setFlag(V, data & (1 << 6));
    setFlag(Z, result == 0x00);
    return 0;
}

// Branch

uint8_t CPU::BXX(FLAGS f, bool v)
{
    if (getFlag(f) == v)
    {
        cycles++;
        absAddr = pc + relAddr;
        if ((absAddr & 0xFF00) != (pc & 0xFF00))
            cycles++;
        pc = absAddr;
    }
    return 0;
}

uint8_t CPU::BCC()
{
    return BXX(C, false);
}

uint8_t CPU::BCS()
{
    return BXX(C, true);
}

uint8_t CPU::BNE()
{
    return BXX(Z, false);
}

uint8_t CPU::BEQ()
{
    return BXX(Z, true);
}

uint8_t CPU::BPL()
{
    return BXX(N, false);
}

uint8_t CPU::BMI()
{
    return BXX(N, true);
}

uint8_t CPU::BVC()
{
    return BXX(V, false);
}

uint8_t CPU::BVS()
{
    return BXX(V, true);
}

// Transfer

uint8_t CPU::TXX(uint8_t &reg, uint8_t value)
{
    reg = value;
    setFlag(N, reg & 0x80);
    setFlag(Z, reg == 0x00);
    return 0;
}

uint8_t CPU::TAX()
{
    return TXX(xReg, accu);
}

uint8_t CPU::TXA()
{
    return TXX(accu, xReg);
}

uint8_t CPU::TAY()
{
    return TXX(yReg, accu);
}

uint8_t CPU::TYA()
{
    return TXX(accu, yReg);
}

uint8_t CPU::TSX()
{
    return TXX(xReg, stackptr);
}

uint8_t CPU::TXS()
{
    stackptr = xReg;
    return 0;
}

// Stack

uint8_t CPU::PHA()
{
    bus->write(STACK_OFFSET + stackptr, accu);
    stackptr--;
    return 0;
}

uint8_t CPU::PLA()
{
    stackptr++;
    accu = bus->read(STACK_OFFSET + stackptr);
    setFlag(Z, accu == 0x00);
    setFlag(N, accu & 0x80);
    return 0;
}

uint8_t CPU::PHP()
{
    bus->write(STACK_OFFSET + stackptr, status | B | U);
    setFlag(B, 0);
    setFlag(U, 0);
    stackptr--;
    return 0;
}

uint8_t CPU::PLP()
{
    stackptr++;
    status = bus->read(STACK_OFFSET + stackptr);
    setFlag(U, 1);
    return 0;
}

// Subroutines and Jump

uint8_t CPU::JMP()
{
    pc = absAddr;
    return 0;
}

uint8_t CPU::JSR()
{
    pc--;
    bus->write(STACK_OFFSET + stackptr, (pc >> 8) & 0xFF);
    stackptr--;
    bus->write(STACK_OFFSET + stackptr, pc & 0xFF);
    stackptr--;
    pc = absAddr;
    return 0;
}

uint8_t CPU::RTS()
{
    stackptr++;
    pc = (uint16_t)bus->read(STACK_OFFSET + stackptr);
    stackptr++;
    pc |= (uint16_t)bus->read(STACK_OFFSET + stackptr) << 8;
    pc++;
    return 0;
}

uint8_t CPU::RTI()
{
    stackptr++;
    status = bus->read(STACK_OFFSET + stackptr);
    status &= ~B;
    status &= ~U;

    stackptr++;
    pc = (uint16_t)bus->read(STACK_OFFSET + stackptr);
    stackptr++;
    pc |= (uint16_t)bus->read(STACK_OFFSET + stackptr) << 8;
    return 0;
}

// Set and Clear

uint8_t CPU::CLC()
{
    setFlag(C, 0);
    return 0;
}

uint8_t CPU::SEC()
{
    setFlag(C, 1);
    return 0;
}

uint8_t CPU::CLD()
{
    setFlag(D, 0);
    return 0;
}

uint8_t CPU::SED()
{
    setFlag(D, 1);
    return 0;
}

uint8_t CPU::CLI()
{
    setFlag(I, 0);
    return 0;
}

uint8_t CPU::SEI()
{
    setFlag(I, 1);
    return 0;
}

uint8_t CPU::CLV()
{
    setFlag(V, 0);
    return 0;
}

// Miscellaneous

uint8_t CPU::BRK()
{
    pc++;

    setFlag(I, 1);
    bus->write(STACK_OFFSET + stackptr, (pc >> 8) & 0xFF);
    stackptr--;
    bus->write(STACK_OFFSET + stackptr, pc & 0xFF);
    stackptr--;

    setFlag(B, 1);
    bus->write(STACK_OFFSET + stackptr, status);
    stackptr--;
    setFlag(B, 0);

    pc = (uint16_t)bus->read(0xFFFE) | ((uint16_t)bus->read(0xFFFF) << 8);
    return 0;
}

uint8_t CPU::NOP()
{
    if (opcode == 0xFC)
        return 1;
    return 0;
}

uint8_t CPU::XXX()
{
    return 0;
}