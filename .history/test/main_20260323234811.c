#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "hash.h"

int main(void) {
    HashTable* ht = criarTabela(HASH_SIZE);
    if (!ht) {
        fprintf(stderr, "Erro ao criar tabela.\n");
        return 1;
    }

    inserirReg(ht, "cep_123", "Rua A");
    inserirReg(ht, "cep_456", "Rua B");
    inserirReg(ht, "cep_789", "Rua C");

    printf("cep_123 existe? %s\n", existeKey(ht, "cep_123") ? "sim" : "não");
    printf("cep_123 -> %s\n", getValue(ht, "cep_123"));
    printf("cep_456 -> %s\n", getValue(ht, "cep_456"));

    freeHash(ht);
    return 0;
}