# include<stdio.h>
# include<malloc.h>
# include<stdlib.h>

# define n 11
# define m 3

typedef struct node{
	int data;
	struct node* next;
}node,*pnode;

int main(){
	int count = 0;
	int i;
	pnode p,q,r;
	p = q = (pnode)malloc(sizeof(node));
	p->data = 1;
	
	for(i=2;i<=n;i++){
		r = (pnode)malloc(sizeof(node));
		r->data = i; 
		q->next = r;
		q = r;
	} 
	q->next = p;
	
	q = p;
	while(q->next!=q){
		for(i=1;i<m;i++){
			p = q;
			q = q->next;
		}
		p->next = q->next;
		free(q);
		q = p->next;
	}
	
	printf("%d ",q->data);
	return 0;
} 
