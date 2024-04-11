#pragma once


#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <nmmintrin.h>


typedef uint32_t hash_t;


const size_t HASH_TABLE_CAPACITY = 1019;     // 239 2551
const size_t NUM_OF_BITS = sizeof(hash_t) * 8;


hash_t HashFuncConstant(const char* word, size_t lenght_word);

hash_t HashFuncFirstLetter(const char* word, size_t lenght_word);

hash_t HashFuncStrlen(const char* word, size_t lenght_word);

hash_t HashFuncSumDivStrlen(const char* word, size_t lenght_word);

hash_t HashFuncAsciiSum(const char* word, size_t lenght_word);

hash_t HashFuncRor(const char* word, size_t lenght_word);

hash_t HashFuncRol(const char* word, size_t lenght_word);

hash_t HashFuncCRC32(const char* word, size_t lenght_word);

hash_t AsciiSum(const char* word, size_t lenght_word);

hash_t HashFuncSimdCRC32(const char* word, size_t lenght_word);
