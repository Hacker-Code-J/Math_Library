#include "aes_utils.h"

#ifndef _AES_H
#define _AES_H

#define AES_IRREDUCIBLE 0x1B;

#define BLOCK_LEN 16
#define BLOCK_SIDE 4

#define AES_128 128
#define AES_192 192
#define AES_256 256

extern const u8 s_box[256];

extern const u8 mixColMat[BLOCK_SIDE][BLOCK_SIDE];

u8 galoisMul(u8 g1, u8 g2);

void AddRoundKey(u8 state[BLOCK_SIDE][BLOCK_SIDE], u8 roundKey[BLOCK_SIDE][BLOCK_SIDE]);
void SubByte(u8 state[BLOCK_SIDE][BLOCK_SIDE]);
void ShiftRows(u8 state[BLOCK_SIDE][BLOCK_SIDE]);
void MixColumns(u8 state[BLOCK_SIDE][BLOCK_SIDE]);

void KeySchedule(u8* ukey, int keyLen, u8 roundKeys[][BLOCK_SIDE][BLOCK_SIDE]);
void KeySchedule128(u8* ukey, u8 roundKeys[11][BLOCK_SIDE][BLOCK_SIDE]);
// void KeySchedule192(u8* ukey, int keyLen, u8[13][BLOCK_SIDE][BLOCK_SIDE]);
// void KeySchedule256(u8* ukey, int keyLen, u8[15][BLOCK_SIDE][BLOCK_SIDE]);

void aes_encrypt_block(u8* input, int n,
                        u8 roundKeys[][BLOCK_SIDE][BLOCK_SIDE], int Nr,
                        u8 output[BLOCK_LEN]);

void aes_encrypt(u8* input, int n,
                 u8* ukey, int keyLen,
                 u8** output);

#endif // _AES_H