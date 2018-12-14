#include<cstdio>
#define re register
#define maxn 100000
#define max2 64
#define max3 40

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

int n,ec;
long long a[maxn+1],v[max2+1][max3+1];
int f[max2+1][max3+1],p[max2+1][max3+1];

void dfs(re int x,re int y){
	if(p[x][y]){
		if(p[x][y]==1)
			dfs(x-1,y);
		else
			dfs(x,y+1);
	}
	if(v[x][y])
		cltstream::write(v[x][y],32);
}

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		re int x=0,y=0;
		re long long z=a[i];
		for(;z%2==0;++x,z/=2);
		for(;z%3==0;++y,z/=3);
		v[x][y]=a[i];
		f[x][y]=1;
	}
	for(re int i=1;i<=max2;++i){
		f[i][max3]+=f[i-1][max3];
		p[i][max3]=1;
	}
	for(re int i=max3-1;i>=0;--i){
		f[0][i]+=f[0][i+1];
		p[0][i]=2;
	}
	for(re int i=1;i<=max2;++i)
		for(re int j=max3-1;j>=0;--j)
			if(f[i-1][j]>f[i][j+1]){
				f[i][j]+=f[i-1][j];
				p[i][j]=1;
			}
			else{
				f[i][j]+=f[i][j+1];
				p[i][j]=2;
			}
	cltstream::write(f[max2][0],10);
	dfs(max2,0);
	clop();
	return 0;
}
