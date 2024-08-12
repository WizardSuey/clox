#include <stdio.h>
#include <string.h>

#include "common.h"
#include "scanner.h"


typedef struct {
    const char* start;  // Указатель на начало текущей лексемы
    const char* current; // Указатель на текущий символ
    int line;
} Scanner;

Scanner scanner;

void initScanner(const char* source) {
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}