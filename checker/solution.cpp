#include<cstdio>
#define re register
#define maxn 100000
#define maxlog 20

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
int a[maxn+1],l[maxn+1],r[maxn+1];
int lg[maxn+1],st[maxn+1][maxlog+1];

inline int stmax(re int l,re int r){
	re int x=lg[r-l+1];
	return a[st[l][x]]>=a[st[r-(1<<x)+1][x]]?st[l][x]:st[r-(1<<x)+1][x];
}

long long F(re int l,re int r){
	if(l>r)
		return 0;
	else{
		re int m=stmax(l,r);
		return (r-l+1)+F(l,m-1)+F(m+1,r);
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]);
	for(re int i=1;i<=m;++i)
		cltstream::read(l[i]);
	for(re int i=1;i<=m;++i)
		cltstream::read(r[i]);
	for(re int i=2;i<=n;++i)
		lg[i]=lg[i>>1]+1;
	for(re int i=1;i<=n;++i)
		st[i][0]=i;
	for(re int j=1,k=1;j<=lg[n];++j)
		for(re int i=1;i+(k<<1)-1<=n;++i)
			st[i][j]=a[st[i][j-1]]>=a[st[i+k][j-1]]?st[i][j-1]:st[i+k][j-1];
	for(re int i=1;i<=m;++i)
		cltstream::write(F(l[i],r[i]),32);
	clop();
	return 0;
}
