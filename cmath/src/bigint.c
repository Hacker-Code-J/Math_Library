#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "bigint.h"

const bigint BIGINT_ZERO = {true, 0, 0, NULL};

bigint allocateBigint(u32 capacity) {
    bigint ret;
    ret.capacity = capacity;
    ret.used = 0;
    ret.sign = true;
#if WORD_BITLEN == 8
    ret.digits = (u8*)malloc(capacity * sizeof(u8));
#elif WORD_BITLEN == 64
    ret.digits = (u64*)malloc(capacity * sizeof(u64));
#else
    ret.digits = (u32*)malloc(capacity * sizeof(u32));
#endif
    return ret;
}

void freeBigint(bigint* data) {
    data->capacity = 0;
    data->used = 0;
    data->sign = 1;
    free(data->digits);
}

bigint strToBigint(char* str) {
    u32 len = strlen(str);
    u32 used = len;

    bool sign = true;
    if (str[0] == '-') {
        sign = false;
        used--;
    }

    if (used == 0) return BIGINT_ZERO;

    bigint ret = allocateBigint(used);
    ret.used = used;
    ret.sign = sign;

    for (u32 idx = 0; idx < used; idx++) {
        char c = str[len - 1 - idx];
        if (c >= '0' && c < '9')
            ret.digits[idx] = c - '0';
        else
            return BIGINT_ZERO;
    }

    return ret;
}

bigint newBigint(int data) {
    bool sign = true;
    if (data < 0) {
        sign = false;
        data *= -1;
    }

    bigint ret = newPositiveBigint(data);
    ret.sign = sign;
    
    return ret;
}
bigint newPositiveBigint(u32 data) {
    u32 copyData = data;
    int used = 0;
    while (copyData > 0) {
        used++;
        copyData /= 10;
    }

    bigint ret = allocateBigint(used);
    ret.used = used;
    for (u32 idx = 0;
         idx < used;
         idx++, data /= 10) {
        ret.digits[idx] = data % 10;
    }

    return ret;
}

char* bigintPtrToString(bigint* data) {
    if (!data->used) return "0";

    u32 usedChars = data->used;
    if(!data->sign) usedChars++;

    char* ret = (char*)malloc((usedChars + 1) * sizeof(char));

    if(!ret) return NULL;

    u32 strIdx = 0;
    if (!data->sign) ret[strIdx++] = '-';

    for (u32 digitIdx = data->used;
         digitIdx != 0;
         digitIdx--, strIdx++) {
        ret[strIdx] = '0' + data->digits[digitIdx - 1];
    }

    ret[usedChars] = '\0';

    return ret;
}
char* bigintToString(bigint data) {
    return bigintPtrToString(&data);
}

char compareBigint(bigint data1, bigint data2) {
    if (data1.sign && !data2.sign)           // data1 >= 0, data2 < 0
        return 1;
    else if (!data1.sign && data2.sign)      // data1 < 0, data2 >= 0
        return -1;
    else if (!data1.sign && !data2.sign) {
        data1.sign = true;
        data2.sign = true;
        char comp = compareBigint(data1, data2);
        return -comp;
    }

    if (data1.used > data2.used)
        return 1;
    else if (data1.used < data2.used)
        return -1;

    u32 idx = data1.used;
    while (idx--) {
        if (data1.digits[idx] > data2.digits[idx])
            return 1;
        else if (data1.digits[idx] < data2.digits[idx])
            return -1;
    }

    return 0;
}

bigint addBigint(bigint data1, bigint data2) {
    if (data1.sign && !data2.sign) {            // data1 + -data2 = data1 - data2
        data2.sign = true;
        return subBigint(data1, data2);
    } else if (!data1.sign && data2.sign) {     // -data1 + data2 = data2 - data1
        data1.sign = true;
        return subBigint(data2, data1);
    }

    u32 used = MAXIMUM(data1.used, data2.used) + 1;

    bigint ret = allocateBigint(used);
    ret.used = used;

    bool carry = false;
    for (u32 idx = 0; idx < ret.used; idx++) {
        WORD res = carry ? 1 : 0;
        if (idx < data1.used)
            res += data1.digits[idx];
        if (idx < data2.used)
            res += data2.digits[idx];

        if (res >= 10) {
            carry = true;
            res -= 10;
        } else {
            carry = false;
        }

        ret.digits[idx] = res;
    }

    while (!ret.digits[ret.used - 1])
        ret.used--;

    if (!data1.sign && !data2.sign)
        ret.sign = false;

    return ret;
}
bigint subBigint(bigint data1, bigint data2) {
    char comp = compareBigint(data1, data2);
    if (!comp) return BIGINT_ZERO;

    if (data1.sign && !data2.sign) {            // data1 - -data2 = data1 + data2
        data2.sign = true;
        return addBigint(data1, data2);
    } else if (!data1.sign && data2.sign) {     // -data1 - data2 = -data1 + -data2
        data1.sign = false;
        return addBigint(data1, data2);
    } else if (!data1.sign && !data2.sign) {    // -data1 - -data2 = data2 - data1
        data1.sign = true;
        data2.sign = true;
        return subBigint(data2,data1);
    } else {
        if (comp < 0) {
            bigint res = subBigint(data2, data1);
            res.sign = !res.sign;
            return res;
        }
    }

    u32 used = data1.used;

    bigint ret = allocateBigint(used);
    ret.used = used;

    bool carry = false;
    for (u32 idx = 0; idx < ret.used; idx++) {
        char res = carry ? -1 : 0;
        if (idx < data1.used)
            res += data1.digits[idx];
        if (idx < data2.used)
            res -= data2.digits[idx];

        if (res < 0) {
            carry = true;
            res += 10;
        } else {
            carry = false;
        }

        ret.digits[idx] = res;
    }

    while (!ret.digits[ret.used - 1])
        ret.used--;
    
    return ret;
}