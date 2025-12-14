#include "list.h"

#include <assert.h>

int AoC_listPush(AoC_list_t* l, void* elem) {
    assert(l);
    assert(elem);
    return 1;
}

void* AoC_listPop(AoC_list_t* l) {
    assert(l);
    return NULL;
}

int AoC_listIterNext(AoC_list_t* l, void* elem) {
    assert(l);
    assert(elem);
    return 1;
}

int AoC_listDestroy(AoC_list_t* l) {
    assert(l);
    return 1;
}

int AoC_listCount(AoC_list_t* l) {
    assert(l);
    return 1;
}
