#include<cstdio>
#include<algorithm>
#define re register
#define maxn 60000
#define maxm 90000
#define maxval 1000000

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

int n,m,q,mx;
int val[maxn+1],bit[maxn+(maxval<<2)+1];
struct Point{
	int tp,t,x,y;
};
Point a[maxn+(maxm<<2)+1],b[maxn+(maxm<<2)+1];
int ans[maxm+1];

inline bool operator<(re Point p1,re Point p2){
	if(p1.t!=p2.t)
		return p1.t<p2.t;
	else
		if(p1.x!=p2.x)
			return p1.x<p2.x;
		else
			if(p1.y!=p2.y)
				return p1.y<p2.y;
			else
				return !p1.tp;
}

inline void update(re int x,re int y){
	for(;x<=mx;x+=x&(-x))
		bit[x]+=y;
}

inline int getsum(re int x){
	re int res=0;
	for(;x>=1;x-=x&(-x))
		res+=bit[x];
	return res;
}

void solve(re int l,re int r){
	if(l<r){
		re int mid=(l+r)>>1;
		solve(l,mid);
		solve(mid+1,r);
		re int L=l,R=mid+1,X=l;
		for(;L<=mid&&R<=r;)
			if(a[L].x<=a[R].x){
				if(!a[L].tp)
					update(a[L].y,1);
				b[X++]=a[L++];
			}
			else{
				if(a[R].tp)
					ans[a[R].t]+=a[R].tp*getsum(a[R].y);
				b[X++]=a[R++];
			}
		for(;L<=mid;){
			if(!a[L].tp)
				update(a[L].y,1);
			b[X++]=a[L++];
		}
		for(;R<=r;){
			if(a[R].tp)
				ans[a[R].t]+=a[R].tp*getsum(a[R].y);
			b[X++]=a[R++];
		}
		for(re int i=l;i<=mid;++i)
			if(!a[i].tp)
				update(a[i].y,-1);
		for(re int i=l;i<=r;++i)
			a[i]=b[i];
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		cltstream::read(val[i]);
		a[i].x=i-val[i];
		a[i].y=i+val[i];
		mx=std::max(mx,a[i].y);
	}
	re int cnt=n;
	for(re int i=1;i<=m;++i){
		re char opt=cltstream::gc();
		for(;opt!='M'&&opt!='Q';opt=cltstream::gc());
		int p,k;
		cltstream::read(p);
		cltstream::read(k);
		if(opt=='M'){
			val[p]=k;
			a[++cnt].t=q;
			a[cnt].x=p-k;
			a[cnt].y=p+k;
			mx=std::max(mx,a[cnt].y);
		}
		else{
			a[++cnt].t=q;
			a[cnt].x=p-val[p]+k;
			a[cnt].y=p+val[p]+k;
			a[cnt].tp=1;
			mx=std::max(mx,a[cnt].y);
			// An empty line.
			a[++cnt].t=q;
			a[cnt].x=p-val[p]+k;
			a[cnt].y=p+val[p]-k-1;
			a[cnt].tp=-1;
			// An empty line.
			a[++cnt].t=q;
			a[cnt].x=p-val[p]-k-1;
			a[cnt].y=p+val[p]+k;
			a[cnt].tp=-1;
			// An empty line.
			a[++cnt].t=q;
			a[cnt].x=p-val[p]-k-1;
			a[cnt].y=p+val[p]-k-1;
			a[cnt].tp=1;
			// An empty line.
			++q;
		}
	}
	std::sort(a+1,a+cnt+1);
	solve(1,cnt);
	for(re int i=0;i<q;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
