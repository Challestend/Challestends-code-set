#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#define re register
#define maxn 1000
#define mod 1000000007

namespace cltstream{
    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=getchar();
        for(;c!=45&&(c<48||c>57);c=getchar());
        if(c==45)
            sn=-1,c=getchar();
        for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
        x*=sn;
    }

    template <typename _tp>
    inline void write(_tp x){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
    }
}

std::string s;
int num[maxn+1],v[10][10][maxn+1][2],f[10][10][maxn+1][2];

int cltpow(int x,int y){
    if(y==0)
        return 1;
    if(y==1)
        return x;
    int res=cltpow(x,y>>1);
    res=1LL*res*res%mod;
    if(y&1)
        res=1LL*res*x%mod;
    return res;
}

int dfs(int pre2,int pre1,int pos,int touchLimit,int valid,int palin){
    if(!touchLimit&&v[pre2][pre1][pos][palin]){
        printf("(%d,%d,%d,%d,%d,%d)\n",pre2,pre1,pos,touchLimit,valid,palin);
        return f[pre2][pre1][pos][palin];}
    if(!pos)
        return palin;
    if(!touchLimit&&palin){
        v[pre2][pre1][pos][palin]=1;
        f[pre2][pre1][pos][palin]=cltpow(10,pos);
        return f[pre2][pre1][pos][palin];
    }
    int res=0;
    if(touchLimit)
        for(re int i=0;i<=num[pos];++i){
            int k=dfs(pre1,i,pos-1,i==num[pos],valid+(valid||i),palin||(valid&&i==pre1)||(valid>1&&i==pre2));
            res=(res+k)%mod;
        }
    else{
        for(re int i=0;i<10;++i){
            int k=dfs(pre1,i,pos-1,0,valid+(valid||i),palin||(valid&&i==pre1)||(valid>1&&i==pre2));
            res=(res+k)%mod;
        }
        v[pre2][pre1][pos][palin]=1;
        f[pre2][pre1][pos][palin]=res;
    }
    return res;
}

int main(){
    std::cin>>s;
    num[0]=s.length();
    for(re int i=1;i<=num[0];++i)
        num[num[0]-i+1]=s[i-1]^48;
    --num[1];
    for(int i=1;i<=num[0]&&num[i]<0;num[i]+=10,--num[++i]);
    if(!num[num[0]])
        --num[0];
    int l=dfs(0,0,num[0],1,0,0);
    memset(v,0,sizeof(v));
    memset(f,0,sizeof(f));
    std::cin>>s;
    num[0]=s.length();
    for(re int i=1;i<=num[0];++i)
        num[num[0]-i+1]=s[i-1]^48;
    int r=dfs(0,0,num[0],1,0,0);
    cltstream::write(r-l);
    return 0;
}
