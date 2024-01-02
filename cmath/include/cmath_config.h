#ifndef _CMATH_CONFIG_H
#define _CMATH_CONFIG_H

typedef unsigned char       u8;
typedef unsigned int        u32;
typedef unsigned long long  u64;

typedef float  f32;  // 32-bit floating-point
typedef double f64;  // 64-bit floating-point
typedef long double f128; // 128-bit floating-point (common on other systems)

#define false 0
#define true  1

/**
 * 
*/
#define NUMARGS(type, ...) (sizeof((type[]){0.0f, ##__VA_ARGS__}) / sizeof(type) - 1)

/**
 * #define convert(from, to, conversion, from_type, to_type) \
    to_type convert_##from##_to_##to(from_type f)         \
    {                                                     \
        return conversion;                                \
    }

    convert(f, c, (f - 32) * 5.0 / 9.0, float, float);
    printf("%f F = %f C\n", 70.0f, convert_f_to_c(70.0f));

    return 0;
}
*/

#define MAXIMUM(a, b) (a > b ? a: b)
#define MINIMUM(a, b) (a < b ? a: b)

#define WORD_BITLEN 8

#if WORD_BITLEN == 8
typedef u8 WORD;
#define WORD_ONE 0x01
#elif WORD_BITLEN == 64
typedef u64 WORD;
#define WORD_ONE 0x01LL
#else
typedef u32 WORD;
#define WORD_ONE 0x01
#endif


#endif // _CMATH_CONFIG_H