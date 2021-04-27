//
//  방법 1 - 모든 차수의 계수를 저장
//
//  Created by 김지우
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX(a,b)(((a)>(b))?(a):(b))
#define MAX_DEGREE 101

typedef struct {
    int degree;
    int coef[MAX_DEGREE];
} polynomial;

//다항식 입력 받는 함수
int input_number(int number[100]) {
    char input[100];
    char* token;
    int i = 0;

    fgets(input, sizeof(input), stdin);
    
    token = strtok(input, " ");
    while (token != NULL) {
        number[i++] = atoi(token);
        token = strtok(NULL, " ");
    }
    return i;
}

//다항식 덧셈 함수
polynomial polyAdd (polynomial A, polynomial B)
{
    polynomial C; //덧셈 결과 다항식
    int Apos=0, Bpos=0, Cpos=0; //배열 인덱스 변수
    int degree_a=A.degree;
    int degree_b=B.degree;
    C.degree = MAX(A.degree, B.degree);
    while (Apos<=A.degree && Bpos<=B.degree){
        if (degree_a>degree_b){
            C.coef[Cpos++]=A.coef[Apos++];
            degree_a--;
        }
        else if (degree_a == degree_b){
            C.coef[Cpos++]=A.coef[Apos++]+B.coef[Bpos++];
            degree_a--;
            degree_b--;
        }
        else {
            C.coef[Cpos++]=B.coef[Bpos++];
            degree_b--;
        }
    }
    return C;
}

//다항식 곱셈 함수
polynomial polyMult (polynomial A, polynomial B)
{
    int i, j;
    polynomial C;
    for(i = 0; i < A.degree + B.degree; i++)
        C.coef[i] = 0;

    C.degree = A.degree + B.degree - 1;

    for (i = 0; i < A.degree ; i++)
     for (j = 0; j < B.degree ; j++)
      C.coef[i + j] += A.coef[i] * B.coef[j];

    return C;
}

//다항식 대입 함수
int polySum (polynomial P, int x){
    int result, degree, i;
    degree=P.degree;
    
    result = P.coef[0];
    for (i = 1; i<degree; i++)
        result = result * x + P.coef[i];
    
    return result;
}

//다항식 출력 함수
void printPoly(polynomial P)
{
 int i, degree;
 degree=P.degree-1;
 
 for(i=0; i<P.degree; i++){
     printf("%dx^%d ",P.coef[i], degree--);
     }
    printf("\n");
}


int main()
{
    int i;
    int j, result, p; //j = 대입시 x 값 , result = 대입한 다항식의 값, p = 수식 고르기
    int num[100];
    int count; //항의 갯수
    
    polynomial A;
    printf ("수식 1을 입력하세요 :");
    count = input_number(num);
    A.degree=count;
    if (count <6){
        for (i = 0; i < count; i++){
        A.coef[i]=num[i];
        }
    }
    else {
        printf ("다항식의 차수는 5를 넘으면 안됩니다");
        return 0;
    }
    printPoly(A);
    
    polynomial B;
    printf ("수식 2을 입력하세요 :");
    count = input_number(num);
    B.degree=count;
    if (count <6){
        for (i = 0; i < count; i++){
        B.coef[i]=num[i];
        }
    }
    else {
        printf ("다항식의 차수는 5를 넘으면 안됩니다");
        return 0;
    }
    printPoly(B);
    
    polynomial C = polyAdd(A, B);
    printf("수식 1 + 2 는 :");
    printPoly(C);
    
    polynomial D = polyMult(A,B);
    printf("수식 1 * 2 는 :");
    printPoly(D);
    
    printf ("수식에 값을 넣으세요");
    scanf("%d %d",&p,&j);
    if (p==1)
        result = polySum(A,j);
    else if (p==2)
        result = polySum(B,j);
    else if (p==3)
        result = polySum(C,j);
    else
        result = polySum(D,j);

    printf("결과 값은 %d",result);
    
}
