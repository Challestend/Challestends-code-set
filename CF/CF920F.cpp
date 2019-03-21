#include<cstdio>
#define re register
#define maxn 300000
#define maxval 1000000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

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
int f[maxval+1],g[maxval+1],d[maxval+1],lst[maxval+1];
long long sum[(maxn<<2)+1],mx[(maxn<<2)+1];

void build(re int cur,re int l,re int r){
	if(l==r){
		cltstream::read(sum[cur]);
		mx[cur]=sum[cur];
	}
	else{
		re int mid=(l+r)>>1;
		build(cur<<1,l,mid);
		build(cur<<1|1,mid+1,r);
		sum[cur]=sum[cur<<1]+sum[cur<<1|1];
		mx[cur]=max(mx[cur<<1],mx[cur<<1|1]);
	}
}

void modify(re int L,re int R,re int cur,re int l,re int r){
	if(mx[cur]<=2)
		return;
	if(l==r){
		sum[cur]=d[sum[cur]];
		mx[cur]=d[mx[cur]];
	}
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			modify(L,R,cur<<1,l,mid);
		if(R>mid)
			modify(L,R,cur<<1|1,mid+1,r);
		sum[cur]=sum[cur<<1]+sum[cur<<1|1];
		mx[cur]=max(mx[cur<<1],mx[cur<<1|1]);
	}
}

long long getsum(re int L,re int R,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		return sum[cur];
	else{
		re int mid=(l+r)>>1;
		re long long res=0;
		if(L<=mid)
			res+=getsum(L,R,cur<<1,l,mid);
		if(R>mid)
			res+=getsum(L,R,cur<<1|1,mid+1,r);
		return res;
	}
}

int main(){
	for(re int i=2;i<=maxval;++i){
		if(!f[i]){
			g[++g[0]]=i;
			d[i]=1;
			lst[i]=2;
		}
		for(re int j=1;j<=g[0]&&i*g[j]<=maxval;++j){
			f[i*g[j]]=1;
			if(i%g[j]){
				d[i*g[j]]=d[i]*lst[i];
				lst[i*g[j]]=lst[g[j]];
			}
			else{
				d[i*g[j]]=d[i];
				lst[i*g[j]]=lst[i]+1;
				break;
			}
		}
	}
	d[1]=1;
	for(re int i=2;i<=maxval;++i)
		d[i]*=lst[i];
	cltstream::read(n);
	cltstream::read(m);
	build(1,1,n);
	for(re int i=1;i<=m;++i){
		int opt,l,r;
		cltstream::read(opt);
		cltstream::read(l);
		cltstream::read(r);
		if(opt==1)
			modify(l,r,1,1,n);
		else
			cltstream::write(getsum(l,r,1,1,n),10);
	}
	clop();
	return 0;
}
