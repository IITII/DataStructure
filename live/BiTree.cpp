#include "bits/stdc++.h"
typedef struct TREENODE
{
    char data;
    struct TREENODE *lchild, *rchild;
} TNode, *BiTree;

BiTree CreateBiTree()
{
    char ch;
    BiTree T;
    scanf("%c", &ch);
    if (ch == '#')
        return NULL;
    else
    {
        T = (BiTree)malloc(sizeof(TNode));
        T->data = ch;
        T->lchild = CreateBiTree(); //构造左子树
        T->rchild = CreateBiTree(); //构造右子树
        return T;
    }
}

void PreOrder(BiTree BT)
{
    if (BT != NULL)
    {
        printf("%c", BT->data);
        PreOrder(BT->lchild);
        PreOrder(BT->rchild);
    }
}
void levelorder(BiTree BT) {
    BiTree T, queue[100];
    int front = 0, rear = 1;
    queue[0] = BT;
    while (front < rear)
    {
        T = queue[front++];
        printf("%c", T->data);
        if (T->lchild != NULL)
        {
            queue[rear++] = T->lchild;
        }
        if (T->rchild != NULL)
        {
            queue[rear++] = T->rchild;
        }
    }
}

//BiTree Pre_Create_BT(){//构造二叉树void NRPreOrder(BiTree bt) {
    InitStack(S);
    BiTree p = bt;
    while (p||!StackEmpty(S))
    {
        while (p)
        {
            Visite(p->data);
            Push(S, p);
            p = p->lchild;

        }
        if (!StackEmpty(S))
        {
            Pop(S, p);
            p = p->rchild;

        }
    }
}
int flag;
s.top = -1;
T = NULL;
scanf("%c", &ch);
while (ch != '#') {
    switch (ch)
    {
    case '(':s.base[++s.top] = p;
        flag = 1;
        break;
    case ')':s.top--; break;
    case ',':flag = 0; break;
    default:
        p = (BiTree)malloc(sizeof(TNode));
        p->lchild = NULL;
        p->rchild = NULL;
        p->data = ch;
        if (T == NULL)
        {
            T = p;
        }
        else {
            e = s.base[s.top];
            if (flag)
            {
                e->lchild = p;
            }
            else
                e->rchild = p;
        }
        break;
    }
}
//	char ch=getchar();
//	BiTree BT;
//	if(ch=='#') return NULL;//构造空树
//	else {
//		BT = (BiTree)malloc(sizeof(BiTree));//构造新节点
//		BT->data = ch;
//		BT->lchild = Pre_Create_BT;//构造左子树
//		BT->rchild = Pre_Create_BT;//构造右子树
//		return BT;
//	}
//}

//void preorder(BiTree T){//先序遍历算法
//    if(T != NULL ){
//        visite(T);//访问T的根节点
//        preoder(T->lchild);//先序遍历T的左子树
//        preoder(T->rchild);//先序遍历T的右子树
//    }
//}
//
//void preorder(BiTree T){//中序遍历算法
//    if(T != NULL ){
//        preorder(T->lchild);//中序遍历T的左子树
//        visite(T);//访问T的根节点
//        preoder(T->rchild);//中遍历T的右子树
//    }
//}

int main(int argc, char *argv[])
{
    BiTree BT;
    BT = CreateBiTree();
    PreOrder(BT);

    return 0;
}
