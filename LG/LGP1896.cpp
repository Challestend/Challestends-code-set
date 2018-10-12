#include<cstdio>
#define re register
#define maxn 9
#define maxm 81
#define maxsize 512

namespace cltstream{
    #define LOCAL

    #ifdef LOCAL
        #define gc getchar
    #else
        #define size 1048576

        char str[size+1],*head=str,*tail=str;
        inline char gc(){
            if(head==tail){
                tail=(head=str)+fread(str,1,size,stdin);
                if(head==tail)
                    return EOF;
            }
            return *head++;
        }

        #undef size
    #endif

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

int n,m,size;
int cnt[maxsize+1],a[maxsize+1]={1},b[maxsize+1][maxsize+1];
long long f[maxn+1][maxm+1][maxsize+1];

int binConvert(int x){
    int bin[12];
    for(re int i=1;i<=n;bin[i]=x&1,x>>=1,++i);
    int res=0;
    for(re int i=n;i>=1;--i)
        res=10*res+bin[i];
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    size=1<<n;
    for(re int i=1;i<size;++i){
        cnt[i]=cnt[i>>1]+(i&1);
        a[i]=a[i>>1]&a[i>>2]&(~(i&(i>>1))&1);
    }
    for(re int i=0;i<size;++i)
        for(re int j=0;j<size;++j)
            b[i][j]=(~((((i<<1)|i|(i>>1))&j)||(((j<<1)|j|(j>>1))&i)))&1;
    for(re int i=0;i<size;++i)
        if(a[i])
            f[1][cnt[i]][i]=1;
    for(re int i=2;i<=n;++i)
        for(re int j=0;j<=m;++j)
            for(re int k=0;k<size;++k)
                if(a[k]&&cnt[k]<=j)
                    for(re int l=0;l<size;++l)
                        if(b[k][l])
                            f[i][j][k]+=f[i-1][j-cnt[k]][l];
    for(re int i=1;i<size;++i)
        f[n][m][0]+=f[n][m][i];
    cltstream::write(f[n][m][0],'\n');
    return 0;
}
