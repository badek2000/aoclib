#ifndef AOC_FILE_PARSER_
#define AOC_FILE_PARSER_

#include <stddef.h>
#include <stdbool.h>

/* ~~~~~~~~~~~~~~~~ File parser ~~~~~~~~~~~~~~~ */
typedef void(*AoC_parserFun)(char* line, size_t len, void* args);
int AoC_parseFile(char* file_name, AoC_parserFun parserFunction, void* args);

/* ~~~~~~~~~~~~~~~~ String utils ~~~~~~~~~~~~~~ */
bool AoC_isNumerical(char c);
bool AoC_isAlpha(char c);
bool AoC_isAlphanumerical(char c);

#endif // AOC_FILE_PARSER_
