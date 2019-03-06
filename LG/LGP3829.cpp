#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 40000
#define eps 1e-15

int n,m,top;
double a,b,r;
struct Point{
	double x,y;

	Point(re double _x=0,re double _y=0){
		x=_x;
		y=_y;
	}
};
Point pnt[maxn+1];
int stk[maxn+1];

inline bool operator<(re Point p1,re Point p2){
	return atan2(p1.y,p1.x)-atan2(p2.y,p2.x)<-eps;
}

inline Point operator-(re Point p1,re Point p2){
	return Point(p1.x-p2.x,p1.y-p2.y);
}

inline double operator*(re Point p1,re Point p2){
	return p1.x*p2.y-p2.x*p1.y;
}

inline double Dist(re Point p1,re Point p2){
	return sqrt((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y));
}

int main(){
	scanf("%d%lf%lf%lf",&n,&b,&a,&r);
	a=a/2-r;
	b=b/2-r;
	for(re int i=1;i<=n;++i){
		double x,y,th;
		scanf("%lf%lf%lf",&x,&y,&th);
		pnt[++m]=Point(x+a*cos(th)-b*sin(th),y+a*sin(th)+b*cos(th));
		if(pnt[m].y-pnt[1].y<-eps)
			std::swap(pnt[m],pnt[1]);
		pnt[++m]=Point(x+a*cos(th)+b*sin(th),y+a*sin(th)-b*cos(th));
		if(pnt[m].y-pnt[1].y<-eps)
			std::swap(pnt[m],pnt[1]);
		pnt[++m]=Point(x-a*cos(th)-b*sin(th),y-a*sin(th)+b*cos(th));
		if(pnt[m].y-pnt[1].y<-eps)
			std::swap(pnt[m],pnt[1]);
		pnt[++m]=Point(x-a*cos(th)+b*sin(th),y-a*sin(th)-b*cos(th));
		if(pnt[m].y-pnt[1].y<-eps)
			std::swap(pnt[m],pnt[1]);
	}
	for(re int i=2;i<=m;++i){
		pnt[i].x-=pnt[1].x;
		pnt[i].y-=pnt[1].y;
	}
	pnt[1].x=pnt[1].y=0;
	std::sort(pnt+2,pnt+m+1);
	stk[++top]=1;
	for(re int i=2;i<=m;++i){
		for(;top>1&&(pnt[stk[top]]-pnt[stk[top-1]])*(pnt[i]-pnt[stk[top]])<eps;--top);
		stk[++top]=i;
	}
	re double ans=2*acos(-1)*r+Dist(pnt[stk[top]],pnt[stk[1]]);
	for(re int i=1;i<top;++i)
		ans+=Dist(pnt[stk[i]],pnt[stk[i+1]]);
	printf("%0.2lf",ans);
	return 0;
}
