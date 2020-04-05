#include "cpu6502.h"

// Installs the Opcode Lookup table.
cpu6502::cpu6502(void)
{
	// Shortname for cpu6052.
	using CPU = cpu6502;

	LookupTable =	// 256 Instruction Set for Opcode decoding. The ones marked "???" are Illegal Instructions.
					// Since writing this is redundant, these were copied from OneLoneCoders NES Emulator Implementation.
					// Checkout his work at https://github.com/OneLoneCoder/olcNES/
	{
		{ "BRK", &CPU::BRK, &CPU::IMM, 7 },{ "ORA", &CPU::ORA, &CPU::IAX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::ZPA, 3 },{ "ASL", &CPU::ASL, &CPU::ZPA, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "PHP", &CPU::PHP, &CPU::IMP, 3 },{ "ORA", &CPU::ORA, &CPU::IMM, 2 },{ "ASL", &CPU::ASL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABS, 4 },{ "ASL", &CPU::ASL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BPL", &CPU::BPL, &CPU::REL, 2 },{ "ORA", &CPU::ORA, &CPU::IAY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ZPX, 4 },{ "ASL", &CPU::ASL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "CLC", &CPU::CLC, &CPU::IMP, 2 },{ "ORA", &CPU::ORA, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ORA", &CPU::ORA, &CPU::ABX, 4 },{ "ASL", &CPU::ASL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "JSR", &CPU::JSR, &CPU::ABS, 6 },{ "AND", &CPU::AND, &CPU::IAX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "BIT", &CPU::BIT, &CPU::ZPA, 3 },{ "AND", &CPU::AND, &CPU::ZPA, 3 },{ "ROL", &CPU::ROL, &CPU::ZPA, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "PLP", &CPU::PLP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::IMM, 2 },{ "ROL", &CPU::ROL, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },
		{ "BIT", &CPU::BIT, &CPU::ABS, 4 },{ "AND", &CPU::AND, &CPU::ABS, 4 },{ "ROL", &CPU::ROL, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BMI", &CPU::BMI, &CPU::REL, 2 },{ "AND", &CPU::AND, &CPU::IAY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ZPX, 4 },{ "ROL", &CPU::ROL, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "SEC", &CPU::SEC, &CPU::IMP, 2 },{ "AND", &CPU::AND, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "AND", &CPU::AND, &CPU::ABX, 4 },{ "ROL", &CPU::ROL, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTI", &CPU::RTI, &CPU::IMP, 6 },{ "EOR", &CPU::EOR, &CPU::IAX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::ZPA, 3 },{ "LSR", &CPU::LSR, &CPU::ZPA, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "PHA", &CPU::PHA, &CPU::IMP, 3 },{ "EOR", &CPU::EOR, &CPU::IMM, 2 },{ "LSR", &CPU::LSR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },
		{ "JMP", &CPU::JMP, &CPU::ABS, 3 },{ "EOR", &CPU::EOR, &CPU::ABS, 4 },{ "LSR", &CPU::LSR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVC", &CPU::BVC, &CPU::REL, 2 },{ "EOR", &CPU::EOR, &CPU::IAY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ZPX, 4 },{ "LSR", &CPU::LSR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "CLI", &CPU::CLI, &CPU::IMP, 2 },{ "EOR", &CPU::EOR, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "EOR", &CPU::EOR, &CPU::ABX, 4 },{ "LSR", &CPU::LSR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "RTS", &CPU::RTS, &CPU::IMP, 6 },{ "ADC", &CPU::ADC, &CPU::IAX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 3 },{ "ADC", &CPU::ADC, &CPU::ZPA, 3 },{ "ROR", &CPU::ROR, &CPU::ZPA, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "PLA", &CPU::PLA, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::IMM, 2 },{ "ROR", &CPU::ROR, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },
		{ "JMP", &CPU::JMP, &CPU::IND, 5 },{ "ADC", &CPU::ADC, &CPU::ABS, 4 },{ "ROR", &CPU::ROR, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BVS", &CPU::BVS, &CPU::REL, 2 },{ "ADC", &CPU::ADC, &CPU::IAY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ZPX, 4 },{ "ROR", &CPU::ROR, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "SEI", &CPU::SEI, &CPU::IMP, 2 },{ "ADC", &CPU::ADC, &CPU::ABY, 4 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "ADC", &CPU::ADC, &CPU::ABX, 4 },{ "ROR", &CPU::ROR, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::IAX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "STY", &CPU::STY, &CPU::ZPA, 3 },{ "STA", &CPU::STA, &CPU::ZPA, 3 },{ "STX", &CPU::STX, &CPU::ZPA, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },
		{ "DEY", &CPU::DEY, &CPU::IMP, 2 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "TXA", &CPU::TXA, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },
		{ "STY", &CPU::STY, &CPU::ABS, 4 },{ "STA", &CPU::STA, &CPU::ABS, 4 },{ "STX", &CPU::STX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCC", &CPU::BCC, &CPU::REL, 2 },{ "STA", &CPU::STA, &CPU::IAY, 6 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "STY", &CPU::STY, &CPU::ZPX, 4 },{ "STA", &CPU::STA, &CPU::ZPX, 4 },{ "STX", &CPU::STX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "TYA", &CPU::TYA, &CPU::IMP, 2 },{ "STA", &CPU::STA, &CPU::ABY, 5 },{ "TXS", &CPU::TXS, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "???", &CPU::NOP, &CPU::IMP, 5 },{ "STA", &CPU::STA, &CPU::ABX, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::IMM, 2 },{ "LDA", &CPU::LDA, &CPU::IAX, 6 },{ "LDX", &CPU::LDX, &CPU::IMM, 2 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "LDY", &CPU::LDY, &CPU::ZPA, 3 },{ "LDA", &CPU::LDA, &CPU::ZPA, 3 },{ "LDX", &CPU::LDX, &CPU::ZPA, 3 },{ "???", &CPU::XXX, &CPU::IMP, 3 },
		{ "TAY", &CPU::TAY, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::IMM, 2 },{ "TAX", &CPU::TAX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },
		{ "LDY", &CPU::LDY, &CPU::ABS, 4 },{ "LDA", &CPU::LDA, &CPU::ABS, 4 },{ "LDX", &CPU::LDX, &CPU::ABS, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "BCS", &CPU::BCS, &CPU::REL, 2 },{ "LDA", &CPU::LDA, &CPU::IAY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "LDY", &CPU::LDY, &CPU::ZPX, 4 },{ "LDA", &CPU::LDA, &CPU::ZPX, 4 },{ "LDX", &CPU::LDX, &CPU::ZPY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "CLV", &CPU::CLV, &CPU::IMP, 2 },{ "LDA", &CPU::LDA, &CPU::ABY, 4 },{ "TSX", &CPU::TSX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "LDY", &CPU::LDY, &CPU::ABX, 4 },{ "LDA", &CPU::LDA, &CPU::ABX, 4 },{ "LDX", &CPU::LDX, &CPU::ABY, 4 },{ "???", &CPU::XXX, &CPU::IMP, 4 },
		{ "CPY", &CPU::CPY, &CPU::IMM, 2 },{ "CMP", &CPU::CMP, &CPU::IAX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "CPY", &CPU::CPY, &CPU::ZPA, 3 },{ "CMP", &CPU::CMP, &CPU::ZPA, 3 },{ "DEC", &CPU::DEC, &CPU::ZPA, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "INY", &CPU::INY, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::IMM, 2 },{ "DEX", &CPU::DEX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 2 },
		{ "CPY", &CPU::CPY, &CPU::ABS, 4 },{ "CMP", &CPU::CMP, &CPU::ABS, 4 },{ "DEC", &CPU::DEC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BNE", &CPU::BNE, &CPU::REL, 2 },{ "CMP", &CPU::CMP, &CPU::IAY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ZPX, 4 },{ "DEC", &CPU::DEC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "CLD", &CPU::CLD, &CPU::IMP, 2 },{ "CMP", &CPU::CMP, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "CMP", &CPU::CMP, &CPU::ABX, 4 },{ "DEC", &CPU::DEC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "CPX", &CPU::CPX, &CPU::IMM, 2 },{ "SBC", &CPU::SBC, &CPU::IAX, 6 },{ "???", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "CPX", &CPU::CPX, &CPU::ZPA, 3 },{ "SBC", &CPU::SBC, &CPU::ZPA, 3 },{ "INC", &CPU::INC, &CPU::ZPA, 5 },{ "???", &CPU::XXX, &CPU::IMP, 5 },
		{ "INX", &CPU::INX, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::IMM, 2 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::SBC, &CPU::IMP, 2 },
		{ "CPX", &CPU::CPX, &CPU::ABS, 4 },{ "SBC", &CPU::SBC, &CPU::ABS, 4 },{ "INC", &CPU::INC, &CPU::ABS, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "BEQ", &CPU::BEQ, &CPU::REL, 2 },{ "SBC", &CPU::SBC, &CPU::IAY, 5 },{ "???", &CPU::XXX, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 8 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ZPX, 4 },{ "INC", &CPU::INC, &CPU::ZPX, 6 },{ "???", &CPU::XXX, &CPU::IMP, 6 },
		{ "SED", &CPU::SED, &CPU::IMP, 2 },{ "SBC", &CPU::SBC, &CPU::ABY, 4 },{ "NOP", &CPU::NOP, &CPU::IMP, 2 },{ "???", &CPU::XXX, &CPU::IMP, 7 },
		{ "???", &CPU::NOP, &CPU::IMP, 4 },{ "SBC", &CPU::SBC, &CPU::ABX, 4 },{ "INC", &CPU::INC, &CPU::ABX, 7 },{ "???", &CPU::XXX, &CPU::IMP, 7 },

	};
}

void cpu6502::set_flag(flag f, bool value)
{
	if (value)
		ST |= f;
	else
		ST &= ~f;
}

bool cpu6502::get_flag(flag f)
{
	return ((ST & f) > 0 ? true : false);
}

void cpu6502::linkBus(Bus* bus)
{
	parentBus = bus;
}

uint8_t cpu6502::cpuRead(uint16_t address)
{
	return parentBus -> busRead(address);
}

void cpu6502::cpuWrite(uint16_t address, uint8_t data)
{
	parentBus->busWrite(address, data);
}

void cpu6502::stack_push(uint8_t data)	// TODO: Implement Stack Size Check.
{
	// Stack is located in Page 1, SP holds the byte addr in pg1.
	uint16_t pg1_offset = 0x100;	// Page 1 Start.
	cpuWrite((pg1_offset + SP), data);
	SP--;							// Decrement Stack Pointer.
}

uint8_t cpu6502::stack_pop(void)	// TODO: Implement Stack Size Check.
{
	uint16_t pg1_offset = 0x100;	// Page 1 Start.
	SP++;
	return (cpuRead(pg1_offset + SP));
}

void cpu6502::irq(void)
{
	// Check if interrupts are disabled. ( 1 = dis, 0 = en )
	if (get_flag(IRQ) == 0) {
		// Reading IRQ Start Address.
		uint16_t lowerByte = cpuRead(0xFFFE);
		uint16_t upperByte = cpuRead(0xFFFF);

		// Push Program Counter to Stack.
		stack_push((PC >> 8) & 0x00FF);	// Upper Byte of PC.
		stack_push(PC & 0x00FF);		// Lower Byte of PC.

		// Setting Status register.
		set_flag(IRQ, true);	// No interrupts for now.
		set_flag(BRF, false);	// BRK will be set when IRQ ends.
		set_flag(UNU, true);	// UNU is always 1.

		// Push Status register to stack.
		stack_push(ST);			// Status Register is 8 Bits wide.

		// Loading Program Counter.
		PC = (upperByte << 8) | lowerByte;

		// IRQ takes 7 ticks.
		cycles = 7;
	}
}
void cpu6502::reset(void)
{
	// Reading Programs Start Address.
	uint16_t lowerByte = cpuRead(0xFFFC);
	uint16_t upperByte = cpuRead(0xFFFD);

	// Loading Program Counter.
	PC = (upperByte << 8) | lowerByte;

	// Setting Helping Variables as Zero.
	operand  = 0x00;
	opcode   = 0x00;
	abs_addr = 0x00;
	rel_addr = 0x00;

	// Unused Bit in Status Flag is 1.
	ST = 0x00 | UNU;	// Just Bit 5 set rest unset.

	// Setting up Stack Pointer to Page 1 defined addr.
	SP = 0xFF;	// Stack ROOT at 0x01FF grows downwards.

	// Reset Global Tick Count.
	ticks = 0;

	// Reset taked 6 + 2 ticks to complete.
	cycles = 8;
}

void cpu6502::nmi(void)
{
	// NMI is not maskable hence no need to check I flag.
	// Reading IRQ Start Address.
	uint16_t lowerByte = cpuRead(0xFFFA);
	uint16_t upperByte = cpuRead(0xFFFB);

	// Push Program Counter to Stack.
	stack_push((PC >> 8) & 0x00FF);	// Upper Byte of PC.
	stack_push(PC & 0x00FF);		// Lower Byte of PC.

	// Setting Status register.
	set_flag(IRQ, true);	// No interrupts for now.
	set_flag(BRF, false);	// BRK will be set when IRQ ends.
	set_flag(UNU, true);	// UNU is always 1.

	// Push Status register to stack.
	stack_push(ST);			// Status Register is 8 Bits wide.

	// Loading Program Counter.
	PC = (upperByte << 8) | lowerByte;

	// NMI takes 8 ticks.
	ticks = 8;

}
void cpu6502::tick(void)
{
	// NES works on synchronous devices hence the concept of time is required to maintain sync.
	// Physically each instruction takes some time to get executed electronically, however,
	// this is not the case with emulation hence we execute the complete instruction in one
	// cycle and just count the ticks for the remaining cycles for the sake of sync.

	// Check if this is the start of the instruction.
	if (cycles == 0) {
		// Load Instruction.
		opcode = cpuRead(PC++);	// Program Counter increments after OPCODE fetch.

		// Load the instruction values.
		cycles = LookupTable[opcode].cycles_to_complete;				// Cycles required.
		adtnl_cycles adr = (this->*LookupTable[opcode].addr_mode)();	// Execute Addr Mode.
		adtnl_cycles opc = (this->*LookupTable[opcode].operation)();	// Execute Instruction.

		cycles += (adr & opc);	// Adds an additional Cycle if both require it.

		// Setting Unused Flag to 1 (Always :D).
		set_flag(UNU, true);
	}

	// Decrementing Cycles for the instruction.
	cycles--;

	// Incrementing Global Ticks.
	ticks++;

}
uint8_t cpu6502::fetch(void)
{
	// Nothing to Fetch if Accumulator/Implied Addressing is used.
	if (LookupTable[opcode].addr_mode != &cpu6502::IMP) {
		operand = cpuRead(abs_addr);	// abs_addr is set by the Addressing Function.
		return operand;
	}
	return 0;
}

cpu6502::adtnl_cycles cpu6502::IMP()
{
	// Usually IMP instructions have operand implied in their opcodes
	// fetch isn't called for IMP instructions. Here we copy accumulator 
	// to operand for instructions such as PHA which push Accumulator to
	// stack.
	operand = A;
	return 0;		// No adtnl cycle required.
}

cpu6502::adtnl_cycles cpu6502::IMM()
{
	abs_addr = cpuRead(PC++);
	return 0;		// No adtnl cycle required.
}

cpu6502::adtnl_cycles cpu6502::ZPA()
{
	uint8_t lowerByte = cpuRead(PC++);
	abs_addr = (lowerByte & 0xFF);
	return 0;		// No adtnl cycle required.
}

cpu6502::adtnl_cycles cpu6502::ZPX()
{
	uint8_t lowerByte = cpuRead(PC++) + X;	// With added X offset.
	abs_addr = (lowerByte & 0xFF);
	return 0;		// No adtnl cycle required.
}

cpu6502::adtnl_cycles cpu6502::ZPY()
{
	uint8_t lowerByte = cpuRead(PC++) + Y;	// With added Y offset.
	abs_addr = (lowerByte & 0xFF);
	return 0;		// No adtnl cycle required.
}

cpu6502::adtnl_cycles cpu6502::ABS()
{
	uint8_t lowerByte = cpuRead(PC++);
	uint8_t upperByte = cpuRead(PC++);
	abs_addr = ((upperByte << 8) | lowerByte);
	return 0;		// No adtnl cycle required.
}

cpu6502::adtnl_cycles cpu6502::ABX()
{
	uint8_t lowerByte = cpuRead(PC++);
	uint8_t upperByte = cpuRead(PC++);
	abs_addr = ((upperByte << 8) | lowerByte) + X;	// With added X offset.
	if ((abs_addr >> 8) & 0x00FF != upperByte)
		return 1;		// Page Incremented hence 1 adtnl cycle required.
	else
		return 0;		// No adtnl cycle required.
}

cpu6502::adtnl_cycles cpu6502::ABY()
{
	uint8_t lowerByte = cpuRead(PC++);
	uint8_t upperByte = cpuRead(PC++);
	abs_addr = ((upperByte << 8) | lowerByte) + Y;	// With added Y offset.
	if ((abs_addr >> 8) & 0x00FF != upperByte)
		return 1;		// Page Incremented hence 1 adtnl cycle required.
	else
		return 0;		// No adtnl cycle required.
}

cpu6502::adtnl_cycles cpu6502::REL()
{
	uint8_t offset = cpuRead(PC++);
	if (offset & 0x80) // If MSB is set the offset is negative.
		rel_addr = 0xFF | offset;	// 2's compliment form.
	else
		rel_addr = 0x00FF & offset;	// Else offset is positive.

	return 0;
}

cpu6502::adtnl_cycles cpu6502::IAX()
{
	// Using the value at PC as a pointer to actual memory location.
	uint16_t ptr_to_memory = (cpuRead(PC++) + X);
	
	// Actual Memory Addr Fetch.
	uint8_t lowerByte = cpuRead(ptr_to_memory++ & 0x00FF);	// Wrap to Page 0.
	uint8_t upperByte = cpuRead(ptr_to_memory & 0x00FF);	// Page 0.

	// setting the actual required address.
	abs_addr = (upperByte << 8) | lowerByte;

	return 0;
}

// IAY and IAX are not identical, IAY takes carry bit as well.
cpu6502::adtnl_cycles cpu6502::IAY()
{
	// Since we have to consider carry bit, we'll add offset at last.
	uint16_t ptr_to_memory = cpuRead(PC++);

	// Actual Address.
	uint8_t lowerByte = cpuRead(ptr_to_memory++ & 0x00FF);	// Wrap to Page 0.
	uint8_t upperByte = cpuRead(ptr_to_memory & 0x00FF);	// Page 0.
	
	// setting the actual required address.
	abs_addr = ((upperByte << 8) | lowerByte) + Y;	// Added Y Offset.

	// Check if Page has changed after adding offset.
	if ((abs_addr >> 8) & 0x00FF != upperByte)
		return 1;
	else
		return 0;
}

// Note : There's a known bug in this instruction's implementation, programs are
// written taking it in consideration. Hence, we'll have to implement this bug as well.
// Bug : "When the vector of an indirect address begins at the last byte of a page, the second
// byte is fetched from the beginning of that page rather than the beginning of the next. "
cpu6502::adtnl_cycles cpu6502::IND()
{
	// Fetching the pointer.
	uint8_t lowerByte_ptr = cpuRead(PC++);
	uint8_t upperByte_ptr = cpuRead(PC++);

	// Constructing ptr.
	uint16_t ptr = (upperByte_ptr << 8) | lowerByte_ptr;
	
	// Checking if the ptr poitns to the last memory of a page.
	if (lowerByte_ptr == 0xFF)
		abs_addr = (cpuRead(ptr & 0xFF00) << 8) | cpuRead(ptr);
	else
		abs_addr = (cpuRead(ptr + 1) << 8) | cpuRead(ptr);

	return 0;
}

// Addition with Carry forward.
cpu6502::adtnl_cycles cpu6502::ADC()
{
	// Fetches the operand according to the previosuly called Addr_mode.
	fetch();
	
	//Calculate the Addition.
	uint16_t sum = (uint16_t)A + uint16_t(operand) + (uint16_t)get_flag(CAR);

	// Calculate Flag statuses.
	// CAR - 1 if sum > 0xFF else 0;
	// NEG - 1 if MSB is 1 else 0;
	// ZER - 1 if sum is 0 else 0;
	// OVF : If sum wraps over 8 bits
	//		 either positively or negatively.

	set_flag(CAR, (sum > 255));
	set_flag(NEG, (sum & 0x0080));
	set_flag(ZER, (sum == 0));
	// We're interested in knowing if the 8th bit overflowed.
	set_flag(OVF, (~((((uint16_t)A ^ (uint16_t)operand) & ((uint16_t)A ^ (uint16_t)sum)) & 0x0080)));

	// Load Accumulator with the sum.
	A = sum & 0x00FF;

	return 1;	// May require additional clock cycle.
}

cpu6502::adtnl_cycles cpu6502::AND()
{
	fetch();
	A = A & operand;
	set_flag(NEG, (A & 0x80));
	set_flag(ZER, (A == 0));

	return 1;
}

cpu6502::adtnl_cycles cpu6502::ASL()
{
	fetch();

	uint16_t shifted = operand << 1;
	// We're only interested in lowerByte.
	set_flag(ZER, (shifted & 0x00FF) == 0);
	set_flag(NEG, (shifted & 0x0080));
	set_flag(CAR, (shifted & 0xFF00) > 0); // If bit any set bit exist in upperByte.

	if (LookupTable[opcode].addr_mode == &cpu6502::IMP)
		A = shifted & 0x00FF;					// Load to accumulator if implied addressing mode.
	else
		cpuWrite(abs_addr, (shifted & 0x00FF));	// Load to address according to addressing mode.

	return 0;
}

cpu6502::adtnl_cycles cpu6502::BCC()
{
	// Branching will take place if carry flag is clear.
	if (get_flag(CAR) == false) {
		cycles++; // Braching causes addition of 1 cycle.

		// Branch Address = ABS_ADDR + OFFSET -> OFFSET E (-128, +127).
		abs_addr = PC + rel_addr;

		// Check if page is changing.
		if ((abs_addr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;	// acc to datasheet.
		}
		PC = abs_addr;	// To branch to.
	}

	return 0;	// We managed additional cycles here.
}

cpu6502::adtnl_cycles cpu6502::BCS()
{
	// Branching will take place if carry flag is set.
	if (get_flag(CAR) == true) {
		cycles++; // Braching causes addition of 1 cycle.

		// Branch Address = ABS_ADDR + OFFSET -> OFFSET E (-128, +127).
		abs_addr = PC + rel_addr;

		// Check if page is changing.
		if ((abs_addr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;	// acc to datasheet.
		}
		PC = abs_addr;	// To branch to.
	}

	return 0;
}

cpu6502::adtnl_cycles cpu6502::BEQ()
{
	// Branching will take place if zero flag is set.
	if (get_flag(ZER) == 1) {
		cycles++; // Braching causes addition of 1 cycle.

		// Branch Address = ABS_ADDR + OFFSET -> OFFSET E (-128, +127).
		abs_addr = PC + rel_addr;

		// Check if page is changing.
		if ((abs_addr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;	// acc to datasheet.
		}
		PC = abs_addr;	// To branch to.
	}

	return 0;
}

// Special function used for testing bit 6 and bit 7 of operand.
// Applications in I/O usually for interrupt polling etc.
cpu6502::adtnl_cycles cpu6502::BIT()
{
	fetch();
	uint8_t and_operation = A & operand;

	set_flag(ZER, and_operation == 0);
	set_flag(OVF, operand & OVF);	// Store Bit 6 of operand in OVF.
	set_flag(NEG, operand & NEG);	// Store Bit 7 of operand in NEG.

	return 0;
}

cpu6502::adtnl_cycles cpu6502::BMI()
{
	// Branching will take place if negative flag is set.
	if (get_flag(NEG) == 1) {
		cycles++; // Braching causes addition of 1 cycle.

		// Branch Address = ABS_ADDR + OFFSET -> OFFSET E (-128, +127).
		abs_addr = PC + rel_addr;

		// Check if page is changing.
		if ((abs_addr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;	// acc to datasheet.
		}
		PC = abs_addr;	// To branch to.
	}

	return 0;
}

cpu6502::adtnl_cycles cpu6502::BNE()
{
	// Branching will take place if zero flag is clear.
	if (get_flag(ZER) == 0) {
		cycles++; // Braching causes addition of 1 cycle.

		// Branch Address = ABS_ADDR + OFFSET -> OFFSET E (-128, +127).
		abs_addr = PC + rel_addr;

		// Check if page is changing.
		if ((abs_addr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;	// acc to datasheet.
		}
		PC = abs_addr;	// To branch to.
	}

	return 0;
}

cpu6502::adtnl_cycles cpu6502::BPL()
{
	// Branching will take place if zero flag is clear.
	if (get_flag(NEG) == 0) {
		cycles++; // Braching causes addition of 1 cycle.

		// Branch Address = ABS_ADDR + OFFSET -> OFFSET E (-128, +127).
		abs_addr = PC + rel_addr;

		// Check if page is changing.
		if ((abs_addr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;	// acc to datasheet.
		}
		PC = abs_addr;	// To branch to.
	}

	return 0;
}

// Regardless what many documentations say, BRK is a two byte Instruction.
// First Byte is 00 which is the opcode of the instruction.
// Second Byte is a padding byte which is ignored by the CPU.
// Here, we'll call fetch to fetch the padding byte but will ignore it.
// Thus while pushing to Stack we'll be 2 Bytes ahead of the location 
// where BRK command was stored.
cpu6502::adtnl_cycles cpu6502::BRK()
{
	fetch();	// Ignore the fetched padding byte.

	set_flag(IRQ, 1);	// BRK is Software Interrupt routine.
	
	// Pushing to Stack.
	stack_push((PC >> 8) & 0x00FF);	// Store PCH
	stack_push(PC & 0x00FF);		// Store PCL
	set_flag(BRF, true);			// Set Break Flag.
	stack_push(ST & 0x00FF);		// Store Status Register.
	set_flag(BRF, false);			// Clear Break Flag.

	// Load Program Counter with IRQ ADDR.
	PC = ((uint16_t)cpuRead(0xFFFF) << 8) | (uint16_t)(cpuRead(0xFFFE));

	return 0;
}

cpu6502::adtnl_cycles cpu6502::BVC()
{
	// Branching will take place if Overflow flag is clear.
	if (get_flag(OVF) == 0) {
		cycles++; // Braching causes addition of 1 cycle.

		// Branch Address = ABS_ADDR + OFFSET -> OFFSET E (-128, +127).
		abs_addr = PC + rel_addr;

		// Check if page is changing.
		if ((abs_addr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;	// acc to datasheet.
		}
		PC = abs_addr;	// To branch to.
	}

	return 0;
}

cpu6502::adtnl_cycles cpu6502::BVS()
{
	// Branching will take place if zero flag is clear.
	if (get_flag(OVF) == 1) {
		cycles++; // Braching causes addition of 1 cycle.

		// Branch Address = ABS_ADDR + OFFSET -> OFFSET E (-128, +127).
		abs_addr = PC + rel_addr;

		// Check if page is changing.
		if ((abs_addr & 0xFF00) != (PC & 0xFF00)) {
			cycles++;	// acc to datasheet.
		}
		PC = abs_addr;	// To branch to.
	}

	return 0;
}

cpu6502::adtnl_cycles cpu6502::CLC()
{
	set_flag(CAR, false);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::CLD()
{
	set_flag(DEF, false);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::CLI()
{
	set_flag(IRQ, false);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::CLV()
{
	set_flag(OVF, false);
	return 0;
}

// Comparison is done in MCU's using substraction.
// If the difference is 0 they're equal, if it's negative
// it means A < M and if it's positive A > M.
cpu6502::adtnl_cycles cpu6502::CMP()
{
	fetch();	// Fetch Data to be compared.

	uint8_t difference = A - operand;

	set_flag(CAR, A >= operand);
	set_flag(ZER, difference == 0);
	set_flag(NEG, difference & 0x80);
	
	return 1;
}

cpu6502::adtnl_cycles cpu6502::CPX()
{
	fetch();	// Fetch Data to be compared.

	uint8_t difference = X - operand;

	set_flag(CAR, X >= operand);
	set_flag(ZER, difference == 0);
	set_flag(NEG, difference & 0x80);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::CPY()
{
	fetch();	// Fetch Data to be compared.

	uint8_t difference = Y - operand;

	set_flag(CAR, Y >= operand);
	set_flag(ZER, difference == 0);
	set_flag(NEG, difference & 0x80);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::DEC()
{
	fetch();	// Fetch operand to be decremented.

	operand--;	// Decrement the operand.
	set_flag(ZER, operand == 0);
	set_flag(NEG, operand & 0x80);
	cpuWrite(abs_addr, operand);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::DEX()
{
	// Implied Addressing hence fetch() is not required.
	X--;	// Decrementing X;
	set_flag(ZER, X == 0);
	set_flag(NEG, X & 0x80);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::DEY()
{
	// Implied Addressing hence fetch() is not required.
	X--;	// Decrementing X;
	set_flag(ZER, X == 0);
	set_flag(NEG, X & 0x80);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::EOR()
{
	fetch();	// Fetch operand to be decremented.

	A = A ^ operand;
	set_flag(ZER, A == 0);
	set_flag(NEG, A & 0x80);

	return 1;
}

cpu6502::adtnl_cycles cpu6502::INC()
{
	fetch();	// Fetch operand to be incremented.

	operand++;	// Decrement the operand.
	set_flag(ZER, operand == 0);
	set_flag(NEG, operand & 0x80);
	cpuWrite(abs_addr, operand);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::INX()
{
	// Implied Addressing hence fetch() is not required.
	X++;	// Decrementing X;
	set_flag(ZER, X == 0);
	set_flag(NEG, X & 0x80);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::INY()
{
	// Implied Addressing hence fetch() is not required.
	Y++;	// Decrementing X;
	set_flag(ZER, Y == 0);
	set_flag(NEG, Y & 0x80);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::JMP()
{
	PC = abs_addr;
	return 0;
}

// Return address is the address lying just before the jump operation.
// RTS instruction used to return after completion of the subroutine 
// pops the PC from stack add 1 to it and then return the control.
// We'll do exactly as the system does.
cpu6502::adtnl_cycles cpu6502::JSR()
{
	PC--;
	stack_push((PC >> 8) & 0x00FF);	// Store PCH.
	stack_push(PC & 0x00FF);		// Store PCL.
	PC = abs_addr;					// Copy Jump Destination to PC.

	return 0;
}

cpu6502::adtnl_cycles cpu6502::LDA()
{
	fetch();	// Fetch Data to load into accumulator.
	A = operand;
	set_flag(ZER, A == 0);
	set_flag(NEG, A & 0x80);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::LDX()
{
	fetch();	// Fetch Data to load into X register.
	A = operand;
	set_flag(ZER, A == 0);
	set_flag(NEG, A & 0x80);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::LDY()
{
	fetch();	// Fetch Data to load into Y register.
	A = operand;
	set_flag(ZER, A == 0);
	set_flag(NEG, A & 0x80);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::LSR()
{
	fetch();
	// Since it's right shift BIT 0 will move to Carry.
	set_flag(CAR, operand & (0x01));
	operand = operand >> 1;
	set_flag(ZER, operand == 0);
	set_flag(NEG, operand & 0x80);

	if (LookupTable[opcode].addr_mode == &cpu6502::IMP)
		A = operand;					// Load to accumulator if implied addressing mode.
	else
		cpuWrite(abs_addr, operand);	// Load to address according to addressing mode.

	return 0;
}

cpu6502::adtnl_cycles cpu6502::NOP()
{
	// Referred from https://wiki.nesdev.com/w/index.php/CPU_unofficial_opcodes#Games_using_unofficial_opcodes
	// Contains Illegal opcodes that are used.
	// Will be updated as newer opcodes would come to my knowledge.
	std::vector<uint8_t> two_byte_NOP{ 0x1C, 0x3C, 0x5C, 0x7C, 0xDC, 0xFC };
	for (auto& x : two_byte_NOP) {
		if (opcode == x)
			return 1;
	}

	return 0;
}

cpu6502::adtnl_cycles cpu6502::ORA()
{
	fetch();

	A |= operand;
	set_flag(ZER, A == 0);
	set_flag(NEG, A & 0x80);

	return 1;
}

cpu6502::adtnl_cycles cpu6502::PHA()
{
	stack_push(A);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::PHP()
{
	stack_push(ST | BRF | UNU);
	// Implementation. Replicating 6052 Flag Behaviour.
	// BRK Flag is set if control issued from PHP or BRK 0 if from interrupts.
	set_flag(BRF, 0);
	set_flag(UNU, 0);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::PLA()
{
	A = stack_pop();
	set_flag(ZER, A == 0);
	set_flag(NEG, A & 0x80);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::PLP()
{
	ST = stack_pop();
	set_flag(UNU, true); // To make sure the value popped from stack doesnt clear UNU Flag.
	return 0;
}

cpu6502::adtnl_cycles cpu6502::ROL()
{
	fetch();
	
	uint16_t shifted = (uint16_t)(operand << 1) | get_flag(CAR);
	set_flag(CAR, shifted & 0xFF00);
	set_flag(ZER, (shifted & 0x00FF) == 0);
	set_flag(NEG, shifted & 0x0080);

	if (LookupTable[opcode].addr_mode == &cpu6502::IMP)
		A = shifted & 0x00FF;					// Load to accumulator if implied addressing mode.
	else
		cpuWrite(abs_addr, shifted & 0x00FF);	// Load to address according to addressing mode.

	return 0;
}

cpu6502::adtnl_cycles cpu6502::ROR()
{
	fetch();

	uint16_t shifted = (uint16_t)(operand >> 1) | (get_flag(CAR) << 7);
	set_flag(CAR, shifted & 0xFF00);
	set_flag(ZER, (shifted & 0x00FF) == 0);
	set_flag(NEG, shifted & 0x0080);

	if (LookupTable[opcode].addr_mode == &cpu6502::IMP)
		A = shifted & 0x00FF;					// Load to accumulator if implied addressing mode.
	else
		cpuWrite(abs_addr, shifted & 0x00FF);	// Load to address according to addressing mode.

	return 0;
}

cpu6502::adtnl_cycles cpu6502::RTI()
{
	ST = stack_pop();
	set_flag(BRF, false);
	set_flag(UNU, false);

	uint8_t lowerByte = stack_pop();
	uint8_t upperByte = stack_pop();

	PC = (upperByte << 8) | lowerByte;

	return 0;

}

cpu6502::adtnl_cycles cpu6502::RTS()
{
	uint8_t lowerByte = stack_pop();
	uint8_t upperByte = stack_pop();

	PC = (upperByte << 8) | lowerByte;
	PC++;

	return 0;
}

// Substraction in digital system is implemented using 2's compliment system.
cpu6502::adtnl_cycles cpu6502::SBC()
{
	fetch();

	uint16_t flipped_operand = operand ^ 0x00FF;
	uint16_t difference = (uint16_t)A + flipped_operand + (uint16_t)get_flag(CAR);	// Using 2's compliment method.

	set_flag(CAR, difference & 0xFF00);
	set_flag(NEG, difference & 0x0080);
	set_flag(ZER, (difference&0x00FF) == 0);
	set_flag(OVF, (((uint16_t)A ^ difference) & (difference ^ flipped_operand)) & 0x0080);

	// Load Accumulator.
	A = difference & 0x00FF;
	return 0;
}

cpu6502::adtnl_cycles cpu6502::SEC()
{
	set_flag(CAR, true);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::SED()
{
	set_flag(DEF, true);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::SEI()
{
	set_flag(IRQ, true);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::STA()
{
	cpuWrite(abs_addr, A);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::STX()
{
	cpuWrite(abs_addr, X);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::STY()
{
	cpuWrite(abs_addr, Y);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::TAX()
{
	X = A;
	set_flag(ZER, X == 0);
	set_flag(NEG, X & 0x80);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::TAY()
{
	Y = A;
	set_flag(ZER, Y == 0);
	set_flag(NEG, Y & 0x80);
	return 0;
}

cpu6502::adtnl_cycles cpu6502::TSX()
{
	// Trnasferring SP to X.
	X = SP;

	// Setting up flags.
	set_flag(ZER, X == 0);
	set_flag(NEG, X & 0x80);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::TXA()
{
	A = X;	// Copying X's content to A register.

	// Setting up flags.
	set_flag(ZER, A == 0);
	set_flag(NEG, A & 0x80);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::TXS()
{
	SP = X;
	return 0;
}

cpu6502::adtnl_cycles cpu6502::TYA()
{
	A = Y;	// Copying X's content to A register.

	// Setting up flags.
	set_flag(ZER, Y == 0);
	set_flag(NEG, A & 0x80);

	return 0;
}

cpu6502::adtnl_cycles cpu6502::XXX()
{
	// Does what the description says. (NOTHING :D).
	return 0;
}




