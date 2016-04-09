#ifndef __REGISTERS_H__
#define __REGISTERS_H__

struct registers {
	unsigned int GS, FS, ES, DS;
	unsigned int EDI, ESI, EBP, ESP, EBX, EDX, ECX, EAX;
	unsigned int interrupt_number, error_code;
	unsigned int EIP, CS, eflags, useresp, SS;
};

typedef struct registers registers_t;

#endif /* __REGISTERS_H__ */
