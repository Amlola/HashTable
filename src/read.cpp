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

    data->str = (String*)calloc(data->count_n, sizeof(String));

    replace_slash_n(data);

    Parsing_pointers(data);
    }


void Free(Text* data)
    {
    free(data->Buf);
    free(data->str);
    }