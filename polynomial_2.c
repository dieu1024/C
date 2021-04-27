//
//  방법 2 - 0이 아닌 계수의 차수만 저장
//
//  Created by 김지우 on 2021/03/26.
//

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TERMS 101

typedef struct {
    int coef;
    int expon;
} terms;
int avail=0;

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

//두개의 정수 비교 함수
char compare (int a, int b)
{
    if (a>b) return '>';
    else if (a==b) return '=';
    else return '<';
}

//다항식 출력 함수
void printTerm(int As, int Ae, terms A[])
{
    int i ;
    for (i = As; i <= Ae ; i++){
        printf("%dx^%d ", A[i].coef, A[i].expon);
    }
    printf("\n");
}

//덧셈 후에 배열에 항을 추가하는 함수
void attachAdd(int coef, int expon, terms A[])
{
    if (avail>MAX_TERMS){
        printf("항의 갯수가 너무 많음 \n");
        exit(1);
    }
    A[avail].coef=coef;
    A[avail++].expon=expon;
}

//다항식 덧셈 함수
void polyAdd(terms A[], int As, int Ae, int Bs, int Be, int *Cs, int *Ce){
    int tempcoef;
    *Cs=avail;
    while(As<=Ae&&Bs<=Be)
        switch(compare(A[As].expon,A[Bs].expon)){
            case'>'://A의차수>B의차수
                attachAdd(A[As].coef,A[As].expon,A);
                As++;
                break;
            case'='://A의차수==B의차수
                tempcoef=A[As].coef+A[Bs].coef;
                if(tempcoef)
                    attachAdd(tempcoef,A[As].expon,A);
                As++;
                Bs++;
                break;
            case'<'://A의차수<B의차수
                attachAdd(A[Bs].coef,A[Bs].expon,A);
                Bs++;
                break;
        }
    *Ce=avail-1;
}

//곱셈 후에 다항식에 추가하는 함수
void attachMult(int coef, int expon, int s, terms A[])
{
    int i, j;
    if (avail>MAX_TERMS){
        printf("항의 갯수가 너무 많음 \n");
        exit(1);
    }
    
    i=avail-1;
    
    for (j = i; j >= s; j--)
    {
        //차수가 같을 경우 계수를 더함
        if (A[j].expon == expon)
        {
            A[j].coef += coef;
            return;
        }
    }
    //차수가 같지 않을 경우 그냥 다항식에 추가
    A[avail].coef = coef;
    A[avail++].expon = expon;
}

//다항식의 곱셈 함수
void polyMult(terms A[], int As, int Ae, int Bs, int Be, int* Ds, int* De)
{
    int coefficient;
    int exponent;
    int i, j;
    int s;

    *Ds = avail;
    s= avail;

    for (i = As; i <= Ae; i++)
    {
        for (j = Bs; j <= Be; j++)
        {
            coefficient = A[i].coef * A[j].coef;   //계수의 곱
            exponent = A[i].expon + A[j].expon;   // 지수의 합
            attachMult(coefficient, exponent, s, A);     //곱셈항 추가
        }
    }

    *De = avail - 1;

}

//대입 함수
int polySum (int As, int Ae, int x, terms A[]){
    int result=0;
    int i, j;
    for(i=As; i<Ae+1; i++){
        int temp = 1;
        for(j=0; j<A[i].expon; j++){
            temp = temp * x;
        }
        result += A[i].coef * temp;
    }
    return result;
}

int main(){
    int i, count, p, j, result;
    int num[100];
    int As,Ae,Bs,Be,Cs,Ce,Ds,De;
    
    terms A[MAX_TERMS];
    printf("수식 1을 입력하세요 :");
    count = input_number(num);
    As=avail;
    if (count <12){
        for (i = 0; i < count; i++){
            if((i%2)==0) A[avail].coef=num[i];
            else A[avail++].expon=num[i];
        }
    }
    else {
        printf ("다항식의 차수는 5를 넘으면 안됩니다");
        return 0;
    }
    Ae=avail-1;
    printTerm(As,Ae,A);
    
    printf("수식 2를 입력하세요 :");
    count = input_number(num);
    Bs=avail;
    if (count <12){
        for (i = 0; i < count; i++){
        if((i%2)==0) A[avail].coef=num[i];
        else A[avail++].expon=num[i];
        }
    }
    else {
        printf ("다항식의 차수는 5를 넘으면 안됩니다");
        return 0;
    }
    Be=avail-1;
    printTerm(Bs,Be,A);
    
    polyAdd(A, As, Ae, Bs, Be, &Cs, &Ce);
    printf("수식 1 + 2 는 :");
    printTerm(Cs,Ce,A);
    
    polyMult(A, As, Ae, Bs, Be, &Ds, &De);
    printf("수식 1 * 2 는 :");
    printTerm(Ds,De,A);
    
    printf ("수식에 값을 넣으세요 ");
    scanf("%d %d",&p,&j);
    if (p==1)
        result = polySum(As,Ae,j,A);
    else if (p==2)
        result = polySum(Bs,Be,j,A);
    else if (p==3)
        result = polySum(Cs,Ce,j,A);
    else
        result = polySum(Ds,De,j,A);

    printf("결과 값은 %d \n",result);
}
