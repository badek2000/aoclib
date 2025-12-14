#include "list.h"

#include <assert.h>

int AoC_listPush(AoC_list_t* l, void* elem) {
    assert(l);
    assert(elem);

    if (l->first_element == NULL) {
        l->first_element = elem;
        return 0;
    }

    while () {
        
    }
    
}

void* AoC_listPop(AoC_list_t* l) {

}

int AoC_listIterNext(AoC_list_t* l, void* elem) {

}

int AoC_listDestroy(AoC_list_t* l) {

}

int AoC_listCount(AoC_list_t* l) {

}
