#include "../inc/hash_table.h"


int main() 
    {
    Text data = {};

    FILE* input_file = fopen("in_file.txt", "r");

    GetDataFromFile(input_file, &data);

    #ifdef COMPARISON

    GetInfoAboutFunc(&data);

    #else

    HashTable hash_table = {};

    HashTableCtor(&hash_table, HASH_TABLE_CAPACITY);

    hash_table.hash_function = HashFuncIntrincicCRC32;

    FillHashTable(&hash_table, &data);

    Text data_test = {};

    FILE* test_file = fopen("test_file.txt", "r");

    GetDataFromFile(test_file, &data_test);

    size_t find_words = GetResultsFindWords(&hash_table, &data_test);

    printf("find words = %zu\n", find_words);

    HashTableDtor(&hash_table);

    Free(&data_test);

    Free(&data);

    #endif

    return 0;
    }


HASH_STATUS GetInfoAboutFunc(Text* data)
    {  
    hash_t (*hash_functions[])(const char*, size_t) = 
        {
        HashFuncConstant,        // 0
        HashFuncFirstLetter,     // 1
        HashFuncStrlen,          // 2
        HashFuncAsciiSum,        // 3
        HashFuncSumDivStrlen,    // 4
        HashFuncRor,             // 5
        HashFuncRol,             // 6
        HashFuncCRC32            // 7
        };

    for (size_t i = 0; i < sizeof(hash_functions) / sizeof(*hash_functions); i++)
        {
        HashTable hash_table = {};

        HashTableCtor(&hash_table, HASH_TABLE_CAPACITY);

        hash_table.hash_function = hash_functions[i];

        FillHashTable(&hash_table, data);

        /*if (i == 7)
            TableDump(&hash_table, i);*/

        GetStatOfHashFunc(&hash_table, files[i]);

        printf("Func%zu Load factor: %lf\n", i, (double)hash_table.count_elem / (double)HASH_TABLE_CAPACITY);

        HashTableDtor(&hash_table);
        }
    
    Free(data);

    return HASH_OK;
    }