#include<cstdio>
#define re register
#define maxn 400
#define maxm 400
#define maxc 400
#define mod 1000000007

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

int n,m,c,ans;
int row[maxn+1],col[maxm+1],cnt[maxc+1];

void dfs(re int x,re int y){
	if(x<=n){
		if(y<m)
			dfs(x,y+1);
		else
			dfs(x+1,1);
		for(re int i=1;i<=c;++i){
			++row[x];
			++col[y];
			++cnt[i];
			if(y<m)
				dfs(x,y+1);
			else
				dfs(x+1,1);
			--row[x];
			--col[y];
			--cnt[i];
		}
	}
	else{
		re int val=1;
		for(re int i=1;i<=n&&val;++i)
			val&=row[i]>0;
		for(re int i=1;i<=m&&val;++i)
			val&=col[i]>0;
		for(re int i=1;i<=c&&val;++i)
			val&=cnt[i]>0;
		ans=(ans+val)%mod;
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(c);
	dfs(1,1);
	cltstream::write(ans,10);
	clop();
	return 0;
}
