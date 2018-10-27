#include<cstdio>
#define re register
#define maxn 15
#define maxm 100

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
        if(c==-1)
            fwrite(cltout,1,oh-cltout,stdout);
        else{
            if(oh==ot){
                fwrite(cltout,1,size,stdout);
                oh=cltout;
            }
            *oh++=c;
        }
    }
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
    inline void write(_tp x,char text=' '){
        if(x<0)
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        pc(text);
    }
}

int n,m;
int value[maxn+1],pre[maxn+1],valid[(1<<maxn)+1];
double f[maxm+1][(1<<maxn)+1];
char str[20];

char* print(int status,int digcnt){
    for(re int i=0;i<digcnt;str[i]=(status&1)^48,status>>=1,++i);
    return str;
}

int main(){
    cltstream::read(m);
    cltstream::read(n);
    for(re int i=1;i<=n;++i){
        cltstream::read(value[i]);
        int x;
        for(cltstream::read(x);x;pre[i]|=1<<(x-1),cltstream::read(x));
        printf("pre[%d]=%s\n",i,print(pre[i],n));
    }
    for(re int i=0;i<(1<<n);++i){
        valid[i]=1;
        for(re int j=1;j<=n;++j)
            if(((i>>(j-1))&1)&&(i|pre[j])!=i){
                valid[i]=0;
                break;
            }
    }
    for(re int i=0;i<(1<<n);++i)
        printf("valid[%s]=%d\n",print(i,n),valid[i]);
    return 0;
}
