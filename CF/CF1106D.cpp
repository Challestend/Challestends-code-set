#include<cstdio>
#include<algorithm>
#include<vector>
#define re register
#define maxn 1000
#define maxm 1000
#define maxp 9

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

const int dx[]={-1,0,0,1},dy[]={0,-1,1,0};

int n,m,p;
int cnt[maxp+1],s[maxp+1],a[maxn+1][maxm+1];
std::vector<std::pair<std::pair<int,int>,int> > h[maxp+1];

inline void expand(re int cur){
	re int limit=h[cur].size();
	for(re std::vector<std::pair<std::pair<int,int>,int> >::iterator head=h[cur].begin();head!=h[cur].end();++head){
		re int x=head->first.first,y=head->first.second,z=head->second;
		printf("%d,%d,%d\n",x,y,z);
		if(z<s[cur]){
			re int f=1;
			for(re int i=0;i<4;++i){
				re int _x=x+dx[i],_y=y+dy[i];
				f&=(_x<1||_x>n||_y<1||_y>m||a[_x][_y]!=0);
				if(_x>=1&&_x<=n&&_y>=1&&_y<=m&&a[_x][_y]==0){
					++cnt[0];
					++cnt[cur];
					a[_x][_y]=cur;
					h[cur].push_back(std::make_pair(std::make_pair(_x,_y),z+1));
				}
			}
			if(f){
				re std::vector<std::pair<std::pair<int,int>,int> >::iterator tmp=head;
				++head;
				h[cur].erase(tmp);
			}
		}
	}
	for(re int i=limit;i<h[cur].size();++i)
		h[cur][i].second=0;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(p);
	for(re int i=1;i<=p;++i)
		cltstream::read(s[i]);
	for(re int i=1;i<=n;++i)
		for(re int j=1;j<=m;++j){
			re char c=cltstream::gc();
			for(;c!='.'&&c!='#'&&(c<'1'||c>'9');c=cltstream::gc());
			a[i][j]=c=='.'?0:c=='#'?-1:c-'0';
			cnt[0]+=c!='.';
			if(c>='1'&&c<='9'){
				++cnt[c-'0'];
				h[c-'0'].push_back(std::make_pair(std::make_pair(i,j),0));
			}
		}
	for(re int i=1;cnt[0]<n*m;++i)
		expand((i-1)%p+1);
	for(re int i=1;i<=p;++i)
		cltstream::write(cnt[i],32);
	clop();
	return 0;
}
