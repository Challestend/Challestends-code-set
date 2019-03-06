#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#define re register

int n,len,l,r,ans;
std::string s;
int a[26];

int main(){
	scanf("%d",&n);
	std::cin>>s;
	len=s.length();
	for(re int i=1;i<=len;++i)
		a[s[i-1]-'a']=1;
	for(int i=2;i<=n;++i){
		std::cin>>s;
		len=s.length();
		l=1,r=len;
		for(;l<len&&s[l-1]==s[l];++l);
		for(;r>1&&s[r-1]==s[r-2];--r);
		r=len-r+1;
		for(int j=0;j<26;++j)
			if(a[j]){
				if(s[0]=='a'+j)
					ans=std::max(ans,(s[len-1]=='a'+j)*r+1+l);
				else
					ans=std::max(ans,(s[len-1]=='a'+j)*r+1);
			}
		for(re int j=1;j<=len;++j)
			a[s[j-1]-'a']=1;
	}
	printf("%d",std::max(std::max(ans,l),r));
	return 0;
}
