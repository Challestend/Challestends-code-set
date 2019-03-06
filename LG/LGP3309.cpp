#include<cstdio>
#include<algorithm>
#include<vector>
#define re register
#define maxn 400000

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
long long lastans;
struct Point{
	int x,y;

	Point(re int _x=0,re int _y=0){
		x=_x;
		y=_y;
	}
};
std::vector<Point> a[(maxn<<2)+1],tmp;

inline bool operator<(re Point p1,re Point p2){
	return p1.x!=p2.x?p1.x<p2.x:p1.y<p2.y;
}

inline Point operator-(re Point p1,re Point p2){
	return Point(p1.x-p2.x,p1.y-p2.y);
}

inline long long operator*(re Point p1,re Point p2){
	return 1LL*p1.x*p2.y-1LL*p2.x*p1.y;
}

inline void pushUp(re int cur){
	tmp.clear();
	for(std::vector<Point>::iterator it=a[cur<<1].begin();it!=a[cur<<1].end();tmp.push_back(*it),++it);
	for(std::vector<Point>::iterator it=a[cur<<1|1].begin();it!=a[cur<<1|1].end();tmp.push_back(*it),++it);
	std::sort(tmp.begin(),tmp.end());
	for(std::vector<Point>::iterator it=tmp.begin();it!=tmp.end();a[cur].push_back(*it),++it)
		for(;a[cur].size()>1&&(*a[cur].rbegin()-*(a[cur].rbegin()-1))*(*it-*(a[cur].rbegin()-1))<=0;a[cur].pop_back());
}

inline void Add(re int L,re int x,re int y,re int cur,re int l,re int r){
	if(l==r)
		a[cur].push_back(Point(x,y));
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			Add(L,x,y,cur<<1,l,mid);
		else
			Add(L,x,y,cur<<1|1,mid+1,r);
		if(L==r)
			pushUp(cur);
	}
}

inline long long Query(re int L,re int R,re int x,re int y,re int cur,re int l,re int r){
	long long res=-9e18;
	if(l>=L&&r<=R)
		for(std::vector<Point>::iterator it=a[cur].begin();it!=a[cur].end();++it){
			res=std::max(res,1LL*x*it->x+1LL*y*it->y);
			if((it+1)!=a[cur].end()&&1LL*x*(it+1)->x+1LL*y*(it+1)->y<1LL*x*it->x+1LL*y*it->y)
				break;
		}
	else{
		re int mid=(l+r)>>1;
		if(L<=mid)
			res=std::max(res,Query(L,R,x,y,cur<<1,l,mid));
		if(R>mid)
			res=std::max(res,Query(L,R,x,y,cur<<1|1,mid+1,r));
	}
	return res;
}

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		re char opt=cltstream::gc();
		for(;opt!='A'&&opt!='Q';opt=cltstream::gc());
		if(opt=='A'){
			int x,y;
			cltstream::read(x);
			x^=lastans;
			cltstream::read(y);
			y^=lastans;
			Add(++m,x,y,1,1,n);
		}
		else{
			int x,y,l,r;
			cltstream::read(x);
			x^=lastans;
			cltstream::read(y);
			y^=lastans;
			cltstream::read(l);
			l^=lastans;
			cltstream::read(r);
			r^=lastans;
			cltstream::write(lastans=Query(l,r,x,y,1,1,n),10);
			lastans&=0x7fffffff;
		}
	}
	clop();
	return 0;
}
