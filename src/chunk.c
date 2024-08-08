#include <stdlib.h>

#include "chunk.h"

#include "memory.h"

// Инициализация массива
void initChunk(Chunk* chunk) {
    chunk->count = 0;
    chunk->capacity = 0;
    chunk->code = NULL;
    chunk->lines = NULL;
    initValueArray(&chunk->constants);
}

void freeChunk(Chunk* chunk) {
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    freeValueArray(&chunk->constants);
    initChunk(chunk);
}

// Добавление инструкции в массив
void writeChunk(Chunk* chunk, uint8_t byte, int line) {
    if (chunk->capacity < chunk->count + 1) {
        int oldCapacity = chunk->capacity;
        // Вычисляет новую вместимость массива на основе старой
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        // Как только мы узнаем желаемую емкость, мы создаем или увеличиваем массив до этого размера
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }

    chunk->code[chunk->count] = byte;
    chunk->lines[chunk->count] = line;
    chunk->count++;
}

// Добавление константы в массив значений
int addConstant(Chunk* chunk, Value value) {
    writeValueArray(&chunk->constants, value);
    //Возвращение индекса, к которому была принесена константа
    return chunk->constants.count - 1;
}
