/*
 *  File:       stack.c
 *  Author:     Carl B. Smiley
 *  Date:       Nov 10 2020
 *  Course:     Fundamentals of Embedded and Real Time Systems
 *
 * Description: stack implementation which supports multiple stack instances
 */
#include <stack.h>
#include <stdlib.h>

struct stack_t {
    int data[STACK_SIZE];
    int* sp;
};

static struct stack_t stack_pool[STACK_STATIC_POOL_COUNT];
static stack_t* alloc_sp = stack_pool;


stack_t* stack_create() {
    int size = alloc_sp - stack_pool;
    if (size < STACK_STATIC_POOL_COUNT) {
        alloc_sp->sp = alloc_sp->data;
        return alloc_sp++;
    }
    return NULL;
}

void stack_delete(stack_t** stack) {
    if (*stack == (alloc_sp - 1)) {
        alloc_sp--;
        *stack = NULL;
    }
    return;
}

int stack_push(stack_t* stack, int data) {
    if (stack == NULL) return STACK_ERROR_HANDLE;
    if (stack_full(stack)) return STACK_ERROR_FAILURE;
    *(stack->sp++) = data;
    return STACK_SUCCESS;
}

int stack_pop(stack_t* stack, int* data) {
    if (stack == NULL) return STACK_ERROR_HANDLE;
    if (stack_empty(stack)) return STACK_ERROR_FAILURE;
    --stack->sp;
    if (data != NULL) *data = *stack->sp;
    return STACK_SUCCESS;
}

int stack_full(const stack_t* stack) {
    if (stack == NULL) return STACK_ERROR_HANDLE;
    int size = stack->sp - stack->data;
    return size == STACK_SIZE;
}

int stack_empty(const stack_t* stack) {
    if (stack == NULL) return STACK_ERROR_HANDLE;
    return stack->data == stack->sp;
}

int stack_size(const stack_t* stack) {
    if (stack == NULL) return STACK_ERROR_HANDLE;
    return stack->sp - stack->data;
}
