#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 50000

int n;
std::pair<double,std::pair<double,double> > a[maxn+1];
double ans;

int main(){
	scanf("%d",&n);
	for(re int i=1;i<=n;++i)
		scanf("%lf%lf%lf",&a[i].second.first,&a[i].second.second,&a[i].first);
	std::sort(a+1,a+n+1);
	for(re int i=2;i<=n;++i)
		ans+=sqrt((a[i-1].second.second-a[i].second.second)*(a[i-1].second.second-a[i].second.second)+
		(a[i-1].second.first-a[i].second.first)*(a[i-1].second.first-a[i].second.first)+
		(a[i-1].first-a[i].first)*(a[i-1].first-a[i].first));
	printf("%0.3lf",ans);
	return 0;
}
