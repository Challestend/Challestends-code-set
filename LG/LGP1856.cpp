#include<cstdio>
#include<algorithm>
#define re register
#define maxn 5000
#define maxval 20000
#define abs(a) ((a)>=0?(a):(-(a)))

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

int n,ans;
struct seg{
	int x,y1,y2,w;

	seg(re int _x=0,re int _y1=0,re int _y2=0,re int _w=0){
		x=_x;
		y1=_y1;
		y2=_y2;
		w=_w;
	}
};
seg a[(maxn<<2)+1];
int cvr[(maxval<<2)+1],len[(maxval<<2)+1];

inline bool operator<(re seg p1,re seg p2){
	return p1.x<p2.x||(p1.x==p2.x&&p1.w>p2.w);
}

inline void update(re int L,re int R,re int x,re int cur,re int l,re int r){
	if(l>=L&&r<=R)
		cvr[cur]+=x;
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			update(L,R,x,cur<<1,l,mid);
		if(R>mid)
			update(L,R,x,cur<<1|1,mid+1,r);
	}
	len[cur]=cvr[cur]?r-l+1:l<r?len[cur<<1]+len[cur<<1|1]:0;
}

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		int p,q,r,s;
		cltstream::read(p);
		cltstream::read(r);
		cltstream::read(q);
		cltstream::read(s);
		p+=10000;
		q+=10000;
		r+=10000;
		s+=10000;
		a[(i<<1)-1]=seg(p,r+1,s,1);
		a[(i<<1)]=seg(q,r+1,s,-1);
		a[(n<<1)+(i<<1)-1]=seg(r,p+1,q,1);
		a[(n<<1)+(i<<1)]=seg(s,p+1,q,-1);
	}
	std::sort(a+1,a+(n<<1)+1);
	for(re int i=1,lst=0;i<=(n<<1);++i){
		update(a[i].y1,a[i].y2,a[i].w,1,1,maxval);
		ans+=abs(len[1]-lst);
		lst=len[1];
	}
	std::sort(a+(n<<1)+1,a+(n<<2)+1);
	for(re int i=(n<<1)+1,lst=0;i<=(n<<2);++i){
		update(a[i].y1,a[i].y2,a[i].w,1,1,maxval);
		ans+=abs(len[1]-lst);
		lst=len[1];
	}
	cltstream::write(ans);
	clop();
	return 0;
}
