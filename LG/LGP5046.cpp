#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define maxn 100000
#define maxs 320
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

int n,m,sq;
long long lastans;
int id[maxn+1],a[maxn+1],pos[maxn+1],bit[maxn+1],cnt[maxs+1][maxn+2],lc[maxn+1],rc[maxn+1];
long long ans[maxs+1][maxs+1];
int mrk[maxs+1],rnk[maxs+1][maxs+1][(maxs<<1)+1],tmp[(maxs<<1)+1];

inline void update(re int x){
	for(;x<=n;x+=lowbit(x))
		++bit[x];
}

inline int getsum(re int x){
	re int res=0;
	for(;x>=1;x-=lowbit(x))
		res+=bit[x];
	return res;
}

int main(){
	freopen("LGP5046.in","r",stdin);
	freopen("LGP5046.out","w",stdout);
	cltstream::read(n);
	cltstream::read(m);
	for(;(sq+1)*(sq+1)<=n;++sq);
	for(re int i=1;i<=n;++i){
		id[i]=i<=sq?1:id[i-sq]+1;
		cltstream::read(a[i]);
		pos[a[i]]=i;
		cnt[id[i]][a[i]-1]=1;
	}
	for(re int i=1;i<=id[n];++i)
		for(re int j=n;j>=1;--j)
			cnt[i][j]+=cnt[i][j+1];
	for(re int i=1;i<=id[n];++i)
		for(re int j=n;j>=1;--j)
			cnt[i][j]+=cnt[i-1][j];
	for(re int i=1;i<=n;++i){
		if(id[i]==id[i-1])
			lc[i]+=lc[i-1];
		else
			memset(bit,0,sizeof(bit));
		lc[i]+=i-(id[i]-1)*sq-getsum(a[i])-1;
		update(a[i]);
	}
	for(re int i=n;i>=1;--i){
		if(id[i]==id[i+1])
			rc[i]+=rc[i+1];
		else
			memset(bit,0,sizeof(bit));
		rc[i]+=getsum(a[i]);
		update(a[i]);
	}
	for(re int i=1;i<=id[n];++i)
		ans[i][i]=rc[(i-1)*sq+1];
	for(re int i=1;i<=id[n];++i)
		for(re int j=i+1;j<=id[n];++j){
			ans[i][j]=ans[i][j-1]+ans[j][j];
			for(re int k=(j-1)*sq+1;k<=j*sq&&k<=n;++k)
				ans[i][j]+=cnt[j-1][a[k]]-cnt[i-1][a[k]];
		}
	for(re int i=1;i<=n;++i){
		for(re int j=id[pos[i]]-1;j>=1;--j)
			rnk[j][id[pos[i]]][pos[i]-(id[pos[i]]-2)*sq]=mrk[j]+mrk[id[pos[i]]]+1;
		rnk[id[pos[i]]][id[pos[i]]][pos[i]-(id[pos[i]]-1)*sq]=mrk[id[pos[i]]]+1;
		for(re int j=id[pos[i]]+1;j<=id[n];++j)
			rnk[id[pos[i]]][j][pos[i]-(id[pos[i]]-1)*sq]=mrk[id[pos[i]]]+mrk[j]+1;
		++mrk[id[pos[i]]];
	}
	for(re int i=1;i<=m;++i){
		re long long l,r;
		cltstream::read(l);
		cltstream::read(r);
		// l^=lastans;
		// r^=lastans;
		if(l>r)
			l^=r^=l^=r;
		memset(tmp,0,sizeof(tmp));
		if(id[l]<id[r]){
			lastans=ans[id[l]+1][id[r]-1]+rc[l]+lc[r];
			for(re int j=l;j<=id[l]*sq;++j){
				lastans+=(id[r]-id[l]-1)*sq-cnt[id[r]-1][a[j]]+cnt[id[l]][a[j]];
				++tmp[rnk[id[l]][id[r]][j-(id[l]-1)*sq]-1];
			}
			for(re int j=(sq<<1);j>=1;--j)
				tmp[j-1]+=tmp[j];
			for(re int j=(id[r]-1)*sq+1;j<=r;++j)
				lastans+=cnt[id[r]-1][a[j]]-cnt[id[l]][a[j]]+tmp[rnk[id[l]][id[r]][j-(id[r]-2)*sq]];
		}
		else{
			lastans=lc[r];
			if(id[l]==id[l-1])
				lastans-=lc[l-1];
			for(re int j=(id[l]-1)*sq+1;j<l;++j)
				++tmp[rnk[id[j]][id[j]][j-(id[j]-1)*sq]-1];
			for(re int j=sq;j>=1;--j)
				tmp[j-1]+=tmp[j];
			for(re int j=l;j<=r;++j)
				lastans-=tmp[rnk[id[j]][id[j]][j-(id[j]-1)*sq]];
		}
		cltstream::write(lastans,10);
	}
	clop();
	return 0;
}
