#include<cstdio>
#include<algorithm>
#define re register
#define maxn 200
#define maxm 200
#define mod 1000000007
#define I100 570000004

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
int m[maxn+1],q[maxn+1],v[maxn+1],cnt[maxn+1],tmp[maxn+1],ans[maxn+1];
struct card{
	int id,a,g,p;
};
card c[maxn*maxm+1];

inline bool operator<(const card& p1,const card& p2){
	return p1.a>p2.a;
}

inline int cltpow(re int x,re int y){
	re int res=1;
	for(;y;){
		if(y&1)
			res=1LL*res*x%mod;
		x=1LL*x*x%mod;
		y>>=1;
	}
	return res;
}

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		cltstream::read(m[i]);
		for(re int j=m[0]+1;j<=m[0]+m[i];++j){
			c[j].id=i;
			cltstream::read(c[j].a);
			cltstream::read(c[j].g);
			c[j].g=1LL*(100-c[j].g)*I100%mod;
			cltstream::read(c[j].p);
			q[i]=(q[i]+c[j].p)%mod;
		}
		q[i]=cltpow(q[i],mod-2);
		m[0]+=m[i];
	}
	for(re int i=1;i<=n;++i)
		cltstream::read(v[i]);
	std::sort(c+1,c+m[0]+1);
	for(re int i=1;i<=m[0];++i){
		cnt[0]+=!cnt[c[i].id];
		++cnt[c[i].id];
		tmp[0]=1;
		for(re int j=1;j<=n;++j)
			if(j!=c[i].id&&cnt[j])
				tmp[0]=1LL*tmp[0]*tmp[j]%mod*q[j]%mod;
		ans[c[i].id]=(ans[c[i].id]+1LL*tmp[0]*c[i].p%mod*q[c[i].id]%mod*c[i].g%mod*v[cnt[0]]%mod)%mod;
		tmp[c[i].id]=(tmp[c[i].id]+c[i].p)%mod;
	}
	for(re int i=1;i<=n;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
