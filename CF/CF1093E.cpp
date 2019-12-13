#include<cstdio>
#include<cmath>
#define re register
#define maxn 200000
#define maxs 450

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

int n,m,sq;
int id[maxn+1],a[maxn+1],b[maxn+1],f[maxn+1],g[maxn+1];
int cnt1[maxs+1][maxs+1],cnt2[maxs+1][maxn+1];

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq=sqrt(n);
	for(re int i=1;i<=n;++i)
		id[i]=(i-1)/sq+1;
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		f[a[i]]=i;
	}
	for(re int i=1;i<=n;++i){
		cltstream::read(b[i]);
		g[i]=f[b[i]];
	}
	for(re int i=1;i<=n;++i){
		f[g[i]]=i;
		for(re int j=id[g[i]];j<=id[n];++j){
			++cnt1[j][id[i]];
			++cnt2[j][i];
		}
	}
	for(re int i=1;i<=m;++i){
		re int opt,l,r,x,y;
		cltstream::read(opt);
		cltstream::read(l);
		cltstream::read(r);
		if(opt==1){
			cltstream::read(x);
			cltstream::read(y);
			re int ans=0,L=id[l],R=id[r],X=id[x],Y=id[y];
			if(L<R){
				for(re int j=l;j<=L*sq;++j)
					ans+=f[j]>=x&&f[j]<=y;
				if(X<Y){
					for(re int j=x;j<=X*sq;++j)
						ans+=cnt2[R-1][j]-cnt2[L][j];
					for(re int j=X+1;j<=Y-1;++j)
						ans+=cnt1[R-1][j]-cnt1[L][j];
					for(re int j=(Y-1)*sq+1;j<=y;++j)
						ans+=cnt2[R-1][j]-cnt2[L][j];
				}
				else
					for(re int j=x;j<=y;++j)
						ans+=cnt2[R-1][j]-cnt2[L][j];
				for(re int j=(R-1)*sq+1;j<=r;++j)
					ans+=f[j]>=x&&f[j]<=y;
			}
			else
				for(re int j=l;j<=r;++j)
					ans+=f[j]>=x&&f[j]<=y;
			cltstream::write(ans,10);
		}
		else{
			re int L=id[g[l]],R=id[g[r]];
			for(re int j=L;j<=id[n];++j){
				--cnt1[j][id[l]];
				--cnt2[j][l];
				++cnt1[j][id[r]];
				++cnt2[j][r];
			}
			for(re int j=R;j<=id[n];++j){
				--cnt1[j][id[r]];
				--cnt2[j][r];
				++cnt1[j][id[l]];
				++cnt2[j][l];
			}
			f[g[l]]^=f[g[r]]^=f[g[l]]^=f[g[r]];
			g[l]^=g[r]^=g[l]^=g[r];
		}
	}
	clop();
	return 0;
}
