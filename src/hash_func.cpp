#include "../inc/hash_func.h"


uint64_t HashFuncZero(const char* word, size_t lenght_word)
    {
    return 0;
    }


uint64_t HashFuncFirstLetter(const char* word, size_t lenght_word)
    {
    return word[0] % HASH_TABLE_CAPACITY;
    }


uint64_t HashFuncStrlen(const char* word, size_t lenght_word)
    {
    return lenght_word % HASH_TABLE_CAPACITY;
    }


uint64_t HashAsciiSum(const char* word, size_t lenght_word)
    {
    uint64_t sum = 0;

    for (size_t i = 0; i < lenght_word; i++) 
        sum += word[i];

    return sum % HASH_TABLE_CAPACITY;
    }


uint64_t HashFuncSumDivStrlen(const char* word, size_t len)
    {
    uint64_t sum = HashAsciiSum(word, len);

    return (sum / len) % HASH_TABLE_CAPACITY;
    }
