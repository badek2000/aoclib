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
