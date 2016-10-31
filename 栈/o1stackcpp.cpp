#include<iostream>
#include<ctime>
using namespace std;
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
bool push(int key){
	if (st->top == STACKSIZE){
		return false;
	}
	st->a[st->top++] = key;
	if (minst->top == 0 || key <= minst->a[minst->top - 1])
		minst->a[minst->top++] = key;
	return true;
}
bool pop(int *m){
	if (st->top == 0){		
		return false;
	}
	*m = st->a[st->top - 1];
	st->top--;
	if (*m == minst->a[minst->top - 1]){
		minst->top--;
	}
	return true;
}
bool mins(int *m){
	if (minst->top == 0){
		return false;
	}
	*m = minst->a[minst->top - 1];
	return true;
}
void print(stack* st){
	cout << "��ǰջ������Ԫ�أ�" << endl;
	if (st->top > 0){
		for (int i = st->top; i > 0; i--){
			cout << st->a[i - 1] << endl;
		}
	}
	else{
		cout << "ջ�ѿ�" << endl;
	}
}
void clear(stack* st){
	while (st->top>0){
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
		int randi = rand() % 10;
		if(push(randi))	print(st);
		else cout << "ջ����" << endl;
		if(mins(&m))cout << "��ǰջ����СԪ��%d\n"<< m << endl;
		else cout << "��Сջ�ѿ�" << endl;
	}
	cout <<"�������ջ��Ԫ��"<<endl;
	for (int i = 0; i < 5; i++){
		if(pop(&m))	cout << "����Ԫ�أ�%d\n" << m << endl;
		else cout << "ջ�ѿ�" << endl;
		print(st);
		if (mins(&m)){
			cout << "��ǰջ����СԪ��%d\n" << m << endl;
		}
		else{
			cout << "��Сջ�ѿ�" << endl;
		}
	}
	getchar();
}