#ifndef _STR_HASH_H_
#define _STR_HASH_H_

#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Structure for creating a node of a hash table, used to represent a street.
struct str_hash_node {
    
    //Name of street
    char str[31];
    //To check if the street has been visited.
    bool visited;
    //Length or distance of weight of the given street 
    int length;
    //Start and end nodes or intersection of the street.
    int v1, v2;
    //The congestion or the number of cars on the given street.
    int congestion;
};

//Renaming the structure for Hash Node.
typedef struct str_hash_node StrHash_NODE;

//Creating the structure for hash table.
struct StrHash {

    //The current capacity of the given hash table. It may change dynamically. 
    unsigned long int cap;
    //The current size of the given hash table.
    unsigned long int curr;
    //A pointer to hash table nodes.
    StrHash_NODE *bkt_arr;
};

//Renaming the structure for Hash Table. 
typedef struct StrHash *StrHash;

//To find the length of a string.
int len(char *str);
//Hashes using the given string. Horner Hash.
unsigned long int Str_Hash(char *str, unsigned long int cap);

//Initializes the Hash Table.
StrHash Init_StrHash(unsigned long int cap);
//Inserting into the Hash Table (to be used inside Insert_StrHash).
void __insert_StrHash(StrHash_NODE *arr, char *data, unsigned long int index, unsigned long int cap, int v1, int v2, int congestion,int length);
//Rehashing in case of collision in the the Hash Table.
void Rehash_StrHash(StrHash table, unsigned long int new_size);
//Inserting into the Hash Table.
void Insert_StrHash(StrHash table, char *data, int v1, int v2, int congestion,int length);
//To find particular data inside the hash table.
unsigned long int Find_StrHash(StrHash table, char *data);
#endif