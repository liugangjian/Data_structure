# include<stdio.h>
# include<malloc.h>
# define Maxsize 100

typedef long long datatype;
typedef struct{
	datatype data[Maxsize];
	int size;
} Sqlist;

// 创建序列表
Sqlist* createSqlist(){
	Sqlist* p = (Sqlist*)malloc(sizeof(Sqlist));
	p -> size = 0;
	return p;	
};

// 在序列表后添加一个元素
void push(Sqlist* p,datatype x){
	p -> data[p->size++] = x;	
};

// 计算一个整数的倒序数
long long reverse(datatype x){
	datatype r;
	r = 0;
	while(x){
		r = 10*r + x%10;
		x = x/10;
	}
	return r;	
};

void Print(Sqlist* p){
	int i;
	for (i=0;i<p->size;i++)
		printf("%lld ",p->data[i]);	
	printf("\n");
};

void main(){
	long long i,sum;
	while(scanf("%lld",&i)){
		Sqlist* p = createSqlist();
		push(p,i);
		while(reverse(i) != i){
			i = reverse(i) + i;
			push(p, i);
		}
		
		Print(p);
	}
}
