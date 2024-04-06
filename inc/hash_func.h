#pragma once


#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>

const size_t HASH_TABLE_CAPACITY = 1279;


uint64_t HashFuncZero(const char* word, size_t lenght_word);

uint64_t HashFuncFirstLetter(const char* word, size_t lenght_word);

uint64_t HashFuncStrlen(const char* word, size_t lenght_word);

uint64_t HashAsciiSum(const char* word, size_t lenght_word);

uint64_t HashFuncSumDivStrlen(const char* word, size_t len);