#include<cstdio>
#include<iostream>
#include<string>
#define re register
#define maxn 2000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

namespace cltstream{
    #define gc getchar

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

const int dx[2]={1,0},dy[2]={0,1};

int n,m,acnt;
int a[maxn+1][maxn+1],nxt[maxn+1][maxn+1],cnt[maxn+1][maxn+1];
std::string ans;

void getStr(int x,int y,std::string& res){
    for(;x<=n&&y<=n;){
        res=res+(char)(a[x][y]+'a');
        int dir=nxt[x][y];
        x+=dx[dir];
        y+=dy[dir];
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        std::string s;
        std::cin>>s;
        for(re int j=1;j<=n;++j)
            a[i][j]=s[j-1]-'a';
    }
    for(re int i=1;i<n;++i)
        for(re int j=1;j<n;++j)
            nxt[i][j]=(a[i+1][j]>a[i][j+1]);
    for(re int i=1;i<n;++i)
        nxt[n][i]=1;
    for(re int i=1;i<=n;++i)
        for(re int j=1;j<=n;++j){
            cnt[i][j]=max(cnt[i-1][j],cnt[i][j-1])+(!a[i][j]);
            if(i+j-1>cnt[i][j]+m)
                cnt[i][j]=-1;
            else
                acnt=max(acnt,i+j-1);
        }
    if(acnt>=(n<<1)-1){
        for(re int i=1;i<=(n<<1)-1;++i)
            putchar('a');
        return 0;
    }
    for(re int i=acnt+1;i<=(n<<1)-1;++i)
        ans=ans+'z';
    for(re int i=1;i<=n&&i<=acnt;++i)
        if(acnt-i+1<=n){
            int j=acnt-i+1;
            std::string res;
            getStr(i+dx[nxt[i][j]],j+dy[nxt[i][j]],res);
            ans=min(ans,res);
        }
    for(re int i=1;i<=acnt;++i)
        putchar('a');
    std::cout<<ans;
    return 0;
}
