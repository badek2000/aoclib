#ifndef AOC_FILE_PARSER_
#define AOC_FILE_PARSER_

/* ~~~~~~~~~~~~~~~~ File parser ~~~~~~~~~~~~~~~ */
typedef void(*AoC_parserFun)(char* line, size_t len, void* args);
int AoC_parseFile(char* file_name, AoC_parserFun parserFunction, void* args);

#endif // AOC_FILE_PARSER_
