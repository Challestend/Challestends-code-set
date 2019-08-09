#include<cstdio>
#include<cstdlib>
#include<ctime>
#include<cmath>
#define re register

const double PI=acos(-1.0);

double W,H,D;
int n;
double x,y,r,v,a;

int main(){
	system("generator1.exe");
	freopen("1.in","r",stdin);
	freopen("graph.out","w",stdout);
	scanf("%lf %lf %d",&W,&H,&n);
	D=sqrt(W*W+H*H);
	printf("Polygon\n0 0\n%0.2lf 0\n%0.2lf %0.2lf\n0 %0.2lf\n...\n",W,H,W,H);
	for(re int i=1;i<=n;++i){
		scanf("%lf%lf%lf%lf%lf",&x,&y,&r,&v,&a);
		printf("Circle %0.2lf %0.2lf %0.2lf\n",x,y,r);
		x-=r*cos(a+PI/2);
		y-=r*sin(a+PI/2);
		printf("Segment %0.2lf %0.2lf %0.2lf %0.2lf\n",x,y,x+D*cos(a),y+D*sin(a));
		x+=2*r*cos(a+PI/2);
		y+=2*r*sin(a+PI/2);
		printf("Segment %0.2lf %0.2lf %0.2lf %0.2lf\n",x,y,x+D*cos(a),y+D*sin(a));
	}
	scanf("%lf%lf%lf%lf",&x,&y,&r,&v);
	printf("Circle %0.2lf %0.2lf %0.2lf\n",x,y,r);
	printf("Line 1 0 %0.2lf\n",-x);
	printf("Line 0 1 %0.2lf\n",-y);
	return 0;
}
