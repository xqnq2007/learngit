#include <stdio.h>
#include <time.h>
#include <stdlib.h>
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
int print_at_level(BiTree *T, int level,int ntap) {	
	if (!T || level < 0)
		return 0;
	if (0 == level) {
		for (int i = 0; i < ntap; i++){
			printf("   ");
		}
		printf("%d",T->data);
		return 1;
	}
	return print_at_level(T->lchild, level - 1,ntap-1) + print_at_level(T->rchild, level - 1,ntap+1);
}
void print_by_level_1(BiTree *T) {
	int i = 0;
	int ntap = 5;
	for (i = 0;; i++) {	
		if (i > 0)printf("\n");
		if (!print_at_level(T, i,ntap))
			break;
	}
	printf("\n");
}
int main(){
	BiTree *p, *root;
	p = (struct BiTree*)malloc(sizeof(struct BiTree));
	root = NULL;
	int d[5] = {1, 3, 2, 7, 5};
	//printf("%d",p->rchild->data);
	p = CreateBiTree(root,d,5);
	//printf("%d", p->rchild->data);
	//showTree(p);
	print_by_level_1(p);
	system("pause");
	return 0;
}