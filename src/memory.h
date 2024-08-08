#ifndef clox_memory_h
#define clox_memory_h

#include "common.h"

// Вычисляет новую вместимость массива на основе старой
#define GROW_CAPACITY(capacity) ((capacity) < 8 ? 8 : (capacity) * 2)

// Создание или увеличение массива
#define GROW_ARRAY(type, pointer, oldCount, newCount) (type*)reallocate(pointer, sizeof(type) * (oldCount), sizeof(type) * (newCount))

// Для освобождения памяти
#define FREE_ARRAY(type, pointer, oldCount) reallocate(pointer, sizeof(type) * (oldCount), 0)

// Функция для динамического управления памятью
void* reallocate(void* pointer, size_t oldSize, size_t newSize);

#endif