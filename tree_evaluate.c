//
//  main.c
//  tree
//
//  Created by 김지우 on 2021/05/25.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct TreeNode {
    int data;
    struct TreeNode *left, *right;
} TreeNode;

TreeNode* CreateTree(void){
    TreeNode* node = (TreeNode*)malloc(sizeof(TreeNode));
    node -> left = NULL;
    node -> right = NULL;
    return node;
}

void Lchild(TreeNode* par, TreeNode* chi){
    if (par->left != NULL) free(par->left);
    par->left = chi;
}

void Rchild(TreeNode* par, TreeNode* chi){
    if (par->right != NULL) free(par->right);
    par -> right = chi;
}

void SetData (TreeNode* node, int Data){
    node->data = Data;
}

void ShowNodeData(int data){
    if (0<=data && data<=9) printf("%d ",data);
    else printf("%c ",data);
}

TreeNode* ExpTree(char exp[]);
int Evaluate(TreeNode* root);

void PreorderTraverse(TreeNode* root);
void InorderTraverse(TreeNode* root);
void PostorderTraverse(TreeNode* root);
void Levelorder (TreeNode* root);


//----------main----------

int main() {
    
    char exp[50];
    printf("수식을 입력하세요(공백 없이 입력) : ");
    gets(exp);
    TreeNode* Tree = ExpTree(exp);
    
    printf("전위 순회 : ");
    PreorderTraverse(Tree);
    printf("\n");
    
    printf("중위 순회 : ");
    InorderTraverse(Tree);
    printf("\n");

    printf("후위 순회 : ");
    PostorderTraverse(Tree);
    printf("\n");
    
    printf("레벨 순회 : ");
    Levelorder (Tree);
    printf("\n");

    printf("계산 결과 : %d \n", Evaluate(Tree));

    return 0;
}


//----------evaluate----------

#define True 1
#define False 0

typedef int Bool;

typedef struct {
     int stackArr[10];
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
    if (pstack->top == 50 - 1)
        return True;
    else
        return False;
}

void Spush(Stack* pstack, int Data) {
    pstack->stackArr[++pstack->top] = Data;
}

int Spop(Stack* pstack) {
    return pstack->stackArr[pstack->top--];
}

int peek(Stack* pstack) {
    if (isEmpty(pstack)) {
        printf("Stack is empty. \n");
        exit(1);
    }
    else
        return pstack->stackArr[pstack->top];
}


TreeNode* stack[50];
int top = -1;

void push(TreeNode* data) {
    if (top< 49 && data != NULL) stack[++top] = data;
}

TreeNode* pop() {
    TreeNode* node;
    if (top >=0) node = stack[top--];
    return node;
}

int pri(char ch) {
    switch (ch) {
    case '+': case '-':
        return 1;
    case '*': case '/':
        return 2;
    }
    return -1;
}

TreeNode* ExpTree(char exp[]){
    
    TreeNode* node;
    
    int len = (int)strlen(exp);
    int i;
    
    Stack* s = Create();
    int j = 0;
    char ch;
    char str[10];
    
    for (i = 0; i < len; i++) {
        ch = exp[i];

        switch (ch) {
        case '+': case '-': case '*': case '/':
                while (!isEmpty(s) && pri(ch) <= pri(peek(s)))
                    str[j++] = Spop(s);
                Spush(s, ch);
                break;
            
        default:
            if (ch >= '0' && ch <= '9') {
                str[j++] = ch;
                break;
            }
        }
    }
    while (!isEmpty(s))
        str[j++] = Spop(s);
    
    
    for (i=0; i<len; i++){
        node = CreateTree();
        
        if(isdigit(str[i]))SetData(node, str[i]-'0');
        else {
            Rchild(node, pop());
            Lchild(node, pop());
            SetData(node, str[i]);
        }
        
        push(node);
    }
    
    return pop();
}

void PreorderTraverse(TreeNode* root) {
    if(root == NULL) return;
    
    ShowNodeData(root->data);
    PreorderTraverse(root->left);
    PreorderTraverse(root->right);
}

void InorderTraverse(TreeNode* root) {
    if(root == NULL) return;
    
    InorderTraverse(root->left);
    ShowNodeData(root->data);
    InorderTraverse(root->right);
}

void PostorderTraverse(TreeNode* root) {
    if(root == NULL) return;
    
    PostorderTraverse(root->left);
    PostorderTraverse(root->right);
    ShowNodeData(root->data);
}

int front =0, rear =0;
TreeNode* Queue[20];

void addQ(TreeNode* node) {
    Queue[++rear] = node;
}

TreeNode* delQ() {
    return Queue[++front];
}

void Levelorder (TreeNode* root) {
    
    if(root == NULL) return;
    
    addQ(root);
    
    while(1){
        root = delQ();
        if (root != NULL){
            ShowNodeData(root->data);
            
            if(root->left != NULL) addQ(root->left);
            if(root->right != NULL) addQ(root->right);
        }
        else break;
    }
}

int Evaluate(TreeNode* root) {
    
    if (root == NULL) return 0;
    
    if (root->left == NULL && root->right ==NULL) return root->data;
    else {
        int op1 = Evaluate(root->left);
        int op2 = Evaluate(root->right);
        switch (root->data) {
            case '+': printf("%d + %d\n",op1,op2); return op1+op2;
            case '-': printf("%d - %d\n",op1,op2);return op1-op2;
            case '*': printf("%d * %d\n",op1,op2);return op1*op2;
            case '/': printf("%d / %d\n",op1,op2);return op1/op2;
        }
    }
    return 0;
}
