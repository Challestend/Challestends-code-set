#include<cstdio>
#include<iostream>
#include<string>
#define maxlen 10000
#define maxdig 10000000
using namespace std;

struct bignum{
    int s[(maxlen>>3)+1];
    bignum(){
        s[0]=1;
        for(int i=1;i<=(maxlen>>3);++i)
            s[i]=0;
    }
    void read(){
        string str;
        cin>>str;
        int len=str.length();
        for(;len%8;str='0'+str,++len);
        s[0]=(len>>3);
        for(int i=1;i<=s[0];++i)
            for(int j=0;j<8;++j)
                s[s[0]-i+1]=(s[s[0]-i+1]<<3)+(s[s[0]-i+1]<<1)+(str[(i-1<<3)+j]^48);
    }

    void print(){
        printf("%d",s[s[0]]);
        for(int i=s[0]-1;i>=1;--i)
            printf("%08d",s[i]);
    }
};
bignum a,b,c;

bool operator>=(bignum& a,bignum& b){
    if(a.s[0]>b.s[0])
        return true;
    for(int i=a.s[0];i>=1;--i)
        if(a.s[i]>b.s[i])
            return true;
        else
            return false;
    return true;
}

bool operator!=(bignum& a,bignum& b){
    if(a.s[0]!=b.s[0])
        return true;
    for(int i=a.s[0];i>=1;--i)
        if(a.s[i]!=b.s[i])
            return true;
    return false;
}

void operator-=(bignum& a,bignum& b){
    for(int i=1;i<=b.s[0];++i){
        a.s[i]-=b.s[i];
        if(a.s[i]<0)
            --a.s[i+1],a.s[i]+=maxdig;
    }
    for(int i=b.s[0]+1;i<a.s[0]&&a.s[i]<0;++i)
        --a.s[i+1],a.s[i]+=maxdig;
    if(a.s[0]>1&&!a.s[a.s[0]])
        --a.s[0];
}

int main(){
    a.read();
    b.read();
    for(;a!=c&&b!=c;){
        if(a>=b)
            a-=b;
        else
            b-=a;
    }
    if(a!=c)
        a.print();
    else
        b.print();
    return 0;
}
