#include<cstdio>
#include<algorithm>
#define re register
#define maxn 200000

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

int n,r,c;
struct square{
	int x1,y1,x2,y2;

	inline long long area(){
		return 1LL*(x2-x1+1)*(y2-y1+1);
	}
};
square a[maxn+1],p[maxn+1],s[maxn+1];

inline square merge(re square P,re square Q){
	if(P.x2<Q.x1||P.x1>Q.x2||P.y2<Q.y1||P.y1>Q.y2)
		return square{2E9,2E9,2E9,2E9};
	else
		return {std::max(P.x1,Q.x1),std::max(P.y1,Q.y1),
				std::min(P.x2,Q.x2),std::min(P.y2,Q.y2)};
}

int main(){
	cltstream::read(n);
	cltstream::read(r);
	cltstream::read(c);
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i].x1);
		cltstream::read(a[i].y1);
		cltstream::read(a[i].x2);
		cltstream::read(a[i].y2);
	}
	p[1]=a[1];
	s[n]=a[n];
	for(re int i=2;i<=n;++i){
		p[i]=merge(p[i-1],a[i]);
		s[n-i+1]=merge(s[n-i+2],a[n-i+1]);
	}
	a[0]=p[0]=s[n+1]={-1E9,-1E9,1E9,1E9};
	re long long ans=0;
	for(re int i=1;i<=n;++i){
		a[i]=merge(p[i-1],s[i+1]);
		ans+=a[i].area();
		a[0]=merge(a[0],a[i]);
	}
	ans-=(n-1)*a[0].area();
	cltstream::write(ans);
	clop();
	return 0;
}
