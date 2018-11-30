#include<cstdio>
#define re register
#define maxn 1000000
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

int n,maxRight,mid,maxLen;
int v[maxn+1],ch[maxn+1][2],dep[maxn+1],size[maxn+1],a[maxn+1],ans[maxn+1];

void dfs(int cur){
	size[cur]=1;
	if(ch[cur][0]>=1){
		dep[ch[cur][0]]=dep[cur]+1;
		dfs(ch[cur][0]);
		size[cur]+=size[ch[cur][0]];
	}
	a[++a[0]]=cur;
	if(ch[cur][1]>=1){
		dep[ch[cur][1]]=dep[cur]+1;
		dfs(ch[cur][1]);
		size[cur]+=size[ch[cur][1]];
	}
}

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i)
		cltstream::read(v[i]);
	for(re int i=1;i<=n;++i){
		cltstream::read(ch[i][0]);
		cltstream::read(ch[i][1]);
	}
	dep[1]=1;
	dfs(1);
	for(re int i=1;i<=n;++i){
		ans[i]=max(min(ans[(mid<<1)-i],maxRight-i+1),1);
		for(;i-ans[i]>=1&&i+ans[i]<=n&&v[a[i-ans[i]]]==v[a[i+ans[i]]]&&dep[a[i-ans[i]]]==dep[a[i+ans[i]]];++ans[i]);
		if(i+ans[i]-1>maxRight){
			maxRight=i+ans[i]-1;
			mid=i;
		}
		if(((ans[i]<<1)>size[a[i]])&size[a[i]])
			maxLen=max(maxLen,size[a[i]]);
	}
	cltstream::write(maxLen);
	clop();
	return 0;
}
