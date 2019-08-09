#include<cstdio>
#define re register

int main(){
	for(re int i=2;i<99991;++i)
		if(99991%i==0)
			puts("FAQ!");
	return 0;
}
