#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#define NULLKEY 0 // 0Ϊ�޼�¼��־ 
#define N 10  // ����Ԫ�ظ��� 
typedef int KeyType;// ��ؼ�����Ϊ���� 
typedef struct
{
	 KeyType key;
	 int ord;
}ElemType; // ����Ԫ������ 
// ���Ŷ�ַ��ϣ���Ĵ洢�ṹ 
int hashsize[]={11,19,29,37}; // ��ϣ��������������һ�����ʵ��������� 
int m=0; // ��ϣ��������ȫ�ֱ��� 
typedef struct
{
 ElemType *elem; // ����Ԫ�ش洢��ַ����̬�������� 
 int count; // ��ǰ����Ԫ�ظ��� 
 int sizeindex; // hashsize[sizeindex]Ϊ��ǰ���� 
}HashTable;
#define SUCCESS 1
#define UNSUCCESS 0
#define DUPLICATE -1
// ����һ���յĹ�ϣ��
int InitHashTable(HashTable *H)
{  
 int i;
 (*H).count=0; // ��ǰԪ�ظ���Ϊ0 
 (*H).sizeindex=0; // ��ʼ�洢����Ϊhashsize[0] 
 m=hashsize[0];
 (*H).elem=(ElemType*)malloc(m*sizeof(ElemType));
 if(!(*H).elem)
  exit(0); // �洢����ʧ�� 
 for(i=0;i<m;i++)
  (*H).elem[i].key=NULLKEY; // δ���¼�ı�־ 

 return 1;
}
//  ���ٹ�ϣ��H
void DestroyHashTable(HashTable *H)
{ 
 free((*H).elem);
 (*H).elem=NULL;
 (*H).count=0;
 (*H).sizeindex=0;
}
// һ���򵥵Ĺ�ϣ����(mΪ������ȫ�ֱ���)
unsigned Hash(KeyType K)
{ 
 return K%m;
}
// ���Ŷ�ַ��������ͻ
void collision(int *p,int d) // ����̽����ɢ�� 
{  
 *p=(*p+d)%m;
}
// �㷨9.17 
// �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,�����ҳɹ�,��pָʾ�������� 
// Ԫ���ڱ���λ��,������SUCCESS;����,��pָʾ����λ��,������UNSUCCESS 
// c���ԼƳ�ͻ���������ֵ���㣬����������ʱ�ο���
int SearchHash(HashTable H,KeyType K,int *p,int *c)
{
 *p=Hash(K); // ��ù�ϣ��ַ 
 while(H.elem[*p].key!=NULLKEY&&!(K == H.elem[*p].key))
 {
  // ��λ�������м�¼�����ҹؼ��ֲ���� 
  (*c)++;
  if(*c<m)
   collision(p,*c); // �����һ̽���ַp 
  else
   break;
 }
 if (K == H.elem[*p].key)
  return SUCCESS; // ���ҳɹ���p���ش�������Ԫ��λ�� 
 else
  return UNSUCCESS; // ���Ҳ��ɹ�(H.elem[p].key==NULLKEY)��p���ص��ǲ���λ�� 
}
int InsertHash(HashTable *,ElemType); // �Ժ��������� 
// �ؽ���ϣ��
void RecreateHashTable(HashTable *H) // �ؽ���ϣ�� 
{ 
 int i,count=(*H).count;
 ElemType *p,*elem=(ElemType*)malloc(count*sizeof(ElemType));
 p=elem;
 printf("�ؽ���ϣ��\n");
 for(i=0;i<m;i++) // ����ԭ�е����ݵ�elem�� 
  if(((*H).elem+i)->key!=NULLKEY) // �õ�Ԫ������ 
   *p++=*((*H).elem+i);
 (*H).count=0;
 (*H).sizeindex++; // ����洢���� 
 m=hashsize[(*H).sizeindex];
 p=(ElemType*)realloc((*H).elem,m*sizeof(ElemType));
 if(!p)
  exit(0); // �洢����ʧ�� 
 (*H).elem=p;
 for(i=0;i<m;i++)
  (*H).elem[i].key=NULLKEY; // δ���¼�ı�־(��ʼ��) 
 for(p=elem;p<elem+count;p++) // ��ԭ�е����ݰ����µı������뵽�ؽ��Ĺ�ϣ���� 
  InsertHash(H,*p);
}
// �㷨9.18 
// ���Ҳ��ɹ�ʱ��������Ԫ��e�����Ŷ�ַ��ϣ��H�У�������1�� 
// ����ͻ�����������ؽ���ϣ����
int InsertHash(HashTable *H,ElemType e)
{
 int c,p;
 c=0;
 if(SearchHash(*H,e.key,&p,&c)) // ����������e����ͬ�ؼ��ֵ�Ԫ�� 
  return DUPLICATE;
 else if(c<hashsize[(*H).sizeindex]/2) // ��ͻ����cδ�ﵽ����,(c�ķ�ֵ�ɵ�) 
 {
  // ����e 
  (*H).elem[p]=e;
  ++(*H).count;
  return 1;
 }
 else
  RecreateHashTable(H); // �ؽ���ϣ�� 

 return 0;
}
// ����ϣ��ַ��˳�������ϣ��
void TraverseHash(HashTable H,void(*Vi)(int,ElemType))
{  
 int i;
 printf("��ϣ��ַ0��%d\n",m-1);
 for(i=0;i<m;i++)
  if(H.elem[i].key!=NULLKEY) // ������ 
   Vi(i,H.elem[i]);
}
// �ڿ��Ŷ�ַ��ϣ��H�в��ҹؼ���ΪK��Ԫ��,�����ҳɹ�,��pָʾ�������� 
// Ԫ���ڱ���λ��,������SUCCESS;����,����UNSUCCESS 
int Find(HashTable H,KeyType K,int *p)
{
 int c=0;
 *p=Hash(K); // ��ù�ϣ��ַ 
 while(H.elem[*p].key!=NULLKEY&&!(K == H.elem[*p].key))
 { // ��λ�������м�¼�����ҹؼ��ֲ���� 
  c++;
  if(c<m)
   collision(p,c); // �����һ̽���ַp 
  else
   return UNSUCCESS; // ���Ҳ��ɹ�(H.elem[p].key==NULLKEY) 
 }
 if (K == H.elem[*p].key)
  return SUCCESS; // ���ҳɹ���p���ش�������Ԫ��λ�� 
 else
  return UNSUCCESS; // ���Ҳ��ɹ�(H.elem[p].key==NULLKEY) 
}
void print(int p,ElemType r)
{
 printf("address=%d (%d,%d)\n",p,r.key,r.ord);
}
int main()
{
 ElemType r[N] = {
  {17,1},{60,2},{29,3},{38,4},{1,5},
  {2,6},{3,7},{4,8},{60,9},{13,10}
 };
 HashTable h;
 int i, j, p;
 KeyType k;

 InitHashTable(&h);
 for(i=0;i<N-1;i++)
 {
  // ����ǰN-1����¼ 
  j=InsertHash(&h,r[i]);
  if(j==DUPLICATE)
   printf("�������йؼ���Ϊ%d�ļ�¼���޷��ٲ����¼(%d,%d)\n",
    r[i].key,r[i].key,r[i].ord);
 }
 printf("����ϣ��ַ��˳�������ϣ��:\n");
 TraverseHash(h,print);
 printf("����������Ҽ�¼�Ĺؼ���: ");
 scanf("%d",&k);
 j=Find(h,k,&p);
 if(j==SUCCESS)
  print(p,h.elem[p]);
 else
  printf("û�ҵ�\n");
 j=InsertHash(&h,r[i]); // �����N����¼ 
 if(j==0) // �ؽ���ϣ�� 
  j=InsertHash(&h,r[i]); // �ؽ���ϣ�������²����N����¼ 
 printf("����ϣ��ַ��˳������ؽ���Ĺ�ϣ��:\n");
 TraverseHash(h,print);
 printf("����������Ҽ�¼�Ĺؼ���: ");
 scanf("%d",&k);
 j=Find(h,k,&p);
 if(j==SUCCESS)
  print(p,h.elem[p]);
 else
  printf("û�ҵ�\n");
 DestroyHashTable(&h);

 system("pause");
 return 0; 
}