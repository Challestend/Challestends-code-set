#include<cstdio>
#include<iostream>
#include<string>
#define re register

int n,k,ans[26];
std::string s;

int main(){
	scanf("%d%d",&n,&k);
	std::cin>>s;
	for(re int i=0,j=0;i<n;++i){
		if(!i||s[i]==s[i-1])
			++j;
		else
			j=1;
		if(j==k){
			++ans[s[i]-'a'];
			j=0;
		}
	}
	for(re int i=1;i<26;++i)
		if(ans[0]<ans[i])
			ans[0]=ans[i];
	printf("%d",ans[0]);
	return 0;
}
