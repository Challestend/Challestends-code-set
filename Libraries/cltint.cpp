#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define min(a,b) ((a)<=(b)?(a):(b))

namespace cltint{
    #define maxsize 1000000
    #define base 100000000
    struct bigInt{
        int sign,size;
        int val[maxsize+1];

        inline void operator=(std::string src){
            if(src[0]==45){
                sign=-1;
                src=src.substr(1);
            }
            size=src.length();
            for(;size>1&&src[0]==48;--size,src=src.substr(1));
            for(re int i=1;i<=size;++i)
                val[size-i+1]=src[i-1]^48;
            re int tmp=0;
            for(;(tmp<<3)+1<=size;++tmp){
                for(re int i=min((tmp+1)<<3,size);i>(tmp<<3);--i)
                    val[i-1]+=(val[i]<<3)+(val[i]<<1);
                val[tmp+1]=val[(tmp<<3)+1];
            }
            size=tmp;
            if(size==1&&val[size]==0)
                sign=1;
        }

        inline void print(){
            if(sign==-1)
                putchar(45);
            printf("%d",val[size]);
            for(re int i=size-1;i>=1;--i)
                printf("%08d",val[i]);
        }

        bigInt(){
            sign=1;
            size=0;
            for(register int i=0;i<=maxsize;++i)
                val[i]=0;
        }
    };
    #undef maxsize

    template <typename _tp>
    inline std::string strprint(_tp src){
        std::string str;
        for(;src;str=(char)((src%10)^48)+str,src/=10);
        return str;
    }
}

int main(){
    for(;;){
        unsigned long long num;
        scanf("%I64u",&num);
        cltint::bigInt a;
        a=cltint::strprint(num);
        a.print();
        putchar(10);
    }
    return 0;
}
