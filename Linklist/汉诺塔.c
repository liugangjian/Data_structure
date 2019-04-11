# include<stdio.h>

/*if(n>1){
	先把 A 柱子上的前 n-1 个盘子从 A 借助 C 移到 B
	将 A 柱子上的第 n 个盘子直接移到 C
	再将 B 柱子上的 n-1 个盘子借助 A 移到 C 
	（需要移动 2^n - 1 次 ） 
}*/

void hannuota(int n, char A, char B, char C){
	if(1 == n)
		printf("将编号为%d的盘子直接从%c柱子移到%c柱子\n",n,A,C); 
	else{
		hannuota(n-1,A,C,B);
		printf("将编号为%d的盘子直接从%c柱子移到%c柱子\n",n,A,C);
		hannuota(n-1,B,A,C);	
	}
} 

int main(void){
	
	char ch1 = 'A';
	char ch2 = 'B';
	char ch3 = 'C';
	int n;
	
	printf("请输入要移动的盘子的个数：");
	
	scanf("%d",&n);
	
	hannuota(n,'A','B','C');
	return 0; 
} 
