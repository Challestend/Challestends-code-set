#include<cstdio>
#include<cmath>
#define re register
#define maxn 100000
#define maxs 320
#define max(a,b) ((a)>=(b)?(a):(b))

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

int n,m,sq;
int id[maxn+1],a[maxn+1],cnt1[maxs+1][maxn+1],cnt2[maxn+1],tmp[maxn+1];

int main(){
	cltstream::read(n);
	sq=sqrt(n);
	for(re int i=1;i<=n;++i)
		id[i]=(i-1)/sq+1;
	for(re int i=1;i<=n;++i){
		cltstream::read(a[i]);
		a[0]=max(a[0],a[i]);
		for(re int j=id[i];j<=id[n];++j)
			++cnt1[j][a[i]];
	}
	cltstream::read(m);
	for(re int i=1;i<=m;++i){
		int l,r,x;
		cltstream::read(l);
		cltstream::read(r);
		cltstream::read(x);
		for(re int j=0;j<x;++j)
			tmp[++tmp[0]]=j;
		re int L=id[l],R=id[r];
		if(L<R){
			for(re int j=l;j<=L*sq;++j)
				++cnt2[a[j]];
			for(re int j=(R-1)*sq+1;j<=r;++j)
				++cnt2[a[j]];
			for(re int ans=0;;++ans){
				re int cnt=0;
				for(re int j=1;j<=tmp[0];++j){
					re int y=ans*x+tmp[j];
					if(cnt1[R-1][y]-cnt1[L][y]+cnt2[y]){
						tmp[cnt+1]=tmp[j];
						++cnt;
					}
				}
				tmp[0]=cnt;
				if(!tmp[0]){
					cltstream::write(ans,10);
					break;
				}
			}
			for(re int j=l;j<=L*sq;++j)
				--cnt2[a[j]];
			for(re int j=(R-1)*sq+1;j<=r;++j)
				--cnt2[a[j]];
		}
		else{
			for(re int j=l;j<=r;++j)
				++cnt2[a[j]];
			for(re int ans=0;;++ans){
				re int cnt=0;
				for(re int j=1;j<=tmp[0];++j){
					re int y=ans*x+tmp[j];
					if(cnt2[y]){
						tmp[cnt+1]=tmp[j];
						++cnt;
					}
				}
				tmp[0]=cnt;
				if(!tmp[0]){
					cltstream::write(ans,10);
					break;
				}
			}
			for(re int j=l;j<=r;++j)
				--cnt2[a[j]];
		}
	}
	clop();
	return 0;
}
