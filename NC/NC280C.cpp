#include<cstdio>
#include<algorithm>
#define re register

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

long long A,B,cnt,a[15][2],d[3200000];

void dfs(re int cur,re long long prod){
	if(cur==cnt)
		d[++d[0]]=prod;
	else
		for(re long long i=0,j=1;i<=a[cur+1][1];++i,j*=a[cur+1][0])
			dfs(cur+1,prod*j);
}

int main(){
	cltstream::read(A);
	cltstream::read(B);
	for(;B^=A^=B^=A%=B;);
	for(re long long i=2;i*i<=A;++i)
		if(A%i==0){
			a[++cnt][0]=i;
			for(;A%i==0;A/=i,++a[cnt][1]);
		}
	if(A>1){
		a[++cnt][0]=A;
		a[cnt][1]=1;
	}
	dfs(0,1);
	std::sort(d+1,d+d[0]+1);
	for(re int i=1;i<=d[0];++i)
		cltstream::write(d[i],32);
	clop();
	return 0;
}
