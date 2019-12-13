#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000

int n;
double A,B,ans,res;
double a[maxn+1],b[maxn+1];

inline bool cmp(re double x,re double y){
	return x>=y;
}

int main(){
	scanf("%d",&n);
	for(re int i=1;i<=n;++i)
		scanf("%lf",&a[i]);
	std::sort(a+1,a+n+1,cmp);
	for(re int i=1;i<=n;++i)
		scanf("%lf",&b[i]);
	std::sort(b+1,b+n+1,cmp);
	for(re int i=0,j=0;i<n||j<n;){
		if(i<n&&A<=B)
			A+=a[++i];
		else
			B+=b[++j];
		res=std::min(A,B);
		ans=std::max(ans,res-i-j);
	}
	printf("%0.4lf",ans);
	return 0;
}
