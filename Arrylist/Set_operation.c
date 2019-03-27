/* 编译环境：DEV C++ */
# include<stdio.h>
# include<malloc.h>
# define Maxsize 100

typedef char datatype;
typedef struct{
	// 此处包含两个信息：1.总长度 2.首地址data[0]  
	datatype data[Maxsize];
	int size;
} Sqset;

// 创建一个指向结构体变量的指针 
Sqset* CreateSet() {
	Sqset* p = (Sqset *)malloc(sizeof(Sqset));
	p -> size = 0;
	return p;
};

// 从数组元素建立集合 
Sqset* CreateSetFromArry(datatype a[],int i){
	Sqset* p = (Sqset *)malloc(sizeof(Sqset));
	p -> size = i;
	for (i = 0; i<p->size;i++)
		p -> data[i] = a[i];
	return p;
};

// 查找集合中是否存在元素 x
int Find(Sqset* p,datatype x){
	int i;
	for (i = 0;i < p->size;i++)
		if (x == p->data[i])
			return 1;
	return 0;
}; 

// 往集合中添加元素 x 
void Add(Sqset* p, datatype x){
	if (Find(p,x) || p -> size == Maxsize)
		return;
	p -> data[p->size++] = x;
};

// 删除集合中的元素 x
void Delete(Sqset* p, datatype x){
	int i;
	for (i = 0;i<p->size;i++){
		if (p -> data[i] == x)
			// 将最后一个元素覆盖在p->data[i]且总长度减一 
			p -> data[i] = p -> data[--p -> size]; 
	}
}; 

// 求两个集合的并集
void Union(Sqset* p, Sqset* q , Sqset* t){
	int i;
	for (i = 0;i < p -> size; i++)
		t->data[i] = p -> data[i];
	t -> size = p -> size;
	for (i = 0;i<q->size;i++)
		Add(t, q->data[i]);
};

// 求两集合的交集
void Intersection(Sqset* p, Sqset* q , Sqset* t){
	int i,j;
	int flag;
	for (i = 0;i < p -> size; i++)
		t->data[i] = p -> data[i];
	t -> size = p -> size;
	for (i = 0;i<t->size;i++){
		flag = 0;
		for (j=0;j<q->size;j++){
			if (q->data[j] == t->data[i])
				flag = 1;
		}
		if (flag == 0){
			Delete(t,t->data[i]);
			// 删除操作时，被删除数组长度发生了改变，要归零重新开始 
			i = 0; 
		}		
	}
};

// 求两集合交集方法二 
void  Intersection2(Sqset* p, Sqset* q , Sqset* t){
	int i,j;
	t -> size = 0;
	for (i = 0; i<p->size; i++){
		if (Find(q,p->data[i]))
			t->data[t->size++] = p->data[i];
	} 
}

// 输出集合
void Print(Sqset* p){
	int i;
	for (i = 0;i < p -> size; i++)
		printf("%c",p -> data[i]);
	printf("\n"); 
};

int main(){
	datatype a[] = {'a','b','c'};
	datatype b[] = {'d','e','a','c'};
	Sqset *p,*q,*t;
	p = CreateSetFromArry(a,3);
	q = CreateSetFromArry(b,4);
	t = CreateSet();
	Print(p);
	Print(q);
	Union(p,q,t);
	Print(t);
	Intersection2(p,q,t);
	Print(t);
	return 0;		
}
