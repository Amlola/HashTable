#include "../inc/hash_table.h"


HASH_STATUS HashTableCtor(HashTable* hash_table, size_t table_size) 
    {
    hash_table->size = 0;

    hash_table->list = (LIST*)calloc(table_size, sizeof(LIST));

    if (!hash_table->list)
        return LISTS_ALLOC_ERROR;

    hash_table->hash_function = nullptr;                                               

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

    hash_table->size       = 0;                                                            
    hash_table->count_elem = 0;

    hash_table = nullptr;
    }


HASH_STATUS TableInsert(HashTable* hash_table, const char* word, size_t lenght_word)
    {
    CHECK_HASH_TABLE_ERROR(hash_table);

    hash_t hash_value = hash_table->hash_function(word, lenght_word) % HASH_TABLE_CAPACITY;

    LIST* cur_list = &hash_table->list[hash_value]; 

    List_type key = _mm256_load_si256((List_type*)word);

    if (cur_list->size == 0) 
        hash_table->size++;

    else 
        if (CheckValueInTable(cur_list, key, lenght_word)) return VALUE_REPEAT;

    PushBack(cur_list, key);

    hash_table->count_elem++;

    CHECK_HASH_TABLE_ERROR(hash_table);

    return HASH_OK;
    }


HASH_STATUS TableDelete(HashTable* hash_table, const char* word, size_t lenght_word)
    {
    CHECK_HASH_TABLE_ERROR(hash_table);

    hash_t hash_value = hash_table->hash_function(word, lenght_word) % HASH_TABLE_CAPACITY;

    LIST* cur_list = &hash_table->list[hash_value];

    List_type key = _mm256_load_si256((List_type*)word);

    iterator_t pos = CheckValueInTable(cur_list, key, lenght_word);                           

    if (!pos) 
        return NOT_FIND_VALUE;

    ListDelete(cur_list, pos);

    hash_table->count_elem--;

    if (cur_list->size == 0) 
        hash_table->size--;

    CHECK_HASH_TABLE_ERROR(hash_table);

    return HASH_OK;
    }


iterator_t CheckValueInTable(LIST* list, List_type avx_key, size_t lenght_word) 
    {
    iterator_t i = list->front;

    while (i != list->data[list->front].prev) 
        {
        if (_mm256_movemask_epi8(_mm256_cmpeq_epi8(avx_key, list->data[i].value)) == -1)                            
            return i;

        i = list->data[i].next;
        }

    return 0;
    }


bool HashTableSearch(HashTable* hash_table, const char* word, size_t lenght_word)
    {
    hash_t hash_value = hash_table->hash_function(word, lenght_word) % HASH_TABLE_CAPACITY;

    List_type key = _mm256_load_si256((List_type*)word);

    if (!CheckValueInTable(&hash_table->list[hash_value], key, lenght_word))  
        return false;                                                                      

    return true;
    }


HASH_STATUS FillHashTable(HashTable* hash_table, Text* data)
    {
    CHECK_HASH_TABLE_ERROR(hash_table);

    char* ptr = data->aligned_Buf;

    for (size_t i = 0; i < data->count_n; i++)
        {
        size_t lenght_word = (data->str + i)->length;

        TableInsert(hash_table, ptr, lenght_word);

        ptr += 32;
        }
    
    CHECK_HASH_TABLE_ERROR(hash_table);

    return HASH_OK;
    }


HASH_STATUS GetStatOfHashFunc(HashTable* hash_table, const char* name_file)
    {
    CHECK_HASH_TABLE_ERROR(hash_table);

    FILE* file = fopen(name_file, "w");

    if (!file)
        return CANT_OPEN_FILE;

    for (size_t i = 0; i < HASH_TABLE_CAPACITY; i++)
        fprintf(file, "%zu, %zu \n", i, hash_table->list[i].size);

    fclose(file);

    CHECK_HASH_TABLE_ERROR(hash_table);

    return HASH_OK;
    }


size_t GetResultsFindWords(HashTable* hash_table, Text* data)
    {
    CHECK_HASH_TABLE_ERROR(hash_table);

    size_t find_words = 0;

    char* ptr = data->aligned_Buf;

    for (size_t i = 0; i < data->count_n; i++)
        {
        find_words += (HashTableSearch(hash_table, ptr, (data->str + i)->length));
        ptr += 32;
        }

    CHECK_HASH_TABLE_ERROR(hash_table);

    return find_words;
    }


int TableVerify(HashTable* hash_table) 
    {
    assert(hash_table);

    if (ListVerify(hash_table->list) != NO_ERROR)
            return HASH_TABLE_ERROR;

    for (size_t i = 0; i < HASH_TABLE_CAPACITY; i++)
        {
        if (ListVerify(&hash_table->list[i]) != NO_ERROR)
            return HASH_TABLE_ERROR;
        }

    return NO_ERROR;
    }


ON_DEBUG_TABLE 
    (
    void HashTableDump(HashTable* hash_table, size_t table_num) 
        {
        hash_logfile = fopen("hash_logfile.txt", "w");

        if (hash_table->list->status != NO_ERROR) 
            {
            for (size_t j = 0; j < NUMBER_OF_ERROR; j++)
                {
                if ((hash_table->list->status & (1 << j)))
                    fprintf(hash_logfile, "ERROR: %s\n", ErrorArray[j].NameError);
                }      
            }

        else 
            {
            fprintf(hash_logfile, "HASH_TABLE №%zu\n", table_num);

            fprintf(hash_logfile, "----------------------------------------------------------------------------------------\n");

            int log_size = (int)(log10((double)(HASH_TABLE_CAPACITY))) + 1;

            for (size_t hash = 0; hash < HASH_TABLE_CAPACITY; hash++) 
                {
                LIST* cur_list = &hash_table->list[hash];

                fprintf(hash_logfile, "HASH[%0*zu] Size: %zu\n{\n", log_size, hash, cur_list->size);

                for (iterator_t i = Begin(cur_list); i != End(cur_list); i = NextCurIndex(cur_list, i))
                    fprintf(hash_logfile, "%d) %s  ", i, cur_list->data[i].value);

                fprintf(hash_logfile, "\n}\n\n");
                }
            }

        fclose(hash_logfile);
        }
    )