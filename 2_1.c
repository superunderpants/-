// 实验2 一元稀疏多项式计算器
// 【问题描述】
// 设计一个一元稀疏多项式简单计算器。
// 【基本要求】
// 一元稀疏多项式简单计算器的基本功能是：
// （1）输入并建立多项式；
// （2）输出并显示多项式，输出形式为整数序列：n,c1,e1,c2,e2,…,cn,en,其中n是多项式的项数，
//ci和ei分别是第i项的系数和指数，序列按指数降序排列；
// （3）多项式a和b相加，建立多项式a+b;
// （4）多项式a和b相减，建立多项式a-b;
// （5）求多项式a的导数。
// 【测试数据】
// 以多项式相加功能为例，可以设计如下的测试数据。
// （1）  
// （2）  
// （3）  
// （4）  
// （5）  
// （6）  
// 【实现提示】
// 用带表头结点的单链表存储多项式。
// 【思考题】
// 求多项式a和b相乘，可以用类C伪代码写出主要流程和步骤。
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
struct item//每一项
{
    float c;
    float e;
};

typedef struct ListNode
{
    struct item eachItem;
    struct ListNode *next;
}Lnode, *Linklist;
void InitListNode(Linklist L){
    L = (Lnode *)malloc(sizeof(Lnode));
    if(!L) exit(1);
    L->next = NULL;
}
void CreateListNode( Linklist L, struct item eachItem[], int n){
    //L = (Lnode *)malloc(sizeof(Lnode));
    Linklist p;
    //L->next = NULL;
    // if (!L)
    // {
    //     exit(1);
    // }
    for (int i = 0; i < n; i++)//头插法
    {
        p = (Lnode *)malloc(sizeof(Lnode));
        if(!p) exit(1);
        p->eachItem = eachItem[i];
        p->next = L->next;
        L->next = p;
    }
    for (int i = 0; i < n; i++)//把每一项按指数从大到小排序
    {
        for (int j = i; j < n; j++)
        {
            if(eachItem[i].e < eachItem[j].e){
                float temp = eachItem[i].e;
                eachItem[i].e = eachItem[j].e;
                eachItem[j].e = temp;
            }
        }
    }
}
void add(Linklist L1, Linklist L2, Linklist L3){//加法
    //L3 = (Lnode *)malloc(sizeof(Lnode));
    //L3->next = NULL;
    Linklist p, q;
    q = L3;
    while (L1->next != NULL && L2->next != NULL)
    {
        p = (Lnode *)malloc(sizeof(Lnode));
        if (fabs(L1->next->eachItem.e - L2->next->eachItem.e) < 0.01)
        {
            p->eachItem.c = L1->next->eachItem.c + L2->next->eachItem.c;
            p->eachItem.e = L1->next->eachItem.e;
            L1 = L1->next;
            L2 = L2->next;
        }else if(L1->next->eachItem.e > L2->next->eachItem.e){
            p->eachItem = L1->next->eachItem;
            L1 = L1->next;
        }else{
            p->eachItem = L2->next->eachItem;
            L2 = L2->next;
        }
        p->next = NULL;
        q->next = p;
        q = q->next;
    }
    if (L1->next == NULL)
    {
        p->next = L2->next;
    }else{
        p->next = L1->next;
    }
}
void minus(Linklist L1, Linklist L2, Linklist L3){//减法
    //L3 = (Lnode *)malloc(sizeof(Lnode));
    //L3->next = NULL;
    Linklist p;
    Linklist q = L3;
    while (L1->next != NULL && L2->next != NULL)
    {
        p = (Lnode *)malloc(sizeof(Lnode));
        if (fabs(L1->next->eachItem.e - L2->next->eachItem.e) < 0.01)
        {
            p->eachItem.c = L1->next->eachItem.c - L2->next->eachItem.c;
            p->eachItem.e = L1->next->eachItem.e;
            L1 = L1->next;
            L2 = L2->next;
        }else if(L1->next->eachItem.e > L2->next->eachItem.e){
            p->eachItem = L1->next->eachItem;
            L1 = L1->next;
        }else{
            p->eachItem.c = - L2->next->eachItem.c;
            p->eachItem.e = L2->next->eachItem.e;
            L2 = L2->next;
        }
        p->next = NULL;
        q->next = p;
        q = q->next;
    }
    while(L1->next == NULL && L2->next != NULL)
    {
        p->next->eachItem.c = - L2->next->eachItem.c;
        p->next->eachItem.e = L2->next->eachItem.e;
    }
    if(L2->next == NULL){
        p->next = L1->next;
    }
}
void diff(Linklist L1, Linklist L2){
    L2 = (Lnode *)malloc(sizeof(Lnode));
    L2->next = NULL;
    Linklist p;
    Linklist q = L2;
    while (L1->next != NULL){
        p = (Lnode *)malloc(sizeof(Lnode));
        p->eachItem.c = L1->next->eachItem.c * L1->next->eachItem.e;
        p->eachItem.e = L1->next->eachItem.e - 1;
        L1 = L1->next;
        p->next = NULL;
        q->next = p;
        q = q->next;
    }
}
void output(const Linklist L){
    //将同系数项合并
    Linklist left = L;
    Linklist right;
    while(left->next->next != NULL){
        right = left->next;
        while(right->next != NULL && left->next->eachItem.e == right->next->eachItem.e){
            left->next->eachItem.c = left->next->eachItem.c + right->next->eachItem.c;
            left->next->next = right->next->next;
            right = left->next;
            //free(right);
        }
        left = left->next;
    }
    Linklist p = L;
    printf("(");
    while (p->next->next != NULL)
    {
        if(p->next->eachItem.c < 0.01 && p->next->eachItem.c > -0.01){
            printf("");
        }else if(p->next->eachItem.e < 0.01 && p->next->eachItem.e > 0.01){
            printf("%2.1f + ", p->next->eachItem.c);
        }else if(p->next->eachItem.e < 1.01 && p->next->eachItem.e > 0.99){
            printf("%2.1f x + ", p->next->eachItem.c);
        }else{
            printf("%2.1f x**(%2.1f) + ", p->next->eachItem.c, p->next->eachItem.e);
        }
        p = p->next;
    }
    if(p->next->eachItem.c < 0.01 && p->next->eachItem.c > -0.01){
        printf("0");
    }else if(p->next->eachItem.e < 0.01 && p->next->eachItem.e > -0.01){
        printf("%2.1f", p->next->eachItem.c);
    }else if(p->next->eachItem.c < 1.01 && p->next->eachItem.c > 0.99){
        printf("%2.1f x", p->next->eachItem.c);
    }
    else{
        printf("%2.1f x**(%2.1f)", p->next->eachItem.c, p->next->eachItem.e);
    }
    printf(")");
}

int main(){
    //生成测试数据以及数据初始化
    //加数，被减数，减数
    Linklist test01, test02, test03, test04, test05, test06, test07, test08, test09, test10, test11, test12;
    test01 = (Lnode *)malloc(sizeof(Lnode));
    test02 = (Lnode *)malloc(sizeof(Lnode));
    test03 = (Lnode *)malloc(sizeof(Lnode));
    test04 = (Lnode *)malloc(sizeof(Lnode));
    test05 = (Lnode *)malloc(sizeof(Lnode));
    test06 = (Lnode *)malloc(sizeof(Lnode));
    test07 = (Lnode *)malloc(sizeof(Lnode));
    test08 = (Lnode *)malloc(sizeof(Lnode));
    test09 = (Lnode *)malloc(sizeof(Lnode));
    test10 = (Lnode *)malloc(sizeof(Lnode));
    test11 = (Lnode *)malloc(sizeof(Lnode));
    test12 = (Lnode *)malloc(sizeof(Lnode));
    test01->next = NULL;
    test02->next = NULL;
    test03->next = NULL;
    test04->next = NULL;
    test05->next = NULL;
    test06->next = NULL;
    test07->next = NULL;
    test08->next = NULL;
    test09->next = NULL;
    test10->next = NULL;
    test11->next = NULL;
    test12->next = NULL;
    struct item eachItem01[3] = {{2, 1}, {5, 8}, {-3.1, 11}};
    struct item eachItem02[3] = {{7, 0}, {-5, 8}, {11, 9}};
    struct item eachItem03[4] = {{6, -3}, {-1, 1}, {4.4, 2}, {-1.2, 9}};
    struct item eachItem04[4] = {{-6, -3}, {5.4, 2}, {-1, 2}, {7.8, 15}};
    struct item eachItem05[6] = {{1, 0}, {1, 1}, {1, 2}, {1, 3}, {1, 4}, {1, 5}};
    struct item eachItem06[2] = {{-1, 3}, {-1, 4}};
    struct item eachItem07[2] = {{1, 1}, {1, 3}};
    struct item eachItem08[2] = {{-1, 1}, {-1, 3}};
    struct item eachItem09[2] = {{1, 1}, {1, 100}};
    struct item eachItem10[2] = {{1, 100}, {1, 200}};
    struct item eachItem11[3] = {{1, 1}, {1, 2}, {1, 3}};
    struct item eachItem12[1] = {{0, 0}};
    //printf("测试%f", eachItem01[0].c);
    CreateListNode(test01, eachItem01, 3);
    CreateListNode(test02, eachItem02, 3);
    CreateListNode(test03, eachItem03, 4);
    CreateListNode(test04, eachItem04, 4);
    CreateListNode(test05, eachItem05, 6);
    CreateListNode(test06, eachItem06, 2);
    CreateListNode(test07, eachItem07, 2);
    CreateListNode(test08, eachItem08, 2);
    CreateListNode(test09, eachItem09, 2);
    CreateListNode(test10, eachItem10, 2);
    CreateListNode(test11, eachItem11, 3);
    CreateListNode(test12, eachItem12, 1);
    //初始化测试结果数据
    Linklist result01, result02, result03, result04, result05, result06;
    result01 = (Lnode *)malloc(sizeof(Lnode));
    result02 = (Lnode *)malloc(sizeof(Lnode));
    result03 = (Lnode *)malloc(sizeof(Lnode));
    result04 = (Lnode *)malloc(sizeof(Lnode));
    result05 = (Lnode *)malloc(sizeof(Lnode));
    result06 = (Lnode *)malloc(sizeof(Lnode));
    result01->next = NULL;
    result02->next = NULL;
    result03->next = NULL;
    result04->next = NULL;
    result05->next = NULL;
    result06->next = NULL;
    printf("===================测试结果==================\n");
    add(test01, test02, result01);
    output(test01);
    printf(" + ");
    output(test02);
    printf(" = ");
    output(result01);
    printf("\n");
    minus(test03, test04, result02);
    output(test03);
    printf(" - ");
    output(test04);
    printf(" = ");
    output(result02);
    printf("\n");
    add(test05, test06, result03);
    output(test05);
    printf(" + ");
    output(test06);
    printf(" = ");
    output(result03);
    printf("\n");
    add(test07, test08, result04);
    output(test07);
    printf(" + ");
    output(test08);
    printf(" = ");
    output(result04);
    printf("\n");
    add(test09, test10, result05);
    output(test09);
    printf(" + ");
    output(test10);
    printf(" = ");
    output(result05);
    printf("\n");
    add(test11, test12, result06);
    output(test11);
    printf(" + ");
    output(test12);
    printf(" = ");
    output(result06);
    printf("\n");
    return 0;
}