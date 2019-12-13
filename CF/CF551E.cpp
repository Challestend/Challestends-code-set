#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 500000
#define maxs 710
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define pli std::pair<long long,int>
#define mp(a,b) std::make_pair(a,b)

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
int id[maxn+1],cnt[maxn+1];
long long a[maxn+1];
pli vec[maxs+1][maxs+1];
long long mn[maxs+1],mx[maxs+1],add[maxs+1];

inline void build(re int x){
	mn[x]=1E18;
	mx[x]=add[x]=0;
	for(re int i=(x-1)*sq+1;i<=x*sq&&i<=n;++i){
		vec[x][++cnt[x]]=mp(a[i],i);
		mn[x]=min(mn[x],a[i]);
		mx[x]=max(mx[x],a[i]);
	}
	std::sort(vec[x]+1,vec[x]+cnt[x]+1);
}

inline void modify(re int x,re long long y,re int L,re int R){
	re int cnt1=0,cnt2=0,l1=1,l2=1,r=1;
	pli tmp1[maxs+1],tmp2[maxs+1];
	for(re int i=1;i<=cnt[x];++i)
		if(vec[x][i].second>=L&&vec[x][i].second<=R){
			tmp1[++cnt1]=vec[x][i];
			tmp1[cnt1].first+=y;
		}
		else
			tmp2[++cnt2]=vec[x][i];
	for(;l1<=cnt1&&l2<=cnt2;)
		vec[x][r++]=tmp1[l1]<=tmp2[l2]?tmp1[l1++]:tmp2[l2++];
	for(;l1<=cnt1;)
		vec[x][r++]=tmp1[l1++];
	for(;l2<=cnt2;)
		vec[x][r++]=tmp2[l2++];
	mn[x]=vec[x][1].first;
	mx[x]=vec[x][cnt[x]].first;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	sq=sqrt(n);
	for(re int i=1;i<=n;++i){
		id[i]=(i-1)/sq+1;
		cltstream::read(a[i]);
	}
	for(re int i=1;i<=id[n];++i)
		build(i);
	for(re int i=1;i<=m;++i){
		int opt,l,r,x;
		cltstream::read(opt);
		if(opt==1){
			cltstream::read(l);
			cltstream::read(r);
			cltstream::read(x);
			re int L=id[l],R=id[r];
			if(L<R){
				modify(L,x,l,L*sq);
				for(re int j=L+1;j<=R-1;++j){
					mn[j]+=x;
					mx[j]+=x;
					add[j]+=x;
				}
				modify(R,x,(R-1)*sq+1,r);
			}
			else
				modify(L,x,l,r);
		}
		else{
			cltstream::read(x);
			re int L=0,R=0;
			for(re int j=1;j<=id[n];++j){
				re int tmp=std::lower_bound(vec[j]+1,vec[j]+cnt[j]+1,x-add[j])-vec[j];
				if(tmp<=cnt[j]&&vec[j][tmp].first+add[j]==x){
					L=vec[j][tmp].second;
					break;
				}
			}
			for(re int j=id[n];j>=1;--j){
				re int tmp=std::upper_bound(vec[j]+1,vec[j]+cnt[j]+1,x-add[j])-vec[j]-1;
				if(tmp>=1&&vec[j][tmp].first+add[j]==x){
					R=vec[j][tmp].second;
					break;
				}
			}
			cltstream::write(L?R-L:-1,10);
		}
	}
	clop();
	return 0;
}
