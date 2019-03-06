#include<cstdio>
#include<cmath>
#define re register
#define maxn 50000
#define maxs 230
#define mod 1000000007
#define swap(a,b) a^=b,b^=a,a^=b

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
long long ans;
int id[maxn+1],a[maxn+1],b[maxn+1];
int cnt[maxn+1],cnt1[maxs+1][maxs+1],cnt2[maxs+1][maxn+1],tmpcnt1[maxs+1],tmpcnt2[maxn+1];
long long sum[maxn+1],sum1[maxs+1][maxs+1],sum2[maxs+1][maxn+1],tmpsum1[maxs+1],tmpsum2[maxn+1];

inline void update(re int x,re int y){
	for(;x<=n;x+=x&(-x)){
		++cnt[x];
		sum[x]+=y;
	}
}

inline int getcnt(re int x){
	re int res=0;
	for(;x>=1;x-=x&(-x))
		res+=cnt[x];
	return res;
}

inline long long getsum(re int x){
	re long long res=0;
	for(;x>=1;x-=x&(-x))
		res+=sum[x];
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq=sqrt(n);
	for(re int i=1;i<=n;++i)
		id[i]=(i-1)/sq+1;
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		cltstream::read(b[i]);
		for(re int j=id[i];j<=id[n];++j){
			++cnt1[j][id[a[i]]];
			++cnt2[j][a[i]];
			sum1[j][id[a[i]]]+=b[i];
			sum2[j][a[i]]+=b[i];
		}
		ans+=(getsum(n)-getsum(a[i]))+1LL*(getcnt(n)-getcnt(a[i]))*b[i];
		update(a[i],b[i]);
	}
	for(re int i=1;i<=m;++i){
		int l,r;
		cltstream::read(l);
		cltstream::read(r);
		if(l>r)
			swap(l,r);
		if(l<r){
			re int L=id[l],R=id[r];
			if(L<R){
				for(re int j=l+1;j<=L*sq;++j){
					++tmpcnt1[id[a[j]]];
					++tmpcnt2[a[j]];
					tmpsum1[id[a[j]]]+=b[j];
					tmpsum2[a[j]]+=b[j];
				}
				for(re int j=(R-1)*sq+1;j<=r-1;++j){
					++tmpcnt1[id[a[j]]];
					++tmpcnt2[a[j]];
					tmpsum1[id[a[j]]]+=b[j];
					tmpsum2[a[j]]+=b[j];
				}
				for(re int j=1;j<=id[a[l]]-1;++j)
					ans-=(sum1[R-1][j]-sum1[L][j]+tmpsum1[j])+1LL*(cnt1[R-1][j]-cnt1[L][j]+tmpcnt1[j])*b[l];
				for(re int j=(id[a[l]]-1)*sq+1;j<=a[l]-1;++j)
					ans-=(sum2[R-1][j]-sum2[L][j]+tmpsum2[j])+1LL*(cnt2[R-1][j]-cnt2[L][j]+tmpcnt2[j])*b[l];
				for(re int j=a[l]+1;j<=id[a[l]]*sq&&j<=n;++j)
					ans+=(sum2[R-1][j]-sum2[L][j]+tmpsum2[j])+1LL*(cnt2[R-1][j]-cnt2[L][j]+tmpcnt2[j])*b[l];
				for(re int j=id[a[l]]+1;j<=id[n];++j)
					ans+=(sum1[R-1][j]-sum1[L][j]+tmpsum1[j])+1LL*(cnt1[R-1][j]-cnt1[L][j]+tmpcnt1[j])*b[l];
				for(re int j=1;j<=id[a[r]]-1;++j)
					ans+=(sum1[R-1][j]-sum1[L][j]+tmpsum1[j])+1LL*(cnt1[R-1][j]-cnt1[L][j]+tmpcnt1[j])*b[r];
				for(re int j=(id[a[r]]-1)*sq+1;j<=a[r]-1;++j)
					ans+=(sum2[R-1][j]-sum2[L][j]+tmpsum2[j])+1LL*(cnt2[R-1][j]-cnt2[L][j]+tmpcnt2[j])*b[r];
				for(re int j=a[r]+1;j<=id[a[r]]*sq&&j<=n;++j)
					ans-=(sum2[R-1][j]-sum2[L][j]+tmpsum2[j])+1LL*(cnt2[R-1][j]-cnt2[L][j]+tmpcnt2[j])*b[r];
				for(re int j=id[a[r]]+1;j<=id[n];++j)
					ans-=(sum1[R-1][j]-sum1[L][j]+tmpsum1[j])+1LL*(cnt1[R-1][j]-cnt1[L][j]+tmpcnt1[j])*b[r];
				for(re int j=l+1;j<=L*sq;++j){
					--tmpcnt1[id[a[j]]];
					--tmpcnt2[a[j]];
					tmpsum1[id[a[j]]]-=b[j];
					tmpsum2[a[j]]-=b[j];
				}
				for(re int j=(R-1)*sq+1;j<=r-1;++j){
					--tmpcnt1[id[a[j]]];
					--tmpcnt2[a[j]];
					tmpsum1[id[a[j]]]-=b[j];
					tmpsum2[a[j]]-=b[j];
				}
			}
			else{
				for(re int j=l+1;j<=r-1;++j){
					++tmpcnt1[id[a[j]]];
					++tmpcnt2[a[j]];
					tmpsum1[id[a[j]]]+=b[j];
					tmpsum2[a[j]]+=b[j];
				}
				for(re int j=1;j<=id[a[l]]-1;++j)
					ans-=tmpsum1[j]+1LL*tmpcnt1[j]*b[l];
				for(re int j=(id[a[l]]-1)*sq+1;j<=a[l]-1;++j)
					ans-=tmpsum2[j]+1LL*tmpcnt2[j]*b[l];
				for(re int j=a[l]+1;j<=id[a[l]]*sq&&j<=n;++j)
					ans+=tmpsum2[j]+1LL*tmpcnt2[j]*b[l];
				for(re int j=id[a[l]]+1;j<=id[n];++j)
					ans+=tmpsum1[j]+1LL*tmpcnt1[j]*b[l];
				for(re int j=1;j<=id[a[r]]-1;++j)
					ans+=tmpsum1[j]+1LL*tmpcnt1[j]*b[r];
				for(re int j=(id[a[r]]-1)*sq+1;j<=a[r]-1;++j)
					ans+=tmpsum2[j]+1LL*tmpcnt2[j]*b[r];
				for(re int j=a[r]+1;j<=id[a[r]]*sq&&j<=n;++j)
					ans-=tmpsum2[j]+1LL*tmpcnt2[j]*b[r];
				for(re int j=id[a[r]]+1;j<=id[n];++j)
					ans-=tmpsum1[j]+1LL*tmpcnt1[j]*b[r];
				for(re int j=l+1;j<=r-1;++j){
					--tmpcnt1[id[a[j]]];
					--tmpcnt2[a[j]];
					tmpsum1[id[a[j]]]-=b[j];
					tmpsum2[a[j]]-=b[j];
				}
			}
			for(re int j=L;j<=id[n];++j){
				--cnt1[j][id[a[l]]];
				--cnt2[j][a[l]];
				sum1[j][id[a[l]]]-=b[l];
				sum2[j][a[l]]-=b[l];
				++cnt1[j][id[a[r]]];
				++cnt2[j][a[r]];
				sum1[j][id[a[r]]]+=b[r];
				sum2[j][a[r]]+=b[r];
			}
			for(re int j=R;j<=id[n];++j){
				--cnt1[j][id[a[r]]];
				--cnt2[j][a[r]];
				sum1[j][id[a[r]]]-=b[r];
				sum2[j][a[r]]-=b[r];
				++cnt1[j][id[a[l]]];
				++cnt2[j][a[l]];
				sum1[j][id[a[l]]]+=b[l];
				sum2[j][a[l]]+=b[l];
			}
			swap(a[l],a[r]);
			swap(b[l],b[r]);
			if(a[l]>a[r])
				ans+=b[l]+b[r];
			else
				ans-=b[l]+b[r];
		}
		cltstream::write(ans%mod,10);
	}
	clop();
	return 0;
}
