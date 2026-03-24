#ifndef UNITY_H
#define UNITY_H

#include <stdio.h>
#include <setjmp.h>
#include <string.h>

#define TEST_ASSERT(condition)       \
    do {                             \
        if (!(condition)) {          \
            unity_fail(#condition);  \
            longjmp(unity_jump_env, 1); \
        }                            \
    } while (0)

#define TEST_ASSERT_TRUE(condition)  TEST_ASSERT(condition)
#define TEST_ASSERT_FALSE(condition) TEST_ASSERT(!(condition))
#define TEST_ASSERT_EQUAL_INT(a,b)   TEST_ASSERT((a) == (b))
#define TEST_ASSERT_EQUAL_STRING(a,b) TEST_ASSERT(strcmp((a),(b)) == 0)
#define TEST_ASSERT_NOT_NULL(ptr)    TEST_ASSERT((ptr) != NULL)
#define TEST_ASSERT_NULL(ptr)        TEST_ASSERT((ptr) == NULL)

void setUp(void);
void tearDown(void);
int  main(void);

void _unity_begin(void);
void _unity_end(void);
int  _unity_run_test(void (*func)(void), const char* name);
void unity_fail(const char* msg);
extern jmp_buf unity_jump_env;

#endif