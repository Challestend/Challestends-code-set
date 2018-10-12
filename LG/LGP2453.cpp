#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 200
#define maxm 200
#define min(a,b) ((a)<=(b)?(a):(b))

namespace cltstream{
    #ifdef ONLINE_JUDGE
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
    #else
        #define gc getchar
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

int n,m;
std::string s1,s2;
int cost[5],f[maxn+1][maxm+1];

int main(){
    std::cin>>s1>>s2;
    n=s1.length();
    m=s2.length();
    for(re int i=0;i<5;++i)
        cltstream::read(cost[i]);
    for(re int i=0;i<=n;++i)
        f[i][0]=i*cost[0];
    for(re int i=0;i<=m;++i)
        f[0][i]=i*cost[3];
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j)
            f[i][j]=2e9;
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=m;++j){
            f[i][j]=min(f[i][j],f[i-1][j]+cost[0]);
            f[i][j]=min(f[i][j],f[i-1][j-1]+cost[1]);
            if(s1[i-1]==s2[j-1])
                f[i][j]=min(f[i][j],f[i-1][j-1]+cost[2]);
            f[i][j]=min(f[i][j],f[i][j-1]+cost[3]);
            if(i>=2&&j>=2&&s1[i-1]==s2[j-2]&&s1[i-2]==s2[j-1])
                f[i][j]=min(f[i][j],f[i-2][j-2]+cost[4]);
        }
    for(re int i=0;i<n;++i)
        f[n][m]=min(f[n][m],f[i][m]+(n-i)*cost[0]-1);
    cltstream::write(f[n][m],'\n');
    return 0;
}
