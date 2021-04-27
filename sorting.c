//
//  main.c
//  sorting
//
//  Created by 김지우
//

#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STU 50000

typedef struct student{
    int code;
    char name[12];
    int phone;
} std;

int compare(const void *t1, const void *t2){
    const std *p1 = (const std *)t1;
    const std *p2 = (const std *)t2;
    return strcmp(p1->name, p2->name);
}

void swap(std *a, std *b){
    std tmp;
    tmp = *a;
    *a = *b;
    *b = tmp;
}

void printData(std *d){
    int i=0;
    while (i<50000){
        printf("%s ,",d[i].name);
        printf("%d ,",d[i].code);
        printf("0%d\n ",d[i].phone);
        i+=1000;
    }
}

void selection_sort (std *d);
void quick_sort (std *d, int left, int right);
void heap_sort(std *d, int n);

int main() {
    clock_t start, finish;
    double duration;
    int i,j,k = 0;
    int yr[9];
    int num[5556];
    int stucode[MAX_STU];
    std member[MAX_STU];
    std members[MAX_STU];
    std memberq[MAX_STU];
    std memberh[MAX_STU];
    
    for (i=0;i<9;i++){
        yr[i] = 2013 + i;
    }
    
    srand ((unsigned)time(NULL));
    for (i=0;i<5556;i++){
        num[i] = rand()%10000;
        for(j=0;j<i;j++){
            if(num[i]==num[j]){
                i--;
                continue;
            }
        }
    }
    
    while (k<50000){
        for (i=0;i<9;i++){
            for (j=0;j<5556;j++){
                    stucode[k++] = yr[i] * 10000 + num[j];
            }
        }
    }
    
    for(i=0;i<MAX_STU;i++){
        member[i].code = stucode[i];
        member[i].phone = 1000000000 + num[rand()%5556] * 10000 + num[rand()%5556];
        for(k=0;k<10;k++){
            member[i].name[k]=(char)(rand()%26+65);
        }
    }
    
    memcpy(&memberh, &member, sizeof(struct student)*MAX_STU);
    memcpy(&memberq, &member, sizeof(struct student)*MAX_STU);
    memcpy(&members, &member, sizeof(struct student)*MAX_STU);

    
    printData(member);
    
    printf("-----------c sorting-----------\n");
    start = clock();
    qsort(member,MAX_STU, sizeof(std),compare);
    finish = clock();
    duration = (double)(finish-start)/CLOCKS_PER_SEC;
    printf("%f 초 걸림 \n",duration);
    printData(member);
    
    printf("-----------selection sorting-----------\n");
    start = clock();
    selection_sort(members);
    finish = clock();
    duration = (double)(finish-start)/CLOCKS_PER_SEC;
    printf("%f 초 걸림 \n",duration);
    printData(members);
    
    printf("-----------quick sorting-----------\n");
    start = clock();
    quick_sort(memberq, 0, 49998);
    finish = clock();
    duration = (double)(finish-start)/CLOCKS_PER_SEC;
    printf("%f 초 걸림 \n",duration);
    printData(memberq);
    
    printf("-----------heap sorting------------\n");
    start = clock();
    heap_sort(memberh, MAX_STU);
    finish = clock();
    duration = (double)(finish-start)/CLOCKS_PER_SEC;
    printf("%f 초 걸림 \n",duration);
    printData(memberh);
    
    
    printf("%s // %s // %s // %s //",member[49999].name,memberq[49999].name,memberh[49999].name,members[49999].name);
    
    return 0;
}



void selection_sort (std *d){
    int i,j,least;
    
    for(i=0;i<MAX_STU-1;i++){
        least=i;
        for(j=i+1;j<MAX_STU;j++){
            if(strcmp(d[least].name, d[j].name)>0) least=j;
        }
        swap(&d[i], &d[least]);
    }
}



int partition (std *d, int left, int right){
    int pivot, low, high;
    
    low = left;
    high = right + 1;
    pivot = left;
    
    while(low<high){
        while(strcmp(d[low].name, d[pivot].name)<0 && low<=right) low++;
        while(strcmp(d[high].name, d[pivot].name)>0 && high>=left) high--;
        if(low<high){
            swap(&d[low], &d[high]);
        }
    }
    swap(&d[low], &d[high]);
    return high;
}

void quick_sort (std *d, int left, int right){
    if(left<right){
        int q = partition(d,left, right);
        quick_sort(d, left, q-1);
        quick_sort(d, q+1, right);
    }
}



void adjust (std *d, int root, int n){
    int child, rootkey;
    child = 2*root +1;
    rootkey = root;
    if (child<n && strcmp(d[child].name, d[rootkey].name)>0) rootkey=child;
    if (child+1<n && strcmp(d[child+1].name, d[rootkey].name)>0) rootkey=child+1;
    
    if(rootkey != root){
        swap(&d[root], &d[rootkey]);
        adjust(d, rootkey, n);
    }
}

void heap_sort (std *d, int n){
    int i, j;
    for (i = n/2-1; i>=0; i--)
        adjust(d, i, n);
    for (j=n-1; j>=0; j--){
        swap(&d[0],&d[j]);
        adjust(d, 0, j);
    }
}
