//Designed By Dark http://blog.csdn.net/xzongyuan
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include "myEqual.h"  
#include "myHashCode.h"  
#include "myHashSet.h"  
#define NUM 5
#define S 10  
char* strs[S]=  
{  
    "abc",  
    "qq",  
    "hello",  
    "abc",  
    "lmy",  
    "ab",  
    "qq",  
    "lqw",  
    "sww",  
    "lqw"  
};  
   
typedef struct _node
{
   int value;
   struct _node *left;
   struct _node *right;
}TNode,*Tree;

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
   Queue *queue=(Queue*)malloc(sizeof(Queue));
   queue->head = queue->tail = NULL;
   return queue;
}

int enQueue(Queue *pQueue,TNode *pTNode,int pDepth)
{

      QNode *pQNode = (QNode *)malloc(sizeof(QNode));
      pQNode->depth = pDepth;
      pQNode->blank = 0; //default config 
      if(pTNode==NULL)
      {
         //change default setting; 1 means it's blank QNode
         pQNode->blank =1;
      }

      pQNode->t_node= pTNode;
	  pQNode->next=NULL;
      if(pQueue->head == NULL)
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
	if(pQueue->head == NULL)
	{
	   return NULL;
	}

	QNode *deNode= pQueue->head;
	pQueue->head = pQueue->head->next;  
        return deNode;
}

TNode* init_TNode(int value)
{
    TNode  *new_node = (TNode*)malloc(sizeof(TNode));
    new_node->value=value;
    new_node->left = new_node->right = NULL;
    return new_node;
}

//0:empty
int ifEmpty(Queue *pQueue)
{
   if(pQueue->head == NULL)
   {
     //printf("empty tree\n");
     return 0;
   }
   
   //printf("queue is not empty\n");
   return 1;
}


int insert_tree(Tree pTree,int pValue)
{

   //found NULL sub tree, then add to his father->left
   if(!pTree)
   {
      return 0;
   }
   TNode *tNode = init_TNode(pValue);
   if(tNode==NULL)
   {
       printf("create TNode error!\n");
       return 0;
   }
	   

   if(pValue < pTree->value) 
        if(insert_tree(pTree->left,pValue)==0)
        {
	   //no left child any more,set a new left child to pTree
	   pTree->left = tNode;
   	   printf("insert :%d\n",pValue);
	}
   if(pValue > pTree->value)
        if(insert_tree(pTree->right,pValue)==0)
        {
           pTree->right = tNode;
	   printf("insert :%d\n",pValue);
        }
}
int get_tree_height(Tree pRoot)
{

  if(!pRoot)
  {
    return 0; 
  }

  int lh=0,rh=0;
  lh = get_tree_height(pRoot->left);
  rh = get_tree_height(pRoot->right);
  return (lh<rh)?(rh+1):(lh+1);
}

Tree creatTree1(int num)
{
    srand(time(NULL));
    //Tree root = init_TNode(rand()%100);
	Tree root = init_TNode(20);
    printf("root is %d\n",root->value);
    int i ;
	int d[4]={8,22,4,12};
	int lend=sizeof(d)/sizeof(d[0]);	
    for(i=0;i<lend;i++)
    {
        insert_tree(root,d[i]); 
    }
    printf("creat tree succuess!Tree heigh is:%d\n",get_tree_height(root));
    return root ;
}

Tree creatTree(int num)
{
    srand(time(NULL));
    Tree root = init_TNode(rand()%100);
    printf("root is %d\n",root->value);
    int i ;
    for(i=1;i<num;i++)
    {
        insert_tree(root,rand()%100); 
    }
    printf("creat tree succuess!Tree heigh is:%d\n",get_tree_height(root));
    return root ;
}





int breath_travel(Tree pRoot,Queue *pQueue)
{
   int height = get_tree_height(pRoot);
   int pad_num = 2;
   char buf_branch[200]="\n";
   char leaf[10]="oooooooo";
   char vertical[10]="|||||||||";   
   char blank[30]="                             "; 
   //you can cut it down for the branch
   //when I debug, I found the size can't be too large
   //when I set it as 50, it break down.
   char line[40]="______________________________"; 


   //compare to the node's depth in the "while loop"
   int current_depth = 1;
   if(!pRoot)
   {
      return 0;
   }      
   
   enQueue(pQueue,pRoot,1);
   printf("_______________________\n");
   printf("breath begin,enter root:\n");

   while(ifEmpty(pQueue)!=0)
   {

     QNode  *qNode  = deQueue(pQueue);
     //the sub node's depth is 1 more then the parent's
     int child_depth = qNode->depth+1; 

     if(qNode->depth > current_depth)
     {
         current_depth = qNode->depth;
         printf("%s\n",buf_branch);
         sprintf(buf_branch,"\n");  //reset the buffer after print
     }
// ***************0****************  pad_between = 31 ; pad_front = 15  (depth == 1)
// *******0***************0********  pad_between = 15 ; pad_front = 7   (depth == 2)
// ***0*******0*******0*******0****  pad_between = 7  ; pad_front = 3   (depth == 3)
// *0***0***0***0***0***0***0***0**  pad_between = 3  ; pad_front = 1   (depth == 4)
// 0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*0*  pad_between = 1  ; pad_front = 0;  (depth == 5)
// Tree height = 5
// pad_num = 1
// padding between node = (1+2*pad_front)*pad_num = (1+ (1<<(height-depth))-1)*pad_num
    
     int pad_front = (1<< (height - current_depth))-1;
     int pad_blank = (pad_front-1)>>1;
     int pad_under = (pad_front+1)>>1;

     if((qNode->blank == 1))
     {
       //add the parent node's padding:2
        if(pad_front == 0)    printf("%.*s%*s",pad_num,leaf,pad_num," ");

        else              
            {
             printf("%*s%.*s%*s",pad_front*pad_num," ",pad_num,leaf,(1+pad_front)*pad_num," ");
             char *new_buf=(char*)malloc(100);
	     char *old_buf = buf_branch;
            
             sprintf(new_buf,"%.*s%.*s%.*s%.*s%.*s",pad_num*pad_blank,blank,pad_num*pad_under,line,pad_num,vertical,pad_num*pad_under,line,(pad_front-pad_blank)*pad_num,blank);
	     sprintf(buf_branch,"%s%s",old_buf,new_buf);
 	    }
       if(child_depth<=height)
       {
         //enter two NULL sub-tree node.
         //every time you enter NULL TNode,there's corresponding blank QNode.
         enQueue(pQueue,NULL,child_depth);
         enQueue(pQueue,NULL,child_depth);
       }
     }
     else
     {
        if(pad_front == 0)   
            {
              printf("%*d%*s",pad_num,qNode->t_node->value,pad_num," ");
	    }
        else  
            {

               char *new_buf=(char*)malloc(100);
               char *old_buf=buf_branch;
               printf("%*s%*d%*s",pad_front*pad_num," ",pad_num,qNode->t_node->value,(1+pad_front)*pad_num," ");
               sprintf(new_buf,"%.*s%.*s%.*s%.*s%.*s",pad_num*pad_blank,blank,pad_num*pad_under,line,pad_num,vertical,pad_num*pad_under,line,(pad_front-pad_blank)*pad_num,blank);
	       sprintf(buf_branch,"%s%s",old_buf,new_buf);
            }
       if(child_depth <=height)
       {
	 enQueue(pQueue,qNode->t_node->left,child_depth);
         enQueue(pQueue,qNode->t_node->right,child_depth); 
       } 
     }

   } //while end   
     printf("\n-----------\nbreath end!\n-----------\n");

   return 1;
}

int main(int argc,char **argv)
{
  /*Queue *queue=init_queue();
  int i;

  ifEmpty(queue);
  printf("insert node to queue\n");

  int num = NUM; //default
  if(argc == 2)
  {
    num = atoi(argv[1]); 
  }

  Tree root = creatTree1(num);
  if(!root)
  {
    printf("create Tree failed!\n");
    return 0;
  }

  breath_travel(root,queue);*/
  //创建集合需要指定两个函数，hashCode函数和equal函数。  
   /* MyHashSet * set = createMyHashSet(myHashCodeString, myEqualString);  
  
    //插入数据  
    for (int i=0; i<S; i++)  
    {  
        myHashSetAddData(set, strs[i]);  
    }  
  
    //输出大小  
    printf("size=%d\n",myHashSetGetSize(set));  
  
    //测试删除  
    myHashSetRemoveData(set,"qq");  
    myHashSetRemoveData(set,"ab");  
    myHashSetRemoveData(set,"qwert");  
  
    //输出大小  
    printf("after remove size=%d\n",myHashSetGetSize(set));  
  
    //遍历  
    MyHashSetIterator * it = createMyHashSetIterator(set);  */
   /* while(myHashSetIteratorHasNext(it))  
    {  
        char * pp= myHashSetIteratorNext(it);  
        puts(pp);  
    }  
    //释放遍历器  
    freeMyHashSetIterator(it);  
  
    //释放集合  
    freeMyHashSet(set);  
	*/
  
  getchar();
  return 0;
}
