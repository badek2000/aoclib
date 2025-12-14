#include "file_parser.h"

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int AoC_parseFile(char* file_name, AoC_parserFun parserFunction, void* args) {
    FILE* fp = NULL;
    char* line = NULL;
    size_t len = 0;
    ssize_t read = 0;

    fp = fopen(file_name, "r");

    if (fp == NULL) {
        return -1;
    }

    while (-1 != (read = getline(&line, &len, fp))) {
        assert(parserFunction);
        parserFunction(line, read, args);
    }

    free(line);
    return fclose(fp);
}

bool AoC_isNumerical(char c) {
    return ('0' <= c) && (c <= '9');    
}
bool AoC_isAlpha(char c) {
    return ('a' <= c) && (c <= 'Z');
}
bool AoC_isAlphanumerical(char c) {
    return AoC_isAlpha(c) || AoC_isNumerical(c);
}
