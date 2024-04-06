#include "../inc/test.h"



int main() 
    {
    Text data = {};

    FILE* input_file = fopen("in_file.txt", "r");

    GetDataFromFile(input_file, &data);

    #ifdef COMPARISON

    GetInfoAboutFunc(&data);

    #else

    OptimisionPart(&data);

    #endif

    return 0;
    }


HASH_STATUS GetInfoAboutFunc(Text* data)
    {  
    hash_t (*hash_functions[])(const char*, size_t) = 
        {
        HashFuncZero,            // 0
        HashFuncFirstLetter,     // 1
        HashFuncStrlen,          // 2
        HashFuncAsciiSum,        // 3
        HashFuncSumDivStrlen,    // 4
        HashFuncRor,             // 5
        HashFuncRol              // 6
        /*HashFuncCRC32            // 7*/
        };

    for (size_t i = 0; i < sizeof(hash_functions) / sizeof(*hash_functions); i++)
        {
        HashTable hash_table = {};

        HashTableCtor(&hash_table, HASH_TABLE_CAPACITY);

        hash_table.hash_function = hash_functions[i];

        FillHashTable(&hash_table, data);

        /*if (i == 3) 
            HashTableDump(&hash_table, i);*/

        GetStatOfHashFunc(&hash_table, files[i]);

        printf("Func: %zu Dispload Factor: %.3lf\n", i, double(hash_table.count_elem) / (double)hash_table.size);

        HashTableDtor(&hash_table);
        }

    Free(data);

    return HASH_OK;
    }


HASH_STATUS OptimisionPart(Text* data) 
    {
    HashTable hash_table = {};

    HashTableCtor(&hash_table, HASH_TABLE_CAPACITY);

    hash_table.hash_function = HashFuncRol;

    FillHashTable(&hash_table, data);

    Text data_test = {};

    FILE* input_file = fopen("test_file.txt", "r");

    GetDataFromFile(input_file, &data_test);

    printf ("FIND_WORDS = %zu\n", GetResultsFindWords(&hash_table, &data_test));

    HashTableDtor(&hash_table);

    Free(&data_test);

    Free(data);

    return HASH_OK;
    }