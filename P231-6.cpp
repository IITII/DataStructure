#include <stdio.h>
#include <stdlib.h>
typedef struct TREENODE {
    char data;
    struct TREENODE* lchild, * rchild;
}TNode, * BiTree;
typedef struct Stack {
    BiTree base[100];
    int top;
}Stack;
BiTree CreateBiTree() {
    Stack S;
    BiTree T, P, E;
    char ch;
    int flag;
    S.top = -1;
    T = NULL;
    scanf("%c", &ch);
    while (ch != '#') {
        switch (ch) {
        case'(': S.base[++S.top] = P; flag = 1; break;
        case')': S.top--; break;
        case',': flag = 0; break;
        default: {
            P = (BiTree)malloc(sizeof(TNode));
            P->lchild = NULL;
            P->rchild = NULL;
            P->data = ch;
            if (T == NULL)
                T = P;
            else {
                E = S.base[S.top];
                if (flag)
                    E->lchild = P;
                else

                    E->rchild = P;
            }
            break;
        }
        }
        scanf("%c", &ch);
    }
    return T;
}
void PreOrder(BiTree BT) {//先序遍历算法 
    if (BT != NULL) {
        printf("%c", BT->data);
        PreOrder(BT->lchild);
        PreOrder(BT->rchild);
    }
}
int NodeCountBiTree(BiTree BT) {
    int num1, num2;
    if (BT == NULL) return 0;
    else {
        /*num1 = NodeCountBiTree(BT->lchild);
        num2 = NodeCountBiTree(BT->rchild);
        return (num1 + num2);*/
        return (NodeCountBiTree(BT->lchild) + NodeCountBiTree(BT->rchild) + 1);
    }
}
int main(int argc, char* argv[]) {
    BiTree BT;
    BT = CreateBiTree();
    PreOrder(BT);
    printf("\n总结点数为：%d", NodeCountBiTree(BT));
    return 0;
}
