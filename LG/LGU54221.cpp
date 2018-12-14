#include<cstdio>
#define re register
#define maxn 10
#define maxm 100000

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
	#define clop() fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout)
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
int a[maxn+1][maxm+1];

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j){
			re char c=cltstream::gc();
			for(;c!='#'&&c!='.';c=cltstream::gc());
			a[i][j]=(c=='#');
		}
	for(re int j=1;j<=m;++j)
		for(re int i=1;i<=n;++i)
			if(a[i][j]){
				if(!a[i][j+1]){
					if(a[i+3][j])
						cltstream::write(1);
					else{
						cltstream::write(4);
						j+=2;
					}
				}
				else{
					if(!a[i+1][j])
						cltstream::write(!a[i+3][j+2]?2:a[i+2][j+1]?3:7);
					else
						if(!a[i+1][j+2])
							cltstream::write(!a[i+3][j]?5:6);
						else
							cltstream::write(a[i+2][j+1]?a[i+3][j]?8:9:0);
					j+=2;
				}
				break;
			}
	clop();
	return 0;
}
