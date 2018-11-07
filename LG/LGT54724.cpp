#include<cstdio>
#include<cmath>
#define re register
#define maxn 100
#define maxm 100
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,q,eh,ea,ed,hx,hy,ha,hd,lh;
int a[maxn+1][maxm+1];

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j){
			char c=cltstream::gc();
			for(;c!='.'&&c!='R'&&c!='Q'&&c!='Y'&&c!='M';c=cltstream::gc());
			switch(c){
				case '.':
					a[i][j]=0;
					break;
				case 'R':
					a[i][j]=1;
					break;
				case 'Q':
					a[i][j]=2;
					break;
				case 'Y':
					a[i][j]=3;
					break;
				case 'M':
					a[i][j]=4;
					break;
			}
		}
	cltstream::read(eh);
	cltstream::read(ea);
	cltstream::read(ed);
	cltstream::read(hx);
	cltstream::read(hy);
	cltstream::read(ha);
	cltstream::read(hd);
	cltstream::read(q);
	for(re int i=1;i<=q;++i){
		char opt=cltstream::gc();
		for(;opt!='M'&&opt!='Q';opt=cltstream::gc());
		if(opt=='M'){
			char dir=cltstream::gc();
			for(;dir!='W'&&dir!='E'&&dir!='N'&&dir!='S';dir=cltstream::gc());
			switch(dir){
				case 'W':
					--hy;
					break;
				case 'E':
					++hy;
					break;
				case 'N':
					--hx;
					break;
				case 'S':
					++hx;
					break;
			}
			switch(a[hx][hy]){
				case 1:
					lh=max(lh-10,0);
					break;
				case 2:
					ha+=5;
					break;
				case 3:
					hd+=5;
					break;
				case 4:
					lh+=max(ceil(double(eh)/max(ha-ed,1))*max(ea-hd,1),1);
					break;
			}
		}
		else{
			cltstream::write(lh,32);
			cltstream::write(ha,32);
			cltstream::write(hd,10);
		}
	}
	clop();
	return 0;
}
