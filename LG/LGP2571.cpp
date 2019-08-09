#include<cstdio>
#include<cmath>
#define re register
#define eps 1E-4

double Ax,Ay,Bx,By,Cx,Cy,Dx,Dy,P,Q,R,AB,CD;

inline double Dist(re double x1,re double y1,re double x2,re double y2){
	return sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
}

inline double Final(re double p,re double q){
	return Dist(Ax+p*(Bx-Ax),Ay+p*(By-Ay),Dx-q*(Dx-Cx),Dy-q*(Dy-Cy))/R;
}

inline double Inner(re double p){
	re double l=0,r=1;
	for(;(r-l)*CD>eps;){
		re double t=(r-l)/3,u=Final(p,l+t),v=Final(p,r-t);
		if(u-v-t*CD/Q>-eps)
			l+=t;
		else
			r-=t;
	}
	return l*CD/Q+Final(p,l);
}

inline double Outer(){
	re double l=0,r=1;
	for(;(r-l)*AB>eps;){
		re double t=(r-l)/3,u=Inner(l+t),v=Inner(r-t);
		if(u-v-t*AB/P>-eps)
			l+=t;
		else
			r-=t;
	}
	return l*AB/P+Inner(l);
}

int main(){
	scanf("%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf%lf",&Ax,&Ay,&Bx,&By,&Cx,&Cy,&Dx,&Dy,&P,&Q,&R);
	AB=Dist(Ax,Ay,Bx,By);
	CD=Dist(Cx,Cy,Dx,Dy);
	printf("%0.2lf",Outer());
	return 0;
}
