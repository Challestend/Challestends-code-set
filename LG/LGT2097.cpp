#include<cstdio>
#define re register
#define maxn 2500
#define lowbit(a) ((a)&(-(a)))

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
int a[maxn+1][maxn+1][4];

inline void update(re int x,re int y,re int S){
	if(!x||!y)
		return;
	for(re int i=x;i<=n;i+=lowbit(i))
		for(re int j=y;j<=n;j+=lowbit(j)){
			a[i][j][0]^=S;
			a[i][j][1]^=(x&1)?S:0;
			a[i][j][2]^=(y&1)?S:0;
			a[i][j][3]^=(x&y&1)?S:0;
		}
}

inline int getxor(re int x,re int y){
	re int res=0;
	for(re int i=x;i>=1;i-=lowbit(i))
		for(re int j=y;j>=1;j-=lowbit(j)){
			res^=((y+1)&(x+1)&1)?a[i][j][0]:0;
			res^=((y+1)&1)?a[i][j][1]:0;
			res^=((x+1)&1)?a[i][j][2]:0;
			res^=a[i][j][3];
		}
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=m;++i){
		re char opt=cltstream::gc();
		for(;opt!='P'&&opt!='Q';opt=cltstream::gc());
		re int x1,y1,x2,y2,k,S=0;
		cltstream::read(x1);
		cltstream::read(y1);
		cltstream::read(x2);
		cltstream::read(y2);
		if(opt=='P'){
			cltstream::read(k);
			for(re int j=1;j<=k;++j){
				re int x,y;
				cltstream::read(x);
				cltstream::read(y);
				S^=(y&1)<<(x-1);
			}
			update(x1,y1,S);
			update(x2+1,y1,S);
			update(x1,y2+1,S);
			update(x2+1,y2+1,S);
		}
		else{
			S^=getxor(x2,y2);
			S^=getxor(x1-1,y2);
			S^=getxor(x2,y1-1);
			S^=getxor(x1-1,y1-1);
			for(re int j=1;j<=30;S>>=1,++j)
				cltstream::pc(((S&1)^48)+1);
			cltstream::pc(10);
		}
	}
	clop();
	return 0;
}
