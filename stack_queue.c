//
//  main.c
//  stack_queue_hw
//
//  Created by 김지우 on 2021/04/08.
//

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>
#define _CRT_SECURE_NO_WARNINGS

#define MAX_STACK_SIZE 100
#define True 1
#define False 0

typedef int Bool;
typedef int Element;
typedef struct {
    Element stackArr[MAX_STACK_SIZE];
    int top;
}Stack;

Stack* Create(void) {
    Stack* tempstack;

    tempstack = malloc(sizeof(Stack));
    tempstack->top = -1;
    
    return tempstack;
}

Bool isEmpty(Stack* pstack) {
    if (pstack->top == -1)
        return True;
    else
        return False;
}

Bool isFull(Stack* pstack) {
    if (pstack->top == MAX_STACK_SIZE - 1)
        return True;
    else
        return False;
}

void push(Stack* pstack, Element Data) {
    pstack->stackArr[++pstack->top] = Data;
}

Element pop(Stack* pstack) {
    return pstack->stackArr[pstack->top--];
}

Element peek(Stack* pstack) {
    if (isEmpty(pstack)) {
        printf("스택이 비어있음\n");
        exit(1);
    }
    else
        return pstack->stackArr[pstack->top];
}
//--------------------function--------------------
int postfix(char exp[], char str[]);
void manageQueue();


//----------------------main-----------------------
int main() {
    
    int a;
    char s[50];
    char str[50] = { '\0', };
    

    while (1)
    { 
        
        printf("계산할 수식을 입력하시오\n");
        gets(s);

        a = postfix(s, str);
        if (a < 0) {
            continue;
        }
        else {
            printf("%d \n", a);
        }
               
        if (getch() == 'z') {
            break;
        }    
    }
    manageQueue();
    
}

//----------------------------------------calculator------------
// cal_priority
int pri(char ch) {
    switch (ch) {
    case '(': case ')':
        return 0;
    case '+': case '-':
        return 1;
    case '*': case '%':
        return 2;
    case '^':
        return 3;
    }
    return -1;
}

//matching
Bool matching(char str[]) {
  
        Stack* s = Create();
        char ch, open_ch;
        int i, n = strlen(str); 
        for (i = 0; i < n; i++) {
            ch = str[i];
            switch (ch) {
            case '(':
                push(s, ch);
                break;
            case ')':
                if (isEmpty(s)) return False;
                else {
                    open_ch = pop(s);
                    if (open_ch == '(') {
                        return True;
                    }
                    break;
                }
            }
        }
        if (!isEmpty(s)) return False;  
        return True;
    
}


//infix_to_postfix
int postfix(char exp[], char str[]) {
    int i = 0, j = 0, k=0;
    int a;
    char ch, top_ch;
    int len = (int)strlen(exp);
    Stack* s = Create();
       
    for (i = 0; i < len; i++) {
        ch = exp[i];

        switch (ch) {
        case '+': case '-': case '*': case '%': case '^':
            if (exp[i + 1] == '+' || exp[i + 1] == '-' || exp[i + 1] == '%' || exp[i + 1] == '^' || exp[i + 1] == '*') {
                for (k = 0; k < i; k++) {
                    printf(" ");
                }
                printf(" ^ 이 위치에 오류가 있습니다. \n");
                return -1;
            }
            else {
                while (!isEmpty(s) && pri(ch) <= pri(peek(s)))
                    str[j++] = pop(s);
                push(s, ch);
                break;
            }
            
        case '(':
            
                if (matching(exp,')') == True) {
                    push(s, ch);
                    break;
                }
                else {
                    for (k = 0; k < len; k++) {
                        printf(" ");
                    }
                    printf("^ 이 위치에 오류가 있습니다. \n");
                    return -1;
                }
                      
        case ')':
            
                if (matching(exp, '(') == True) {
                    top_ch = pop(s);
                    while (top_ch != '(') {
                        str[j++] = top_ch;
                        top_ch = pop(s);
                    }
                    break;
                }
                else {
                    printf("^ 이 위치에 오류가 있습니다. \n");
                    return -1;
                }
            
            
        default:
            if (ch >= '0' && ch <= '9') {
                str[j++] = ch;
                break;
            }
        }
    }
    while (!isEmpty(s))
        str[j++] = pop(s);

    a = calculate(str);
    return a;
}

// calculate
int calculate(char exp[]) {
    int op1, op2, value, i = 0;
    int len = (int)strlen(exp);
    char ch;
    Stack* s = Create();
    for (i = 0; i < len; i++) {
        ch = exp[i];
        if (ch != '+' && ch != '-' && ch != '%' && ch != '*' && ch != '^') {
            value = ch - '0';
            push(s, value);
        }
        else {
            op2 = pop(s);
            op1 = pop(s);
            switch (ch) {
            case '+': push(s, op1 + op2); break;
            case '-': push(s, op1 - op2); break;
            case '*': push(s, op1 * op2); break;
            case '%': push(s, op1 % op2); break;
            case '^': push(s, pow(op1, op2)); break;
            }
        }
    }
    return pop(s);
}

//--------------------------------------queue--------------
#define MAX_QUEUE_SIZE 20
typedef struct __circleQueue {
    int rear;
    int front;
    Element* data;
}Queue;

void initQueue(Queue* q) {
    q->front = 0;
    q->rear = 0;
    q->data = (int*)malloc(sizeof(int) * MAX_QUEUE_SIZE);
}

Bool is_empty(Queue* q) {
    if (q->front == q->rear) return 1;
    else return 0;
}

Bool is_full(Queue* q) {
    if (((q->rear + 1) % MAX_QUEUE_SIZE) == q->front) return 1;
    else return 0;
}

void addQ(Queue* q, Element data) {
    if (is_full(q)) {
        printf("error : Queue is full.\n");
        return;
    }
    else {
        q->rear = (q->rear + 1) % (MAX_QUEUE_SIZE);
        q->data[q->rear] = data;
    }
}

Element delQ(Queue* q) {
    if (is_empty(q)) {
        printf("QueueEmpty\n");
    }
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
    return q->data[q->front];
}

void printQ(Queue q) {
    int i = q.front;
    int j = 0;
    if (is_empty(&q)) {
        printf("QUEUE = (0)\n");
        return;
    }
    printf("QUEUE = ");
    do {
        i = (i + 1) % MAX_QUEUE_SIZE;
        printf("%c", q.data[i]);
        j++;
        if (i == q.rear) {
            printf("(%d)\n", j);
            break;
        }
    } while (i != q.front);
    return;
}

void manageQueue() {
    int i = 0, j = 0, k = 0;
    int n = 0;
    int t = 0;
    clock_t start, end;
    Queue q;
    initQueue(&q);
    while (1) {
        int result[20] = {0, };
        start = clock();
        printf(">>>");
        scanf_s("%d", &i);

        end = clock();
        t = (int)(end - start) / 1000;
        //printf("%d", t);

        for (j = n; j < t + n; j++) {
            if (is_full(&q)) {
                printf("ADDQUEUE() FAIL.QueueFull\n");
            }
            addQ(&q, 65 + (j%26));
            printf("(SYSTEM) ADDQUEUE(%c) F=%d R=%d \n", 65 + j, q.front, q.rear);
        }
        n = j;

        if (i == 0) {
            printQ(q);
        }
        else {
            j = 0;
            while (j < i) {
                if (!is_empty(&q)) {
                    k = delQ(&q);
                    printf("DELETEQUEUE() = %c, F=%d R=%d\n", k, q.front, q.rear);
                    result[j++] = k;
                }
                else {
                    printf("DELETEQUEUE() = FAIL.QueueEmpty\n");
                    break;
                }
            }
            printf("RESULT = ");
            for (j = 0; j < i; j++) {
                printf("%c", (char)result[j]);
            }
            printf("\n");
            printQ(q);
            
        }
        
    }
}
