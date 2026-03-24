# Módulo: extensible_hash (C)

Implementação de uma **tabela hash extensível** em C com:
- Encadeamento separado (lista encadeada por bucket)
- Testes unitários com o framework **Unity**
- Demonstração com `main.c`
- Compilação suportada no Windows (MinGW/PowerShell)

## Estrutura de pastas

- `hash.h` - interface pública
- `hash.c` - implementação da tabela hash
- `src/` - `unity.c` e `unity.h`
- `test/` - `test_runner.c` (testes), `main.c` (demo)

## Como compilar (Windows)

```bash
gcc -std=c11 -Wall -Wextra -O0 unity.c hash.c test_runner.c -o test_runner.exe
.\test_runner.exe
```

## Como usar como módulo

```c
#include "hash.h"

HashTable* ht = criarTabela(1009);
inserirReg(ht, "cep_123", "Rua A");
printf("value: %s\n", getValue(ht, "cep_123"));
freeHash(ht);
```
