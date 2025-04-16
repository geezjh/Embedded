#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct
{
    char *data;
    int top;
    int capacity;
} Stack;
// 初始化栈
Stack *initStack(int capacity)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    stack->data = (char *)malloc(sizeof(char) * capacity);
    if (!stack || !stack->data)
    {
        return NULL;
    }

    stack->top = -1;
    stack->capacity = capacity;
    return stack;
}
// 入栈操作
void push(Stack *stack, char c)
{
    stack->data[++stack->top] = c;
}
// 出栈操作
char pop(Stack *stack)
{
    return stack->data[stack->top--];
}
// 判断栈是否为空
int isEmpty(Stack *stack)
{
    return stack->top == -1;
}
// 检测括号匹配的函数
int check(const char *code)
{
    int len = strlen(code);
    Stack *stack = initStack(len);

    for (int i = 0; i < len; i++)
    {
        char c = code[i];
        switch (c)
        {
        case '(':
        case '[':
        case '{':
            push(stack, c);
            break;
        case ')':
            if (isEmpty(stack) || pop(stack) != '(')
            {
                free(stack->data);
                free(stack);
                return -1;
            }
            break;
        case ']':
            if (isEmpty(stack) || pop(stack) != '[')
            {
                free(stack->data);
                free(stack);
                return -1;
            }
            break;
        case '}':
            if (isEmpty(stack) || pop(stack) != '{')
            {
                free(stack->data);
                free(stack);
                return -1;
            }
            break;
        }
    }

    int result = isEmpty(stack) ? 0 : -1;
    free(stack->data);
    free(stack);
    return result;
}

int main()
{
    const char *code = "{ int a[12] ={1,2} }";
    puts(code);
    int result = check(code);
    printf("Result: %d\n", result);
    return 0;
}
