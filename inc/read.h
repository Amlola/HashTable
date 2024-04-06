#pragma once


#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <cmath>


struct String
    {
    size_t length = 0;
    char* adress = nullptr;
    };


struct Text
    {
    char* Buf;
    long long BufSize;
    int count_n;
    String* str;
    };


long long GetFileSize(FILE* file);

void replace_slash_n(Text* data);

void Parsing_pointers(Text* data);

int Number_lines(Text* data);

void GetDataFromFile(FILE* file, Text* data);

void Free(Text* data);