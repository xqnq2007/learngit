#include "stdio.h"
#include "stdlib.h"
typedef enum{
	left = 1,
	right = 2
}direction;
typedef struct chainnode{
	char data;
	struct chainnode* left;
	struct chainnode* right;
}node;
void init(node* s, char k){
	s->left = NULL;
	s->right = NULL;
	s->data = k;
}
void insert(node* root, char cur, char new, direction d){
		if (root == NULL)
			return;
		struct chainnode* tmp = root;
		/*while (strcmp(tmp->data, cur) != 0){
			insert(tmp->left,cur,new,d);
			insert(tmp->right, cur,new, d);
		}*/
		if (root->data==cur){
			node* newnode = (node*)malloc(sizeof(node));
			newnode->left = NULL;
			newnode->right = NULL;
			newnode->data = new;
			if (d == 1){			
				tmp->left = newnode;
			}
			else{
				tmp->right = newnode;
			}
		}
	}
void main(){
	node* root=(node*)malloc(sizeof(node));
	//(root, "A");
	char rc = 'A';
	init(root, rc);
	insert(root, 'A', 'B', left);
	printf("%c",root->left->data);
	system("PAUSE");
}
