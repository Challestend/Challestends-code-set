#include<cstdio>
#include<cmath>
#define re register
#define maxn 100000
#define maxs 320
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
int id[maxn+1],lwr[maxs+1],upr[maxs+1];
int p[maxn+1],l[maxn+1],r[maxn+1];
long long w[maxn+1];
long long sum[maxs+1],presum[maxn+1],sucsum[maxn+1],add[maxs+1];
int cnt[maxn+1];
long long tag[maxn+1],tms[maxs+1][maxn+1],ans[maxs+1];

inline void update(re int x,re int y,re long long z){
	if(id[x]<id[y]){
		for(re int i=x,k=1;i<=upr[id[x]];++i,++k)
			presum[i]+=k*z;
		for(re int i=upr[id[x]],k=1;i>=x;--i,++k)
			sucsum[i]+=k*z;
		for(re int i=x-1,k=upr[id[x]]-x+1;i>=lwr[id[x]];--i)
			sucsum[i]+=k*z;
		sum[id[x]]+=(upr[id[x]]-x+1)*z;
		// An empty line.
		for(re int i=id[x]+1;i<=id[y]-1;++i){
			sum[i]+=(upr[i]-x+1)*z;
			add[i]+=z;
		}
		// An empty line.
		for(re int i=lwr[id[y]],k=1;i<=y;++i,++k)
			presum[i]+=k*z;
		for(re int i=y+1,k=y-lwr[id[y]]+1;i<=upr[id[y]];++i)
			presum[i]+=k*z;
		for(re int i=y,k=1;i>=lwr[id[y]];--i,++k)
			sucsum[i]+=k*z;
		sum[id[y]]+=(y-x+1)*z;
		// An empty line.
		for(re int i=id[y]+1;i<=id[n];++i)
			sum[i]+=(y-x+1)*z;
	}
	else{
		for(re int i=x,k=1;i<=y;++i,++k)
			presum[i]+=k*z;
		for(re int i=y+1,k=y-x+1;i<=upr[id[x]];++i)
			presum[i]+=k*z;
		for(re int i=y,k=1;i>=x;--i,++k)
			sucsum[i]+=k*z;
		for(re int i=x-1,k=y-x+1;i>=lwr[id[x]];--i)
			sucsum[i]+=k*z;
		sum[id[x]]+=(y-x+1)*z;
		// An empty line.
		for(re int i=id[x]+1;i<=id[n];++i)
			sum[i]+=(y-x+1)*z;
	}
}

inline long long query(re int x,re int y){
	return sucsum[x]+(upr[id[x]]-x+1)*add[id[x]]+presum[y]+(y-lwr[id[y]]+1)*add[id[y]]+sum[id[y]-1]-sum[id[x]];
}

int main(){
	freopen("F:/clt/challestends-code-set/Documentaries/Croi0001/D2T3/dl11.in","r",stdin);
	freopen("LGT69650.out","w",stdout);
	cltstream::read(n);
	cltstream::read(m);
	sq=sqrt(n);
	for(re int i=1;i<=n;++i){
		id[i]=(i-1)/sq+1;
		cltstream::read(p[i]);
		cltstream::read(w[i]);
		presum[p[i]]+=w[i];
		sucsum[p[i]]+=w[i];
		++cnt[p[i]];
		cltstream::read(l[i]);
		++tms[id[i]][l[i]];
		cltstream::read(r[i]);
		if(r[i]<n)
			--tms[id[i]][r[i]+1];
	}
	for(re int i=1;i<=id[n];++i){
		lwr[i]=(i-1)*sq+1;
		upr[i]=min(i*sq,n);
		for(re int j=lwr[i]+1;j<=upr[i];++j)
			presum[j]+=presum[j-1];
		for(re int j=upr[i]-1;j>=lwr[i];--j)
			sucsum[j]+=sucsum[j+1];
		sum[i]=sum[i-1]+presum[upr[i]];
	}
	for(re int i=1;i<=id[n];++i){
		for(re int j=1;j<=n;++j){
			tms[i][j]+=tms[i][j-1];
			ans[i]+=tms[i][j]*query(j,j);
		}
		for(re int j=1;j<=n;++j)
			tms[i][j]+=tms[i][j-1];
	}
	for(re int i=1;i<=m;++i){
		int opt,x,y,k;
		cltstream::read(opt);
		if(opt==1){
			cltstream::read(x);
			cltstream::read(y);
			re long long Ans=0;
			if(id[x]<id[y]){
				for(re int j=x;j<=upr[id[x]];++j)
					Ans+=query(l[j],r[j]);
				for(re int j=id[x]+1;j<=id[y]-1;++j)
					Ans+=ans[j];
				for(re int j=lwr[id[y]];j<=y;++j)
					Ans+=query(l[j],r[j]);
			}
			else{
				for(re int j=x;j<=y;++j)
					Ans+=query(l[j],r[j]);
			}
			cltstream::write(Ans,10);
		}
		if(opt==2){
			cltstream::read(x);
			cltstream::read(y);
			cltstream::read(k);
			update(x,y,k);
			for(re int j=1;j<=id[n];++j)
				ans[j]+=(tms[j][y]-tms[j][x-1])*k;
		}
		if(opt==3){
			cltstream::read(x);
			cltstream::read(k);
			update(x,x,1LL*k*cnt[x]);
			tag[x]+=k;
			for(re int j=1;j<=id[n];++j)
				ans[j]+=(tms[j][x]-tms[j][x-1])*k*cnt[x];
		}
		if(opt==4){
			cltstream::read(x);
			cltstream::read(y);
			w[x]+=tag[p[x]];
			update(p[x],p[x],-w[x]);
			update(y,y,w[x]);
			for(re int j=1;j<=id[n];++j)
				ans[j]+=(tms[j][y]-tms[j][y-1]-tms[j][p[x]]+tms[j][p[x]-1])*w[x];
			p[x]=y;
			w[x]-=tag[p[x]];
		}
	}
	clop();
	return 0;
}
