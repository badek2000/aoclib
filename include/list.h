#ifndef AOC_LIST_H_
#define AOC_LIST_H_

#include <stdlib.h>

typedef struct _AoC_list_s {
    size_t count;
    void* first_element;
} AoC_list_t;

int AoC_listPush(AoC_list_t* l, void* elem);
void* AoC_listPop(AoC_list_t* l);
int AoC_listIterNext(AoC_list_t* l, void* elem);
int AoC_listDestroy(AoC_list_t* l);
int AoC_listCount(AoC_list_t* l);

#endif // AOC_LIST_H_