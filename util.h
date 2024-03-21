#ifndef __UTIL_H__
#define __UTIL_H__
#include <stdio.h>
#define ANDYS_DEBUG_OUT(...) printf(__VA_ARGS__);
#if 0
#define DEBUG_OUT(...) printf(__VA_ARGS__);
#else
#define DEBUG_OUT(...) (void)0;
#endif

void initUART0(unsigned long baud, int alt);
unsigned char UART0Receive();
void UART0Send(unsigned char b);

#define DYNAMIC_MEMORY_SIZE 0x400
extern unsigned char __xdata dynamic_memory_pool[DYNAMIC_MEMORY_SIZE];


typedef void(* __data FunctionReference)();
extern FunctionReference runBootloader;

#endif