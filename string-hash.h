#ifndef _STR_HASH_H_
#define _STR_HASH_H_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

struct str_hash_node
{
    char str[100001];
    bool visited;
};

typedef struct str_hash_node StrHash_NODE;

struct StrHash
{
    unsigned long int cap, curr;
    StrHash_NODE *bkt_arr;
};
typedef struct StrHash *StrHash;

int len(char *str);
unsigned long int Str_Hash(char *str, unsigned long int cap);

StrHash Init_StrHash(unsigned long int cap);
void __insert_StrHash(StrHash_NODE *arr, char *data, unsigned long int index, unsigned long int cap);
void Rehash_StrHash(StrHash table, unsigned long int new_size);

void Insert_StrHash(StrHash table, char *data);
unsigned long int Find_StrHash(StrHash table, char *data);
#endif