#include<cstdio>
#include<algorithm>
#define re register
#define maxn 300000
#define maxw 5

namespace cltstream{
	#define size 1048576
	char cltin[size+1],*ih=cltin,*it=cltin;
	inline char gc(){
		#ifdef ONLINE_JUDGE
			if(ih==it)
				it=cltin+fread(ih=cltin,1,size,stdin);
			return ih==it?EOF:*ih++;
		#else
			return getchar();
		#endif
	}

	char cltout[size+1],*oh=cltout,*ot=cltout+size;
	inline void pc(char c){
		if(oh==ot)
			fwrite(oh=cltout,1,size,stdout);
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

int w,n,m,sz=1;
struct node{
	int val,p[maxw+1];
};
node a[maxn+1],l,r;
int tmp[maxn+1];

inline bool cmp(re int p1,re int p2){
	return a[p1].val<a[p2].val;
}

int main(){
	cltstream::read(w);
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=w;++i)
		sz*=n;
	for(re int i=1;i<=sz;++i){
		cltstream::read(a[i].val);
		for(re int j=w,k=i-1;j>=1;--j,k/=n)
			a[i].p[j]=k%n+1;
	}
	for(re int i=1;i<=m;++i){
		int x;
		for(re int j=1;j<=w;++j)
			cltstream::read(l.p[j]);
		for(re int j=1;j<=w;++j)
			cltstream::read(r.p[j]);
		cltstream::read(x);
		tmp[0]=0;
		for(re int k=1;k<=sz;++k){
			re int f=1;
			for(re int j=1;j<=w&&f;++j)
				f&=a[k].p[j]>=l.p[j]&&a[k].p[j]<=r.p[j];
			f&&(tmp[++tmp[0]]=k);
		}
		std::nth_element(tmp+1,tmp+x,tmp+tmp[0]+1,cmp);
		cltstream::write(a[tmp[x]].val,10);
	}
	clop();
	return 0;
}
