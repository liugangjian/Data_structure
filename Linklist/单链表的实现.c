# include <stdio.h>
# include <malloc.h>
# include <stdlib.h>

typedef int datatype;
typedef struct node{
	datatype data;
	struct node* next;
} node, *pnode;

// 初始化链表 
pnode  CreateList(){
	pnode phead;
	phead = (pnode)malloc(sizeof(node));
	if(phead == NULL)
	exit(-1);
	phead -> next = NULL;
	return phead; 
}; 

// 求链表元素的个数
int Num(pnode phead){
	pnode p = phead -> next;
	int count = 0;
	while(p!=NULL){
		count++;
		p = p -> next; 
	}
	return count;
}; 

// 在链表第k个位置插入元素x
void Insert(pnode phead,int pos,datatype x){
	int i = 0;
	pnode p = phead;
	
	while(p!=NULL && i<pos-1){
		p = p -> next;
		i++; 
	}
	
	if(i>pos-1 || p == NULL)
		exit (-1);
	
	pnode pnew = (pnode)malloc(sizeof(node));
	if(pnew == NULL)
		exit(-1);
		
	pnew->data = x;
	pnew->next = p->next;
	p->next = pnew;
};

// 删除链表中的第k个元素
void Delete(pnode phead,int pos){
	int i = 0;
	pnode p = phead;
	
	while(p!=NULL&&i<pos-1){
		p=p->next;
		i++;
	}	
	if(i>pos-1 || p == NULL)
		exit (-1);
	
	pnode q = p->next;
	p->next = p->next->next;
	free(q);
};

// 判断链表是否为空 
int Empty(pnode phead){
	return phead -> next == NULL;
};

// 输出链表
void Print(pnode phead){
	pnode p = phead->next;
	while(p){
		printf("%d ",p->data);
		p = p->next; 
	} 
	printf("\n");
};

// 清空链表 : 节点全部清空但是链表还存在，即头指针存在，还可以插入元素 
void ClearList(pnode phead){
	pnode p,q;
	p = phead;
	while(p){
		q = p;
		p = p->next;
		free(q); 
	}
	phead ->next = NULL;
}; 

// 销毁链表: 链表整个空间全部被释放 
void DestroyList(pnode phead){
	pnode p;
	p = phead;
	while(p){
		p = phead->next;
		free(phead);
	}
} 

int main(){
	pnode phead = CreateList();
	Insert(phead,1,10);
	Insert(phead,2,20);
	Insert(phead,3,30);
	Insert(phead,4,40);
	Insert(phead,5,50);
	printf("%d\n" , Num(phead));
	Print(phead);
	Delete(phead,2);
	Print(phead);
	ClearList(phead);
	Print(phead);
	
	DestroyList(phead);
	return 0;
}
