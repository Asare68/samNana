#include "hash.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/* ESTRUTURAS DE DADOS A IMPLEMENTAR */
typedef struct HashNode {
    char* key;
    char* value;
    struct HashNode* next;
} HashNode;

typedef struct HashTable {
    HashNode** buckets;
    int tamanho;
} HashTable;

/*************************************** FUNÇÕES AUXILIARES ***************************************/
unsigned int hashFunction(const char* key) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + (*key++);
    }
    return hash % HASH_SIZE;
}

bool existeKey(HashTable* table, const char* key) {
    if (table == NULL || key == NULL) return false;
    unsigned int index = hashFunction(key);
    HashNode* current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) return true;
        current = current->next;
    }
    return false;
}

HashNode* getRegistro(HashTable* table, const char* key) {
    if (table == NULL || key == NULL) return NULL;
    if (!existeKey(table, key)) return NULL;
    unsigned int index = hashFunction(key);
    HashNode* current = table->buckets[index];
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) return current;
        current = current->next;
    }
    return NULL;
}

char* getValue(HashTable* table, const char* key) {
    if (table == NULL || key == NULL) return NULL;
    HashNode* node = getRegistro(table, key);
    return (node != NULL) ? node->value : NULL;
}

int getTamanho(HashTable* table) {
    if (table == NULL) return -1;
    return table->tamanho;
}

/* FUNÇÕES PRINCIPAIS */
HashTable* criarTabela(int entradas) {
    if (entradas <= 0) return NULL;
    HashTable* table = (HashTable*)malloc(sizeof(HashTable));
    if (table == NULL) return NULL;

    table->buckets = (HashNode**)malloc(entradas * sizeof(HashNode*));
    if (table->buckets == NULL) {
        fprintf(stderr, "ERRO: Alocação de memória para os buckets.\n");
        free(table);
        return NULL;
    }

    table->tamanho = entradas;
    for (int i = 0; i < entradas; i++) table->buckets[i] = NULL;
    return table;
}

int freeHash(HashTable* table) {
    if (table == NULL) return -1;

    for (int i = 0; i < HASH_SIZE; i++) {
        HashNode* current = table->buckets[i];
        while (current != NULL) {
            HashNode* temp = current;
            current = current->next;
            free(temp->key);
            free(temp->value);
            free(temp);
        }
    }
    free(table);
    return 0;
}

int inserirReg(HashTable* table, const char* key, const char* value) {
    if (table == NULL || key == NULL || value == NULL) return -1;
    unsigned int index = hashFunction(key);
    HashNode* current = table->buckets[index];

    // Update existing key
    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            free(current->value);
            current->value = _strdup(value); // Windows-safe
            return 0;
        }
        current = current->next;
    }

    // Insert new key
    HashNode* newNode = (HashNode*)malloc(sizeof(HashNode));
    if (newNode == NULL) {
        fprintf(stderr, "ERRO: Alocação de memória para novo nó.\n");
        return -1;
    }
    newNode->key = _strdup(key);
    newNode->value = _strdup(value);
    newNode->next = table->buckets[index];
    table->buckets[index] = newNode;
    return 0;
}

int removerKey(HashTable* table, const char* key) {
    if (table == NULL || key == NULL) return -1;
    unsigned int index = hashFunction(key);
    HashNode* current = table->buckets[index];
    HashNode* prev = NULL;

    while (current != NULL) {
        if (strcmp(current->key, key) == 0) {
            if (prev == NULL) table->buckets[index] = current->next;
            else prev->next = current->next;
            free(current->key);
            free(current->value);
            free(current);
            return 0;
        }
        prev = current;
        current = current->next;
    }
    return -1;
}