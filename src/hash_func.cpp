#include "../inc/hash_func.h"


hash_t HashFuncZero(const char* word, size_t lenght_word)
    {
    return 0;
    }


hash_t HashFuncFirstLetter(const char* word, size_t lenght_word)
    {
    return word[0];
    }


hash_t HashFuncStrlen(const char* word, size_t lenght_word)
    {
    return lenght_word;
    }


hash_t HashFuncAsciiSum(const char* word, size_t lenght_word) 
    {
    return AsciiSum(word, lenght_word);
    }


hash_t HashFuncSumDivStrlen(const char* word, size_t lenght_word)
    {
    return (AsciiSum(word, lenght_word) / lenght_word);
    }


hash_t HashFuncRor(const char* word, size_t lenght_word)
    {
    hash_t hash_value = 0;

    for (size_t i = 0; i < lenght_word; i++) 
        hash_value = ((hash_value >> 1) | (hash_value << (NUM_OF_BITS - 1))) ^ word[i];

    return hash_value;
    }


hash_t HashFuncRol(const char* word, size_t lenght_word)
    {
    hash_t hash_value = 0;

    for (size_t i = 0; i < lenght_word; i++) 
        hash_value = ((hash_value << 1) | (hash_value >> (NUM_OF_BITS - 1))) ^ word[i];

    return hash_value;
    }


hash_t HashFuncCRC32(const char* word, size_t lenght_word) 
    {
    unsigned int byte = 0, mask = 0;
    unsigned int crc = 0xFFFFFFFF;
    
    for (int i = 0; word[i] != 0; i++) 
        {
        byte = word[i];

        crc = crc ^ byte;
            
        for (int j = 7; j >= 0; j--) 
            {
            mask = -(crc & 1);
            crc = (crc >> 1) ^ (0xEDB88320 & mask);
            }
        }

    return (hash_t)(~crc);
    }


hash_t AsciiSum(const char* word, size_t lenght_word)
    {
    hash_t ascii_sum = 0;

    for (size_t i = 0; i < lenght_word; i++) 
        ascii_sum += word[i];

    return ascii_sum;
    }