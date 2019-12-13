#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 100000
#define maxs 320

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

int n,m,sq;
int a[maxn+1],b[maxn+1];
struct operation{
	int t,l,r,x;
};
operation p[maxs+5];

inline bool operator<(const operation& A,const operation& B){
	return A.l<B.l;
}

inline void rebuild(){
	std::sort(p+1,p+sq+1);
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq=sqrt(n);
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	for(re int i=1;i<=n;++i)
		cltstream::read(b[i]);
	for(re int i=1,cnt=0;i<=m;++i){
		int opt;
		cltstream::read(opt);
		if(opt==1){
			++cnt;
			p[cnt].t=i;
			cltstream::read(p[cnt].l);
			cltstream::read(p[cnt].r);
			cltstream::read(p[cnt].x);
		}
		else{
			int x,res=2E9;
			cltstream::read(x);
			for(re int j=cnt;j>=1;--j)
				if(p[j].r<=x&&p[j].r+p[j].x>x){
					res=a[p[j].l+x-p[j].r];
					break;
				}
			cltstream::write(res<2E9?res:b[x],10);
		}
		if(cnt==sq)
			rebuild();
	}
	clop();
	return 0;
}
