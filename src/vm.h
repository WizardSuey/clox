#ifndef  clox_vm_h
#define  clox_vm_h

#include "chunk.h"
#include "value.h"

#define STACK_MAX 256

// Виртуальная машина
typedef struct {
    Chunk* chunk;
    uint8_t* ip; // указатель на текущую инструкцию
    Value stack[STACK_MAX]; // Стек значений
    Value* stackTop;    // Указатель на вершину стека
} VM;

typedef enum {
    INTERPRET_OK,
    INTERPRET_COMPILE_ERROR,
    INTERPRET_RUNTIME_ERROR
} InterpretResult;

void initVM();
void freeVM();
InterpretResult interpret(Chunk* chunk);
void push(Value value);
Value pop();

#endif