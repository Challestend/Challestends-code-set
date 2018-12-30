#include<cstdio>
#include<cstdlib>
#include<ctime>
#include"cltrnd.h"
#define re register

namespace cltstream{
	template <typename _tp>
	inline void read(_tp& x){
		int sn=1;
		char c=getchar();
		for(;c!=45&&(c<48||c>57)&&c!=EOF;c=getchar());
		if(c==45&&c!=EOF)
			sn=-1,c=getchar();
		for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=getchar());
		x*=sn;
	}

	template <typename _tp>
	inline void write(_tp x,char text=' '){
		if(x<0)
			putchar(45),x=-x;
		if(!x)
			putchar(48);
		else{
			int digit[20];
			for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
			for(;digit[0];putchar(digit[digit[0]--]^48));
		}
		putchar(text);
	}
}

int p[10000001];
struct edge{
	int src,des;
};
edge e[10000001];

inline void printHelp(){
	puts("1: Generate a normal tree.");
	puts("2: Generate a tree with a long enough chain.");
	puts("3: Generate a single chain.");
	puts("4: Generate a flower.");
}

inline void genNormalTree(int size){
	for(re int i=1;i<=size;p[i]=i,++i);
	cltlib::rnd_shuffle(p,1,size);
	for(re int i=2;i<=size;++i){
		e[i].src=p[cltlib::rnd()%(i-1)+1];
		e[i].des=p[i];
	}
	cltlib::rnd_shuffle(e,2,size);
	for(re int i=2;i<=size;++i){
		if(cltlib::rnd()&1)
			cltlib::swp(e[i].src,e[i].des);
		cltstream::write(e[i].src);
		cltstream::write(e[i].des,'\n');
	}
}

inline void genLongChain(int size){
	for(re int i=1;i<=size;p[i]=i,++i);
	cltlib::rnd_shuffle(p,1,size);
	int chainLength=cltlib::rnd()%size+1;
	for(re int i=2;i<=chainLength;++i){
		e[i].src=p[i-1];
		e[i].des=p[i];
	}
	for(re int i=chainLength+1;i<=size;++i){
		e[i].src=p[cltlib::rnd()%(i-1)+1];
		e[i].des=p[i];
	}
	cltlib::rnd_shuffle(e,2,size);
	for(re int i=2;i<=size;++i){
		if(cltlib::rnd()&1)
			cltlib::swp(e[i].src,e[i].des);
		cltstream::write(e[i].src);
		cltstream::write(e[i].des,'\n');
	}
}

inline void genSingleChain(int size){
	for(re int i=1;i<=size;p[i]=i,++i);
	cltlib::rnd_shuffle(p,1,size);
	for(re int i=2;i<=size;++i){
		e[i].src=p[i-1];
		e[i].des=p[i];
	}
	cltlib::rnd_shuffle(e,2,size);
	for(re int i=2;i<=size;++i){
		if(cltlib::rnd()&1)
			cltlib::swp(e[i].src,e[i].des);
		cltstream::write(e[i].src);
		cltstream::write(e[i].des,'\n');
	}
}

inline void genFlower(int size){
	for(re int i=1;i<=size;p[i]=i,++i);
	cltlib::rnd_shuffle(p,1,size);
	for(re int i=2;i<=size;++i){
		e[i].src=p[1];
		e[i].des=p[i];
	}
	cltlib::rnd_shuffle(e,2,size);
	for(re int i=2;i<=size;++i){
		if(cltlib::rnd()&1)
			cltlib::swp(e[i].src,e[i].des);
		cltstream::write(e[i].src);
		cltstream::write(e[i].des,'\n');
	}
}

int main(){
	cltlib::srnd(time(0));
	printHelp();
	int tp;
	printf("Type=");
	cltstream::read(tp);
	for(;tp<1||tp>4;){
		system("cls");
		puts("Invalid tree type!");
		printHelp();
		printf("Type=");
		cltstream::read(tp);
	}
	system("cls");
	printf("Type=%d\n",tp);
	int n;
	printf("Size=");
	cltstream::read(n);
	for(;;){
		if(n<=0){
			system("cls");
			puts("Size must be a positive integer!");
			printf("Type=%d\n",tp);
			printf("Size=");
			cltstream::read(n);
			continue;
		}
		if(n>10000000){
			system("cls");
			puts("Size is too large!");
			printf("Type=%d\n",tp);
			printf("Size=");
			cltstream::read(n);
			continue;
		}
		break;
	}
	system("cls");
	printf("Type=%d\n",tp);
	printf("Size=%d\n",n);
	char fn[100000];
	printf("Filename=");
	scanf("%s",fn);
	freopen(fn,"w",stdout);
	switch(tp){
		case 1:
			genNormalTree(n);
			break;
		case 2:
			genLongChain(n);
			break;
		case 3:
			genSingleChain(n);
			break;
		case 4:
			genFlower(n);
			break;
	}
	system("cls");
	return 0;
}
