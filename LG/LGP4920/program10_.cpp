#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<map>
#define re register

std::map<std::string,unsigned long long> mp;
unsigned long long ans;

inline std::string readFunc(){
	std::string res="";
	char c=getchar();
	for(;(c<'A'||c>'Z')&&c!='_';c=getchar());
	for(;(c>='A'&&c<='Z')||c=='_';res+=c,c=getchar());
	return res;
}

#define repeat(a) {for(re int i=1;i<=a;++i)readFunc();}

#define getAns() {ans=0;for(;;){std::string name=readFunc();if(name!="__")ans+=mp[name];else break;}}

int main(){
	freopen("program10.cpp","r",stdin);
	freopen("program10.out","w",stdout);
	repeat(6);
	mp["_"]=1,mp["A"]=26,mp["B"]=651,mp["C"]=15651;
	for(;;){
		std::string name=readFunc();
		re unsigned long long res=0;
		for(re unsigned j=0;j<(name.size()==1?26:name.size()*(name.size()+1)/2-1);++j){
			std::string namf=readFunc();
			res+=mp[namf];
		}
		mp[name]=res;
		if(name=="REPRESENTATIVES")
			break;
	}
	repeat(2);
	getAns();
	printf("%llu\n",ans);
	repeat(2);
	getAns();
	printf("%llu\n",9ULL*ans);
	printf("%llu\n",9ULL*ans);
	repeat(3);
	getAns();
	printf("%llu\n",4ULL*ans);
	printf("%llu\n",4ULL*ans);
	repeat(3);
	getAns();
	printf("%llu\n",9ULL*ans);
	printf("%llu\n",9ULL*ans);
	printf("%llu\n",9ULL*ans);
	printf("%llu\n",9ULL*ans);
	printf("%llu\n",9ULL*ans);
	return 0;
}
