#include<cstdio>
#include<fstream>
#include<cmath>
#define re register
#define lg(a) ((int)(floor(log10(a))))

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

int n;
long long ans;
long long pw[19];

int main(){
	std::fstream out;
	out.open("data");
	pw[0]=1;
	for(re int i=1;i<=18;++i)
		pw[i]=10*pw[i-1];
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		for(re int j=1;j<=i;++j)
			((i*pw[lg(j)]+j)%(1LL*i*j)*pw[lg(i*j)]%(1LL*i*j))||(++ans);
		for(re int j=1;j<i;++j)
			((j*pw[lg(i)]+i)%(1LL*i*j)*pw[lg(i*j)]%(1LL*i*j))||(++ans);
		out<<ans<<',';
		system("cls");
		printf("%7d/%7d\n",i,n);
	}
	return 0;
}
