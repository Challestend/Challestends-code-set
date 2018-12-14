#include<cstdio>
#include<algorithm>
#define re register
#define maxn 20000
#define maxm 2000
#define maxs 145
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

int n,m,sq,ropcnt;
int id[maxn+1],a[maxn+1],p[maxn+1],bit[maxn+1];
int cnt1[maxs+1][maxs+1],cnt2[maxs+1][maxn+1];

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
	cltstream::read(n);
	for(;(sq+1)*(sq+1)<=n;++sq);
	for(re int i=1;i<=n;++i){
		id[i]=(i-1)/sq+1;
		cltstream::read(a[i]);
		p[++p[0]]=a[i];
	}
	std::sort(p+1,p+p[0]+1);
	p[0]=std::unique(p+1,p+p[0]+1)-p-1;
	for(re int i=1;i<=n;++i){
		a[i]=std::lower_bound(p+1,p+p[0]+1,a[i])-p;
		ropcnt+=i-getsum(a[i])-1;
		update(a[i]);
		++cnt1[id[i]][id[a[i]]];
		++cnt2[id[i]][a[i]];
	}
	cltstream::write(ropcnt,10);
	for(re int i=1;i<=id[n];++i){
		for(re int j=1;j<=id[n];++j)
			cnt1[i][j]+=cnt1[i-1][j];
		for(re int j=1;j<=p[0];++j)
			cnt2[i][j]+=cnt2[i-1][j];
	}
	cltstream::read(m);
	for(re int i=1;i<=m;++i){
		re int x,y;
		cltstream::read(x);
		cltstream::read(y);
		if(x>y)
			std::swap(x,y);
		re int l=x+1,r=y-1;
		for(re int j=l;j<=id[l]*sq&&j<=r;++j)
			ropcnt+=(a[j]>a[x])-(a[j]>a[y])-(a[j]<a[x])+(a[j]<a[y]);
		if(id[l]<id[r]){
			for(re int j=(id[r]-1)*sq+1;j<=r;++j)
				ropcnt+=(a[j]>a[x])-(a[j]>a[y])-(a[j]<a[x])+(a[j]<a[y]);
			for(re int j=1;j<id[a[x]];++j)
				ropcnt-=cnt1[id[r]-1][j]-cnt1[id[l]][j];
			for(re int j=(id[a[x]]-1)*sq+1;j<=id[a[x]]*sq&&j<=p[0];++j){
				if(j<a[x])
					ropcnt-=cnt2[id[r]-1][j]-cnt2[id[l]][j];
				if(j>a[x])
					ropcnt+=cnt2[id[r]-1][j]-cnt2[id[l]][j];
			}
			for(re int j=id[a[x]]+1;j<=id[n];++j)
				ropcnt+=cnt1[id[r]-1][j]-cnt1[id[l]][j];
			for(re int j=1;j<id[a[y]];++j)
				ropcnt+=cnt1[id[r]-1][j]-cnt1[id[l]][j];
			for(re int j=(id[a[y]]-1)*sq+1;j<=id[a[y]]*sq&&j<=p[0];++j){
				if(j<a[y])
					ropcnt+=cnt2[id[r]-1][j]-cnt2[id[l]][j];
				if(j>a[y])
					ropcnt-=cnt2[id[r]-1][j]-cnt2[id[l]][j];
			}
			for(re int j=id[a[y]]+1;j<=id[n];++j)
				ropcnt-=cnt1[id[r]-1][j]-cnt1[id[l]][j];
		}
		if(a[x]<a[y])
			++ropcnt;
		if(a[x]>a[y])
			--ropcnt;
		for(re int j=id[x];j<=id[n];++j){
			--cnt1[j][id[a[x]]];
			++cnt1[j][id[a[y]]];
			--cnt2[j][a[x]];
			++cnt2[j][a[y]];
		}
		for(re int j=id[y];j<=id[n];++j){
			--cnt1[j][id[a[y]]];
			++cnt1[j][id[a[x]]];
			--cnt2[j][a[y]];
			++cnt2[j][a[x]];
		}
		std::swap(a[x],a[y]);
		cltstream::write(ropcnt,10);
	}
	clop();
	return 0;
}
