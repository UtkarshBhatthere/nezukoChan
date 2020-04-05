#pragma once

//Includes
#include <iostream>
#include <array>
#include "cpu6502.h"
#include "ram.h"

class Bus
{
private:
	// Devices on the Bus.
	cpu6502 cpu;				// CPU Rockwell 6502.
	ram	sysRam;					// 2 KiloBytes of RAM.

public:
	Bus(void);
	uint8_t& busRead(uint16_t address);
	void	busWrite(uint16_t address, uint8_t data);

};

// EOF ~ Utkarsh Bhatt 2020