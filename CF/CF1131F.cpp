#include<cstdio>
#include<iostream>
#define re register
#define clt 150000

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

int n,m,x,y;
int fa[clt+1],l[clt+1],r[clt+1],tail[clt+1],head[clt+1];

int find(re int x){
	return fa[x]==x?x:fa[x]=find(fa[x]);
}

int main(){
	scanf("%d",&n);
	for(re int i=1;i<=n;i++){
		fa[i]=i;
		l[i]=r[i]=i;
	}
	for(re int i=1;i<=n-1;i++){
		scanf("%d%d",&x,&y);
		int a=find(x),b=find(y);
		head[l[b]]=r[a];
		tail[r[a]]=l[b];
		fa[a]=b;
		l[b]=l[a];
	}
	re int u=l[find(1)];
	for(;u;){
		printf("%d ",u);
		u=tail[u];
	}
	return 0;
}
