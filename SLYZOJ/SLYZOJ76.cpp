#include<cstdio>
#define re register
#define maxn 1000
#define swap(a,b) a^=b,b^=a,a^=b

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

int n,m,tp;
long long a[maxn+1][maxn+1],lastans;

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(tp);
	for(re int i=1;i<=m;++i){
		int opt;
		long long l,r,x;
		cltstream::read(opt);
		if(opt==1){
			cltstream::read(l);
			l=(l+tp*lastans)%n+1;
			cltstream::read(r);
			r=(r+tp*lastans)%n+1;
			if(l>r)
				swap(l,r);
			lastans=0;
			for(re int j=l;j<=r;++j)
				lastans+=a[j][a[j][0]];
			cltstream::write(lastans,10);
		}
		if(opt==2){
			cltstream::read(l);
			l=(l+tp*lastans)%n+1;
			if(a[l][0])
				--a[l][0];
		}
		if(opt==3){
			cltstream::read(l);
			l=(l+tp*lastans)%n+1;
			cltstream::read(r);
			r=(r+tp*lastans)%n+1;
			cltstream::read(x);
			if(l>r)
				swap(l,r);
			for(re int j=l;j<=r;++j)
				a[j][++a[j][0]]=x;
		}
	}
	clop();
	return 0;
}
