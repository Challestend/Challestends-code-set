#include<cstdio>
#include<algorithm>
#define re register
#define maxn 500000
#define maxm 500000

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

int n,m,ec,vc;
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];

inline void connect(re int x,re int y){
	des[++ec]=y;
	suc[ec]=las[x];
	las[x]=ec;
}

void dfs1(re int cur,re int ftr){
	f[cur]=ftr;
	dep[cur]=dep[ftr]+1;
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
	if(hes[cur]){
		dfs2(hes[cur],curtop);
		for(re int i=las[cur];i;i=suc[i])
			if(des[i]!=f[cur]&&des[i]!=hes[cur])
				dfs2(des[i],des[i]);
	}
}

inline void swap(int& x,int& y){
	re int tmp=x;
	x=y;
	y=tmp;
}

inline int lca(re int x,re int y){
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		y=f[top[y]];
	}
	return dep[x]<=dep[y]?x:y;
}

inline int dist(re int x,re int y){
	re int res=0;
	for(;top[x]!=top[y];){
		if(dep[top[x]]>dep[top[y]])
			swap(x,y);
		res+=id[y]-id[top[y]]+1;
		y=f[top[y]];
	}
	if(dep[x]>dep[y])
		swap(x,y);
	res+=id[y]-id[x];
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<n;++i){
		re int x,y;
		cltstream::read(x);
		cltstream::read(y);
		connect(x,y);
		connect(y,x);
	}
	dfs1(1,0);
	dfs2(1,1);
	for(re int i=1;i<=m;++i){
		re int x,y,z;
		cltstream::read(x);
		cltstream::read(y);
		cltstream::read(z);
		re int xy=lca(x,y),xz=lca(x,z),yz=lca(y,z);
		if(xy!=xz&&xy!=yz){
			cltstream::write(xy,32);
			cltstream::write(dist(x,y)+dist(xy,z),10);
		}
		else
			if(xy!=xz){
				cltstream::write(xz,32);
				cltstream::write(dist(x,z)+dist(xz,y),10);
			}
			else{
				cltstream::write(yz,32);
				cltstream::write(dist(y,z)+dist(yz,x),10);
			}
	}
	fwrite(cltstream::cltout,1,cltstream::oh-cltstream::cltout,stdout);
	return 0;
}
