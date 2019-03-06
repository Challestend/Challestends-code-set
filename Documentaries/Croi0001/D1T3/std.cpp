#include<cstdio>
#include<cmath>
#define re register
#define maxm 6000
#define mod 100000000

const long double Pi=acos(-1.0);

long long n;
int m,a,b;
struct complex{
	long double x,y;

	complex(re long double _x=0,re long double _y=0){
		x=_x;
		y=_y;
	}
};
complex p[maxm+1],w[maxm+1],sum[maxm+1],ans;

inline long double cltmod(re long double x){
	return x-floor(x/mod)*mod;
}

inline complex operator+(const complex& p1,const complex& p2){
	return complex(cltmod(p1.x+p2.x),cltmod(p1.y+p2.y));
}

inline complex operator-(const complex& p1,const complex& p2){
	return complex(cltmod(p1.x-p2.x),cltmod(p1.y-p2.y));
}

inline complex operator*(const complex& p1,const complex& p2){
	return complex(cltmod(p1.x*p2.x-p1.y*p2.y),cltmod(p1.x*p2.y+p2.x*p1.y));
}

inline complex operator/(const complex& p1,const complex& p2){
	return complex(cltmod((p1.x*p2.x+p1.y*p2.y)/(p2.x*p2.x+p2.y*p2.y)),cltmod((p2.x*p1.y-p1.x*p2.y)/(p2.x*p2.x+p2.y*p2.y)));
}

inline complex cltpow(complex x,re long long y){
	complex res(1);
	for(;y;){
		if(y&1)
			res=res*x;
		x=x*x;
		y>>=1;
	}
	return res;
}

int main(){
	scanf("%lld%d%d%d",&n,&m,&a,&b);
	p[0]=complex(1);
	p[1]=complex(pow(b,1.0/m));
	for(re int i=2;i<m;++i)
		p[i]=p[i-1]*p[1];
	w[0]=complex(1);
	w[1]=complex(cos(2.0*Pi/m),sin(2.0*Pi/m));
	for(re int i=2;i<m;++i)
		w[i]=w[i-1]*w[1];
	for(re int i=0;i<m;++i)
		sum[i]=cltpow(complex(a)+p[1]*w[i],n);
	for(re int i=0;i<m;++i){
		complex res;
		for(re int j=0;j<m;++j)
			res=res+sum[j]/w[i*j%m];
		ans=ans+res/p[i];
	}
	printf("%0.16Lf",ans.x/m);
	return 0;
}
