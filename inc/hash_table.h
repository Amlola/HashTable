#pragma once



#include "../inc/read.h"
#include "../List_Index/list.h"
#include "../inc/hash_func.h"


static FILE* hash_logfile = NULL;


enum HASH_STATUS 
    {
    HASH_OK           = 0,
    VALUE_REPEAT      = 1 << 1,
    NOT_FIND_VALUE    = 1 << 2,
    LISTS_ALLOC_ERROR = 1 << 3
    };


struct HashTable 
    {
    LIST* list;
    size_t size;
    size_t count_elem;
    uint64_t (*hash_function)(const char*, size_t);
    };


HASH_STATUS HashTableCtor(HashTable* hash_table, size_t table_size);

void HashTableDtor(HashTable* hash_table);

HASH_STATUS TableInsert(HashTable* hash_table, const char* word, size_t lenght_word);

HASH_STATUS TableDelete(HashTable* hash_table, const char* word, size_t lenght_word);

size_t CheckValueInTable(LIST* list, const char* word, size_t lenght_word);

bool FindWord(HashTable* hash_table, const char* word, size_t lenght_word);

HASH_STATUS FillHashTable(HashTable* hash_table, Text* data);

void HashTableDump(HashTable* hash_table);
