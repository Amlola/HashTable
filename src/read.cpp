#include "../inc/read.h"


long long GetFileSize(FILE* file)
    {
    assert(file);

    long long start = ftell(file);
    fseek(file, start, SEEK_END);

    long long bufsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    return bufsize;
    }


void replace_slash_n(Text* data)
    {
    assert(data->Buf);

    for (size_t i = 0; i < data->BufSize; i++)
        {
        if (*(data->Buf + i) == '\n')
            *(data->Buf + i) = '\0';
        }
    }


void GetAlignedBuffer(Text* data)
    {
    for (size_t i = 0; i < data->count_n; i++)
        {
        strcpy(&data->aligned_Buf[i * 32], (data->str + i)->adress);
        if (i < 5) 
            {
            printf("%p\n", &data->aligned_Buf[i * 32]);
            }
        }
    }


int Number_lines(Text* data)
    {
    assert(data->Buf);

    int count_n = 0;
    
    for (size_t i = 0; i < data->BufSize; i++)
        {
        if (*(data->Buf + i) == '\n')
            count_n++;
        }

    return count_n + 1;
    }


void Parsing_pointers(Text* data)
    {
    assert(data->Buf);

    int i = 0;
    
    while (i < data->BufSize)
        {
        data->str->length = atoi(data->Buf + i);

        data->str->adress = (data->Buf + i + (int)(log10((double)(data->str->length))) + 2);
        
        data->str++;

        while (*(data->Buf + i) != '\0')
            i++;

        i++;
        }

    data->str -= data->count_n;
    }


void GetDataFromFile(FILE* file, Text* data)
    {
    data->BufSize = GetFileSize(file);
    data->Buf = (char*)calloc(data->BufSize + 1, sizeof(char));

    fread(data->Buf, sizeof(char), data->BufSize, file);

    fclose(file);

    data->count_n = Number_lines(data);

    data->aligned_Buf = (char*)aligned_alloc(32, data->count_n * 32);

    memset(data->aligned_Buf, 0, data->count_n * 32);

    data->str = (String*)calloc(data->count_n, sizeof(String));

    replace_slash_n(data);

    Parsing_pointers(data);

    for (size_t i = 0; i < data->count_n; i++) 
        memcpy(data->aligned_Buf + (i * 32), data->str[i].adress, (data->str + i)->length);
    }


void Free(Text* data)
    {
    free(data->Buf);
    free(data->str);
    free(data->aligned_Buf);
    }