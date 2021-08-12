#include "CPU.h"

CPU::CPU(std::string filename) : ram(RAM(RAM_SIZE)), rom(ROM(ROM_SIZE)), io(InOut()), pc(0x0000)
{
	rom.getInstructionsFormFIle(filename);
}

CPU::~CPU()
{
	
}

void CPU::run()
{
	while (true)
	{
		char key = 0;
		while (!io.getInput(key))
		{
			opcodesHandler(rom[pc++]);
			io.print(ram[p0], ram[p1]);
			if (pc > rom.getInstructionSize())
				break;
		}
		if (pc > rom.getInstructionSize())
			break;
		ram[p2] = key;
		
	}
}

ushort CPU::getPC()
{
	return pc;
}

uchar CPU::getPSW_C()
{
	return ram[psw] & 0x80;
}

uchar CPU::getPSW_AC()
{
	return ram[psw] & 0x40;
}

uchar CPU::getPSW_F0()
{
	return ram[psw] & 0x20;
}

uchar CPU::getPSW_RS1()
{
	return ram[psw] & 0x10;
}

uchar CPU::getPSW_RS0()
{
	return ram[psw] & 0x08;
}

uchar CPU::getPSW_OV()
{
	return ram[psw] & 0x04;
}

uchar CPU::getPSW_P()
{
	return ram[psw] & 0x01;
}


void CPU::setPSW_C(const bool bit)
{
	if (bit) {
		ram[psw] |= 0x80;
	}
	else {
		ram[psw] &= (~0x80);
	}
}

void CPU::setPSW_AC(const bool bit)
{
	if (bit) {
		ram[psw] |= 0x40;
	}
	else {
		ram[psw] &= (~0x40);
	}
}

void CPU::setPSW_F0(const bool bit)
{
	if (bit) {
		ram[psw] |= 0x20;
	}
	else {
		ram[psw] &= (~0x20);
	}
}

void CPU::setPSW_RS1(const bool bit)
{
	if (bit) {
		ram[psw] |= 0x10;
	}
	else {
		ram[psw] &= (~0x10);
	}
}

void CPU::setPSW_RS0(const bool bit)
{
	if (bit) {
		ram[psw] |= 0x08;
	}
	else {
		ram[psw] &= (~0x08);
	}
}

void CPU::setPSW_OV(const bool bit)
{
	if (bit) {
		ram[psw] |= 0x04;
	}
	else {
		ram[psw] &= (~0x04);
	}
}

void CPU::setPSW_P(const bool bit)
{
	if (bit) {
		ram[psw] |= 0x01;
	}
	else {
		ram[psw] &= (~0x01);
	}
}


ushort CPU::getDPTR()
{
	ushort address = ram[dpl];
	address = (ram[dph] << 8) | address;
	return address;
}

void CPU::setDPTR(const ushort address)
{
	ram[dpl] = (uchar)(address & 0x0F);
	ram[dph] = (uchar)(address >> 8);
}

uchar CPU::returnRegisterAddres(uchar opcode)
{
	opcode &= 0x0F;
	switch (opcode)
	{
	case 0x05:
		return rom[pc];
	case 0x06:
		return ram[0x00];
	case 0x07:
		return ram[0x01];
	case 0x08:
		return 0x00;
	case 0x09:
		return 0x01;
	case 0x0A:
		return 0x02;
	case 0x0B:
		return 0x03;
	case 0x0C:
		return 0x04;
	case 0x0D:
		return 0x05;
	case 0x0E:
		return 0x06;
	case 0x0F:
		return 0x07;
	default:
		break;
	}
	return NULL;
}

void CPU::opcodesHandler(const uchar opcode)
{
	uchar low = 0;
	ushort high = 0;
	ushort address = 0;
	uchar temp, temp1;
	uchar addrBit, tmpaddrBit;
	char offset = 0;
	int c = 0;
	int8_t res = 0;
	int8_t mul = 0;
	uchar immediate;
	switch (opcode)
	{
	case 0x00: // NOP
		break;
	case 0x01: // AJAMP addr1
	{
		low = rom[pc];
		high = rom[pc - 1];
		pc++;
		high >>= 5;
		pc = (high << 8) | low;
	}
	break;
	case 0x02: // LJMP addr 16
	{
		address = rom[pc];
		address <<= 8;
		address |= rom[++pc];
		pc = address;
	}
	break;
	case 0x03: //RR
	{
		temp = ram[acc];
		ram[acc] = ram[acc] >> 1;
		temp = temp & 0x7F;
		ram[acc] = ram[acc] | temp;
	}
	break; 
	case 0x04: //INC A
		ram[acc]++;
		break;
	case 0x05: //INC direct
	{
		ram[rom[pc]]++;
		pc++;
	}
	break;
	case 0x06:
	case 0x07:
	case 0x08:
	case 0x09:
	case 0x0A:
	case 0x0B:
	case 0x0C:
	case 0x0D:
	case 0x0E:
	case 0x0F: //INC register or adress in register
	{
		ram[returnRegisterAddres(opcode)] += 1;
		
	}	
	break;
	case 0x10: //JBC
	{
		addrBit = rom[pc];
		offset = rom[++pc];

		pc += 2;
		tmpaddrBit = ram[addrBit];
		if (tmpaddrBit & 0x01) {
			ram[addrBit] &= 0xFE;
			pc += offset;
		}
	}
	break;
	case 0x11: //ACALL
	{
		low = rom[pc];
		high = rom[pc - 1];
		high >>= 5;
		++pc;
		address = pc;
		ram[sp]++;
		ram[ram[sp]] = address & 0xFF;
		ram[sp]++;
		ram[ram[sp]] = (address >> 8) & 0xFF;
		pc = (high << 8) | low;
	}
	break;
	case 0x12: //LCALL
	{
		address = (rom[pc] << 8) | rom[pc + 1];
		pc += 2;
		ram[sp]++;
		ram[ram[sp]] = pc & 0xFF;
		ram[sp]++;
		ram[ram[sp]] = (pc >> 8) & 0xFF;
		pc = address;
	}
	break;
	case 0x13: //RRC
	{
		temp = ram[acc] & 0x01;
		ram[acc] >>= 1;
		ram[acc] = ram[acc] | (getPSW_C());
		setPSW_C(temp);
	}
	break;
	case 0x14: //DEC A
		ram[acc]--;
		break;
	case 0x15: //DEC direct
		ram[rom[pc]]--;
		break;
	case 0x16:
	case 0x17:
	case 0x18:
	case 0x19:
	case 0x1A:
	case 0x1B:
	case 0x1C:
	case 0x1D:
	case 0x1E:
	case 0x1F: //DEC register or adress in register
		ram[returnRegisterAddres(opcode)] -= 1;
		break;
	case 0x20: //JB
	{
		addrBit = rom[pc];
		offset = rom[++pc];

		pc += 2;
		tmpaddrBit = ram[addrBit];
		if (tmpaddrBit & 0x01) {
			pc += offset;
		}
	}
	break;
	case 0x21: //AJMP
	{
		low = rom[pc];
		high = rom[pc - 1];
		high >>= 5;
		++pc;
		pc = (high << 8) | low;
	}
	break;
	case 0x22: //RET
	{
		address = ram[ram[sp]] << 8;
		ram[sp]--;
		address |= ram[ram[sp]];
		ram[sp]--;
		pc = address;
	}
	break;
	case 0x23: //RL
	{
		temp = ram[acc] & 0x01;
		ram[acc] <<= 1;
		ram[acc] |= temp;
	}
	break;
	case 0x24: //ADD A, #immed
	{
		setPSW_C(((unsigned int)ram[acc] + (unsigned int)rom[pc]) > 255);
		setPSW_AC(((ram[acc] & 0x0F) + (rom[pc] & 0x0F)) & 0xF0);
		setPSW_OV(((ram[acc] & 0x7F) + (rom[pc] & 0x7F)) & 0x80);
		ram[acc] = ram[acc] + rom[pc];
		pc++;
	}
	break;
	case 0x25: //ADD A, direct
	{
		setPSW_C(((unsigned int)ram[acc] + (unsigned int)rom[pc]) > 255);
		setPSW_AC(((ram[acc] & 0x0F) + (rom[pc] & 0x0F)) & 0xF0);
		setPSW_OV(((ram[acc] & 0x7F) + (rom[pc] & 0x7F)) & 0x80);
		ram[acc] = ram[acc] + ram[pc];
		pc++;
	}
	break;
	case 0x26:
	case 0x27:
	case 0x28:
	case 0x29:
	case 0x2A:
	case 0x2B:
	case 0x2C:
	case 0x2D:
	case 0x2E:
	case 0x2F: //ADD a, register or adress in register
	{
		setPSW_C(((unsigned int)ram[acc] + (unsigned int)rom[pc]) > 255);
		setPSW_AC(((ram[acc] & 0x0F) + (rom[pc] & 0x0F)) & 0xF0);
		setPSW_OV(((ram[acc] & 0x7F) + (rom[pc] & 0x7F)) & 0x80);
		ram[acc] = ram[acc] + ram[returnRegisterAddres(opcode)];
	}
	break;
	case 0x30: 
		break;
	case 0x31: //ACALL addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		high >>= 5;
		++pc;
		address = pc;
		ram[sp]++;
		ram[ram[sp]] = address & 0xFF;
		ram[sp]++;
		ram[ram[sp]] = (address >> 8) & 0xFF;
		pc = (high << 8) | low;
	}
	break;
	case 0x32: //RETI
	{
		pc = ram[ram[sp]];
		ram[sp]--;
		pc <<= 8;
		pc |= ram[ram[sp]];
		ram[sp]--;
	}
	break;
	case 0x33: //RLC
	{
		c = getPSW_C() ? 1 : 0;
		temp = ram[acc] >> 7;
		ram[acc] <<= 1;
		ram[acc] |= c;
		setPSW_C(temp);
	}
	break;
	case 0x34: // ADDC A, #immed
	{
		c = (getPSW_C() ? 1 : 0);
		setPSW_C(((unsigned int)ram[acc] + (unsigned int)rom[pc] + (unsigned int)c) > 255);
		setPSW_AC(((ram[acc] & 0x0F) + (rom[pc] & 0x0F) + c) & 0xF0);
		setPSW_OV(((ram[acc] & 0x7F) + (rom[pc] & 0x7F) + c) & 0x80);
		ram[acc] = ram[acc] + rom[pc] + c;
		pc++;
	}
	break;
	case 0x35: // ADDC A, direct
	{
		c = (getPSW_C() ? 1 : 0);
		setPSW_C(((unsigned int)ram[acc] + (unsigned int)rom[pc] + (unsigned int)c) > 255);
		setPSW_AC(((ram[acc] & 0x0F) + (rom[pc] & 0x0F) + c) & 0xF0);
		setPSW_OV(((ram[acc] & 0x7F) + (rom[pc] & 0x7F) + c) & 0x80);
		ram[acc] = ram[acc] + ram[rom[pc]] + c;
		pc++;
	}
	break;
	case 0x36:
	case 0x37:
	case 0x38:
	case 0x39:
	case 0x3A:
	case 0x3B:
	case 0x3C:
	case 0x3D:
	case 0x3E:
	case 0x3F: // ADDC A, register or adress in register
	{
		c = (getPSW_C() ? 1 : 0);
		setPSW_C(((unsigned int)ram[acc] + (unsigned int)rom[pc] + (unsigned int)c) > 255);
		setPSW_AC(((ram[acc] & 0x0F) + (rom[pc] & 0x0F) + c) & 0xF0);
		setPSW_OV(((ram[acc] & 0x7F) + (rom[pc] & 0x7F) + c) & 0x80);
		ram[acc] = ram[acc] + ram[returnRegisterAddres(opcode)] + c;
	}
	break;
	case 0x40: // JC
	{
		offset = (ushort)rom[pc++];
		if ((getPSW_C() >> 7) == 1)
			pc += offset;
	}
	break;
	case 0x41: // AJMP addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		++pc;
		high >>= 5;
		pc = (high << 8) | low;
	}
	break;
	case 0x42: //ORL direct, A
	{
		ram[rom[pc]] |= ram[acc];
		++pc;
	}
	break;
	case 0x43: //ORL direct, #immed
	{
		ram[rom[pc]] |= rom[pc + 1];
		pc += 2;
	}
	break;
	case 0x44: //ORL A, #immed
	{
		ram[acc] |= rom[pc + 1];
		pc += 1;
	}
	break;
	case 0x45: //ORL A, direct
	{
		ram[acc] |= ram[rom[pc + 1]];
		pc += 1;
	}
	break;
	case 0x46:
	case 0x47:
	case 0x48:
	case 0x49:
	case 0x4A:
	case 0x4B:
	case 0x4C:
	case 0x4D:
	case 0x4E:
	case 0x4F: //ORL A, register or adress in register
		ram[acc] |= ram[returnRegisterAddres(opcode)];
		break;
	case 0x50:
	{
		offset = rom[pc++];
		if (getPSW_C() == 0)
			pc += offset;
	}
	break;
	case 0x51: //ACALL addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		high >>= 5;
		++pc;
		address = pc;
		ram[sp]++;
		ram[ram[sp]] = address & 0xFF;
		ram[sp]++;
		ram[ram[sp]] = (address >> 8) & 0xFF;
		pc = (high << 8) | low;
	}
	break;
	case 0x52: //ANL direct, A
	{
		ram[rom[pc]] &= ram[acc];
		++pc;
	}
	break;
	case 0x53: //ANL direct, #immed
	{
		ram[rom[pc]] &= rom[pc + 1];
		pc += 2;
	}
	break;
	case 0x54: //ANL A, #immed
	{
		ram[acc] &= rom[pc + 1];
		pc += 1;
	}
	break;
	case 0x55: //ANL A, direct
	{
		ram[acc] &= ram[rom[pc + 1]];
		pc += 1;
	}
	break;
	case 0x56:
	case 0x57:
	case 0x58:
	case 0x59:
	case 0x5A:
	case 0x5B:
	case 0x5C:
	case 0x5D:
	case 0x5E:
	case 0x5F: //ANL A, register or adress in register
		ram[acc] &= ram[returnRegisterAddres(opcode)];
	case 0x60: // JZ
	{
		offset = rom[pc++];
		if (ram[acc] == 0)
			pc += offset;
	}
	break;
	case 0x61: //AJMP addr 11
	{
		low = rom[pc];
		high = rom[pc - 1];
		++pc;
		high >>= 5;
		pc = (high << 8) | low;
	}
	break;
	case 0x62: //XRL direct, A
	{
		ram[rom[pc]] ^= ram[acc];
		++pc;
	}
	break;
	case 0x63: //XRL direct, #immed
	{
		ram[rom[pc]] ^= rom[pc + 1];
		pc += 2;
	}
	break;
	case 0x64: //XRL A, #immed
	{
		ram[acc] ^= rom[pc];
		pc += 1;
	}
	break;
	case 0x65: //XRL A, direct
	{
		ram[acc] ^= ram[rom[pc]];
		pc += 1;
	}
		
	case 0x66:
	case 0x67:
	case 0x68:
	case 0x69:
	case 0x6A:
	case 0x6B:
	case 0x6C:
	case 0x6D:
	case 0x6E:
	case 0x6F: //XRL register or adress in register
		ram[acc] ^= ram[returnRegisterAddres(opcode)];
	case 0x70:
	{
		pc++;
		if (ram[acc] != 0) {
			pc = pc + rom[pc - 1];
		}
	}
	break;
	case 0x71: //ACALL addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		high >>= 5;
		++pc;
		address = pc;
		ram[sp]++;
		ram[ram[sp]] = address & 0xFF;
		ram[sp]++;
		ram[ram[sp]] = (address >> 8) & 0xFF;
		pc = (high << 8) | low;
	}
	break;
	case 0x72: //ORL
		break;
	case 0x73: // JMP @A + DPTR
		pc = ram[acc] + getDPTR();
		break;
	case 0x74: // MOV A, #immed
	{
		ram[acc] = rom[pc];
		pc++;
	}
	break;
	case 0x75: // MOV direct, #immed
	{
		ram[rom[pc]] = rom[pc + 1];
		pc += 2;
	}
	break;
	case 0x76:
	case 0x77:
	case 0x78:
	case 0x79:
	case 0x7A:
	case 0x7B:
	case 0x7C:
	case 0x7D:
	case 0x7E:
	case 0x7F: // MOV register or adress in register, #immed
	{
		ram[returnRegisterAddres(opcode)] = rom[pc];
		++pc;
	}
	break;
	case 0x80: //SJMP offset
	{
		offset = rom[pc];
		pc++;
		pc = pc + offset;
	}
	break;
	case 0x81: //AJMP addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		++pc;
		high >>= 5;
		pc = (high << 8) | low;
	}
	break;
	case 0x82: //ANL C, bit
		break;
	case 0x83: //MOVC A, @A+PC
	{
		++pc;
		ram[acc] = rom[ram[acc] + pc];
	}
	break;
	case 0x84: //DIV
	{
		if (ram[b] == 0x00)
			setPSW_OV(1);
		else {
			ushort rest = ram[acc] % ram[b];
			ram[acc] /= ram[b];
			ram[b] = (uchar)rest;
			setPSW_C(0);
			setPSW_C(0);
		}
	}
	break;
	case 0x85: //MOV direct, direct
	{
		ram[pc] = ram[pc + 1];
		pc += 2;
	}
	break;
	case 0x86:
	case 0x87:
	case 0x88:
	case 0x89:
	case 0x8A:
	case 0x8B:
	case 0x8C:
	case 0x8D:
	case 0x8E:
	case 0x8F: //MOV direct, register or adress in register
	{
		ram[pc] = ram[returnRegisterAddres(opcode)];
		pc += 1;
	}
	break;
	case 0x90: //MOV DPTR, #immed
	{
		address = (rom[pc] << 8) | rom[pc + 1];
		setDPTR(address);
		pc += 2;
	}
	break;
	case 0x91: //ACALL addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		high >>= 5;
		++pc;
		address = pc;
		ram[sp]++;
		ram[ram[sp]] = address & 0xFF;
		ram[sp]++;
		ram[ram[sp]] = (address >> 8) & 0xFF;
		pc = (high << 8) | low;
	}
	break;
	case 0x92:
		break;
	case 0x93:
	{
		ram[acc] = rom[ram[acc] + getDPTR()];
	}
	break;
	case 0x94: //SUBB A, #immed
	{
		res = ram[acc] - rom[pc];
		c = getPSW_C();
		if (c)
			res--;
		ram[acc] = res;
		setPSW_C(((unsigned int)ram[acc] < (unsigned int)(rom[pc] + c)));
		setPSW_OV((ram[acc] < 0x80 && rom[pc] > 0x7F) ||
			(ram[acc] > 0x7F && rom[pc] < 0x80));
		setPSW_AC((ram[acc] & 0x0F) < ((rom[pc] + c) & 0x0F) ||
			c && ((rom[pc] & 0x0F) == 0x0F));
		pc++;
	}
	break;
	case 0x95:  //SUBB A, direct
	{
		res = ram[acc] - ram[pc];
		c = getPSW_C();
		if (c)
			res--;
		ram[acc] = res;
		setPSW_C(((unsigned int)ram[acc] < (unsigned int)(ram[pc] + c)));
		setPSW_OV((ram[acc] < 0x80 && ram[pc] > 0x7F) ||
			(ram[acc] > 0x7F && ram[pc] < 0x80));
		setPSW_AC((ram[acc] & 0x0F) < ((ram[pc] + c) & 0x0F) ||
			c && ((ram[pc] & 0x0F) == 0x0F));
		++pc;
	}
	break;
	case 0x96:
	case 0x97:
	case 0x98:
	case 0x99:
	case 0x9A:
	case 0x9B:
	case 0x9C:
	case 0x9D:
	case 0x9E:
	case 0x9F:  //SUBB A, register or adress in register
	{
		res = ram[acc] - ram[returnRegisterAddres(opcode)];
		c = getPSW_C();
		if (c)
			res--;
		ram[acc] = res;
		setPSW_C(((unsigned int)ram[acc] < (unsigned int)(ram[returnRegisterAddres(opcode)] + c)));
		setPSW_OV((ram[acc] < 0x80 && ram[returnRegisterAddres(opcode)] > 0x7F) ||
			(ram[acc] > 0x7F && ram[returnRegisterAddres(opcode)] < 0x80));
		setPSW_AC((ram[acc] & 0x0F) < ((ram[returnRegisterAddres(opcode)] + c) & 0x0F) ||
			c && ((ram[returnRegisterAddres(opcode)] & 0x0F) == 0x0F));
	}
	break;
	case 0xA0:
		break;
	case 0xA1: //AJMP addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		++pc;
		high >>= 5;
		pc = (high << 8) | low;
	}
	break;
	case 0xA2:
		break;	
	case 0xA3: //INC DPTR
		setDPTR(getDPTR() + 1);
		break;
	case 0xA4: //MUL AB
	{
		mul = ram[acc] * ram[b];
		setPSW_AC(mul > 255);
		setPSW_C(0);
		ram[acc] = mul & 0xFF;
		mul &= 0xFF00;
		mul >>= 8;
		ram[b] = mul & 0xFF;
	}
	break;
	case 0xA6:
	case 0xA7:
	case 0xA8:
	case 0xA9:
	case 0xAA:
	case 0xAB:
	case 0xAC:
	case 0xAD:
	case 0xAE:
	case 0xAF: //MOV register or adress in register, direct
	{
		ram[returnRegisterAddres(opcode)] = ram[pc];
		pc += 1;
	}
	break;
	case 0xB0:
		break;
	case 0xB1: //ACALL
	{
		low = rom[pc];
		high = rom[pc - 1];
		high >>= 5;
		++pc;
		address = pc;
		ram[sp]++;
		ram[ram[sp]] = address & 0xFF;
		ram[sp]++;
		ram[ram[sp]] = (address >> 8) & 0xFF;
		pc = (high << 8) | low;
	}
	break;
	case 0xB2:
		break;
	case 0xB3:
		setPSW_C(~getPSW_C());
		break;
	case 0xB4: //CJNE A, #immed, offset
	{
		immediate = rom[pc++];
		offset = rom[pc++];
		if (ram[acc] != immediate)
			pc += offset;
		if (ram[acc] < immediate)
			setPSW_C(1);
		else
			setPSW_C(0);
	}
	break;
	case 0xB5: //CJNE A, direct, offset
	{
		immediate = ram[rom[pc++]];
		offset = rom[pc++];
		if (ram[acc] != immediate)
			pc += offset;
		if (ram[acc] < immediate)
			setPSW_C(1);
		else
			setPSW_C(0);
	}
	break;
	case 0xB6:
	case 0xB7:
	case 0xB8:
	case 0xB9:
	case 0xBA:
	case 0xBB:
	case 0xBC:
	case 0xBD:
	case 0xBE:
	case 0xBF: //CJNE register or adress in register
	{
		immediate = rom[pc++];
		offset = rom[pc++];
		if (ram[returnRegisterAddres(opcode)] != immediate)
			pc += offset;
		if (ram[returnRegisterAddres(opcode)] < immediate)
			setPSW_C(1);
		else
			setPSW_C(0);
	}
	break;
	case 0xC0: // PUSH direct
	{
		ram[sp]++;
		ram[ram[sp]] = ram[rom[pc++]];
	}
	break;
	case 0xC1: // AJMP addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		++pc;
		high >>= 5;
		pc = (high << 8) | low;
	}
	break;
	case 0xC2: 
		break;
	case 0xC3: //CLR C
		setPSW_C(0);
		break;
	case 0xC4: //SWAP A
	{
		high = ram[acc] >> 4;
		ram[acc] = (ram[acc] << 4) | high;
	}
	break;
	case 0xC5: //XCH A, direct
	{
		temp = ram[acc];
		ram[acc] = ram[pc];
		ram[pc] = temp;
	}
	break;
	case 0xC6:
	case 0xC7:
	case 0xC8:
	case 0xC9:
	case 0xCA:
	case 0xCB:
	case 0xCC:
	case 0xCD:
	case 0xCE:
	case 0xCF: //XCH A, register or adress in register
	{
		temp = ram[acc];
		ram[acc] = ram[returnRegisterAddres(opcode)];
		ram[returnRegisterAddres(opcode)] = temp;
	}
	break;
	case 0xD0:  //POP
	{
		ram[rom[pc++]] = ram[ram[sp]];
		ram[sp]--;
	}
	break;
	case 0xD1:  //ACALL addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		high >>= 5;
		++pc;
		address = pc;
		ram[sp]++;
		ram[ram[sp]] = address & 0xFF;
		ram[sp]++;
		ram[ram[sp]] = (address >> 8) & 0xFF;
		pc = (high << 8) | low;
	}
	break;
	case 0xD2:
		break;
	case 0xD3: //SETB C
		setPSW_C(1);
		break;
	case 0xD4: //DJNZ direct, offset
	{
		if ((ram[acc] & 0x0F) > 9 || (getPSW_AC() >> 6) == 1)
			ram[acc] += 6;
		if ((ram[acc] & 0xF0) > 9 || (getPSW_C() >> 7) == 1)
			ram[acc] += 0x60;
	}
	break;
	case 0xD5:  //DJNZ direct, offset
	{
		ram[rom[pc++]] -= 1;
		offset = rom[pc++];
		if (ram[rom[pc++]] != 0) {
			pc = pc + offset;
		}
	}
	break;
	case 0xD6:
	case 0xD7: //XCHD A, addres in register
	{
		temp = ram[acc];
		temp1 = ram[returnRegisterAddres(opcode)];
		temp &= 0x0F;
		temp1 &= 0x0F;
		ram[acc] &= 0x0F;
		ram[returnRegisterAddres(opcode)] &= 0x0F;
		ram[acc] |= temp1;
		ram[returnRegisterAddres(opcode)] |= temp;
	}
		
	case 0xD8:
	case 0xD9:
	case 0xDA:
	case 0xDB:
	case 0xDC:
	case 0xDD:
	case 0xDE:
	case 0xDF: //DJNZ  register, offset
	{
		temp = ram[acc];
		temp1 = ram[returnRegisterAddres(opcode)];
		temp &= 0x0F;
		temp1 &= 0x0F;
		ram[acc] &= 0x0F;
		ram[returnRegisterAddres(opcode)] &= 0x0F;
		ram[acc] |= temp1;
		ram[returnRegisterAddres(opcode)] |= temp;
	}
	break;
	case 0xE0: //MOCX A, DPTR
		break;
	case 0xE1: //ACALL addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		++pc;
		high >>= 5;
		pc = (high << 8) | low;
	}
	break;
	case 0xE2: // MOVX A, @R0
		ram[acc] = ram[ram[0x00]];
		break;
	case 0xE3: //MOVX A, @R1
		ram[acc] = ram[ram[0x01]];
		break; 

	case 0xE4: // CLR A
		ram[acc] = 0x00;
		break;
	case 0xE5: //MOV A, direct
	{
		ram[acc] = ram[rom[pc]];
		pc++;
	}
	break;
	case 0xE6:
	case 0xE7:
	case 0xE8:
	case 0xE9:
	case 0xEA:
	case 0xEB:
	case 0xEC:
	case 0xED:
	case 0xEE:
	case 0xEF: // MOV A, register or adress in register
		ram[acc] = ram[returnRegisterAddres(opcode)];
		break;
	case 0xF0:
		break;
	case 0xF1: //ACALL addr11
	{
		low = rom[pc];
		high = rom[pc - 1];
		high >>= 5;
		++pc;
		address = pc;
		ram[sp]++;
		ram[ram[sp]] = address & 0xFF;
		ram[sp]++;
		ram[ram[sp]] = (address >> 8) & 0xFF;
		pc = (high << 8) | low;
	}
	break;
	case 0xF2: //MOVX @R0
		ram[ram[0x00]] = ram[acc];
		break;
	case 0xF3: //MOVX @R0
		ram[ram[0x01]] = ram[acc];
		break;
	case 0xF4: //CPL A
		ram[acc] = ~ram[acc];
		break;
	case 0xF5: //MOV direct, A
	{
		ram[rom[pc]] = ram[acc];
		pc++;
	}
	break;
	case 0xF6:
	case 0xF7:
	case 0xF8:
	case 0xF9:
	case 0xFA:
	case 0xFB:
	case 0xFC:
	case 0xFE:
	case 0xFF: //MOV register or adress in register, A
		ram[returnRegisterAddres(opcode)] = ram[acc];
		break;
	default:
		break;
	}
}

