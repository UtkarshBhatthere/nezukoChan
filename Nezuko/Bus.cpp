#include "Bus.h"

#if 1

// Using Initialisation lists to construct ram object.
Bus::Bus(void) : sysRam(0, 8191, 2048)
{
	// Setting up devices on the bus.
	cpu.linkBus(this);

}

uint8_t& Bus::busRead(uint16_t address)
{
	return sysRam[address];
}

void Bus::busWrite(uint16_t address, uint8_t data)
{
	sysRam[address] = data;		// addr legality and mirroring is managed internally.
}
#endif