#include<cstdio>
#include<cstring>
#define re register
#define maxn 11000000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

char str[(maxn<<1)+5];
int n,maxRight,mid,ans[(maxn<<1)+5],maxLen;

int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	for(re int i=n;i>=0;--i){
		str[i<<1]=str[i];
		str[i<<1|1]='#';
	}
	n=n<<1|1;
	for(re int i=1;i<=n;++i){
		ans[i]=max(min(ans[(mid<<1)-i],maxRight-i+1),1);
		for(;i-ans[i]>=1&&i+ans[i]<=n&&str[i-ans[i]]==str[i+ans[i]];++ans[i]);
		if(i+ans[i]-1>maxRight){
			maxRight=i+ans[i]-1;
			mid=i;
		}
		maxLen=max(maxLen,ans[i]);
	}
	printf("%d",maxLen-1);
	return 0;
}
