#include<cstdio>
#define re register
#define maxn 1000000
#define mod 99991
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define swap(a,b) a^=b^=a^=b

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

int n,m,ec,vc;
int inv[mod];
int des[maxn+1],suc[maxn+1],las[maxn+1];
int tp[maxn+1],val[maxn+1][2],sum[maxn+1],prd[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],len[maxn+1],id[maxn+1],top[maxn+1];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

inline void update(re int x,re int y){
	for(;x<=n;x+=x&(-x)){
		sum[x]=(sum[x]+y)%mod;
		prd[x]=1LL*prd[x]*y%mod;
	}
}

inline int getSum(re int x){
	re int res=0;
	for(;x>=1;x-=x&(-x))
		res=(res+sum[x])%mod;
	return res;
}

inline int getPrd(re int x){
	re int res=1;
	for(;x>=1;x-=x&(-x))
		res=1LL*res*prd[x]%mod;
	return res;
}

void dfs1(re int cur){
	dep[cur]=dep[f[cur]]+1;
	size[cur]=1;
	re int maxsize=0;
	hes[cur]=n+1;
	for(re int i=las[cur];i;i=suc[i]){
		dfs1(des[i]);
		size[cur]+=size[des[i]];
		if(maxsize<size[des[i]]||(maxsize==size[des[i]]&&hes[cur]>des[i])){
			maxsize=size[des[i]];
			hes[cur]=des[i];
		}
	}
}

void dfs2(re int cur,re int curtop){
	id[cur]=++vc;
	++len[top[cur]=curtop];
	if(hes[cur]<=n){
		dfs2(hes[cur],curtop);
		tp[cur]=val[cur][0];
		val[cur][0]=0;
		val[cur][1]=1;
		for(re int i=las[cur];i;i=suc[i])
			if(des[i]!=hes[cur]){
				dfs2(des[i],des[i]);
				val[cur][0]=(val[cur][0]+val[des[i]][tp[des[i]]])%mod;
				val[cur][1]=1LL*val[cur][1]*val[des[i]][tp[des[i]]]%mod;
			}
	}
	update(id[cur],val[cur][tp[cur]]);
}

int main(){
	inv[0]=inv[1]=1;
	for(re int i=2;i<mod;++i)
		inv[i]=(mod-1LL*mod/i*inv[mod%i]%mod)%mod;
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=2;i<=n;++i){
		cltstream::read(f[i]);
		connect(f[i],i);
	}
	for(re int i=1;i<=n;++i)
		cltstream::read(val[i][0]);
	for(re int i=1;i<=n;++i)
		prd[i]=1;
	dfs1(1);
	dfs2(1,1);
	for(re int i=1;i<=n;++i)
		printf("val(%d)=(%d,%d)\n",i,val[i][0],val[i][1]);
	for(re int i=1;i<=m;++i){
		int opt,k;
		cltstream::read(opt);
		cltstream::read(k);
		if(opt==1){
			int x;
			cltstream::read(x);
			for(;hes[f[k]]!=k;k=top[f[k]]){
				val[f[k]][0]=(val[f[k]][0]-val[k][0]+mod)%mod;
				val[f[k]][0]=(val[f[k]][0]+x)%mod;
				val[f[k]][1]=1LL*val[f[k]][1]*val[k][0]%mod;
			}
			val[k][0]=x;
		}
		if(opt==2){
			for(;hes[f[k]]!=k;k=top[f[k]]){
				val[f[k]][0]=(val[f[k]][0]-val[k][tp[k]]+mod)%mod;
				val[f[k]][0]=(val[f[k]][0]+val[k][tp[k]^1])%mod;
				val[f[k]][1]=1LL*val[f[k]][1]*val[k][tp[k]^1]%mod;
			}
			tp[k]^=1;
		}
		if(opt==3){
			k=top[k];
			cltstream::write((getSum(k+len[k]-1)-getSum(k-1)+mod)%mod,32);
			cltstream::write(1LL*getPrd(k+len[k]-1)*inv[getPrd(k-1)]%mod,10);
		}
	}
	clop();
	return 0;
}
