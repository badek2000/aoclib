#ifndef VEC_H_
#define VEC_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct _AoC_vec_s {
    void* data;
    size_t capacity;
    size_t length;
    size_t elem_size;
} AoC_vec_t;

typedef enum {
    AOC_VEC_OK = 0,
    AOC_VEC_OOM,
    AOC_VEC_BOUNDS,
    AOC_VEC_BADARG,
} AoC_vec_rc_e;

AoC_vec_rc_e AoC_vecInit(AoC_vec_t *v, size_t elem_size);
void AoC_vecFree(AoC_vec_t* v);

size_t AoC_vecLength(const AoC_vec_t *v);
size_t AoC_vecCapacity(const AoC_vec_t *v);

AoC_vec_rc_e AoC_vecReserve(AoC_vec_t *v, size_t new_cap);
AoC_vec_rc_e AoC_vecShrinkToFit(AoC_vec_t *v);
void AoC_vecClear(AoC_vec_t *v);

void *AoC_vecGet(AoC_vec_t *v, size_t idx);
const void *AoC_vecGetConst(const AoC_vec_t *v, size_t idx);

AoC_vec_rc_e AoC_vecSet(AoC_vec_t *v, size_t idx, const void *elem);

AoC_vec_rc_e AoC_vecPush(AoC_vec_t *v, const void *elem);
AoC_vec_rc_e AoC_vecPop(AoC_vec_t *v, void *out_elem);
AoC_vec_rc_e AoC_vecInsert(AoC_vec_t *v, size_t idx, const void *elem);
AoC_vec_rc_e AoC_vecErase(AoC_vec_t *v, size_t idx, void *out_elem);

#define AOC_VEC_INIT_TYPED(v, T) AoC_vecInit((v), sizeof(T))
#define AOC_VEC_GET_AS(v, T, i) ((T*) AoC_vecGet((v), (i)))
#define AOC_VEC_PUSH_VAL(v, T, x) do { T _tmp=(x); AoC_vecPush((v), &_tmp); } while(0)

#endif // VEC_H_