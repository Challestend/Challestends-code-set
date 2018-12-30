#include<cstdio>
#define re register
#define maxn 1000000
#define lowbit(a) ((a)&(-(a)))
#define swap(a,b) a^=b,b^=a,a^=b

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

int n,m,root,ec,vc;
int v[maxn+1],des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];
long long bit[maxn+1][2];

inline void update(re int x,re int y){
	for(re int i=x;i<=n;i+=lowbit(i)){
		bit[i][0]+=y;
		bit[i][1]+=1LL*x*y;
	}
}

inline long long query(re int x){
	re long long res=0;
	for(re int i=x;i>=1;i-=lowbit(i))
		res+=(x+1)*bit[i][0]-bit[i][1];
	return res;
}

void dfs1(re int cur,re int ftr){
	f[cur]=ftr;
	dep[cur]=dep[f[cur]]+1;
	size[cur]=1;
	re int maxsize=0;
	for(re int i=las[cur];i;i=suc[i])
		if(des[i]!=f[cur]){
			dfs1(des[i],cur);
			size[cur]+=size[des[i]];
			if(maxsize<size[des[i]]){
				maxsize=size[des[i]];
				hes[cur]=des[i];
			}
		}
}

void dfs2(re int cur,re int curtop){
	id[cur]=++vc;
	top[cur]=curtop;
	update(id[cur],v[cur]);
	update(id[cur]+1,-v[cur]);
	if(!hes[cur])
		return;
	else{
		dfs2(hes[cur],curtop);
		for(re int i=las[cur];i;i=suc[i])
			if(des[i]!=f[cur]&&des[i]!=hes[cur])
				dfs2(des[i],des[i]);
	}
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	cltstream::read(root);
	for(re int i=1;i<=n;++i)
		cltstream::read(v[i]);
	for(re int i=1;i<n;++i){
		re int x,y;
		cltstream::read(x);
		cltstream::read(y);
		des[++ec]=y;
		suc[ec]=las[x];
		las[x]=ec;
		des[++ec]=x;
		suc[ec]=las[y];
		las[y]=ec;
	}
	dfs1(root,0);
	dfs2(root,root);
	for(re int i=1;i<=m;++i){
		re int opt,x,y;
		cltstream::read(opt);
		cltstream::read(x);
		cltstream::read(y);
		switch(opt){
			case 1:
				update(id[x],y);
				update(id[x]+1,-y);
				break;
			case 2:
				update(id[x],y);
				update(id[x]+size[x],-y);
				break;
			case 3:
				re long long res=0;
				for(;top[x]!=top[y];){
					if(dep[top[x]]>dep[top[y]])
						swap(x,y);
					res+=query(id[y])-query(id[top[y]]-1);
					y=f[top[y]];
				}
				if(dep[x]>dep[y])
					swap(x,y);
				cltstream::write(res+query(id[y])-query(id[x]-1),10);
				break;
		}
	}
	clop();
	return 0;
}
