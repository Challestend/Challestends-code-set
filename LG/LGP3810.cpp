#include<cstdio>
#include<algorithm>
#define re register
#define maxn 100000
#define maxm 200000

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

int n,m;
int bit[maxm+1];
struct node{
	int a,b,c,w,v;
};
node mp[maxn+1],tmp[maxn+1];
int ans[maxn+1];

inline bool operator<(re node p1,re node p2){
	if(p1.a!=p2.a)
		return p1.a<p2.a;
	else
		if(p1.b!=p2.b)
			return p1.b<p2.b;
		else
			return p1.c<p2.c;
}

inline bool operator==(re node p1,re node p2){
	return p1.a==p2.a&&p1.b==p2.b&&p1.c==p2.c;
}

inline void modify(re int x,re int y){
	for(;x<=m;x+=x&(-x))
		bit[x]+=y;
}

inline int query(re int x){
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
			if(mp[L].b<=mp[R].b){
				modify(mp[L].c,mp[L].w);
				tmp[X++]=mp[L++];
			}
			else{
				mp[R].v+=query(mp[R].c);
				tmp[X++]=mp[R++];
			}
		for(;L<=mid;){
			modify(mp[L].c,mp[L].w);
			tmp[X++]=mp[L++];
		}
		for(;R<=r;){
			mp[R].v+=query(mp[R].c);
			tmp[X++]=mp[R++];
		}
		for(re int i=l;i<=mid;++i)
			modify(mp[i].c,-mp[i].w);
		for(re int i=l;i<=r;++i)
			mp[i]=tmp[i];
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		cltstream::read(mp[i].a);
		cltstream::read(mp[i].b);
		cltstream::read(mp[i].c);
		mp[i].w=1;
	}
	std::sort(mp+1,mp+n+1);
	re int cnt=1;
	for(re int i=2;i<=n;++i)
		if(mp[i]==mp[cnt])
			++mp[cnt].w;
		else
			mp[++cnt]=mp[i];
	solve(1,cnt);
	for(re int i=1;i<=cnt;++i)
		ans[mp[i].w+mp[i].v-1]+=mp[i].w;
	for(re int i=0;i<n;++i)
		cltstream::write(ans[i],10);
	clop();
	return 0;
}
