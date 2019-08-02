#include<cmath>
#include<cstdio>
#include<cstring>
#include<iostream>
#define maxn 3000000
#define re register

const double Pi=acos(-1.0);

namespace cltstream{
	#define size 1048576
	char cltin[size+1],*ih=cltin,*it=cltin;
	inline char gc(){
		#ifdef ONLINE_JUDGE
			if(ih==it){
				it=(ih=cltin)+fread(cltin,1,size,stdin);
				if(ih==it)
					return EOF;
			}
			return *ih++;
		#else
			return getchar();
		#endif
	}

	char cltout[size+1],*oh=cltout,*ot=cltout+size;
	inline void pc(char c){
		if(oh==ot){
			fwrite(cltout,1,size,stdout);
			oh=cltout;
		}
		*oh++=c;
	}
	#define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout),cltstream::oh=cltstream::cltout
	#undef size

	template <typename _tp>
	inline void read(_tp& x){
		int sn=1;
		char c=gc();
		for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
		if(c==45&&c!=EOF)
			sn=-1,c=gc();
		for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=gc());
		x*=sn;
	}

	template <typename _tp>
	inline void write(_tp x,char text=-1){
		if(x<0)
			pc(45),x=-x;
		if(!x)
			pc(48);
		else{
			int digit[22];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];pc(digit[digit[0]--]^48));
		}
		if(text>=0)
			pc(text);
	}
}

struct cpx{
	double x,y;
	cpx (double xx=0,double yy=0){x=xx,y=yy;}
}a[maxn],b[maxn],c[maxn];

int n,m,lim,l;
int r[maxn],d[maxn],x[maxn],y[maxn],f[maxn];
char ch[maxn];

cpx operator+(cpx a,cpx b){
	return cpx(a.x+b.x,a.y+b.y);
}

cpx operator-(cpx a,cpx b){
	return cpx(a.x-b.x,a.y-b.y);
}

cpx operator*(cpx a,cpx b){
	return cpx(a.x*b.x-a.y*b.y,a.x*b.y+a.y*b.x);
}

inline void FFT(cpx *a,int inv){
	for(re int i=0;i<lim;i++)
		if(i<r[i])
			std::swap(a[i],a[r[i]]);
	for(re int i=1;i<lim;i<<=1){
		cpx unit(cos(Pi/i),inv*sin(Pi/i));
		for(re int j=0;j<lim;j+=(i<<1)){
			cpx tmp(1,0);
			for(re int k=0;k<i;k++,tmp=tmp*unit){
				cpx x=a[j+k],y=tmp*a[j+i+k];
				a[j+k]=x+y;
				a[j+i+k]=x-y;
			}
		}
	}
}

int main(){
	scanf("%s",ch);
	n=strlen(ch);
	for(re int i=0;i<n;i++)
		y[i]=ch[i]-'0'+1;
	scanf("%s",ch);
	m=strlen(ch);
	for(re int i=0;i<m;i++)
		x[m-1-i]=ch[i]-'0'+1;
	for(lim=1;lim<=n+m;lim<<=1,l++);
	for(re int i=0;i<lim;i++){
		r[i]=(r[i>>1]>>1)|((i&1)<<(l-1));
		a[i]=cpx(x[i],0);
		b[i]=cpx(y[i],0);
	}
	re double T=0;
	for(re int i=0;i<m;i++)
		T+=a[i].x*a[i].x;
	f[0]=b[0].x*b[0].x;
	for(re int i=1;i<n;i++)
		f[i]=f[i-1]+b[i].x*b[i].x;
	FFT(a,1);
	FFT(b,1);
	for(re int i=0;i<=lim;i++)
		c[i]=a[i]*b[i];
	FFT(c,-1);
	for(re int i=0;i<lim;i++)
		d[i]=(int)(c[i].x/m+0.5);
	re int ans=0;
	for(re int i=m-1;i<n;i++){
		re int p=T+f[i]-f[i-m]-2*d[i];
		ans+=!(p%2);
	}
	printf("%d",ans);
	return 0;
}
