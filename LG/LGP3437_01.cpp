#include<cstdio>
#include<algorithm>
#define re register

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

int D,S,n;
int mx[2001][2001],upd[2001][2001];

void update2(re int L,re int R,re int D,re int U,re int x,re int rt,re int l,re int r,re int cur,re int d,re int u){
	if(d>=D&&u<=U){
		mx[rt][cur]=x;
		if(l>=L&&r<=R)
			upd[rt][cur]=x;
	}
	else{
		re int mid=(d+u)>>1;
		if(D<=mid)
			update2(L,R,D,U,x,rt,l,r,cur<<1,d,mid);
		if(U>mid)
			update2(L,R,D,U,x,rt,l,r,cur<<1|1,mid+1,u);
	}
}

void update1(re int L,re int R,re int D,re int U,re int x,re int rt,re int l,re int r){
	update2(L,R,D,U,x,rt,l,r,1,1,1000);
	if(l>L||r<R){
		re int mid=(l+r)>>1;
		if(L<=mid)
			update1(L,R,D,U,x,rt<<1,l,mid);
		if(R>mid)
			update1(L,R,D,U,x,rt<<1|1,mid+1,r);
	}
}

int getmax2(re int L,re int R,re int D,re int U,re int rt,re int l,re int r,re int cur,re int d,re int u){
	if(d>=D&&u<=U)
		return l>=L&&r<=R?mx[rt][cur]:upd[rt][cur];
	else{
		re int mid=(d+u)>>1;
		int res=0;
		if(D<=mid)
			res=std::max(res,getmax2(L,R,D,U,rt,l,r,cur<<1,d,mid));
		if(U>mid)
			res=std::max(res,getmax2(L,R,D,U,rt,l,r,cur<<1|1,mid+1,u));
		return res;
	}
}

int getmax1(re int L,re int R,re int D,re int U,re int rt,re int l,re int r){
	int res=getmax2(L,R,D,U,rt,l,r,1,1,1000);
	if(l<L||r>R){
		re int mid=(l+r)>>1;
		if(L<=mid)
			res=std::max(res,getmax1(L,R,D,U,rt<<1,l,mid));
		if(R>mid)
			res=std::max(res,getmax1(L,R,D,U,rt<<1|1,mid+1,r));
	}
	return res;
}

int main(){
	cltstream::read(D);
	cltstream::read(S);
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		int d,s,w,x,y;
		cltstream::read(d);
		cltstream::read(s);
		cltstream::read(w);
		cltstream::read(x);
		cltstream::read(y);
		re int h=getmax1(x+1,x+d,y+1,y+s,1,1,1000);
		printf("%d\n",h);
		update1(x+1,x+d,y+1,y+s,h+w,1,1,1000);
	}
	cltstream::write(getmax1(1,1000,1,1000,1,1,1000));
	clop();
	return 0;
}
