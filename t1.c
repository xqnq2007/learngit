#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <windows.h>
int digui(int n, int k){
	if (n <= k){
		return 1;
	}
	int i = 0;
	int tmp = 0;
	while (i < k){
		tmp += digui(n - 1 - i, k);
		i++;
	}
	return tmp;
}
int diedai(int n, int k){
	if (n <= k){
		return 1;
	}
	int a,b,c,d,tmp;
	a = b = c = d = 1;
	tmp = 0;
	for (int i = 5; i <= n;i++){
		tmp = a + b + c + d;
		a = b;
		b = c;
		c = d;
		d = tmp;
	}
	return tmp;
}
HANDLE hout;
typedef struct BiTree {
	int data;
	struct BiTree *lchild;
	struct BiTree *rchild;
}BiTree;
BiTree* InsertBST(BiTree *t, int key)
{		
	
	if (t==NULL)
	{
		t=(struct BiTree*)malloc(sizeof(struct BiTree));
		t->lchild = t->rchild = NULL;
		t->data = key;		
		return t;
	}
	if (key < t->data)
		t->lchild = InsertBST(t->lchild, key);
	else
		t->rchild = InsertBST(t->rchild, key);

	return t;
}
BiTree* search_BST(BiTree* p, int x)
{
	int solve = 0;
	while (p && !solve){
		if (x == p->data){
			solve = 1;
		}
		else if (x < p->data){
			p = p->lchild;
		}
		else{
			p = p->rchild;
		}
	}
	if (p == NULL){
		printf("没有找到");
	}
	return p;
}
BiTree* CreateBiTree(BiTree *tree, int d[], int n)
{
	for (int i = 0; i < n; i++)
		tree = InsertBST(tree, d[i]);
	return tree;
}
void showTree(BiTree *tree){
	if (tree){
		printf("%d\n",tree->data);
		if (tree->lchild){
			showTree(tree->lchild);
		}
		if (tree->rchild){
			showTree(tree->rchild);
		}
	}
}
int print_at_level(BiTree *T, int level, int ntap, int leveltap) {
	COORD coord; //屏幕上的坐标
	CONSOLE_SCREEN_BUFFER_INFO csbi; //控制台屏幕缓冲区信息
	hout = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hout, &csbi);
	coord.X = csbi.dwCursorPosition.X; //得到坐标X的值
	coord.Y = csbi.dwCursorPosition.Y; //得到坐标Y的值
	while (coord.X > 0){
		coord.X--;
	}
	SetConsoleCursorPosition(hout, coord);
	if (!T || level < 0)
		return 0;
	if (0 == level) {
		for (int i = 0; i < ntap; i++){
			coord.X++;
			SetConsoleCursorPosition(hout, coord);
			//printf("   ");
		}
		printf("%d",T->data);
		return 1;
	}	
	return print_at_level(T->lchild, level - 1, ntap - leveltap, leveltap) + print_at_level(T->rchild, level - 1, ntap + leveltap, leveltap);
}
void print_by_level_1(BiTree *T) {
	int i = 0;
	int ntap = 32;
	for (i = 0;; i++) {	
		if (i > 0)printf("\n");
		int leveltap = 16/(i+1);
		if (!print_at_level(T, i,ntap,leveltap))
			break;
	}
	printf("\n");
}
int Delete(BiTree* p)//从二叉排序树中删除结点p，并重接它的左或右子树
{
	BiTree* q;
	BiTree* s;
	if (!p->rchild)//右子树空则只需重接它的左子树
	{		
		q = p;
		p = p->lchild;
		free(q);
	}
	else if(!p->lchild)//左子树空只需重接它的右子树
	{
		q = p;
		p = p->rchild;
		free(q);
	}
	else//左右子树均不空
	{
		q = p;
		s = p->lchild;
		while (s->rchild)//转左，然后向右到尽头
		{
			q = s;
			s = s->rchild;
		}
		p->data = s->data;//s指向被删结点的“前驱”
		if (q != p)//以上循环至少执行了一次
			q->rchild = s->lchild;
		else
			q->lchild = s->lchild;//重接*q的左子树
		free(s);
	}
	return 1;
}
int main(){
	BiTree *p, *root;
	p = (struct BiTree*)malloc(sizeof(struct BiTree));
	root = NULL;
	//int d[5] = {1, 3, 2, 7, 5};
	int d[10] = {15,5,16,3,12,20,10,13,18,23};
	//int d[10] = { 15, 5, 16};
	//printf("%d",p->rchild->data);
	p = CreateBiTree(root,d,10);
	//printf("%d", p->rchild->data);
	//showTree(p);
	print_by_level_1(p);
	//BiTree *tmp;
	//tmp = (struct BiTree*)malloc(sizeof(struct BiTree));
	//tmp = search_BST(p,3);
	//printf("%d",tmp->data);
	//Delete(tmp);
	//print_by_level_1(p);
	system("pause");
	return 0;
}