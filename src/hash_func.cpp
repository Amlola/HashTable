#include "../inc/hash_func.h"


static inline hash_t Ror(hash_t hash_value);
static inline hash_t Rol(hash_t hash_value);


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
        hash_value = Ror(hash_value) ^ word[i];

    return hash_value;
    }


hash_t HashFuncRol(const char* word, size_t lenght_word)
    {
    hash_t hash_value = 0;

    for (size_t i = 0; i < lenght_word; i++) 
        hash_value = Rol(hash_value) ^ word[i];

    return hash_value;
    }


hash_t HashFuncCRC32(const char* word, size_t lenght_word) 
    {
    hash_t crc_table[256] = {};
    hash_t crc = 0;
    
    for (size_t i = 0; i < 256; i++) 
        {
        crc = i;
            
        for (size_t j = 0; j < 8; j++) 
            {
            if (crc & 1)
                crc = (crc >> 1) ^ 0xEDB88320;
            
            else
                crc = crc >> 1;
            }

        crc_table[i] = crc;
        }

    crc = 0xFFFFFFFF;

    while (lenght_word--)
        crc = crc_table[(crc ^ *word++) & 0xFF] ^ (crc >> 8);

    return crc ^ 0xFFFFFFFF;
    }


hash_t AsciiSum(const char* word, size_t lenght_word)
    {
    hash_t ascii_sum = 0;

    for (size_t i = 0; i < lenght_word; i++) 
        ascii_sum += word[i];

    return ascii_sum;
    }


static inline hash_t Ror(hash_t hash_value)
    {
    return ((hash_value >> 1) | (hash_value << (NUM_OF_BITS - 1)));
    }


static inline hash_t Rol(hash_t hash_value)
    {
    return ((hash_value << 1) | (hash_value >> (NUM_OF_BITS - 1)));
    }