#include<cstdio>
#define re register

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

	inline void read(){
		int sn=1,M3=0,M5=0,M8=0,M11=0;
		char c=gc();
		for(;(c<48||c>57)&&c!=EOF;c=gc());
		for(;c>=48&&c<=57&&c!=EOF;c=gc()){
			M3=((M3<<3)+(M3<<1)+(c^48))%3;
			M5=((M5<<3)+(M5<<1)+(c^48))%5;
			M8=((M8<<3)+(M8<<1)+(c^48))%8;
			M11=((M11<<3)+(M11<<1)+(c^48))%11;
		}
		if(!M3||!M5||!M8||!M11){
			puts("Yes");
			if(!M3)
				printf("3 ");
			if(!M5)
				printf("5 ");
			if(!M8)
				printf("8 ");
			if(!M11)
				printf("11 ");
		}
		else
			puts("No");
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

int main(){
	cltstream::read();
	return 0;
}
