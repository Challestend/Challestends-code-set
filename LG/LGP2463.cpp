#include<cstdio>
#define re register
#define maxn 101010
#define maxlog 20
#define min(a,b) ((a)<=(b)?(a):(b))
#define max(a,b) ((a)>=(b)?(a):(b))
#define stmin(a,b) min(het[(a)][lg[(b)-(a)+1]],het[(b)-(1<<lg[(b)-(a)+1])+1][lg[(b)-(a)+1]])

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

int n,m,len,ans;
int a[maxn+1];
int fst[maxn+1],snd[maxn+1],tak[maxn+1];
int sa[maxn+1],rnk[maxn+1],het[maxn+1][maxlog+1],lg[maxn+1];
int col[maxn+1],cnt[maxn+1];

int main(){
	cltstream::read(n);
	for(re int i=1;i<=n;++i){
		int x,y;
		cltstream::read(m);
		cltstream::read(x);
		for(re int j=2;j<=m;++j,x=y){
			cltstream::read(y);
			a[++len]=y-x+1864;
		}
		a[++len]=4000;
	}
	for(re int i=1;i<=len;++i)
		++tak[fst[i]=a[i]];
	for(re int i=1;i<=4000;++i)
		tak[i]+=tak[i-1];
	for(re int i=len;i>=1;--i)
		sa[tak[fst[i]]--]=i;
	for(re int k=1,mx=4000;;k<<=1,mx=fst[sa[len]]){
		re int cnt=0;
		for(re int i=len-k+1;i<=len;++i)
			snd[++cnt]=i;
		for(re int i=1;i<=len;++i)
			if(sa[i]>k)
				snd[++cnt]=sa[i]-k;
		for(re int i=0;i<=mx;++i)
			tak[i]=0;
		for(re int i=1;i<=len;++i)
			++tak[fst[i]];
		for(re int i=1;i<=mx;++i)
			tak[i]+=tak[i-1];
		for(re int i=len;i>=1;--i)
			sa[tak[fst[snd[i]]]--]=snd[i];
		for(re int i=1;i<=len;++i)
			snd[i]=fst[i];
		fst[sa[1]]=1;
		for(re int i=2;i<=len;++i)
			fst[sa[i]]=fst[sa[i-1]]+(snd[sa[i]]!=snd[sa[i-1]]||snd[sa[i]+k]!=snd[sa[i-1]+k]);
		if(fst[sa[len]]==len)
			break;
	}
	for(re int i=1;i<=len;++i)
		rnk[sa[i]]=i;
	for(re int i=1,j=0;i<=len;++i)
		if(rnk[i]>1){
			if(j)
				--j;
			re int pos=sa[rnk[i]-1];
			for(;i+j<=len&&pos+j<=len&&a[i+j]==a[pos+j];++j);
			het[rnk[i]][0]=j;
		}
	for(re int i=2;i<=len;++i)
		lg[i]=lg[i>>1]+1;
	for(re int j=1,k=1;j<=lg[len];++j,k<<=1)
		for(re int i=1;i+(k<<1)-1<=len;++i)
			het[i][j]=min(het[i][j-1],het[i+k][j-1]);
	for(re int i=1,j=1;i<=len;++i)
		if(a[i]<4000)
			col[rnk[i]]=j;
		else
			++j;
	for(re int l=1,r=0;;col[l]&&--cnt[col[l]],col[l]&&!cnt[col[l]]&&--cnt[0],++l){
		for(;r<len&&cnt[0]<n;++r,col[r]&&!cnt[col[r]]&&++cnt[0],++cnt[col[r]]);
		if(r<len){
			for(;!col[l]||cnt[col[l]]>1;col[l]&&--cnt[col[l]],++l);
			ans=max(ans,stmin(l+1,r));
		}
		else
			break;
	}
	cltstream::write(ans+1);
	clop();
	return 0;
}
