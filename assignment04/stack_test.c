#include <stack.h>
#include <unity.h>
#include <string.h>

#define TEST_NOT_IMPLEMENTED TEST_IGNORE_MESSAGE("not implemented!")

/** Tests whether stack_create creates empty stack
 */
void test_stack_create_should_be_empty(void) {
    int ret_stack_empty1;
    int ret_stack_empty2;

    stack_t* handle = stack_create();
    ret_stack_empty1 = stack_empty(handle);
    stack_push(handle, 0);
    stack_delete(&handle);
    handle = stack_create();
    ret_stack_empty2 = stack_empty(handle);
    stack_delete(&handle);

    TEST_ASSERT_EQUAL(1,ret_stack_empty1);
    TEST_ASSERT_EQUAL(1,ret_stack_empty2);
}

/** Tests whether stack_create returns valid pointer
 */
void test_stack_create_should_be_valid(void) {
    stack_t* actual;

    stack_t* handle = stack_create();
    actual = handle;
    stack_delete(&handle);

    TEST_ASSERT_NOT_EQUAL(NULL, actual);
}

/** Tests whether user pointer is invalidated after call to stack_delete
 */
void test_stack_delete_invalidates_handle(void) {
    stack_t* actual;
    stack_t* original;

    stack_t* handle = stack_create();
    original = handle;
    stack_delete(&handle);
    actual = handle;

    TEST_ASSERT_NOT_EQUAL(original, actual);
    TEST_ASSERT_EQUAL(NULL, actual);
}

/** Tests whether STACK_STATIC_POOL_COUNT stacks can be created
 */
void test_stack_create_all_stack_pool(void) {

    stack_t* handles[STACK_STATIC_POOL_COUNT];
    for (int i = 0; i < STACK_STATIC_POOL_COUNT; ++i) {
        handles[i] = stack_create();
    }
    stack_t* handle = stack_create();

    stack_t* actual_handle = handle;
    stack_t* actual_handles[STACK_STATIC_POOL_COUNT];
    memcpy(actual_handles, handles, STACK_STATIC_POOL_COUNT * sizeof(stack_t*));

    stack_delete(&handle);
    for (int i = 0; i < STACK_STATIC_POOL_COUNT; ++i) {
        stack_delete(&handles[i]);
    }

    for (int i = 0; i < STACK_STATIC_POOL_COUNT; ++i) {
        char msg[64];
        snprintf(msg, sizeof(msg), "Element %d Expected NOT %p Was %p", i, NULL, actual_handles[i]);
        TEST_ASSERT_NOT_EQUAL_MESSAGE(NULL, actual_handles[i], msg);
    }
    TEST_ASSERT_EQUAL(NULL, actual_handle);
}

/** Tests whether error occurs when invalid handle is provided
 */
void test_stack_push_invalid_arguments(void) {
    int actual = stack_push(NULL, 0);
    TEST_ASSERT_EQUAL(STACK_ERROR_HANDLE, actual);
}

/** Tests whether error occurs when invalid handle is provided
 */
void test_stack_pop_invalid_arguments(void) {
    int unused_buffer;
    int actual = stack_pop(NULL, &unused_buffer);
    TEST_ASSERT_EQUAL(STACK_ERROR_HANDLE, actual);
}

/** Tests whether NULL is accepted for pop data arg
 */
void test_stack_pop_null_data(void) {
    int actual, size_before, size_after, is_empty;

    stack_t* handle = stack_create();
    stack_push(handle, 1);
    size_before = stack_size(handle);
    actual = stack_pop(handle, NULL);
    size_after = stack_size(handle);
    is_empty = stack_empty(handle);
    stack_delete(&handle);

    TEST_ASSERT_EQUAL(STACK_SUCCESS, actual);
    TEST_ASSERT_EQUAL(1, size_before);
    TEST_ASSERT_EQUAL(0, size_after);
    TEST_ASSERT_EQUAL(1, is_empty);
}

/** Tests whether error occurs when invalid handle is provided
 */
void test_stack_full_invalid_arguments(void) {
    int actual = stack_full(NULL);
    TEST_ASSERT_EQUAL(STACK_ERROR_HANDLE, actual);
}

/** Tests whether error occurs when invalid handle is provided
 */
void test_stack_empty_invalid_arguments(void) {
    int actual = stack_empty(NULL);
    TEST_ASSERT_EQUAL(STACK_ERROR_HANDLE, actual);
}

/** Tests whether error occurs when invalid handle is provided
 */
void test_stack_size_invalid_arguments(void) {
    int actual = stack_size(NULL);
    TEST_ASSERT_EQUAL(STACK_ERROR_HANDLE, actual);
}

/** Tests whether popping from an empty stack produces an error
 */
void test_pop_from_empty_stack(void) {
    int unused_buffer;
    int ret_stack_pop;

    stack_t* handle = stack_create();
    ret_stack_pop = stack_pop(handle, &unused_buffer);
    stack_delete(&handle);

    TEST_ASSERT_EQUAL(STACK_ERROR_FAILURE, ret_stack_pop);
}

/** Tests whether pushing to a full stack produces an error
 */
void test_push_to_full_stack(void) {
    int ret[STACK_SIZE];
    int ret_stack_push;
    int ret_stack_full;

    stack_t* handle = stack_create();
    for (int i = 0; i < STACK_SIZE; ++i) {
        ret[i] = stack_push(handle, i);
    }
    ret_stack_full = stack_full(handle);
    ret_stack_push = stack_push(handle, 0);
    stack_delete(&handle);

    TEST_ASSERT_EACH_EQUAL_INT(0, ret, STACK_SIZE);
    TEST_ASSERT_EQUAL(1, ret_stack_full);
    TEST_ASSERT_EQUAL(STACK_ERROR_FAILURE, ret_stack_push);

}

/** Tests filling the stack conditionally using stack_full
 */
void test_push_until_full(void) {
    int ret_stack_full;
    int ret_stack_size;
    int ret[STACK_SIZE];
    int i = 0;

    stack_t* handle = stack_create();
    while (!stack_full(handle) && i <= STACK_SIZE) {
        ret[i] = stack_push(handle, i);
        i++;
    }
    ret_stack_full = stack_full(handle);
    ret_stack_size = stack_size(handle);
    stack_delete(&handle);

    TEST_ASSERT_EQUAL(1, ret_stack_full);
    TEST_ASSERT_EQUAL(STACK_SIZE, ret_stack_size);
    TEST_ASSERT_EQUAL(STACK_SIZE, i);
    TEST_ASSERT_EACH_EQUAL_INT(0, ret, STACK_SIZE);
}

/** Tests emptying the stack conditionally using stack-empty
 */
void test_pop_until_empty(void) {
    int start_full;
    int start_empty;
    int ret_stack_empty;
    int ret_stack_size;
    int ret[STACK_SIZE];
    int i = 0;
    int unused;

    // start with a full stack
    stack_t* handle = stack_create();
    i = 0;
    while (!stack_full(handle) && i <= STACK_SIZE) {
        stack_push(handle, 0);
        i++;
    }

    start_full = stack_full(handle);
    start_empty = stack_empty(handle);

    i = 0;
    while (!stack_empty(handle) && i <= STACK_SIZE) {
        ret[i] = stack_pop(handle, &unused);
        i++;
    }
    ret_stack_empty = stack_empty(handle);
    ret_stack_size = stack_size(handle);
    stack_delete(&handle);

    TEST_ASSERT_EQUAL(1, start_full);
    TEST_ASSERT_EQUAL(0, start_empty);
    TEST_ASSERT_EQUAL(1, ret_stack_empty);
    TEST_ASSERT_EQUAL(0, ret_stack_size);
    TEST_ASSERT_EACH_EQUAL_INT(0, ret, STACK_SIZE);
}

/** Tests pushing and popping a single item is successful
 */
void test_push_then_pop_single_item(void) {
    int ret_stack_push;
    int ret_stack_pop;
    int expected = 564;
    int actual;

    stack_t* handle = stack_create();
    ret_stack_push = stack_push(handle, expected);
    ret_stack_pop = stack_pop(handle, &actual);
    stack_delete(&handle);

    TEST_ASSERT_EQUAL(STACK_SUCCESS, ret_stack_push);
    TEST_ASSERT_EQUAL(STACK_SUCCESS, ret_stack_pop);
    TEST_ASSERT_EQUAL(expected, actual);
}

/** Tests pushing and popping all items in order is successful
 */
void test_push_then_pop_all_items(void) {
    int ret_push[STACK_SIZE];
    int ret_pop[STACK_SIZE];
    int ret_full, ret_empty;
    int expected[STACK_SIZE];
    int actual[STACK_SIZE];

    // expect descending integers
    for (int i = 0; i < STACK_SIZE; ++i) {
        expected[i] = 3 - i;
    }

    stack_t* handle = stack_create();
    for (int i = 0; i < STACK_SIZE; ++i) {
        ret_push[i] = stack_push(handle, expected[i]);
    }
    ret_full = stack_full(handle);
    for (int i = 0; i < STACK_SIZE; ++i) {
        int k = STACK_SIZE - i - 1;
        ret_pop[i] = stack_pop(handle, &actual[k]);
    }
    ret_empty = stack_empty(handle);
    stack_delete(&handle);

    TEST_ASSERT_EACH_EQUAL_INT(STACK_SUCCESS, ret_push, STACK_SIZE);
    TEST_ASSERT_EQUAL(1, ret_full);
    TEST_ASSERT_EACH_EQUAL_INT(STACK_SUCCESS, ret_pop, STACK_SIZE);
    TEST_ASSERT_EQUAL(1, ret_empty);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected, actual, STACK_SIZE);
}

/** Tests pushshing and popping all items in interleaved order
 */
void test_push_then_pop_all_items_interleaved(void) {
    int ret1[STACK_SIZE * 3];
    int ret2[STACK_SIZE * 3];
    int expected1[STACK_SIZE-1];
    int expected2[STACK_SIZE-1];
    int expected3[STACK_SIZE];
    int actual1[STACK_SIZE-1];
    int actual2[STACK_SIZE-1];
    int actual3[STACK_SIZE];
    int ret_full, ret_empty;

    // expected1 is ascending integers
    for (int i = 0; i < STACK_SIZE - 1; ++i) { expected1[i] = i; }
    // expected2 is descending integers
    for (int i = 0; i < STACK_SIZE - 1; ++i) { expected2[i] = -i; }
    // expected3 is mized
    for (int i = 0; i < STACK_SIZE; ++i) { expected3[i] = i%2 ? i : -i; }

    stack_t* handle = stack_create();
    for (int i = 0; i < STACK_SIZE; ++i) {
        ret1[i * 3 + 0] = stack_push(handle, expected3[i]);
        ret1[i * 3 + 1] = (i < STACK_SIZE - 1) ? stack_push(handle, expected1[i]) : 0;
        ret1[i * 3 + 2] = (i < STACK_SIZE - 1) ? stack_pop(handle, &actual1[i]) : 0;
    }

    ret_full = stack_full(handle);

    for (int i = 0; i < STACK_SIZE; ++i) {
        int k = STACK_SIZE - i - 1;
        ret2[i * 3 + 0] = (i > 0) ? stack_push(handle, expected2[i-1]) : 0;
        ret2[i * 3 + 1] = (i > 0) ? stack_pop(handle, &actual2[i-1]) : 0;
        ret2[i * 3 + 2] = stack_pop(handle, &actual3[k]);
    }

    ret_empty = stack_empty(handle);
    stack_delete(&handle);

    TEST_ASSERT_EQUAL(1, ret_full);
    TEST_ASSERT_EQUAL(1, ret_empty);
    TEST_ASSERT_EACH_EQUAL_INT(0, ret1, 3*STACK_SIZE);
    TEST_ASSERT_EACH_EQUAL_INT(0, ret2, 3*STACK_SIZE);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected1, actual1, STACK_SIZE - 1);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected2, actual2, STACK_SIZE - 1);
    TEST_ASSERT_EQUAL_INT_ARRAY(expected3, actual3, STACK_SIZE);
}

void setUp(void) {}
void tearDown(void) {}
int main() {
    UNITY_BEGIN();
    RUN_TEST(test_stack_create_should_be_valid);
    RUN_TEST(test_stack_create_should_be_empty);
    RUN_TEST(test_stack_delete_invalidates_handle);
    RUN_TEST(test_stack_create_all_stack_pool);

    RUN_TEST(test_stack_push_invalid_arguments);
    RUN_TEST(test_stack_pop_invalid_arguments);
    RUN_TEST(test_stack_pop_null_data);
    RUN_TEST(test_stack_full_invalid_arguments);
    RUN_TEST(test_stack_empty_invalid_arguments);
    RUN_TEST(test_stack_size_invalid_arguments);

    RUN_TEST(test_pop_from_empty_stack);
    RUN_TEST(test_push_to_full_stack);
    RUN_TEST(test_push_until_full);
    RUN_TEST(test_pop_until_empty);
    RUN_TEST(test_push_then_pop_single_item);
    RUN_TEST(test_push_then_pop_all_items);
    RUN_TEST(test_push_then_pop_all_items_interleaved);

    return UNITY_END();
}
