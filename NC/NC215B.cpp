#include<cstdio>
#define re register
#define maxn 100000
#define maxm 200000

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

int n,m,ec;
int des[(maxm<<1)+1],suc[(maxm<<1)+1],las[maxn+1],col[maxn+1];

inline void connect(int x,int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

bool bi_color(int cur){
    for(re int i=las[cur];i;i=suc[i])
        if(col[des[i]]){
            if(col[des[i]]==col[cur])
                return false;
        }
        else{
            col[des[i]]=col[cur]^1;
            if(!bi_color(des[i]))
                return false;
        }
    return true;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    if(!m){
        putchar(49);
        return 0;
    }
    for(re int i=1;i<=m;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    col[1]=2;
    if(bi_color(1))
        putchar(50);
    else
        putchar(51);
    return 0;
}
