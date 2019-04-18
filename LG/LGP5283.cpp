#include<cstdio>
#include<algorithm>
#include<queue>
#define re register
#define maxn 500000
#define maxlog 32

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

int n,m,vc;
long long ans;
unsigned a[maxn+1];
int b[maxn+1],tmp[maxlog+1],ch[maxn*maxlog+1][2],cnt[maxn*maxlog+1];
std::priority_queue<std::pair<unsigned,int> > h;

inline void Insert(re unsigned x){
	for(re int i=1;i<=maxlog;++i,x>>=1)
		tmp[i]=x&1;
	++cnt[1];
	for(re int i=maxlog,p=1;i>=1;--i){
		ch[p][tmp[i]]||(ch[p][tmp[i]]=++vc);
		++cnt[p=ch[p][tmp[i]]];
	}
}

inline unsigned Query(re unsigned x,re int k){
	re unsigned res=0;
	for(re int i=1;i<=maxlog;++i,x>>=1)
		tmp[i]=x&1;
	for(re int i=maxlog,p=1;i>=1;--i)
		if(k<=cnt[ch[p][tmp[i]^1]]){
			res=res<<1|1;
			p=ch[p][tmp[i]^1];
		}
		else{
			k-=cnt[ch[p][tmp[i]^1]];
			res=res<<1;
			p=ch[p][tmp[i]];
		}
	return res;
}

int main(){
	vc=1;
	cltstream::read(n);
	cltstream::read(m);
	m<<=1;
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		a[i]^=a[i-1];
	}
	for(re int i=0;i<=n;++i)
		Insert(a[i]);
	for(re int i=0;i<=n;++i)
		h.push(std::make_pair(Query(a[i],++b[i]),i));
	for(re int i=1;i<=m;++i){
		ans+=h.top().first;
		re int x=h.top().second;
		h.pop();
		h.push(std::make_pair(Query(a[x],++b[x]),x));
	}
	cltstream::write(ans>>1);
	clop();
	return 0;
}
