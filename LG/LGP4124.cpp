#include<cstdio>
#include<iostream>
#include<cstring>
#include<string>
#define re register

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

long long n;
int num[12],v[10][12][4][2];
long long f[10][12][4][2];

long long dfs(int pre,int pos,int touchLimit,int con,int four,int eight){
    if(!touchLimit&&v[pre][pos][con][four|eight])
        return f[pre][pos][con][four|eight];
    if(!pos)
        return con==3;
    long long res=0;
    if(touchLimit){
        for(re int i=pos==11;i<=num[pos];++i)
            if(!((four&&i==8)||(eight&&i==4)))
                res+=dfs(i,pos-1,i==num[pos],con<3?(i==pre)*con+1:3,four||i==4,eight||i==8);
    }
    else{
        for(re int i=pos==11;i<=9;++i)
            if(!((four&&i==8)||(eight&&i==4)))
                res+=dfs(i,pos-1,0,con<3?(i==pre)*con+1:3,four||i==4,eight||i==8);
        v[pre][pos][con][four|eight]=1;
        f[pre][pos][con][four|eight]=res;
    }
    return res;
}

int main(){
    cltstream::read(n);
    for(re int i=1;i<=11;num[i]=n%10,n/=10,++i);
    --num[1];
    for(re int i=1;num[i]<0;num[i]+=10,--num[++i]);
    long long L=dfs(0,11,1,0,0,0);
    memset(v,0,sizeof(v));
    memset(f,0,sizeof(f));
    cltstream::read(n);
    for(re int i=1;i<=11;num[i]=n%10,n/=10,++i);
    long long R=dfs(0,11,1,0,0,0);
    cltstream::write(R-L);
    return 0;
}
