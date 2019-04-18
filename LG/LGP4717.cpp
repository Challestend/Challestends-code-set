#include<cstdio>
#define re register
#define maxn 17
#define mod 998244353

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

int n;
int F[1<<maxn][3],G[1<<maxn][3];

#define FWT(F,tp) {\
	for(re int p=1;p<n;p<<=1)\
		for(re int i=0;i<n;i+=p<<1)\
			for(re int j=i;j<i+p;++j){\
				F[j+p][0]=!tp?(F[j+p][0]+F[j][0])%mod:(F[j+p][0]-F[j][0]+mod)%mod;\
				F[j][1]=!tp?(F[j][1]+F[j+p][1])%mod:(F[j][1]-F[j+p][1]+mod)%mod;\
				re int x=F[j][2],y=F[j+p][2];\
				F[j][2]=(x+y)%mod;\
				F[j+p][2]=(x-y+mod)%mod;\
				if(tp){\
					F[j][2]=499122177LL*F[j][2]%mod;\
					F[j+p][2]=499122177LL*F[j+p][2]%mod;\
				}\
			}\
}

int main(){
	cltstream::read(n);
	n=1<<n;
	for(re int i=0;i<n;++i){
		cltstream::read(F[i][0]);
		F[i][1]=F[i][2]=F[i][0];
	}
	for(re int i=0;i<n;++i){
		cltstream::read(G[i][0]);
		G[i][1]=G[i][2]=G[i][0];
	}
	FWT(F,0);
	FWT(G,0);
	for(re int j=0;j<3;++j)
		for(re int i=0;i<n;++i)
			F[i][j]=1LL*F[i][j]*G[i][j]%mod;
	FWT(F,1);
	for(re int j=0;j<3;++j)
		for(re int i=0;i<n;++i)
			cltstream::write(F[i][j],i<n-1?32:10);
	clop();
	return 0;
}
