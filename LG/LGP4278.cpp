#include<cstdio>
#include<ctime>
#include<cmath>
#define re register
#define maxn 70000
#define maxs 270

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

int n,m,sq,tmp,lastans;
int id[maxn+1],a[maxn+1],pre[maxn+1],suc[maxn+1],ptr[maxs+1];
int cnt1[maxs+1][maxs+1],cnt2[maxs+1][maxn+1],tmp1[maxs+1],tmp2[maxn+1];

int main(){
	// freopen("LGP4278.in","r",stdin);
	// freopen("LGP4278.out","w",stdout);
	sq=sqrt(8*maxn);
	for(re int i=1;i<=maxn;++i)
 		id[i]=(i-1)/sq+1;
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]),
		pre[i]=i==1?n:i-1,
		suc[i]=i==n?1:i+1;
		if(id[i]>id[i-1])
			ptr[id[i]]=i;
		for(re int j=id[i];j<=id[maxn];++j)
			++cnt1[j][id[a[i]]],
			++cnt2[j][a[i]];
	}
	cltstream::read(m);
	for(re int i=1;i<=m;++i){
		re char opt=cltstream::gc();
		for(;opt!='Q'&&opt!='M'&&opt!='I';opt=cltstream::gc());
		re int x,y,z,l,r;
		cltstream::read(x);
		x^=lastans;
		cltstream::read(y);
		y^=lastans;
		switch(opt){
			case 'Q':
				cltstream::read(z);
				z^=lastans;
				if(id[x]<id[y]){
					if(id[x]*sq-x+1<=(sq>>1)){
						l=id[x];
						tmp=pre[ptr[id[x]+1]];
						for(re int j=id[x]*sq;j>=x;--j,++tmp1[id[a[tmp]]],++tmp2[a[tmp]],tmp=pre[tmp]);
					}
					else{
						l=id[x]-1;
						tmp=ptr[id[x]];
						for(re int j=(id[x]-1)*sq+1;j<x;++j,--tmp1[id[a[tmp]]],--tmp2[a[tmp]],tmp=suc[tmp]);
					}
					if(y-(id[y]-1)*sq<=(sq>>1)){
						r=id[y]-1;
						tmp=ptr[id[y]];
						for(re int j=(id[y]-1)*sq+1;j<=y;++j,++tmp1[id[a[tmp]]],++tmp2[a[tmp]],tmp=suc[tmp]);
					}
					else{
						r=id[y];
						tmp=id[y]==id[n]?pre[1]:pre[ptr[id[y]+1]];
						for(re int j=id[y]==id[n]?n:id[y]*sq;j>y;--j,--tmp1[id[a[tmp]]],--tmp2[a[tmp]],tmp=pre[tmp]);
					}
					if(z<=cnt2[r][0]-cnt2[l][0]+tmp2[0])
						cltstream::write(lastans=0,10);
					else{
						z-=cnt2[r][0]-cnt2[l][0]+tmp2[0];
						for(re int j=1;;++j)
							if(z>cnt1[r][j]-cnt1[l][j]+tmp1[j])
								z-=cnt1[r][j]-cnt1[l][j]+tmp1[j];
							else{
								for(re int k=(j-1)*sq+1;;++k)
									if(z>cnt2[r][k]-cnt2[l][k]+tmp2[k])
										z-=cnt2[r][k]-cnt2[l][k]+tmp2[k];
									else{
										cltstream::write(lastans=k,10);
										break;
									}
								break;
							}
					}
					if(id[x]*sq-x+1<=(sq>>1)){
						tmp=pre[ptr[id[x]+1]];
						for(re int j=id[x]*sq;j>=x;--j,--tmp1[id[a[tmp]]],--tmp2[a[tmp]],tmp=pre[tmp]);
					}
					else{
						tmp=ptr[id[x]];
						for(re int j=(id[x]-1)*sq+1;j<x;++j,++tmp1[id[a[tmp]]],++tmp2[a[tmp]],tmp=suc[tmp]);
					}
					if(y-(id[y]-1)*sq<=(sq>>1)){
						tmp=ptr[id[y]];
						for(re int j=(id[y]-1)*sq+1;j<=y;++j,--tmp1[id[a[tmp]]],--tmp2[a[tmp]],tmp=suc[tmp]);
					}
					else{
						tmp=id[y]==id[n]?pre[1]:pre[ptr[id[y]+1]];
						for(re int j=id[y]==id[n]?n:id[y]*sq;j>y;--j,++tmp1[id[a[tmp]]],++tmp2[a[tmp]],tmp=pre[tmp]);
					}
				}
				else{
					if(x-(id[x]-1)*sq-1<=id[x]*sq-y){
						tmp=ptr[id[x]];
						for(re int j=(id[x]-1)*sq+1;j<x;++j,tmp=suc[tmp]);
						for(re int j=x;j<=y;++j,++tmp1[id[a[tmp]]],++tmp2[a[tmp]],tmp=suc[tmp]);
					}
					else{
						tmp=id[x]==id[n]?pre[1]:pre[ptr[id[x]+1]];
						for(re int j=id[x]==id[n]?n:id[x]*sq;j>y;--j,tmp=pre[tmp]);
						for(re int j=y;j>=x;--j,++tmp1[id[a[tmp]]],++tmp2[a[tmp]],tmp=pre[tmp]);
					}
					if(z<=tmp2[0])
						cltstream::write(lastans=0,10);
					else{
						z-=tmp2[0];
						for(re int j=1;;++j)
							if(z>tmp1[j])
								z-=tmp1[j];
							else{
								for(re int k=(j-1)*sq+1;;++k)
									if(z>tmp2[k])
										z-=tmp2[k];
									else{
										cltstream::write(lastans=k,10);
										break;
									}
								break;
							}
					}
					if(x-(id[x]-1)*sq-1<=id[x]*sq-y){
						tmp=ptr[id[x]];
						for(re int j=(id[x]-1)*sq+1;j<x;++j,tmp=suc[tmp]);
						for(re int j=x;j<=y;++j,--tmp1[id[a[tmp]]],--tmp2[a[tmp]],tmp=suc[tmp]);
					}
					else{
						tmp=id[x]==id[n]?pre[1]:pre[ptr[id[x]+1]];
						for(re int j=id[x]==id[n]?n:id[x]*sq;j>y;--j,tmp=pre[tmp]);
						for(re int j=y;j>=x;--j,--tmp1[id[a[tmp]]],--tmp2[a[tmp]],tmp=pre[tmp]);
					}
				}
				break;
			case 'M':
				if(x-(id[x]-1)*sq<=(sq>>1)){
					tmp=ptr[id[x]];
					for(re int j=(id[x]-1)*sq+1;j<x;++j,tmp=suc[tmp]);
				}
				else{
					tmp=id[x]==id[n]?pre[1]:pre[ptr[id[x]+1]];
					for(re int j=id[x]==id[n]?n:id[x]*sq;j>x;--j,tmp=pre[tmp]);
				}
				for(re int j=id[x];j<=id[maxn];++j)
					--cnt1[j][id[a[tmp]]],
					++cnt1[j][id[y]],
					--cnt2[j][a[tmp]],
					++cnt2[j][y];
				a[tmp]=y;
				break;
			case 'I':
				if(x-(id[x]-1)*sq<=(sq>>1)){
					tmp=ptr[id[x]];
					for(re int j=(id[x]-1)*sq+1;j<x;++j,tmp=suc[tmp]);
				}
				else{
					tmp=id[x]==id[n]?pre[1]:pre[ptr[id[x]+1]];
					for(re int j=id[x]==id[n]?n:id[x]*sq;j>x;--j,tmp=pre[tmp]);
				}
				++n,
				a[n]=y,
				pre[n]=pre[tmp],
				suc[n]=tmp,
				suc[pre[tmp]]=n,
				pre[tmp]=n;
				for(re int j=id[x];j<=id[maxn];++j)
					++cnt1[j][id[y]],
					++cnt2[j][y];
				if(id[x]>id[x-1])
					ptr[id[x]]=pre[ptr[id[x]]];
				for(re int j=id[x]+1;j<=id[n-1];++j)
					ptr[j]=pre[ptr[j]],
					--cnt1[j-1][id[a[ptr[j]]]],
					++cnt1[j][id[a[ptr[j]]]],
					--cnt2[j-1][a[ptr[j]]],
					++cnt2[j][a[ptr[j]]];
				if(id[n]>id[n-1])
					ptr[id[n]]=pre[1],
					--cnt1[id[n]-1][id[a[ptr[id[n]]]]],
					++cnt1[id[n]][id[a[ptr[id[n]]]]],
					--cnt2[id[n]-1][a[ptr[id[n]]]],
					++cnt2[id[n]][a[ptr[id[n]]]];
				break;
		}
	}
	clop();
	// freopen("con","w",stdout);
	// printf("%d",clock());
	return 0;
}
