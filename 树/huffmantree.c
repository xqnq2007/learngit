#include "stdio.h"
#include "stdlib.h"

typedef struct{
	int weight;
	int parent;
	int left;
	int right;
}huffnode;
void selectMinTwoNode(huffnode* hufftree, int nodeNum, int* node1Index, int* node2Index){
	int index1 = -1;
	int index2 = -1;
	for (int i = 0; i < nodeNum; i++){
		if (hufftree[i].parent ==-1){
			if (index1 == -1){
				*node1Index = i;
				index1 = 0;
				continue;
			}
			if (index2 == -1){
				*node2Index = i;
				index2 = 0;
				if (hufftree[*node1Index].weight > hufftree[*node2Index].weight){
					huffnode tmp = hufftree[*node1Index];
					hufftree[*node1Index] = hufftree[*node2Index];
					hufftree[*node2Index] = tmp;
					int tmpIndex = *node1Index;
					*node1Index = *node2Index;
					*node2Index = tmpIndex;
				}
				continue;
			}
			if (index1 != -1 && index2 != -1){
				if (hufftree[i].weight < hufftree[*node1Index].weight){
					//printf("交换了1\n");
					hufftree[*node2Index] = hufftree[*node1Index];
					hufftree[*node1Index] = hufftree[i];
					*node2Index = *node1Index;
					*node1Index = i;
				}
				else{
					if (hufftree[i].weight < hufftree[*node2Index].weight){
						//printf("第一个权重：%d 第二个权重：%d \n", hufftree[i].weight, hufftree[*node2Index].weight);
						//printf("i的值:%d 第一个索引：%d 第二个索引：%d \n", i,*node1Index, *node2Index);
						//printf("交换了2\n");
						/*huffnode tmp = hufftree[*node2Index];
						hufftree[*node2Index] = hufftree[i];
						hufftree[*node2Index] = tmp;*/
						//hufftree[*node2Index] = hufftree[i];
						*node2Index = i;
					}
				}
			}
		}
	}
}
void creatHuffTree(huffnode* hufftree, int leafNum,int* leafWeight){
	int huffNodeNum = 2 * leafNum - 1;
	
	for (int i = 0; i < huffNodeNum; i++){
		hufftree[i].parent = -1;
		if (i < leafNum){
			hufftree[i].weight = leafWeight[i];
		}
		else
			hufftree[i].weight = 0;
	}	
	int* node1 = (int*)malloc(sizeof(int));
	int* node2 = (int*)malloc(sizeof(int));
	for (int i = leafNum; i < huffNodeNum; i++){
		//printf("******\n");
		for (int j = 0; j < i; j++){
			//printf("权重%d 父亲%d 左%d 右%d\n", hufftree[j].weight, hufftree[j].parent, hufftree[j].left, hufftree[j].right);
		}
		*node1 = -1;
		*node2 = -1;
		selectMinTwoNode(hufftree, i, node1, node2);
		
		//printf("%d %d\n", hufftree[*node1].weight, hufftree[*node2].weight);
		//printf("此时的结点数：%d\n", huffNodeNum);
		
		
		hufftree[*node1].parent = i;
		hufftree[*node2].parent = i;		
		hufftree[i].left = *node1;
		hufftree[i].right = *node2;
		hufftree[i].weight = hufftree[*node1].weight + hufftree[*node2].weight;
		
	}
}
void huffCoding(char** str){
	(*str)[1] = "fdafa";
	//return str;
}
void test(int* a, int* b){
	int* t = a;
	a = b;
	b = t;
}
void main(){
	huffnode hufftree[100];
	int leafWeight[4] = { 2, 5, 7, 13 };
	creatHuffTree(hufftree, 4, leafWeight);
	for (int i = 0; i < 9; i++){
		//printf("%d ", hufftree[i].weight);
	}
	//char* a[2]=(char(*)[2])malloc(sizeof(char*)*2);
	char a[4][4] = { "","","","" };
	huffCoding(a);
	printf("%s ", a[1]);
	system("PAUSE");
}