//Designed By Dark http://blog.csdn.net/xzongyuan
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#define NUM 5

typedef struct _node
{
	int value;
	struct _node *left;
	struct _node *right;
}TNode, *Tree;

//add a *next in q_node is my purpose
//other wise , we need to add in the Tree node struct
//So, for the sake of doesn't modify the struct of tree
//I design a q_node struct to include it
//we can use define command to make it as a template.
typedef struct _q_node
{
	TNode *t_node;
	int depth;
	int blank;  //0: means correspoinding tree node is not NULL(default)
	struct _q_node *next;
}QNode;

typedef struct _Queue
{
	QNode *head;
	QNode *tail;
}Queue;

Queue* init_queue()
{
	Queue *queue = (Queue*)malloc(sizeof(Queue));
	queue->head = queue->tail = NULL;
	return queue;
}

int enQueue(Queue *pQueue, TNode *pTNode, int pDepth)
{

	QNode *pQNode = (QNode *)malloc(sizeof(QNode));
	pQNode->depth = pDepth;
	pQNode->blank = 0; //default config 
	if (pTNode == NULL)
	{
		//change default setting; 1 means it's blank QNode
		pQNode->blank = 1;
	}

	pQNode->t_node = pTNode;
	pQNode->next = NULL;
	if (pQueue->head == NULL)
	{//when it's empty
		pQueue->head = pQNode;
		pQueue->tail = pQNode;
	}
	else
	{
		pQueue->tail->next = pQNode;
		pQueue->tail = pQNode;
	}
	return 1;
}

QNode* deQueue(Queue *pQueue)
{
	if (pQueue->head == NULL)
	{
		return NULL;
	}

	QNode *deNode = pQueue->head;
	pQueue->head = pQueue->head->next;
	return deNode;
}

TNode* init_TNode(int value)
{
	TNode  *new_node = (TNode*)malloc(sizeof(TNode));
	new_node->value = value;
	new_node->left = new_node->right = NULL;
	return new_node;
}

//0:empty
int ifEmpty(Queue *pQueue)
{
	if (pQueue->head == NULL)
	{
		//printf("empty tree\n");
		return 0;
	}

	//printf("queue is not empty\n");
	return 1;
}


int insert_tree(Tree pTree, int pValue)
{

	//found NULL sub tree, then add to his father->left
	if (!pTree)
	{
		return 0;
	}
	TNode *tNode = init_TNode(pValue);
	if (tNode == NULL)
	{
		printf("create TNode error!\n");
		return 0;
	}


	if (pValue < pTree->value)
	if (insert_tree(pTree->left, pValue) == 0)
	{
		//no left child any more,set a new left child to pTree
		pTree->left = tNode;
		printf("insert :%d\n", pValue);
	}
	if (pValue > pTree->value)
	if (insert_tree(pTree->right, pValue) == 0)
	{
		pTree->right = tNode;
		printf("insert :%d\n", pValue);
	}
}

int get_node_height(Tree pRoot, Tree p)
{

	if (!pRoot)
	{
		return 0;
	}

	int lh = 1, rh = 0;
	while (pRoot){
		if (p->value == pRoot->value){
			return lh;
		}
		else{
			if (p->value < pRoot->value){
				pRoot = pRoot->left;
			}
			else{
				pRoot = pRoot->right;
			}
			lh += 1;
		}
	}
	if (pRoot == NULL){
		printf("没有该节点");
	}
	return lh;
}
int get_tree_height(Tree pRoot)
{

	if (!pRoot)
	{
		return 0;
	}

	int lh = 0, rh = 0;
	lh = get_tree_height(pRoot->left);
	rh = get_tree_height(pRoot->right);
	return (lh<rh) ? (rh + 1) : (lh + 1);
}
Tree searchPar(Tree pRoot, int key){
	int solve = 0;
	while (pRoot && solve != 1){
		int pleft = -1;
		if (pRoot->left){
			pleft = pRoot->left->value;
		}
		int pright = -1;
		if (pRoot->right){
			pright = pRoot->right->value;
		}
		if (key == pleft||key==pright){
			solve = 1;
		}
		else{
			if (key < pRoot->value){
				pRoot = pRoot->left;
			}
			else{
				pRoot = pRoot->right;
			}
		}
	}
	if (pRoot == NULL){
		printf("没有该节点");
	}
	return pRoot;
}
Tree search(Tree pRoot,int key){
	int solve = 0;
	while (pRoot && solve != 1){
		if (key == pRoot->value){
			solve = 1;			
		}
		else{
			if (key < pRoot->value){
				pRoot = pRoot->left;
			}
			else{
				pRoot = pRoot->right;
			}
		}
	}
	if (pRoot == NULL){
		printf("没有该节点");
	}
	return pRoot;
}
int Delete(Tree pRoot,Tree pTree)//从二叉排序树中删除结点p，并重接它的左或右子树
{
	Tree q;
	Tree s;
	if (!(pTree->right || pTree->left)){
		free(pTree);
		return 1;
	}
	if (!pTree->right)//右子树空则只需重接它的左子树
	{
		if (get_node_height(pRoot, pTree) == 1){
			pRoot ->left = pTree->left;
			free(pTree);
		}
		else{
			Tree ppar = searchPar(pRoot,pTree->value);
			ppar->left = pTree->left;
			free(pTree);
		}		
	}
	else if (!pTree->left)//左子树空只需重接它的右子树
	{
		if (get_node_height(pRoot, pTree) == 1){
			pRoot->right = pTree->right;
			free(pTree);
		}
		else{
			Tree ppar = searchPar(pRoot, pTree->value);
			ppar->right = pTree->right;
			free(pTree);
		}
	}
	else//左右子树均不空
	{
		q = pTree;
		s = pTree->left;
		while (s->right)//转左，然后向右到尽头
		{
			q = s;
			s = s->right;
		}
		pTree->value = s->value;//s指向被删结点的“前驱”
		if (q != pTree)//以上循环至少执行了一次
			q->right = s->left;
		else
			q->left = s->left;//重接*q的左子树
		free(s);
	}
	return 1;
}
Tree creatTree(int num)
{
	srand(time(NULL));
	Tree root = init_TNode(rand() % 100);
	printf("root is %d\n", root->value);
	int i;
	for (i = 1; i<num; i++)
	{
		insert_tree(root, rand() % 100);
	}
	printf("creat tree succuess!Tree heigh is:%d\n", get_tree_height(root));
	return root;
}

Tree creatTree1(int num)
{
	srand(time(NULL));
	Tree root = init_TNode(15);
	printf("root is %d\n", root->value);
	int i;	
	int d[10] = {5,16,3,12,20,10,13,18,23,6};
	//int d[2] = { 5, 16};
	int lend = sizeof(d) / sizeof(d[0]);
	for (i = 0; i<lend; i++)
	{
		insert_tree(root, d[i]);
	}
	printf("creat tree succuess!Tree heigh is:%d\n", get_tree_height(root));
	return root;
}
int breath_travel(Tree pRoot, Queue *pQueue)
{
	int height = get_tree_height(pRoot);
	int pad_num = 2;
	char buf_branch[200] = "\n";
	char leaf[10] = "********";
	char vertical[10] = "|||||||||";
	char blank[30] = "                             ";
	//you can cut it down for the branch
	//when I debug, I found the size can't be too large
	//when I set it as 50, it break down.
	char line[50] = "______________________________";


	//compare to the node's depth in the "while loop"
	int current_depth = 1;
	if (!pRoot)
	{
		return 0;
	}

	enQueue(pQueue, pRoot, 1);
	printf("_______________________\n");
	printf("breath begin,enter root:\n");	
	while (ifEmpty(pQueue) != 0)
	{

		QNode  *qNode = deQueue(pQueue);
		//the sub node's depth is 1 more then the parent's
		int child_depth = qNode->depth + 1;

		if (qNode->depth > current_depth)
		{
			current_depth = qNode->depth;
			printf("%s\n", buf_branch);
			sprintf(buf_branch, "\n");  //reset the buffer after print
		}
		// ***************0****************  pad_between = 31 ; pad_front = 15  (depth == 1)
		// *******0***************0********  pad_between = 15 ; pad_front = 7   (depth == 2)
		// ***0*******0*******0*******0****  pad_between = 7  ; pad_front = 3   (depth == 3)
		// *0***0***0***0***0***0***0***0**  pad_between = 3  ; pad_front = 1   (depth == 4)
		// 0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*  pad_between = 1  ; pad_front = 0;  (depth == 5)
		// Tree height = 5
		// pad_num = 1
		// padding between node = (1+2*pad_front)*pad_num = (1+ (1<<(height-depth))-1)*pad_num

		int pad_front = (1 << (height - current_depth)) - 1;
		int pad_blank = (pad_front - 1) >> 1;
		int pad_under = (pad_front + 1) >> 1;

		if ((qNode->blank == 1))
		{
			//add the parent node's padding:2
			if (pad_front == 0)    printf("%.*s%*s", pad_num, leaf, pad_num, " ");

			else
			{
				printf("%*s%.*s%*s", pad_front*pad_num, " ", pad_num, leaf, (1 + pad_front)*pad_num, " ");
				char *new_buf = (char*)malloc(100);
				char *old_buf = buf_branch;

				sprintf(new_buf, "%.*s%.*s%.*s%.*s%.*s", pad_num*pad_blank, blank, pad_num*pad_under, line, pad_num, vertical, pad_num*pad_under, line, (pad_front - pad_blank)*pad_num, blank);
				sprintf(buf_branch, "%s%s", old_buf, new_buf);
			}
			if (child_depth <= height)
			{
				//enter two NULL sub-tree node.
				//every time you enter NULL TNode,there's corresponding blank QNode.
				enQueue(pQueue, NULL, child_depth);
				enQueue(pQueue, NULL, child_depth);
			}
		}
		else
		{
			if (pad_front == 0)
			{
				printf("%*d%*s", pad_num, qNode->t_node->value, pad_num, " ");
			}
			else
			{

				char *new_buf = (char*)malloc(100);
				char *old_buf = buf_branch;
				printf("%*s%*d%*s", pad_front*pad_num, " ", pad_num, qNode->t_node->value, (1 + pad_front)*pad_num, " ");
				sprintf(new_buf, "%.*s%.*s%.*s%.*s%.*s", pad_num*pad_blank, blank, pad_num*pad_under, line, pad_num, vertical, pad_num*pad_under, line, (pad_front - pad_blank)*pad_num, blank);
				sprintf(buf_branch, "%s%s", old_buf, new_buf);
			}
			if (child_depth <= height)
			{
				enQueue(pQueue, qNode->t_node->left, child_depth);
				enQueue(pQueue, qNode->t_node->right, child_depth);
			}
		}

	} //while end   
	printf("\n-----------\nbreath end!\n-----------\n");
	
	return 1;
}
void getmn(Tree pRoot,int b[],int *count,int min,int max){
	//b[*count] = 10;
	if (pRoot->value >= min && pRoot->value <= max){
		b[*count] = pRoot->value;
		*count+=1;
		if (pRoot->left){
			getmn(pRoot->left,b,count,min,max);
		}
		if (pRoot->right){
			getmn(pRoot->right, b, count, min, max);
		}
	}
	else if (pRoot->value < min){
		if (pRoot->right){
			getmn(pRoot->right, b, count, min, max);
		}
	}
	else{
		if (pRoot->left){
			getmn(pRoot->left, b, count, min, max);
		}
	}
}
Tree getminm(Tree pRoot, int m,int* tmpmax,int* markmax){
	int solve = 0;
	while (pRoot){
		if (m == pRoot->value){
			solve = 1;
		}
		else{
			if (m < pRoot->value){
				if (*markmax==0){
					*tmpmax = pRoot->value;
					*markmax = 1;
				}
				if (pRoot->left){
					if (m > pRoot->left->value){
						solve = 1;
					}
					else if (m == pRoot->left->value){
						solve = 1;
						pRoot = pRoot->left;
					}
					else{
						pRoot = pRoot->left;
					}
				}				
			}
			else{
				if (pRoot->right){
					if (m = pRoot->right->value){
						solve = 1;
						pRoot = pRoot->right;
					}
					else if (m > pRoot->right->value){						
						pRoot = pRoot->right;
					}else{
						pRoot = pRoot->left;
					}
				}
			}
		}
	}
	if (solve == 0){
		printf("没有最小结点");
		return NULL;
	}
	return pRoot;
}
int main(int argc, char **argv)
{
	Queue *queue = init_queue();
	int i;
	
	ifEmpty(queue);
	printf("insert node to queue\n");

	int num = NUM; //default
	if (argc == 2)
	{
		num = atoi(argv[1]);
	}
	num = 10;
	Tree root = creatTree1(num);
	if (!root)
	{
		printf("create Tree failed!\n");
		return 0;
	}
	int b[100] = {0};
	int* count = (int*)malloc(sizeof(int*));
	int* tmpmax = (int*)malloc(sizeof(int*));
	int* markmax = (int*)malloc(sizeof(int*));
	*count = 0;
	*tmpmax = -1;
	*markmax = 0;
	breath_travel(root, queue);
	//getmn(root,b,count,11,17);
	Tree tmp = getminm(root, 11, tmpmax, markmax);

	printf("%d",tmp->value);
	for (int i = 0; i < *count; i++){
		printf("%d", b[i]);
	}

	//printf("%d", root->left->left->value);
	//breath_travel(root, queue);
	//Tree tmp= search(root,13);
	//Tree tmpPar = searchPar(root, 13);
	//printf("%d", get_node_height(root, 13));
	//printf("%d", tmpPar->value);
	//Delete(root,tmp);
	//printf("%d", tmpPar->right->value);
	//if (tmpPar->right){
		//printf("dfdaf");
	//}
	//breath_travel(root, queue);
	
	/*if (Delete(tmp)){
		breath_travel(root, queue);
	}*/
	//printf("%d",tmp->value);
	getchar();
	return 0;
}
