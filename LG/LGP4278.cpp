#include<cstdio>
#include<cmath>
#include<algorithm>
#define re register
#define maxn 70005
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

int n,m,sq,lastans;
int id[maxn+1],lwr[maxs+1],upr[maxs+1],suc[maxn+1],pre[maxn+1],a[maxn+1];
int cnt1[maxs+1][maxs+1],cnt2[maxs+1][maxn+1],tmp1[maxs+1],tmp2[maxn+1];

int main(){
	cltstream::read(n);
	sq=sqrt(n);
	for(re int i=1;i<=maxn;++i)
		id[i]=(i-1)/sq+1;
	for(re int i=1;i<=n;++i){
		if(id[i]>id[i-1]){
			lwr[id[i]]=i;
			upr[id[i]]=i+sq-1;
		}
		suc[i]=i+1;
		pre[i]=i-1;
	}
	upr[id[n]]=n;
	suc[n]=1;
	pre[1]=n;
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		++a[i];
		for(re int j=id[i];j<=id[n];++j){
			++cnt1[j][id[a[i]]];
			++cnt2[j][a[i]];
		}
	}
	cltstream::read(m);
	for(re int i=1;i<=m;++i){
		re char opt=cltstream::gc();
		for(;opt!='Q'&&opt!='M'&&opt!='I';opt=cltstream::gc());
		int l,r,x,p;
		switch(opt){
			case 'Q':
				cltstream::read(l);
				l^=lastans;
				cltstream::read(r);
				r^=lastans;
				cltstream::read(x);
				x^=lastans;
				printf("Q(%d,%d,%d)",l,r,x);
				if(id[l]<id[r]){
					p=upr[id[l]];
					for(re int j=id[l]*sq;j>=l;--j,p=pre[p]){
						++tmp1[id[a[p]]];
						++tmp2[a[p]];
					}
					p=lwr[id[r]];
					for(re int j=(id[r]-1)*sq+1;j<=r;++j,p=suc[p]){
						++tmp1[id[a[p]]];
						++tmp2[a[p]];
					}
					for(re int j=1;;++j)
						if(x>cnt1[id[r]-1][j]-cnt1[id[l]][j]+tmp1[j])
							printf("! %d %d %d\n",(j-1)*sq+1,j*sq,cnt1[id[r]-1][j]-cnt1[id[l]][j]+tmp1[j]),
							x-=cnt1[id[r]-1][j]-cnt1[id[l]][j]+tmp1[j];
						else{
							for(re int k=(j-1)*sq+1;;++k)
								if(x>cnt2[id[r]-1][k]-cnt2[id[l]][k]+tmp2[k])
									x-=cnt2[id[r]-1][k]-cnt2[id[l]][k]+tmp2[k];
								else{
									lastans=k;
									break;
								}
							break;
						}
					p=upr[id[l]];
					for(re int j=id[l]*sq;j>=l;--j,p=pre[p]){
						--tmp1[id[a[p]]];
						--tmp2[a[p]];
					}
					p=lwr[id[r]];
					for(re int j=(id[r]-1)*sq+1;j<=r;++j,p=suc[p]){
						--tmp1[id[a[p]]];
						--tmp2[a[p]];
					}
				}
				else{
					p=lwr[id[l]];
					for(re int j=(id[l]-1)*sq+1;j<l;++j,p=suc[p]);
					for(re int j=l;j<=r;++j,p=suc[p]){
						++tmp1[id[a[p]]];
						++tmp2[a[p]];
					}
					for(re int j=1;;++j)
						if(x>tmp1[j])
							x-=tmp1[j];
						else{
							for(re int k=(j-1)*sq+1;;++k)
								if(x>tmp2[k])
									x-=tmp2[k];
								else{
									lastans=k;
									break;
								}
							break;
						}
					p=lwr[id[l]];
					for(re int j=(id[l]-1)*sq+1;j<l;++j,p=suc[p]);
					for(re int j=l;j<=r;++j,p=suc[p]){
						--tmp1[id[a[p]]];
						--tmp2[a[p]];
					}
				}
				printf("=%d\n",lastans);
				cltstream::write(lastans,10);
				break;
			case 'M':
				cltstream::read(l);
				l^=lastans;
				cltstream::read(x);
				x^=lastans;
				++x;
				p=lwr[id[l]];
				for(re int j=(id[l]-1)*sq+1;j<l;++j,p=suc[p]);
				for(re int j=id[l];j<=id[n];++j){
					--cnt1[j][id[a[p]]];
					--cnt1[j][a[p]];
					++cnt1[j][id[x]];
					++cnt1[j][x];
				}
				a[p]=x;
				break;
			case 'I':
				cltstream::read(l);
				l^=lastans;
				cltstream::read(x);
				x^=lastans;
				++x;
				p=lwr[id[l]];
				for(re int j=(id[l]-1)*sq+1;j<l;++j,p=suc[p]);
				a[n+1]=x;
				suc[n+1]=p;
				pre[n+1]=pre[p];
				pre[suc[n+1]]=suc[pre[n+1]]=n+1;
				++cnt1[id[l]][id[a[n+1]]];
				++cnt2[id[l]][a[n+1]];
				--cnt1[id[l]][id[a[upr[id[l]]]]];
				--cnt2[id[l]][a[upr[id[l]]]];
				upr[id[l]]=pre[upr[id[l]]];
				for(re int j=id[l]+1;j<=id[n];++j){
					lwr[j]=pre[lwr[j]];
					++cnt1[j][id[a[lwr[j]]]];
					++cnt2[j][a[lwr[j]]];
					--cnt1[j][id[a[upr[j]]]];
					--cnt2[j][a[upr[j]]];
					upr[j]=pre[upr[j]];
				}
				if(id[n+1]==id[n])
					upr[id[n+1]]=suc[upr[id[n+1]]];
				else
					lwr[id[n+1]]=upr[id[n+1]]=suc[upr[id[n]]];
				++cnt1[id[n+1]][id[a[upr[id[n+1]]]]];
				++cnt2[id[n+1]][a[upr[id[n+1]]]];
				break;
		}
	}
	clop();
	return 0;
}
