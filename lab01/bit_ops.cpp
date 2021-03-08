#include "bit_ops.h"

// Возвращает бит номер n числа x.
#include "bit_ops.h"

// Возвращает бит номер n числа x.
// Предполагается 0 <= n <= 31
unsigned get_bit(unsigned x,
                 unsigned n) {
    // YOUR CODE HERE
    // Взврат -1 бессмысленный и сделан для правильной компиляции
    return (x >> n) & 1; 
    return -1;
}
// Выставляет значение v в бите номер n
// Предполагается что 0 <= n <= 31 и v равно 0 или 1
void set_bit(unsigned * x,
             unsigned n,
             unsigned v) {
    // YOUR CODE HERE
    *x = ((*x) & ((v ^ 1) << n)) ^ ((*x) | (v << n));
}
// Меняет значение бита номер n на противоположное.
// Предполагается что 0 <= n <= 31
void flip_bit(unsigned * x,
              unsigned n) {
    // YOUR CODE HERE
    (*x) = (*x) ^ (1 << n); 
}

