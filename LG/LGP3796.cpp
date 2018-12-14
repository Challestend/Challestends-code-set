#include<cstdio>
#include<iostream>
#include<algorithm>
#include<string>
#include<queue>
#define re register
#define maxn 150
#define maxlen 70
#define max(a,b) ((a)>=(b)?(a):(b))

int n;
std::string s[maxn+1];
struct node{
	int ch[26];
	int fail,end,cnt;
};
node a[maxn*maxlen+10];
std::queue<int> h;
int pos[maxn+1];

int main(){
	for(;;){
		scanf("%d",&n);
		if(!n)
			break;
		for(re int i=0;i<26;++i)
			a[0].ch[i]=0;
		re int vc=0;
		for(re int i=1;i<=n;++i){
			std::cin>>s[i];
			re int len=s[i].length(),cur=0;
			for(re int j=1;j<=len;++j){
				if(!a[cur].ch[s[i][j-1]-'a']){
					a[cur].ch[s[i][j-1]-'a']=++vc;
					for(re int k=0;k<26;++k)
						a[vc].ch[k]=0;
					a[vc].fail=a[vc].end=a[vc].cnt=0;
				}
				cur=a[cur].ch[s[i][j-1]-'a'];
			}
			a[pos[i]=cur].end=1;
		}
		for(re int i=0;i<26;++i)
			if(a[0].ch[i])
				h.push(a[0].ch[i]);
		for(;!h.empty();){
			re int x=h.front();
			h.pop();
			for(re int i=0;i<26;++i)
				if(a[x].ch[i]){
					a[a[x].ch[i]].fail=a[a[x].fail].ch[i];
					h.push(a[x].ch[i]);
				}
				else
					a[x].ch[i]=a[a[x].fail].ch[i];
		}
		std::cin>>s[0];
		re int len=s[0].length();
		for(re int i=1,cur=0;i<=len;++i)
			for(re int p=cur=a[cur].ch[s[0][i-1]-'a'];p;p=a[p].fail)
				a[p].cnt+=a[p].end;
		re int maxcnt=0;
		for(re int i=1;i<=n;++i)
			maxcnt=max(maxcnt,a[pos[i]].cnt);
		printf("%d\n",maxcnt);
		for(re int i=1;i<=n;++i)
			if(a[pos[i]].cnt==maxcnt)
				std::cout<<s[i]<<std::endl;
	}
	return 0;
}
