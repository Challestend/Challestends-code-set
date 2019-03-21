#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
#include<cmath>
#define re register
#define maxn 100000
#define maxd 181
#define maxs 317
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define merge(x,y) (dep[x]<=dep[y]?(fst[0][x]=y,dep[y]=max(dep[y],dep[x]+1),size[y]+=size[x],y):(fst[0][y]=x,dep[x]=max(dep[x],dep[y]+1),size[x]+=size[y],x))

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
			putchar(45),x=-x;
		if(!x)
			putchar(48);
		else{
			int digit[22];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];putchar(digit[digit[0]--]^48));
		}
		if(text>=0)
			putchar(text);
	}
}

int n,m,sq1,sq2;
short id1[maxn+1],id2[maxn+1];
int a[maxn+1],opt[maxn+1][5],p[(maxn<<1)+1];
int fst[maxd+1][maxn+1],val[maxn+1];
short dep[maxn+1],size[maxn+1];
int cnt1[maxd+1][maxs+1],cnt2[maxd+1][maxn+1];

int find(re int x){
	if(fst[0][fst[0][x]]^fst[0][x]){
		re int ftr=fst[0][x];
		fst[0][x]=find(fst[0][x]),
		size[ftr]-=size[x];
	}
	return fst[0][x];
}

inline void modify(int& l,int& r,int& x,int& y){
	if(x==y)
		return;
	re int tmp=std::lower_bound(p+1,p+p[0]+1,x)-p;
	if(p[tmp]!=x)
		return;
	x=tmp,
	y=std::lower_bound(p+1,p+p[0]+1,y)-p;
	re int L=id1[l],R=id1[r],cnt=0;
	if(L^R){
		fst[L][x]=0;
		for(re int i=(L-1)*sq1+1;i<=l-1;++i)
			(!(val[find(i)]^x))&&(
				(fst[0][i]^i)&&(size[fst[0][i]]-=size[i]),
				fst[L][x]=!fst[L][x]?i:merge(i,fst[L][x]),
				fst[0][fst[L][x]]=fst[L][x],
				val[fst[L][x]]=x);
		for(re int i=l;i<=L*sq1;++i)
			(!(val[find(i)]^x))&&(
				(fst[0][i]^i)&&(size[fst[0][i]]-=size[i]),
				cnt+=size[i],
				fst[L][y]=!fst[L][y]?i:merge(i,fst[L][y]),
				fst[0][fst[L][y]]=fst[L][y],
				val[fst[L][y]]=y);
		cnt1[L][id2[x]]-=cnt,
		cnt2[L][x]-=cnt,
		cnt1[L][id2[y]]+=cnt,
		cnt2[L][y]+=cnt;
		for(re int i=L+1;i<=R-1;++i){
			if(fst[i][x])
				fst[i][y]=!fst[i][y]?fst[i][x]:merge(fst[i][x],fst[i][y]),
				fst[0][fst[i][y]]=fst[i][y],
				val[fst[i][y]]=y,
				fst[i][x]=0;
			cnt=cnt2[i][x]-cnt2[i-1][x],
			cnt1[i][id2[x]]-=cnt,
			cnt2[i][x]-=cnt,
			cnt1[i][id2[y]]+=cnt,
			cnt2[i][y]+=cnt;
		}
		fst[R][x]=0;
		for(re int i=r+1;i<=R*sq1&&i<=n;++i)
			(!(val[find(i)]^x))&&(
				(fst[0][i]^i)&&(size[fst[0][i]]-=size[i]),
				fst[R][x]=!fst[R][x]?i:merge(i,fst[R][x]),
				fst[0][fst[R][x]]=fst[R][x],
				val[fst[R][x]]=x);
		for(re int i=(R-1)*sq1+1;i<=r;++i)
			(!(val[find(i)]^x))&&(
				(fst[0][i]^i)&&(size[fst[0][i]]-=size[i]),
				cnt+=size[i],
				fst[R][y]=!fst[R][y]?i:merge(i,fst[R][y]),
				fst[0][fst[R][y]]=fst[R][y],
				val[fst[R][y]]=y);
		cnt1[R][id2[x]]-=cnt,
		cnt2[R][x]-=cnt,
		cnt1[R][id2[y]]+=cnt,
		cnt2[R][y]+=cnt;
	}
	else{
		fst[L][x]=0;
		for(re int i=(L-1)*sq1+1;i<=l-1;++i)
			(!(val[find(i)]^x))&&(
				(fst[0][i]^i)&&(size[fst[0][i]]-=size[i]),
				fst[L][x]=!fst[L][x]?i:merge(i,fst[L][x]),
				fst[0][fst[L][x]]=fst[L][x],
				val[fst[L][x]]=x);
		for(re int i=r+1;i<=L*sq1&&i<=n;++i)
			(!(val[find(i)]^x))&&(
				(fst[0][i]^i)&&(size[fst[0][i]]-=size[i]),
				fst[L][x]=!fst[L][x]?i:merge(i,fst[L][x]),
				fst[0][fst[L][x]]=fst[L][x],
				val[fst[L][x]]=x);
		for(re int i=l;i<=r;++i)
			(!(val[find(i)]^x))&&(
				(fst[0][i]^i)&&(size[fst[0][i]]-=size[i]),
				cnt+=size[i],
				fst[L][y]=!fst[L][y]?i:merge(i,fst[L][y]),
				fst[0][fst[L][y]]=fst[L][y],
				val[fst[L][y]]=y);
		cnt1[L][id2[x]]-=cnt,
		cnt2[L][x]-=cnt,
		cnt1[L][id2[y]]+=cnt,
		cnt2[L][y]+=cnt;
	}
	for(re int i=R+1;i<=id1[n];++i)
		cnt1[i][id2[x]]-=cnt,
		cnt2[i][x]-=cnt,
		cnt1[i][id2[y]]+=cnt,
		cnt2[i][y]+=cnt;
}

inline void query(int& l,int& r,int& x){
	re int L=id1[l],R=id1[r];
	if(L^R){
		for(re int i=l;i<=L*sq1;++i)
			++cnt1[0][id2[val[find(i)]]],
			++cnt2[0][val[fst[0][i]]];
		for(re int i=(R-1)*sq1+1;i<=r;++i)
			++cnt1[0][id2[val[find(i)]]],
			++cnt2[0][val[fst[0][i]]];
		for(re int i=1;;++i)
			if(x>cnt1[R-1][i]-cnt1[L][i]+cnt1[0][i])
				x-=cnt1[R-1][i]-cnt1[L][i]+cnt1[0][i];
			else{
				for(i=(i-1)*sq2+1;x>cnt2[R-1][i]-cnt2[L][i]+cnt2[0][i];x-=cnt2[R-1][i]-cnt2[L][i]+cnt2[0][i],++i);
				cltstream::write(p[i],10);
				break;
			}
		for(re int i=l;i<=L*sq1;++i)
			--cnt1[0][id2[val[fst[0][i]]]],
			--cnt2[0][val[fst[0][i]]];
		for(re int i=(R-1)*sq1+1;i<=r;++i)
			--cnt1[0][id2[val[fst[0][i]]]],
			--cnt2[0][val[fst[0][i]]];
	}
	else{
		for(re int i=l;i<=r;++i)
			++cnt1[0][id2[val[find(i)]]],
			++cnt2[0][val[fst[0][i]]];
		for(re int i=1;;++i)
			if(x>cnt1[0][i])
				x-=cnt1[0][i];
			else{
				for(i=(i-1)*sq2+1;x>cnt2[0][i];x-=cnt2[0][i],++i);
				cltstream::write(p[i],10);
				break;
			}
		for(re int i=l;i<=r;++i)
			--cnt1[0][id2[val[fst[0][i]]]],
			--cnt2[0][val[fst[0][i]]];
	}
}

int main(){
	cltstream::read(n),
	cltstream::read(m),
	sq1=1.75*sqrt(n);
	for(re int i=1;i<=n;++i)
		id1[i]=(i-1)/sq1+1;
	for(re int i=1;i<=n;++i)
		cltstream::read(a[i]),
		p[++p[0]]=a[i];
	for(re int i=1;i<=m;++i){
		cltstream::read(opt[i][0]);
		if(opt[i][0]&1)
			cltstream::read(opt[i][1]),
			cltstream::read(opt[i][2]),
			cltstream::read(opt[i][3]),
			cltstream::read(opt[i][4]),
			p[++p[0]]=opt[i][4];
		else
			cltstream::read(opt[i][1]),
			cltstream::read(opt[i][2]),
			cltstream::read(opt[i][3]);
	}
	std::sort(p+1,p+p[0]+1),
	p[0]=std::unique(p+1,p+p[0]+1)-p-1,
	sq2=sqrt(p[0]);
	for(re int i=1;i<=p[0];++i)
		id2[i]=(i-1)/sq2+1;
	for(re int i=1;i<=n;++i){
		a[i]=std::lower_bound(p+1,p+p[0]+1,a[i])-p,
		fst[0][i]=i,
		dep[i]=1,
		size[i]=1,
		fst[id1[i]][a[i]]=!fst[id1[i]][a[i]]?i:merge(i,fst[id1[i]][a[i]]),
		fst[0][fst[id1[i]][a[i]]]=fst[id1[i]][a[i]],
		val[fst[id1[i]][a[i]]]=a[i];
		for(re int j=id1[i];j<=id1[n];++j)
			++cnt1[j][id2[a[i]]],
			++cnt2[j][a[i]];
	}
	for(re int i=1;i<=m;++i)
		(opt[i][0]&1)?modify(opt[i][1],opt[i][2],opt[i][3],opt[i][4]):query(opt[i][1],opt[i][2],opt[i][3]);
	return 0;
}
