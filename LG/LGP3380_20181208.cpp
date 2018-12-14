#include<cstdio>
#include<cstring>
#include<algorithm>
#define re register
#define maxn 50000
#define maxm 50000
#define maxs 230
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define lowbit(a) ((a)&(-(a)))

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

int n,m,sq1,sq2;
int id1[maxn+1],id2[maxn+maxm+1],p[maxn+maxm+1];
int a[maxn+1],opt[maxm+1][4];
int cnt1[maxs+1][(maxs<<1)+1],cnt2[maxs+1][maxn+maxm+1],tmp1[(maxs<<1)+1],tmp2[maxn+maxm+1];

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(;(sq1+1)*(sq1+1)<=n;++sq1);
	for(re int i=1;i<=n;++i){
		id1[i]=(i-1)/sq1+1;
		cltstream::read(a[i]);
		p[++p[0]]=a[i];
	}
	for(re int i=1;i<=m;++i){
		cltstream::read(opt[i][0]);
		cltstream::read(opt[i][1]);
		cltstream::read(opt[i][2]);
		if(opt[i][0]!=3)
			cltstream::read(opt[i][3]);
		else
			p[++p[0]]=opt[i][2];
	}
	std::sort(p+1,p+p[0]+1);
	p[0]=std::unique(p+1,p+p[0]+1)-p-1;
	for(;(sq2+1)*(sq2+1)<=p[0];++sq2);
	for(re int i=1;i<=p[0];++i)
		id2[i]=(i-1)/sq2+1;
	for(re int i=1;i<=n;++i){
		a[i]=std::lower_bound(p+1,p+p[0]+1,a[i])-p;
		++cnt1[id1[i]][id2[a[i]]];
		++cnt2[id1[i]][a[i]];
	}
	for(re int i=1;i<=id1[n];++i){
		for(re int j=1;j<=id2[p[0]];++j)
			cnt1[i][j]+=cnt1[i-1][j];
		for(re int j=1;j<=p[0];++j)
			cnt2[i][j]+=cnt2[i-1][j];
	}
	for(re int i=1;i<=m;++i){
		re int l,r,x,ans=0;
		switch(opt[i][0]){
			case 1:
				l=opt[i][1],r=opt[i][2],x=std::lower_bound(p+1,p+p[0]+1,opt[i][3])-p;
				if(id1[l]<id1[r]){
					for(re int j=l;j<=id1[l]*sq1;++j)
						ans+=(a[j]<x);
					for(re int j=(id1[r]-1)*sq1+1;j<=r;++j)
						ans+=(a[j]<x);
					for(re int j=1;j<id2[x];++j)
						ans+=cnt1[id1[r]-1][j]-cnt1[id1[l]][j];
					for(re int j=(id2[x]-1)*sq2+1;j<x;++j)
						ans+=cnt2[id1[r]-1][j]-cnt2[id1[l]][j];
				}
				else
					for(re int j=l;j<=r;++j)
						ans+=(a[j]<x);
				cltstream::write(ans+1,10);
				break;
			case 2:
				l=opt[i][1],r=opt[i][2],x=opt[i][3];
				if(id1[l]<id1[r]){
					for(re int j=l;j<=id1[l]*sq1;++j){
						++tmp1[id2[a[j]]];
						++tmp2[a[j]];
					}
					for(re int j=(id1[r]-1)*sq1+1;j<=r;++j){
						++tmp1[id2[a[j]]];
						++tmp2[a[j]];
					}
					for(re int j=1;;++j)
						if(x>cnt1[id1[r]-1][j]-cnt1[id1[l]][j]+tmp1[j])
							x-=cnt1[id1[r]-1][j]-cnt1[id1[l]][j]+tmp1[j];
						else{
							for(re int k=(j-1)*sq2+1;k<=j*sq2;++k)
								if(x>cnt2[id1[r]-1][k]-cnt2[id1[l]][k]+tmp2[k])
									x-=cnt2[id1[r]-1][k]-cnt2[id1[l]][k]+tmp2[k];
								else{
									cltstream::write(p[k],10);
									break;
								}
							break;
						}
					for(re int j=l;j<=id1[l]*sq1;++j){
						--tmp1[id2[a[j]]];
						--tmp2[a[j]];
					}
					for(re int j=(id1[r]-1)*sq1+1;j<=r;++j){
						--tmp1[id2[a[j]]];
						--tmp2[a[j]];
					}
				}
				else{
					for(re int j=l;j<=r;++j){
						++tmp1[id2[a[j]]];
						++tmp2[a[j]];
					}
					for(re int j=1;;++j)
						if(x>tmp1[j])
							x-=tmp1[j];
						else{
							for(re int k=(j-1)*sq2+1;k<=j*sq2;++k)
								if(x>tmp2[k])
									x-=tmp2[k];
								else{
									cltstream::write(p[k],10);
									break;
								}
							break;
						}
					for(re int j=l;j<=r;++j){
						--tmp1[id2[a[j]]];
						--tmp2[a[j]];
					}
				}
				break;
			case 3:
				l=opt[i][1],x=std::lower_bound(p+1,p+p[0]+1,opt[i][2])-p;
				for(re int j=id1[l];j<=id1[n];++j){
					--cnt1[j][id2[a[l]]];
					++cnt1[j][id2[x]];
					--cnt2[j][a[l]];
					++cnt2[j][x];
				}
				a[l]=x;
				break;
			case 4:
				l=opt[i][1],r=opt[i][2],x=std::lower_bound(p+1,p+p[0]+1,opt[i][3])-p;
				if(id1[l]<id1[r]){
					for(re int j=l;j<=id1[l]*sq1;++j){
						++tmp1[id2[a[j]]];
						++tmp2[a[j]];
					}
					for(re int j=(id1[r]-1)*sq1+1;j<=r;++j){
						++tmp1[id2[a[j]]];
						++tmp2[a[j]];
					}
					for(re int j=x-1;j>=(id2[x]-1)*sq2+1&&!ans;--j)
						if(cnt2[id1[r]-1][j]-cnt2[id1[l]][j]+tmp2[j])
							ans=j;
					for(re int j=id2[x]-1;j>=1&&!ans;--j)
						if(cnt1[id1[r]-1][j]-cnt1[id1[l]][j]+tmp1[j])
							for(re int k=j*sq2;k>=(j-1)*sq2+1&&!ans;--k)
								if(cnt2[id1[r]-1][k]-cnt2[id1[l]][k]+tmp2[k])
									ans=k;
					for(re int j=l;j<=id1[l]*sq1;++j){
						--tmp1[id2[a[j]]];
						--tmp2[a[j]];
					}
					for(re int j=(id1[r]-1)*sq1+1;j<=r;++j){
						--tmp1[id2[a[j]]];
						--tmp2[a[j]];
					}
				}
				else{
					for(re int j=l;j<=r;++j){
						++tmp1[id2[a[j]]];
						++tmp2[a[j]];
					}
					for(re int j=x-1;j>=(id2[x]-1)*sq2+1&&!ans;--j)
						if(tmp2[j])
							ans=j;
					for(re int j=id2[x]-1;j>=1&&!ans;--j)
						if(tmp1[j])
							for(re int k=j*sq2;k>=(j-1)*sq2+1&&!ans;--k)
								if(tmp2[k])
									ans=k;
					for(re int j=l;j<=r;++j){
						--tmp1[id2[a[j]]];
						--tmp2[a[j]];
					}
				}
				cltstream::write(ans?p[ans]:-2147483647,10);
				break;
			case 5:
				l=opt[i][1],r=opt[i][2],x=std::upper_bound(p+1,p+p[0]+1,opt[i][3])-p-1;
				if(id1[l]<id1[r]){
					for(re int j=l;j<=id1[l]*sq1;++j){
						++tmp1[id2[a[j]]];
						++tmp2[a[j]];
					}
					for(re int j=(id1[r]-1)*sq1+1;j<=r;++j){
						++tmp1[id2[a[j]]];
						++tmp2[a[j]];
					}
					for(re int j=x+1;j<=id2[x]*sq2&&!ans;++j)
						if(cnt2[id1[r]-1][j]-cnt2[id1[l]][j]+tmp2[j])
							ans=j;
					for(re int j=id2[x]+1;j<=id2[p[0]]&&!ans;++j)
						if(cnt1[id1[r]-1][j]-cnt1[id1[l]][j]+tmp1[j])
							for(re int k=(j-1)*sq2+1;k<=j*sq2&&!ans;++k)
								if(cnt2[id1[r]-1][k]-cnt2[id1[l]][k]+tmp2[k])
									ans=k;
					for(re int j=l;j<=id1[l]*sq1;++j){
						--tmp1[id2[a[j]]];
						--tmp2[a[j]];
					}
					for(re int j=(id1[r]-1)*sq1+1;j<=r;++j){
						--tmp1[id2[a[j]]];
						--tmp2[a[j]];
					}
				}
				else{
					for(re int j=l;j<=r;++j){
						++tmp1[id2[a[j]]];
						++tmp2[a[j]];
					}
					for(re int j=x+1;j<=id2[x]*sq2&&!ans;++j)
						if(tmp2[j])
							ans=j;
					for(re int j=id2[x]+1;j<=id2[p[0]]&&!ans;++j)
						if(tmp1[j])
							for(re int k=(j-1)*sq2+1;k<=j*sq2&&!ans;++k)
								if(tmp2[k])
									ans=k;
					for(re int j=l;j<=r;++j){
						--tmp1[id2[a[j]]];
						--tmp2[a[j]];
					}
				}
				cltstream::write(ans?p[ans]:2147483647,10);
		}
	}
	clop();
	return 0;
}
