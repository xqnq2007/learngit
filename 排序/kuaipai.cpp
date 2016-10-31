#include "stdio.h"
#include "stdlib.h"
#include "time.h"


void qsort(int*p ,int left,int right){
	if(left>=right){
		return;
	}
	int i=left;
	int j=right;
	int key=p[i];
	while(i<j){
		while(i<j&&key<=p[j]){
			j--;
		}
		p[i]=p[j];
		while(i<j&&key>=p[i]){
			i++;
		}
		p[j]=p[i];
	}
	p[i]=key;
	qsort(p,left,i-1);
	qsort(p,i+1,right);
}
void bubblesort(int*p,int len)
{
	int i,j;
	for(i=0;i<len-1;i++){
		for(j=len-1;j>i;j--){
			if(p[j]<p[j-1]){
				int tmp=p[j];
				p[j]=p[j-1];				
				p[j-1]=tmp;
			}
		}
	}
}
int compInc(const void *a, const void *b)  
{  
    return *(int *)a - *(int *)b;  
}  
  
int compDec(const void *a, const void *b)  
{  
    return *(int *)b - *(int *)a;  
}  
void main(){
	int a[5000],b[5000];
	for(int ii=0;ii<5;ii++){
		printf("第%d次：\n",ii);	
		for(int i=0;i<5000;i++){		
			b[i]=a[i]=rand();
		}
		clock_t t1,t2;
		double duration;
		t1=clock();	
		qsort(a,0,4999);
		t2=clock();
		duration=(double)(t2-t1)/CLOCKS_PER_SEC;
		printf("自己写的排序用时：%f\n",duration);	
		t1=clock();	
		qsort(b,5000,sizeof(b[0]),compInc);		
		t2=clock();
		duration=(double)(t2-t1)/CLOCKS_PER_SEC;
		printf("系统快速排序用时：%f\n",duration);
	}	
	/*for(int i=0;i<2000;i++){		
		printf("%d\n",b[i]);
	}*/
	system("PAUSE");
	
}