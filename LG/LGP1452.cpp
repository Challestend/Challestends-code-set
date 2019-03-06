#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 50000
#define sqr(a) ((a)*(a))

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

int n,top;
struct Point{
	int x,y;

	Point(re int _x=0,re int _y=0){
		x=_x;
		y=_y;
	}
};
Point pnt[maxn+1];
int stk[maxn+2];

inline bool operator<(re Point p1,re Point p2){
	return atan2(p1.y,p1.x)<atan2(p2.y,p2.x);
}

inline Point operator-(re Point p1,re Point p2){
	return Point(p1.x-p2.x,p1.y-p2.y);
}

inline int operator*(re Point p1,re Point p2){
	return p1.x*p2.y-p2.x*p1.y;
}

inline int Dist(re Point p1,re Point p2){
	return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}

int main(){
	scanf("%d",&n);
	for(re int i=1;i<=n;++i){
		scanf("%d %d",&pnt[i].x,&pnt[i].y);
		if(pnt[i].y<pnt[1].y)
			std::swap(pnt[i],pnt[1]);
	}
	for(re int i=2;i<=n;++i){
		pnt[i].x-=pnt[1].x;
		pnt[i].y-=pnt[1].y;
	}
	pnt[1].x=pnt[1].y=0;
	std::sort(pnt+2,pnt+n+1);
	stk[++top]=1;
	for(re int i=2;i<=n;++i){
		for(;top>1&&(pnt[stk[top]]-pnt[stk[top-1]])*(pnt[i]-pnt[stk[top]])<0;--top);
		stk[++top]=i;
	}
	stk[top+1]=1;
	int cur=2,ans=0;
	for(re int i=1;i<=top;++i){
		for(re int j=1;j<=top;++j){
			ans=std::max(ans,std::max(Dist(pnt[stk[i]],pnt[stk[cur]]),Dist(pnt[stk[i+1]],pnt[stk[cur]])));
			if((pnt[stk[i+1]]-pnt[stk[i]])*(pnt[stk[cur%top+1]]-pnt[stk[i]])>=(pnt[stk[i+1]]-pnt[stk[i]])*(pnt[stk[cur]]-pnt[stk[i]]))
				cur=cur%top+1;
			else
				break;
		}
	}
	printf("%d",ans);
	return 0;
}
