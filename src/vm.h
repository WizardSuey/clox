#ifndef  clox_vm_h
#define  clox_vm_h

#include "chunk.h"

// Виртуальная машина
typedef struct {
    Chunk* chunk;
    uint8_t* ip; // указатель на текущую инструкцию
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);

#endif