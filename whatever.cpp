#include<cstdio>
#include<iostream>
#include<string>
#define re register

int n,m;
std::string s;

int main(){
	scanf("%d",&n);
	for(re int i=1;i<=n;++i){
		re int A=0,B=0;
		scanf("%d",&m);
		std::cin>>s;
		for(re int j=0;j<m;++j)
			B+=(s[j]=='B')-2*(s[j]=='S');
		std::cin>>s;
		for(re int j=0;j<m;++j)
			A+=(s[j]=='B')-2*(s[j]=='S');
		if(A>B)
			puts("A wins");
		else
			if(A<B)
				puts("B wins");
			else
				puts("Draw");
	}
	return 0;
}
