#include "vec.h"

#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

#include <stdio.h>

#define DEFUALT_INITIAL_CAP (8)
#define DEFAULT_GROW_COEF   (2)

static bool _checkOverflow(size_t a, size_t b, size_t *out);
static AoC_vec_rc_e _vecGrowIfNeeded(AoC_vec_t *vec, size_t needed_len);

AoC_vec_rc_e AoC_vecInit(AoC_vec_t *v, size_t elem_size) {
    if ((!v) || (elem_size == 0)) return AOC_VEC_BADARG;

    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
    v->elem_size = elem_size;

    return AOC_VEC_OK;
}

void AoC_vecFree(AoC_vec_t* v) {
    if (!v) return;

    free(v->data);
    v->data = NULL;
    v->length = 0;
    v->capacity = 0;
    v->elem_size = 0;
}

size_t AoC_vecLength(const AoC_vec_t *v) {
    return v ? v->length : 0;
}

size_t AoC_vecCapacity(const AoC_vec_t *v) {
    return v ? v->capacity : 0;
}

AoC_vec_rc_e AoC_vecReserve(AoC_vec_t *v, size_t new_cap) {
    if (!v) return AOC_VEC_BADARG;
    if (new_cap <= v->capacity) return AOC_VEC_OK;

    size_t bytes = 0;
    if (_checkOverflow(new_cap, v->elem_size, &bytes)) return AOC_VEC_OOM;

    void *p = realloc(v->data, bytes);
    if (!p) return AOC_VEC_OOM;

    v->data = p;
    v->capacity = new_cap;
    return AOC_VEC_OK;
}

AoC_vec_rc_e AoC_vecShrinkToFit(AoC_vec_t *v) {
    if (!v) return AOC_VEC_BADARG;
    if (v->length == v->capacity) return AOC_VEC_OK;

    if (v->length == 0) {
        free(v->data);
        v->data = NULL;
        v->capacity = 0;
        return AOC_VEC_OK;
    }

    size_t bytes = 0;
    if (_checkOverflow(v->length, v->elem_size, &bytes)) return AOC_VEC_OOM;

    void *p = realloc(v->data, bytes);
    if (!p) return AOC_VEC_OOM;

    v->data = p;
    v->capacity = v->length;
    return AOC_VEC_OK;
}

void AoC_vecClear(AoC_vec_t *v) {
    if (!v) return;
    v->length = 0;
}

void *AoC_vecGet(const AoC_vec_t *v, size_t idx) {
    if ((!v) || (idx >= v->length)) return NULL;
    return (char*)v->data + idx * v->elem_size;
}

const void *AoC_vecGetConst(const AoC_vec_t *v, size_t idx) {
    if ((!v) || (idx >= v->length)) return NULL;
    return (const char*)v->data + idx * v->elem_size;
}

AoC_vec_rc_e AoC_vecSet(AoC_vec_t *v, size_t idx, const void *elem) {
    if ((!v) || idx >= v->length) return AOC_VEC_BADARG;
    if (idx >= v->length) return AOC_VEC_BOUNDS;
    memcpy((char*)v->data + idx * v->elem_size, elem, v->elem_size);
    return AOC_VEC_OK;
}

AoC_vec_rc_e AoC_vecPush(AoC_vec_t *v, const void *elem) {
    if ((!v) || (!elem)) return AOC_VEC_BADARG;
    AoC_vec_rc_e ret = _vecGrowIfNeeded(v, v->length + 1);
    printf("%s\n", AoC_vecRcToString(ret));
    if (ret != AOC_VEC_OK) return ret;

    memcpy((char*)v->data + v->length * v->elem_size, elem, v->elem_size);
    ++v->length;
    return AOC_VEC_OK;
}

AoC_vec_rc_e AoC_vecPop(AoC_vec_t *v, void *out_elem) {
    if (!v) return AOC_VEC_BADARG;
    if (v->length == 0) return AOC_VEC_BOUNDS;

    --v->length;
    if (out_elem) {
        memcpy(out_elem, (char*)v->data + v->length * v->elem_size, v->elem_size);
    }

    return AOC_VEC_OK;
}

AoC_vec_rc_e AoC_vecInsert(AoC_vec_t *v, size_t idx, const void *elem) {
    if (!v || !elem) return AOC_VEC_BADARG;
    if (idx > v->length) return AOC_VEC_BOUNDS;

    AoC_vec_rc_e ret = _vecGrowIfNeeded(v, v->length + 1);
    if (ret != AOC_VEC_OK) return ret;

    char *base = (char*)v->data;
    
    if (idx < v->length) {
        memmove(
            base + (idx + 1) * v->elem_size,
            base + idx * v->elem_size,
            (v->length - idx) * v->elem_size
        );
    }

    memcpy(base + idx * v->elem_size, elem, v->elem_size);
    ++v->length;
    return AOC_VEC_OK;
}

AoC_vec_rc_e AoC_vecErase(AoC_vec_t *v, size_t idx, void *out_elem) {
    if (!v) return AOC_VEC_BADARG;
    if (idx >= v->length) return AOC_VEC_BOUNDS;

    char *base = (char*)v->data;

    if (out_elem) {
        memcpy(out_elem, base + idx * v->elem_size, v->elem_size);
    }

    if (idx + 1 < v->length) {
        memmove(
            base + idx * v->length,
            base + (idx + 1) * v->elem_size,
            (v->length - idx - 1) * v->elem_size
        );
    }

    --v->length;
    return AOC_VEC_OK;
}

AoC_vec_rc_e AoC_vecSwap(AoC_vec_t *v, void *a, void *b) {
    if ((!v) || (!a) || (!b) || (v->elem_size == 0)) {
        return AOC_VEC_BADARG;
    }

    void* tmp = malloc(v->elem_size);
    
    memcpy(a, b, v->elem_size);
    memcpy(b, tmp, v->elem_size);
    
    free(tmp);

    return AOC_VEC_OK;
}

bool AoC_vecCheckIfUnique(const AoC_vec_t *v, const void *elem, eq_t eq) {
    if ((!v) || (!elem) || (!eq)) return false;
    size_t cnt = 0;
    
    printf("len: %lu\n", AoC_vecLength(v));
    for (size_t i = 0; i < AoC_vecLength(v); ++i) {
        if (eq(elem, AoC_vecGet(v, i)) == 0) ++cnt;
    }

    return (cnt < 2);
}

AoC_vec_rc_e AoC_vecSort(AoC_vec_t *v, eq_t eq) {
    if ((!v) || (!eq)) return AOC_VEC_BADARG;
    void* elem_1 = NULL; 
    void* elem_2 = NULL;

    AoC_vec_rc_e ret = 0;

    for (size_t i = 0; i < AoC_vecLength(v); ++i) {
        elem_1 = AoC_vecGet(v, i);
        for (size_t j = 0; j < AoC_vecLength(v); ++j) {
            elem_2 = AoC_vecGet(v, j);
            if (eq(elem_1, elem_2) > 0) {
                ret = AoC_vecSwap(v, elem_1, elem_2);
                if (ret != AOC_VEC_OK) return ret;
            }
        }
    }

    return AOC_VEC_OK;
}

const char* AoC_vecRcToString(const AoC_vec_rc_e rc) {
    switch (rc)
    {
    case AOC_VEC_OK:
        return "AOC_VEC_OK";
    case AOC_VEC_OOM:
        return "AOC_VEC_OOM";
    case AOC_VEC_BOUNDS:
        return "AOC_VEC_BOUNDS";
    case AOC_VEC_BADARG:
        return "AOC_VEC_BADARG";
    default:
        return "AOC_VEC_UNKNOWN_ERR";
    }
}

static bool _checkOverflow(size_t a, size_t b, size_t *out) {
    if ((a == 0) || (b == 0)) {
        *out = 0;
        return false;
    }

    if (a > (SIZE_MAX / b)) return true;

    *out = a * b;
    return false;
}

static AoC_vec_rc_e _vecGrowIfNeeded(AoC_vec_t *v, size_t needed_len) {
    if (needed_len <= v->capacity) return AOC_VEC_OK;

    size_t new_cap = (v->capacity == 0) ? 
                     (DEFUALT_INITIAL_CAP) : 
                     (DEFAULT_GROW_COEF * v->capacity);

    while (new_cap < needed_len) {
        if (new_cap > SIZE_MAX / 2) {
            new_cap = needed_len;
            break;
        }

        return AoC_vecReserve(v, new_cap);
    }

    return AOC_VEC_OK;   
}
