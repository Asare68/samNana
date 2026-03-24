#include "unity.h"
#include <stdio.h>
#include <setjmp.h>
#include <string.h>

jmp_buf unity_jump_env;
static int unity_test_count = 0;

void unity_fail(const char* msg) {
    printf("FAIL: Test %d: %s\n", unity_test_count, msg);
}

int _unity_run_test(void (*func)(void), const char* name) {
    printf("RUNNING TEST: %s\n", name);
    setUp();
    unity_test_count++;

    if (setjmp(unity_jump_env) == 0) {
        func();
    } else {
        tearDown();
        return 0;
    }

    printf("   PASS: %s\n", name);
    tearDown();
    return 1;
}

void _unity_begin(void) {
    printf("========== UNITY TEST RUNNER ==========\n\n");
    unity_test_count = 0;
}

void _unity_end(void) {
    printf("\nTests complete.\n");
}