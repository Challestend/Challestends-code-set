#include<cstdio>
#define re register

int tmp,ans;

int main(){
	putchar('?');
	for(re int i=1;i<=100;++i)
		printf(" %d",i);
	puts("");
	fflush(stdout);
	scanf("%d",&tmp);
	ans|=tmp>>7<<7;
	putchar('?');
	for(re int i=1;i<=100;++i)
		printf(" %d",i<<7);
	puts("");
	fflush(stdout);
	scanf("%d",&tmp);
	ans|=tmp&127;
	printf("! %d",ans);
	return 0;
}
