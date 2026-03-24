#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define HASH_SIZE 1009

typedef struct HashTable HashTable;
typedef struct HashNode HashNode;

/* FUNÇÕES AUXILIARES */
unsigned int hashFunction(const char* key);
bool existeKey(HashTable* table, const char* key);
HashNode* getRegistro(HashTable* table, const char* key);
char* getValue(HashTable* table, const char* key);
int getTamanho(HashTable* table);

/* FUNÇÕES PRINCIPAIS */
HashTable* criarTabela(int entradas);
int freeHash(HashTable* table);
int inserirReg(HashTable* table, const char* key, const char* value);
int removerKey(HashTable* table, const char* key);

#endif