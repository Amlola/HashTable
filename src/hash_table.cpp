#include "../inc/hash_table.h"



HASH_STATUS HashTableCtor(HashTable* hash_table, size_t table_size) 
    {
    hash_table->size = 0;

    hash_table->list = (LIST*)calloc(table_size, sizeof(LIST));

    if (!hash_table->list)
        return LISTS_ALLOC_ERROR;

    hash_table->hash_function = nullptr;                                               // good

    hash_table->count_elem = 0;

    for (size_t i = 0; i < table_size; i++)
        ListCtor(&hash_table->list[i]);

    return HASH_OK;
    }


void HashTableDtor(HashTable* hash_table)
    {
    for (size_t i = 0; i < HASH_TABLE_CAPACITY; i++) 
        ListDtor(&hash_table->list[i]);

    free(hash_table->list);

    hash_table->list = nullptr;

    hash_table->size       = 0;                                                             // good
    hash_table->count_elem = 0;

    hash_table = nullptr;
    }


HASH_STATUS TableInsert(HashTable* hash_table, const char* word, size_t lenght_word)
    {
    uint64_t hash_value = hash_table->hash_function(word, lenght_word);

    LIST* cur_list = &hash_table->list[hash_value];

    if (cur_list->size == 0) 
        hash_table->size++; 

    if (CheckValueInTable(cur_list, word, lenght_word))                                           // good
        return VALUE_REPEAT;

    PushBack(cur_list, word);

    hash_table->count_elem++;

    return HASH_OK;
    }


HASH_STATUS TableDelete(HashTable* hash_table, const char* word, size_t lenght_word)
    {
    uint64_t hash_value = hash_table->hash_function(word, lenght_word);

    LIST* cur_list = &hash_table->list[hash_value];

    iterator_t position = CheckValueInTable(cur_list, word, lenght_word);                           // good

    if (!position) 
        return NOT_FIND_VALUE;

    ListDelete(cur_list, position);

    hash_table->count_elem--;

    if (cur_list->size == 0) 
        hash_table->size--;

    return HASH_OK;
    }


size_t CheckValueInTable(LIST* list, const char* word, size_t lenght_word) 
    {
    for (iterator_t i = Begin(list); i < End(list); i = NextCurIndex(list, i)) 
        {
        if (strncmp(word, list->data[i].value, lenght_word) == 0)                             // good
            return i;
        }

    return 0;
    }


bool FindWord(HashTable* hash_table, const char* word, size_t lenght_word)
    {
    uint64_t hash_value = hash_table->hash_function(word, lenght_word);
    
    if (!CheckValueInTable(&hash_table->list[hash_value], word, lenght_word))  
        return false;                                                                       // good

    return true;
    }


HASH_STATUS FillHashTable(HashTable* hash_table, Text* data)
    {
    for (size_t i = 0; i < data->count_n; i++)
        {
        size_t lenght_word = (data->str + i)->length;

        TableInsert(hash_table, (data->str + i)->adress, lenght_word);
        }

    return HASH_OK;
    }


void HashTableDump(HashTable* hash_table) 
    {
    hash_logfile = fopen("hash_logfile.txt", "w");

    int log_size = (int)(log10((double)(HASH_TABLE_CAPACITY))) + 1;

    for (size_t hash = 0; hash < HASH_TABLE_CAPACITY; hash++) 
        {
        fprintf(hash_logfile, "Hash [%0*zu]: ", log_size, hash);

        LIST* cur_list = &hash_table->list[hash];

        for (iterator_t i = Begin(cur_list); i < End(cur_list); i = NextCurIndex(cur_list, i))
            fprintf(hash_logfile, "%d) %s ", i, cur_list->data[i].value);

        fprintf(hash_logfile, "\n\n");
        }

    fclose(hash_logfile);
    }