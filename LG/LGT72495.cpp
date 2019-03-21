#include<cstdio>
#include<cmath>
#define re register
#define maxn 100000
#define maxs0 160
#define maxs1 320

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

int n,m,sq0,sq1;
int id0[maxn+1],id1[maxn+1],lwr0[maxs0+1],lwr1[maxs1+1],upr0[maxs0+1],upr1[maxs1+1];
int a[maxn+1][4];
long long sum[maxs0+1][maxs1+1],pre[maxs0+1][maxn+1],suf[maxs0+1][maxn+1],tag[maxs0+1][maxs1+1],res[maxs0+1];

inline void update(re int p,re int l,re int r,re long long x){
	re int L=id1[l],R=id1[r];
	if(L<R){
		sum[p][L]+=1LL*(upr1[L]-l+1)*x;
		for(re int i=l,k=1;i<=upr1[L];++i,++k)
			pre[p][i]+=1LL*k*x;
		for(re int i=upr1[L],k=1;i>=l;--i,++k)
			suf[p][i]+=1LL*k*x;
		for(re int i=l-1,k=upr1[L]-l+1;i>=lwr1[L];--i)
			suf[p][i]+=1LL*k*x;
		for(re int i=L+1,k=upr1[L+1]-l+1;i<=R-1;++i,k+=sq1){
			sum[p][i]+=1LL*k*x;
			tag[p][i]+=x;
		}
		sum[p][R]+=1LL*(r-l+1)*x;
		for(re int i=r,k=1;i>=lwr1[R];--i,++k)
			suf[p][i]+=1LL*k*x;
		for(re int i=lwr1[R],k=1;i<=r;++i,++k)
			pre[p][i]+=1LL*k*x;
		for(re int i=r+1,k=r-lwr1[R]+1;i<=upr1[R];++i)
			pre[p][i]+=1LL*k*x;
	}
	else{
		sum[p][L]+=1LL*(r-l+1)*x;
		for(re int i=l,k=1;i<=r;++i,++k)
			pre[p][i]+=1LL*k*x;
		for(re int i=r+1,k=r-l+1;i<=upr1[L];++i)
			pre[p][i]+=1LL*k*x;
		for(re int i=r,k=1;i>=l;--i,++k)
			suf[p][i]+=1LL*k*x;
		for(re int i=l-1,k=r-l+1;i>=lwr1[L];--i)
			suf[p][i]+=1LL*k*x;
	}
	for(re int i=R+1,k=r-l+1;i<=id1[n];++i)
		sum[p][i]+=1LL*k*x;
}

inline long long query(re int p,re int l,re int r){
	re int L=id1[l],R=id1[r];
	return sum[p][R-1]-sum[p][L]+suf[p][l]+pre[p][r]+tag[p][L]*(upr1[L]-l+1)+tag[p][R]*(r-lwr1[R]+1);
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq0=2*sqrt(n);
	sq1=sqrt(n);
	for(re int i=1;i<=n;++i){
		id0[i]=(i-1)/sq0+1;
		id1[i]=(i-1)/sq1+1;
	}
	for(re int i=1;i<=id0[n];++i){
		lwr0[i]=(i-1)*sq0+1;
		upr0[i]=i*sq0;
	}
	for(re int i=1;i<=id1[n];++i){
		lwr1[i]=(i-1)*sq1+1;
		upr1[i]=i*sq1;
	}
	upr0[id0[n]]=upr1[id1[n]]=n;
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i][0]);
		cltstream::read(a[i][1]);
		cltstream::read(a[i][2]);
		cltstream::read(a[i][3]);
		update(0,a[i][0],a[i][0],a[i][1]);
	}
	for(re int i=1;i<=n;++i){
		res[id0[i]]+=query(0,a[i][2],a[i][3]);
		update(id0[i],a[i][2],a[i][3],1);
	}
	for(re int i=1;i<=m;++i){
		int opt;
		cltstream::read(opt);
		if(opt==1){
			int l,r;
			cltstream::read(l);
			cltstream::read(r);
			re int L=id0[l],R=id0[r];
			re long long ans=0;
			if(L<R){
				for(re int j=l;j<=upr0[L];++j)
					ans+=query(0,a[j][2],a[j][3]);
				for(re int j=L+1;j<=R-1;++j)
					ans+=res[j];
				for(re int j=lwr0[R];j<=r;++j)
					ans+=query(0,a[j][2],a[j][3]);
			}
			else
				for(re int j=l;j<=r;++j)
					ans+=query(0,a[j][2],a[j][3]);
			cltstream::write(ans,10);
		}
		if(opt==2){
			int l,r;
			long long x;
			cltstream::read(l);
			cltstream::read(r);
			cltstream::read(x);
			update(0,l,r,x);
			for(re int j=1;j<=id0[n];++j)
				res[j]+=1LL*query(j,l,r)*x;
		}
		if(opt==3){
			int x,l,r;
			cltstream::read(x);
			cltstream::read(l);
			cltstream::read(r);
			res[id0[x]]+=query(0,l,r)-query(0,a[x][2],a[x][3]);
			update(id0[x],l,r,1);
			update(id0[x],a[x][2],a[x][3],-1);
			a[x][2]=l;
			a[x][3]=r;
		}
	}
	clop();
	return 0;
}
