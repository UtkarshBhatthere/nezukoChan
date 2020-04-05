#pragma once

#if 1
#include <iostream>
#include <cstdint>
#include <string>
#include <vector>
#include "Bus.h"

class cpu6502
{
public:
	// Registers
	uint8_t A = 0x00;		// Accumulator
	uint8_t X = 0x00;		// Index X register.
	uint8_t Y = 0x00;		// Index Y register.
	uint8_t SP = 0x00;		// Stack Pointer.
	uint8_t ST = 0x00;		// Status Register.
	uint16_t PC = 0x0000;	// Program Counter.

	// Status Flags
	enum flag {
		CAR = (1 << 0),		// Carry Flag.
		ZER = (1 << 1),		// Zero Flag.
		IRQ = (1 << 2),		// Interrupt Disable Flag.
		DEF = (1 << 3),		// Decimal Mode Flag.
		BRF = (1 << 4),		// Break Flag.
		UNU	= (1 << 5),		// Unused Flag (1).
		OVF = (1 << 6),		// Overflow Flag.
		NEG = (1 << 7)		// Negative Flag.
	};

	cpu6502(void);	// Constructor.

private:
	// Flag Getter-Setter Methods.
	void set_flag(flag, bool);
	bool get_flag(flag);

	// Necessary Variables.
	uint8_t	 operand;		// Fetched Data.
	uint8_t opcode;			// Fetched Opcode.
	uint16_t abs_addr;		// Absolute Address for Instruction.
	uint16_t rel_addr;		// Relative Address for Branched Instruction.
	uint8_t cycles;			// Clock cycles required for execution of current Instruction.
	uint32_t ticks;			// Global tick count.
	// Will Fill According to need.

public:
	// Bus Linkage
	Bus*	parentBus = nullptr;
	void	linkBus(Bus* bus);							// Connect the Bus to CPU.
	uint8_t cpuRead(uint16_t address);					// Internally reads from bus.
	void	cpuWrite(uint16_t address, uint8_t data);	// Internally write to bus.

	// Stack Operations
	void stack_push(uint8_t data);			// Pushes to Stack.
	uint8_t stack_pop(void);				// Pops from Stack.

	// Essential methods.
	void irq(void);			// Execute an Interrupt Routine.
	void reset(void);		// Resets the CPU.
	void nmi(void);			// Same as irq but cant be disabled.
	void tick(void);		// Execute one clock tick of the cpu.

private:
	uint8_t fetch(void);	// Fetches input from the memory.

	/*	Since Addressing Mode decides the selection of address for the operand    ** 
	**	It also decides whether the CPU will require additional cycles. Also if   **
	**	branching takes place then too the number of cycles required will get	  **
	**	increased thus using adtnl_cycles as bool we'll identify the respective	  **
	**	opcodes (using their addressing modes) and return if there's a need of	  **
	**	additional cycles for the processing.								   	  */

	using adtnl_cycles = bool;	// Additional Cycles required for the Execution.

	// Addressing Modes - Used to calculate the Address of the operand.
	adtnl_cycles IMP();	// Implied Addressing. Done.
	adtnl_cycles IMM();	// Immediate Addressing. Done.
	adtnl_cycles ZPA();	// Zero Page Addressing. Done.
	adtnl_cycles ZPX();	// Zero Page Addressing with X offset. Done.
	adtnl_cycles ZPY();	// Zero Page Addressing with Y offset. Done.
	adtnl_cycles ABS();	// Absolute Addressing. Done.
	adtnl_cycles ABX(); // Absolute Address with X offset. Done.
	adtnl_cycles ABY();	// Absolute Addressing with Y offset. Done.
	adtnl_cycles REL();	// Relative Addressing. Done.
	adtnl_cycles IAX();	// Indexed Indirect Addressing with X offset. Done.
	adtnl_cycles IAY(); // Indexed Indirect Addressing with Y offset. Done.
	adtnl_cycles IND(); // Absolute Indirect Addressing. Done.

	// Instruction Set - Implementation of the Opcodes.
	
	// Opcodes. Operations are on operands from memory (not mentioned individually).
	adtnl_cycles ADC();	// Add to Accumulator with carry.
	adtnl_cycles AND();	// Operate 'AND' with Accumulator.
	adtnl_cycles ASL();	// Shift leftwards (1 bit).

	adtnl_cycles BCC();	// Branch on carry clear.
	adtnl_cycles BCS();	// Branch on carry set.
	adtnl_cycles BEQ();	// Branch on result zero. (When comparison results in Equal Zero Flag is set.)
	adtnl_cycles BIT();	// Test Bits with Accumulator.
	adtnl_cycles BMI();	// Branch on negative (minus) result.	
	adtnl_cycles BNE();	// Branch on non-zero result. (When comparison doesnt result in equal zero flag isnt set).
	adtnl_cycles BPL();	// Branch on positive (plus) result.
	adtnl_cycles BRK();	// Force Break.
	adtnl_cycles BVC();	// Branch on Overflow clear.
	adtnl_cycles BVS();	// Branch on Overflow set.

	adtnl_cycles CLC();	// Clear carry flag.
	adtnl_cycles CLD();	// Clear decimal mode.
	adtnl_cycles CLI();	// Clear Interrupt disable.
	adtnl_cycles CLV();	// Clear overflow flag.
	adtnl_cycles CMP();	// Compare with Accumulator.
	adtnl_cycles CPX();	// Compare with X register.
	adtnl_cycles CPY();	// Compare with Y register.

	adtnl_cycles DEC();	// Decrement operand by one.
	adtnl_cycles DEX();	// Decrement X register by one.
	adtnl_cycles DEY();	// Decrement Y register by one.

	adtnl_cycles EOR();	// Operate 'Exclusive OR' with Accumulator.
	
	adtnl_cycles INC();	// Increment operant by one.
	adtnl_cycles INX();	// Increment X register by one.
	adtnl_cycles INY();	// Increment Y register by one.

	adtnl_cycles JMP();	// Jump to new location.
	adtnl_cycles JSR();	// Jump while saving return address.

	adtnl_cycles LDA();	// Load Accumulator.
	adtnl_cycles LDX();	// Load X register.
	adtnl_cycles LDY();	// Load Y register.
	adtnl_cycles LSR();	// Shift rightwards (1 bit).

	adtnl_cycles NOP();	// No Operation.
	
	adtnl_cycles ORA();	// Operate 'OR' with Accumulator.

	adtnl_cycles PHA();	// Push Accumulator on Stack.
	adtnl_cycles PHP();	// Push Status register on Stack.
	adtnl_cycles PLA();	// Pull Accumulator from Stack.
	adtnl_cycles PLP();	// Pull Status register from Stack.

	adtnl_cycles ROL();	// Rotate leftwards (1 bit).
	adtnl_cycles ROR();	// Rotate rightwards (1 bit).
	adtnl_cycles RTI();	// Return from interrupt.
	adtnl_cycles RTS();	// Return from Subroutine.

	adtnl_cycles SBC();	// Subtract from Accumulator with borrow.
	adtnl_cycles SEC();	// Set carry flag.
	adtnl_cycles SED();	// Set decimal Mode.
	adtnl_cycles SEI();	// Set Interrupt-Disable.
	adtnl_cycles STA();	// Store Accumulator in operand.
	adtnl_cycles STX();	// Store X register in operand.
	adtnl_cycles STY();	// Store Y register in operand.

	adtnl_cycles TAX();	// Transfer Accumulator to X register.
	adtnl_cycles TAY();	// Transfer Accumulator to Y register.
	adtnl_cycles TSX();	// Transfer Stack Pointer to X register.
	adtnl_cycles TXA();	// Transfer X register to Accumulator.
	adtnl_cycles TXS();	// Transfer X register to Stack Register.
	adtnl_cycles TYA();	// Transfer Y register to Accumulator.

	adtnl_cycles XXX(); // Does nothing.
	
	struct instruction {
		std::string menmonic;									// For future Disassembly implementation.
		adtnl_cycles (cpu6502::* operation)(void) = nullptr;	// For storing the Opcode Operation.
		adtnl_cycles (cpu6502::* addr_mode)(void) = nullptr;	// For storing the addresing mode.
		uint8_t	cycles_to_complete = NULL;						// Number of cycles required for execution.
	};

	std::vector<instruction> LookupTable;
};

#endif
