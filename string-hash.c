#include "string-hash.h"
#include <stdio.h>
#include <stdlib.h>

int is_prime(unsigned long int n)
{
    if (n <= 1)
        return 0;
    if (n <= 3)
        return 1;
    if (n % 2 == 0 || n % 3 == 0)
        return 0;
    for (unsigned long int i = 5; i * i <= n; i = i + 6)
    {
        if (n % i == 0 || n % (i + 2) == 0)
        {
            return 0;
        }
    }
    return 1;
}

unsigned long int next_prime(unsigned long int n)
{
    if (n <= 1)
        return 2;
    unsigned long int prime = n;
    int found = 0;
    while (!found)
    {
        prime++;
        if (is_prime(prime))
        {
            found = 1;
        }
    }
    return prime;
}

unsigned long int Str_Hash(char *str, unsigned long int cap)
{
    const int p = 31;
    unsigned long int index = 0;
    int len = strlen(str);
    unsigned long long pow = 1;
    for (int i = 0; i < len; i++)
    {
        index = (index + (str[i] - 'a' + 1) * pow) % cap;
        pow = (pow * p) % cap;
    }

    return abs(index);
}

StrHash Init_StrHash(unsigned long int cap)
{

    cap = next_prime(cap);

    StrHash table = (StrHash)malloc(sizeof(struct StrHash));
    table->cap = cap;
    table->curr = 0;

    table->bkt_arr = (StrHash_NODE *)malloc(sizeof(StrHash_NODE) * cap);
    for (unsigned long int i = 0; i < cap; i++)
    {
        table->bkt_arr[i].visited = false;
    }

    return table;
}

void __insert_StrHash(StrHash_NODE *arr, char *str, unsigned long int index, unsigned long int cap)
{
    unsigned long int i = 1;
    unsigned long int base = index;
    while (1)
    {
        if (!arr[index].visited)
        {
            strcpy(arr[index].str, str);

            arr[index].visited = true;
            break;
        }
        else
        {
            index = base + i * i;
            index = index % cap;
            i++;
        }
    }
}

void Rehash_StrHash(StrHash table, unsigned long int new_size)
{
    unsigned long int old_cap = table->cap;

    StrHash_NODE *new_arr;
    new_arr = (StrHash_NODE *)malloc(sizeof(StrHash_NODE) * new_size);

    for (unsigned long int i = 0; i < old_cap; i++)
    {
        if (!table->bkt_arr[i].visited)
        {
            continue;
        }
        else
        {
            unsigned long int place = Str_Hash(table->bkt_arr[i].str, new_size);
            __insert_StrHash(new_arr, table->bkt_arr[i].str, place, new_size);
        }
    }

    table->cap = new_size;
    table->bkt_arr = new_arr;
}

void Insert_StrHash(StrHash table, char *str)
{
    if (table->curr >= (double)(table->cap - 1) / (double)2)
    {
        unsigned long int new_cap = next_prime(table->cap * 2);
        Rehash_StrHash(table, new_cap);
    }

    unsigned long int index = Str_Hash(str, table->cap);

    __insert_StrHash(table->bkt_arr, str, index, table->cap);
    table->curr++;
}

unsigned long int Find_StrHash(StrHash table, char *str)
{
    unsigned long int index = Str_Hash(str, table->cap);
    unsigned long int hsh = index;
    unsigned long int i = 1;
    while (1)
    {
        if (strcmp(str, table->bkt_arr[index].str) == 0)
        {
            return index;
        }
        else if (!table->bkt_arr[index].visited)
        {
            return -1;
        }
        else
        {
            index = hsh + i * i;
            index = index % table->cap;
            i++;
        }
    }
}

void DeleteStrHash(StrHash *table_ref)
{
    (*table_ref)->cap = 0;
    (*table_ref)->curr = 0;
    free((*table_ref)->bkt_arr);
    free(*table_ref);
}