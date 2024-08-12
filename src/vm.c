#include "common.h"
#include "compiler.h"
#include "vm.h"
#include "stdio.h"
#include "debug.h"

VM vm;

// Сброс стека
static void resetStack() {
    vm.stackTop = vm.stack;
}

void initVM() {
    resetStack();
}

void freeVM() {

}

// Помещение значений в стек
void push(Value value) {
    *vm.stackTop = value;
    vm.stackTop++;
}

// Извлечение значений из стека
Value pop() {
    vm.stackTop--;
    return *vm.stackTop;
}

// Выполнение инструкций
static InterpretResult run() {
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    #define BINARY_OP(op) do { double b = pop(); double a = pop(); push(a op b); } while (false) // Бинарная инструкция с двумя операндами

    for (;;) {

        #ifdef DEBUG_TRACE_EXECUTION // Если включен режим отладки
            printf("          ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[ ");
                printValue(*slot);
                printf(" ]");
            }
            printf("\n");
            disassembleInstruction(vm.chunk, (int)((vm.ip - vm.chunk->code))); // Смещенеие в байтах
        #endif

        uint8_t instruction;

        switch (instruction = READ_BYTE()) {
            case OP_CONSTANT: {
                Value constant = READ_CONSTANT();
                push(constant);
                break;
            }
            case OP_ADD:        BINARY_OP(+); break;
            case OP_SUBTRACT:   BINARY_OP(-); break;
            case OP_MULTIPLY:   BINARY_OP(*); break;
            case OP_DIVIDE:     BINARY_OP(/); break;
            case OP_NEGATE:     push(-pop()); break;
            case OP_RETURN: {
                printValue(pop());
                printf("\n");
                return INTERPRET_OK;
            }
        }
    }

    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

InterpretResult interpret(const char* source) {
    compile(source);
    return INTERPRET_OK;
}