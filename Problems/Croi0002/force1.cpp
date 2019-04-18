#include<cstdio>
#define re register
#define maxn 100000

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

int n,m;
int a[maxn+1],p[maxn+1];

int main(){
	freopen("data1.in","r",stdin);
	freopen("data1.ans","w",stdout);
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	for(re int i=1;i<n;++i)
		cltstream::read(p[i]);
	for(re int i=1;i<=m;++i){
		int opt,l,r,x;
		cltstream::read(opt);
		cltstream::read(l);
		cltstream::read(r);
		if(opt==1){
			cltstream::read(x);
			for(re int j=l;j<=r;++j)
				a[j]=x;
		}
		if(opt==2){
			cltstream::read(x);
			for(re int j=l;j<=r;++j)
				p[j]=x;
		}
		if(opt==3){
			re int res=0,tmp=a[l];
			for(re int j=l;j<r;++j)
				if(p[j])
					tmp*=a[j+1];
				else{
					res+=tmp;
					tmp=a[j+1];
				}
			cltstream::write<unsigned>(res+tmp,10);
		}
		// for(re int j=1;j<=n;++j)
		// 	printf("%u%c",a[j],j<n?32:10);
	}
	clop();
	return 0;
}
