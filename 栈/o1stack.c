#include "stdio.h"
#include "stdlib.h"
#define STACKSIZE 1024
typedef struct{
	int a[STACKSIZE];
	int top;
}stack;
stack* st;
stack* minst;
void init(stack* st){
	st->top = 0;
}
int push(int key){
	if (st->top >= STACKSIZE){		
		return 0;
	}
	st->a[(st->top)++] = key;
	if (minst->top==0 )
		minst->a[(minst->top)++] = key;
	else if(key <= minst->a[minst->top - 1]){
		minst->a[(minst->top)++] = key;
	}
	return 1;
}
int pop(int *m){
	if (st->top ==0){
		return 0;
	}
	*m = st->a[st->top-1];
	st->top--;
	if (minst->top > 0 && *m <= minst->a[minst->top - 1]){
		minst->top--;
	}
	return 1;
}
int mins(int *m){
	if (st->top == 0){
		return 0;
	}
	*m = minst->a[minst->top - 1];
	return 1;
}
void print(stack* st){
	printf("当前栈中所有元素：\n");
	if (st->top > 0){
		for (int i = st->top; i > 0; i--){
			printf("%d\n", st->a[i - 1]);
		}
	}
	else{
		printf("栈已空\n");
	}	
}
void clear(stack* st){
	while(st->top>0){
		st->top--;
	}
}
void main(){
	srand((int)time(0));
	st = (stack*)malloc(sizeof(stack));
	minst = (stack*)malloc(sizeof(stack));
	init(st);
	init(minst);
	int m;	
	for (int i = 0; i < 5; i++){
		int randi = rand()%10;
		if (!push(randi))printf("栈已满\n");;
		print(st);
		if(mins(&m))printf("当前栈中最小元素%d\n", m);
		else printf("栈已经空\n");
	}
	printf("逐个弹出栈中元素\n");
	for (int i = 0; i < 5; i++){
		if(pop(&m))	printf("弹出元素：%d\n", m);
		else printf("栈空\n");
		print(st);
		if (mins(&m)){
			printf("当前栈中最小元素%d\n", m);
		}
		else{
			printf("栈已空");
		}
		
	}
	getchar();
}