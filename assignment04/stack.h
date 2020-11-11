/*
 *  File:       stack.h
 *  Author:     Carl B. Smiley
 *  Date:       Nov 10 2020
 *  Course:     Fundamentals of Embedded and Real Time Systems
 *
 * Description: stack interface API which supports multiple stack instances
 */
#pragma once

#ifndef STACK_SIZE
#define STACK_SIZE 50
#endif

#ifndef STACK_STATIC_POOL_COUNT
#define STACK_STATIC_POOL_COUNT 105
#endif

#define STACK_SUCCESS 0
#define STACK_ERROR_HANDLE -2
#define STACK_ERROR_FAILURE -1

struct stack_t;
typedef struct stack_t stack_t;

stack_t* stack_create();
void stack_delete(stack_t**);
int stack_push(stack_t*, int);
int stack_pop(stack_t*, int*);
int stack_full(const stack_t*);
int stack_empty(const stack_t*);
int stack_size(const stack_t*);