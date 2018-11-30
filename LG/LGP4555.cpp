#include<cstdio>
#include<cstring>
#define re register
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

char str[(maxn<<1)+5];
int n,maxRight,mid,ans[(maxn<<1)+5],st[((maxn+1)<<3)+5],maxLen;

void update(int L,int x,int cur,int l,int r){
	if(l==r)
		st[cur]=min(st[cur],x);
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			update(L,x,cur<<1,l,mid);
		else
			update(L,x,cur<<1|1,mid+1,r);
		st[cur]=min(st[cur<<1],st[cur<<1|1]);
	}
}

int query(int L,int R,int cur,int l,int r){
	if(l>=L&&r<=R)
		return st[cur];
	else{
		re int mid=(l+r)>>1,res=2e9,tmp;
		if(L<=mid){
			tmp=query(L,R,cur<<1,l,mid);
			res=min(res,tmp);
		}
		if(R>mid){
			tmp=query(L,R,cur<<1|1,mid+1,r);
			res=min(res,tmp);
		}
		return res;
	}
}

int main(){
	scanf("%s",str+1);
	n=strlen(str+1);
	for(re int i=n;i>=0;--i){
		str[i<<1]=str[i];
		str[i<<1|1]='#';
	}
	n=n<<1|1;
	memset(st,63,sizeof(st));
	for(re int i=1;i<=n;++i){
		ans[i]=max(min(ans[(mid<<1)-i],maxRight-i+1),1);
		for(;i-ans[i]>=1&&i+ans[i]<=n&&str[i-ans[i]]==str[i+ans[i]];++ans[i]);
		if(i+ans[i]-1>maxRight){
			maxRight=i+ans[i]-1;
			mid=i;
		}
		re int tmp=i-query(i-ans[i],n,1,1,n);
		maxLen=max(maxLen,tmp);
		update(i+ans[i]-1,i,1,1,n);
	}
	printf("%d",maxLen);
	return 0;
}
