#include<cstdio>
#define re register
#define maxn 100000
#define maxm 100

int n,m,cnt;
long long ans;
char s[maxn+5],t[maxm+5];
int lst[26],l[maxn+1],r[maxn+1];

int main(){
	scanf("%d%d%s%s",&n,&m,s+1,t+1);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j)
			if(s[i]==t[j]){
				lst[j]=j==1?i:lst[j-1];
				if(j==m){
					++cnt;
					l[cnt]=lst[j];
					r[cnt]=i;
				}
			}
	for(re int i=1;i<=cnt;++i)
		ans+=1LL*(l[i]-l[i-1])*(n-r[i]+1);
	printf("%lld",ans);
	return 0;
}
