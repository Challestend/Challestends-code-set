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
int mx[4000001],upd[4000001];

inline void pushDown(re int cur){
	if(upd[cur]){
		mx[(cur<<2)-2]=upd[cur];
		upd[(cur<<2)-2]=upd[cur];
		mx[(cur<<2)-1]=upd[cur];
		upd[(cur<<2)-1]=upd[cur];
		mx[(cur<<2)]=upd[cur];
		upd[(cur<<2)]=upd[cur];
		mx[(cur<<2)+1]=upd[cur];
		upd[(cur<<2)+1]=upd[cur];
		upd[cur]=0;
	}
}

void update(re int L,re int R,re int D,re int U,re int x,re int cur,re int l,re int r,re int d,re int u){
	if(l>=L&&r<=R&&d>=D&&u<=U){
		mx[cur]=x;
		upd[cur]=x;
	}
	else{
		re int hmid=(l+r)>>1,vmid=(d+u)>>1;
		pushDown(cur);
		if(L<=hmid&&D<=vmid)
			update(L,R,D,U,x,(cur<<2)-2,l,hmid,d,vmid);
		if(L<=hmid&&U>vmid)
			update(L,R,D,U,x,(cur<<2)-1,l,hmid,vmid+1,u);
		if(R>hmid&&D<=vmid)
			update(L,R,D,U,x,(cur<<2),hmid+1,r,d,vmid);
		if(R>hmid&&U>vmid)
			update(L,R,D,U,x,(cur<<2)+1,hmid+1,r,vmid+1,u);
		mx[cur]=std::max(std::max(std::max(mx[(cur<<2)-2],mx[(cur<<2)-1]),mx[(cur<<2)]),mx[(cur<<2)+1]);
	}
}

int getmax(re int L,re int R,re int D,re int U,re int cur,re int l,re int r,re int d,re int u){
	if(l>=L&&r<=R&&d>=D&&u<=U)
		return mx[cur];
	else{
		re int hmid=(l+r)>>1,vmid=(d+u)>>1;
		int res=0;
		pushDown(cur);
		if(L<=hmid&&D<=vmid)
			res=std::max(res,getmax(L,R,D,U,(cur<<2)-2,l,hmid,d,vmid));
		if(L<=hmid&&U>vmid)
			res=std::max(res,getmax(L,R,D,U,(cur<<2)-1,l,hmid,vmid+1,u));
		if(R>hmid&&D<=vmid)
			res=std::max(res,getmax(L,R,D,U,(cur<<2),hmid+1,r,d,vmid));
		if(R>hmid&&U>vmid)
			res=std::max(res,getmax(L,R,D,U,(cur<<2)+1,hmid+1,r,vmid+1,u));
		return res;
	}
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
		re int h=getmax(x+1,x+d,y+1,y+s,1,1,D,1,S);
		update(x+1,x+d,y+1,y+s,h+w,1,1,D,1,S);
	}
	cltstream::write(mx[1]);
	clop();
	return 0;
}
