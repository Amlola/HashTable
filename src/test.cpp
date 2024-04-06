#include "../inc/test.h"


size_t GetResultsFindWords(HashTable* hash_table, Text* data)
    {
    size_t find_words = 0;

    for (size_t i = 0; i < data->count_n; i++)
        find_words += (FindWord(hash_table, (data->str + i)->adress, (data->str + i)->length));

    return find_words;
    }