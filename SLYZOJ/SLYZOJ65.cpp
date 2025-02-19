#include<cstdio>
#define re register
#define maxn 600000
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

int n,m;
int bit[maxn+1][2];

inline void modify(re int x,re int y){
	for(re int i=x;i<=n;i+=lowbit(i)){
		bit[i][0]^=y;
		bit[i][1]^=(x&1)?y:0;
	}
}

inline int query(re int x){
	re int res=0;
	for(re int i=x;i>=1;i-=lowbit(i))
		res^=((x&1)?0:bit[i][0])^bit[i][1];
	return res;
}

int main(){
	cltstream::read(n);
	cltstream::read(m);
	for(re int i=1;i<=n;++i){
		re int x;
		cltstream::read(x);
		modify(i,x);
		modify(i+1,x);
	}
	for(re int i=1;i<=m;++i){
		re int opt,x,y,z;
		cltstream::read(opt);
		cltstream::read(x);
		cltstream::read(y);
		switch(opt){
			case 1:
				z=query(x)^query(x-1)^y;
				modify(x,z);
				modify(x+1,z);
				break;
			case 2:
				cltstream::read(z);
				modify(x,z);
				modify(y+1,z);
				break;
			case 3:
				cltstream::write(query(y)^query(x-1),10);
				break;
		}
	}
	clop();
	return 0;
}
