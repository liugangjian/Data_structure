/* 编译环境：DEV C++ */
# include<stdio.h>
# include<malloc.h>
# include<stdlib.h>
# include<stdbool.h>

struct Arr
{
	int * pfrist; // 第一个元素的地址 
	int count; // 有效元素个数
	int len; // 数组的总长度
};

// 初始化数组 
bool init(struct Arr * Arrlist,int length);
// 销毁数组 
void destroy(struct Arr *pArr);
// 增 
bool append(struct Arr * Arrlist);
bool insert(struct Arr * Arrlist, int pos, int val);
// 删 
bool delate(struct Arr * Arrlist, int pos);
// 改
bool change(struct Arr * Arrlist,int pos,int val);
//查 
bool search1(struct Arr * Arrlist, int val); // 通过数值查位置 
void search2(struct Arr * Arrlist, int pos); // 用过位置查数值 

// 判断空满 
bool isempty(struct Arr * pArr);
bool isfull(struct Arr *pArr);
// 打印 
void showArr(struct Arr *pArr);
// 排序 
void sortArr(struct Arr *pArr);
// 倒置 
void invension(struct Arr *pArr);

int main(){
	int length;
	struct Arr arr;
	
	printf("please input the length = ");
	scanf("%d",&length);
	init(&arr,length);
	append(&arr);
	
	insert(&arr,2,1222);
	//delate(&arr,2);
	
	//sortArr(&arr);
	//invension(&arr);
	
	search1(&arr,2);
	search2(&arr,3);
	showArr(&arr);
	destroy(&arr);
		
	return 0;
}

bool init(struct Arr *pArr, int length){
	pArr -> pfrist = (int *)malloc(sizeof(int)*length);
	if(NULL == pArr -> pfrist)
	{
		printf("allocate fail");
		exit(-1);
	} 
	else
	{
		pArr -> len = length;
		pArr -> count = 0;
	}
	return; 
}

void destroy(struct Arr *pArr){
	free(pArr->pfrist);
	pArr -> pfrist = NULL;
	pArr -> len = 0;
	pArr -> count = 0; 
} 

void showArr(struct Arr *pArr){
	int i;
	if (isempty(pArr))
		printf("the arrlist is empty");
	else{
		for(i = 0; i < pArr -> count; i++)
		printf("%d ",pArr -> pfrist[i]);
	}
}

bool isempty(struct Arr * pArr){
	if (pArr -> count == 0)
		return true;
	else
		return false;
}

bool isfull(struct Arr *pArr){
	if (pArr -> count == pArr -> len)
		return true;
	else 
		return false;
}

bool append(struct Arr *pArr){
	int val;
	
	if(isfull(pArr)){
		printf("the arrlist is full\n");
		return false;
	}
		
	else{
		scanf("%d",&val);
		pArr -> pfrist[pArr -> count] = val;
		pArr -> count ++;
		
		append(pArr);
	}
}

/*bool insert(struct Arr * pArr, int pos, int val){
	int i;
	if ( pos < 0 || pos > pArr -> count ){
		printf("the pos is illegal");
		return false;
	}
		
	else
	{
		for( i = pArr->count-1; i >= pos-1; i-- )
		{ 
			// 神奇之处在于此时的pfrist[i+1]已经越过 
			// malloc所指定范围，但仍可以越界访问内存空间 
			pArr -> pfrist[i+1] = pArr -> pfrist[i];
		}
		pArr -> count ++;
		pArr -> len ++;
		pArr -> pfrist[pos-1]=val;
		return true;
	}
}*/

bool insert(struct Arr * pArr, int pos, int val){
	int i;
	int * newbase;
	if ( pos < 0 || pos > pArr -> count ){
		printf("the pos is illegal");
		return false;
	}
	
	// 当前内存空间已满，增加分配 
	if ( pArr -> count == pArr -> len ){
		newbase = (int *)realloc(pArr -> pfrist,sizeof(int)*(pArr -> count + 1));
		pArr -> pfrist = newbase; 
	} 
		
	for( i = pArr->count-1; i >= pos-1; i-- )
		pArr -> pfrist[i+1] = pArr -> pfrist[i];
	pArr -> count ++;
	pArr -> len ++;
	pArr -> pfrist[pos-1]=val;
	return true;
	
}



bool delate(struct Arr * pArr, int pos){
	int tem;
	int i;
	if (isempty(pArr))
		return false;
	if ( pos < 0 || pos > pArr->count)
		return false;
	else
	{
		tem = pArr->pfrist[pos-1];
		for (i = pos;i<pArr->count;i++)
		{
			pArr -> pfrist[i-1] = pArr -> pfrist[i]; 
		}
		pArr -> count --;
		pArr -> len --;
	}
	printf("the value you delate is %d\n ",tem);
	return 0;
} 

void sortArr(struct Arr *pArr){
	int tem;
	int i,j;
	for (j=0;j<pArr -> count;j++)
	{
		for ( i = 0; i< pArr -> count; i++ )
		{
			if (pArr -> pfrist[i]>=pArr->pfrist[i+1])
				{
					tem = pArr -> pfrist[i];
					pArr -> pfrist[i] = pArr->pfrist[i+1];
					pArr -> pfrist[i+1] = tem;
				}
		}
	}
} 

void invension(struct Arr *pArr)
{
	int i;
	int j;
	int tmp;
	for (i = 0,j=pArr->count; i<j; i++,j--)
	{
		tmp = pArr->pfrist[i];
		pArr ->pfrist[i] = pArr ->pfrist[j];
		pArr ->pfrist[j] = tmp;
	}
}

bool change(struct Arr * pArr,int pos,int val){
	pArr->pfrist[pos-1] = val;
}

bool search1(struct Arr * pArr, int val){
	int i;
	for (i = 0; i<pArr->count;i++)
	{
		if (pArr->pfrist[i] == val)
			{
				printf("the pos of %d is %d\n",val, i+1);
				return true;
			}
		else if ( i == pArr ->count-1 )
			{
				printf("there is no such val in this arry\n");
				return false;
			}
	} 
} 

void search2(struct Arr * pArr, int pos){
	if (pos < 0 || pos > pArr->count)
{
		printf("out of range\n");
		return;
}
	else
		printf("the %d pos' val is %d\n",pos, pArr->pfrist[pos-1]);
	return;
}
