#include<cstdio>
#include<queue>
#define re register
#define maxn 10000
#define maxm 200000
#define htp std::pair<long long,int>
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

int n,m,s,t,ec;
int des[(maxm<<1)+1],len[(maxm<<1)+1],suc[(maxm<<1)+1],las[maxn+1],vis[maxn+1],pre[maxn+1];
long long dis[maxn+1];
std::priority_queue<htp,std::vector<htp >,std::greater<htp > > p;

inline void connect(re int x,re int y,re int z){
	des[++ec]=y;
	len[ec]=z;
	suc[ec]=las[x];
	las[x]=ec;
}

void print(re int x){
	if(pre[x])
		print(pre[x]);
	printf("%d ",x);
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(s);
	cltstream::read(t);
	for(re int i=1;i<=m;++i){
		re int f,x,y,z;
		cltstream::read(f);
		cltstream::read(x);
		cltstream::read(y);
		cltstream::read(z);
		if(f){
			connect(x,y,z);
			// connect(y,x,z);
		}
	}
	for(re int i=1;i<=n;++i)
		dis[i]=9e18;
	p.push(mp(dis[s]=0,s));
	for(re int i=1;i<=n;++i){
		for(;vis[p.top().second];p.pop());
		re int x=p.top().second;
		p.pop();
		vis[x]=1;
		if(x==t)
			break;
		for(re int j=las[x];j;j=suc[j])
			if(dis[des[j]]>dis[x]+len[j]){
				p.push(mp(dis[des[j]]=dis[x]+len[j],des[j]));
				pre[des[j]]=x;
			}
	}
	if(!pre[t])
		printf("My gold!!!");
	else{
		printf("%lld\n",dis[t]);
		print(t);
	}
	return 0;
}
