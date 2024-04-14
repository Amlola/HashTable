#pragma once



#include "../inc/read.h"
#include "../List_Index/list.h"
#include "../inc/hash_func.h"


#ifdef DEBUG_TABLE
    #define ON_DEBUG_TABLE(...) __VA_ARGS__
    #define TableDump(table_ptr, table_num) HashTableDump(table_ptr, table_num);
    static FILE* hash_logfile = NULL;

#else
    #define ON_DEBUG_TABLE(...)
#endif


#define CHECK_HASH_TABLE_ERROR(table)               \
            ON_DEBUG_TABLE                          \
                (                                   \
                if (TableVerify(table) != NO_ERROR) \
                    {                               \
                    TableDump(table, 0)             \
                    return HASH_TABLE_ERROR;        \
                    }                               \
                )                                   \


const char* const files[] =
    {
    "data/hashfunc_constant.csv", 
    "data/hashfunc_[0].csv", 
    "data/hashfunc_strlen.csv", 
    "data/hashfunc_ascii.csv",
    "data/hashfunc_sumdivlen.csv", 
    "data/hashfunc_ror.csv", 
    "data/hashfunc_rol.csv", 
    "data/hashfunc_crc32.csv",
    "data/hashfunc_ascii2.csv",
    };


enum HASH_STATUS 
    {
    HASH_OK               = 0,
    VALUE_REPEAT          = 1 << 1,
    NOT_FIND_VALUE        = 1 << 2,
    LISTS_ALLOC_ERROR     = 1 << 3,
    CANT_OPEN_FILE        = 1 << 4,
    HASH_TABLE_ERROR      = -1
    };


struct HashTable 
    {
    LIST* list;
    size_t size;
    size_t count_elem;
    hash_t (*hash_function)(const char*, size_t);
    };


HASH_STATUS HashTableCtor(HashTable* hash_table, size_t table_size);

void HashTableDtor(HashTable* hash_table);

HASH_STATUS TableInsert(HashTable* hash_table, const char* word, size_t lenght_word);

HASH_STATUS TableDelete(HashTable* hash_table, const char* word, size_t lenght_word);

iterator_t CheckValueInTable(LIST* list, List_type avx_key, size_t lenght_word);

bool HashTableSearch(HashTable* hash_table, const char* word, size_t lenght_word);

HASH_STATUS FillHashTable(HashTable* hash_table, Text* data);

HASH_STATUS GetStatOfHashFunc(HashTable* hash_table, const char* name_file);

HASH_STATUS GetInfoAboutFunc(Text* data);

size_t GetResultsFindWords(HashTable* hash_table, Text* data);

void HashTableDump(HashTable* hash_table, size_t table_num); 

int TableVerify(HashTable* hash_table);