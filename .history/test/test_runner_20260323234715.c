#include <stdio.h>
#include <string.h>
#include "unity.h"
#include "hash.h"

HashTable* tabela_teste = NULL;

void setUp(void) {
    tabela_teste = criarTabela(HASH_SIZE);
    TEST_ASSERT_NOT_NULL(tabela_teste);
}

void tearDown(void) {
    if (tabela_teste != NULL) {
        freeHash(tabela_teste);
        tabela_teste = NULL;
    }
}

void test_CriarTabela_NaoDeveRetornarNull(void) {
    TEST_ASSERT_NOT_NULL(tabela_teste);
    TEST_ASSERT_EQUAL_INT(HASH_SIZE, getTamanho(tabela_teste));
}

void test_CriarTabela_TamanhoInvalido_DeveRetornarNull(void) {
    HashTable* tabela_invalida_zero = criarTabela(0);
    HashTable* tabela_invalida_negativo = criarTabela(-5);
    TEST_ASSERT_NULL(tabela_invalida_zero);
    TEST_ASSERT_NULL(tabela_invalida_negativo);
}

void test_InserirReg_NovaChave_DeveRetornarZero(void) {
    int resultado = inserirReg(tabela_teste, "cep_123", "Rua A");
    TEST_ASSERT_EQUAL_INT(0, resultado);
}

void test_ExisteKey_ChaveInserida_DeveRetornarTrue(void) {
    inserirReg(tabela_teste, "cep_123", "Rua A");
    bool existe = existeKey(tabela_teste, "cep_123");
    TEST_ASSERT_TRUE(existe);
}

void test_ExisteKey_ChaveInexistente_DeveRetornarFalse(void) {
    bool existe = existeKey(tabela_teste, "chave_fantasma");
    TEST_ASSERT_FALSE(existe);
}

void test_GetRegistro_ChaveExistente_DeveRetornarValorCorreto(void) {
    inserirReg(tabela_teste, "cep_456", "Rua B");
    HashNode* no = getRegistro(tabela_teste, "cep_456");
    TEST_ASSERT_NOT_NULL(no);
    TEST_ASSERT_EQUAL_STRING("Rua B", getValue(tabela_teste, "cep_456"));
}

void test_RemoverKey_ChaveExistente_DeveRetornarZeroENaoExistirMais(void) {
    inserirReg(tabela_teste, "cep_789", "Rua C");
    int resultado = removerKey(tabela_teste, "cep_789");
    TEST_ASSERT_EQUAL_INT(0, resultado);
    TEST_ASSERT_FALSE(existeKey(tabela_teste, "cep_789"));
}

void test_InserirReg_ChaveJaExistente_DeveAtualizarValor(void) {
    inserirReg(tabela_teste, "cep_duplicado", "Valor Antigo");
    int resultado = inserirReg(tabela_teste, "cep_duplicado", "Valor Novo");
    TEST_ASSERT_EQUAL_INT(0, resultado);
    HashNode* no = getRegistro(tabela_teste, "cep_duplicado");
    TEST_ASSERT_NOT_NULL(no);
    TEST_ASSERT_EQUAL_STRING("Valor Novo", getValue(tabela_teste, "cep_duplicado"));
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_CriarTabela_NaoDeveRetornarNull);
    RUN_TEST(test_CriarTabela_TamanhoInvalido_DeveRetornarNull);
    RUN_TEST(test_InserirReg_NovaChave_DeveRetornarZero);
    RUN_TEST(test_ExisteKey_ChaveInserida_DeveRetornarTrue);
    RUN_TEST(test_ExisteKey_ChaveInexistente_DeveRetornarFalse);
    RUN_TEST(test_GetRegistro_ChaveExistente_DeveRetornarValorCorreto);
    RUN_TEST(test_RemoverKey_ChaveExistente_DeveRetornarZeroENaoExistirMais);
    RUN_TEST(test_InserirReg_ChaveJaExistente_DeveAtualizarValor);
    return UNITY_END();
}