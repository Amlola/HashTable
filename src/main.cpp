#include "../inc/hash_table.h"


int main() 
    {
    HashTable hash_table = {};

    Text data = {};

    FILE* input_file = fopen("in_file.txt", "r");

    GetDataFromFile(input_file, &data);

    uint64_t (*hash_functions[])(const char*, size_t) = 
    {
    HashFuncZero,
    HashFuncFirstLetter,
    HashFuncStrlen,
    HashAsciiSum,
    HashFuncSumDivStrlen
    };

    HashTableCtor(&hash_table, HASH_TABLE_CAPACITY);

    hash_table.hash_function = hash_functions[4];

    FillHashTable(&hash_table, &data);

    #ifdef HASH_DUMP

    HashTableDump(&hash_table);

    #endif

    printf("Dispload Factor: %ld\n", hash_table.count_elem / hash_table.size);

    HashTableDtor(&hash_table);

    Free(&data);

    return 0;
    }