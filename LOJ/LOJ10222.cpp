#include<cstdio>

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

int n,m,ans;
struct matrix{
    int a[5][5];

    inline void init(){
        for(int i=0;i<5;++i)
            for(int j=0;j<5;++j)
                a[i][j]=0;
    }

    inline void operator*=(matrix& X){
        matrix Y;
        for(int i=0;i<5;++i)
            for(int j=0;j<5;++j)
                for(int k=0;k<5;++k)
                    Y.a[i][j]=(1LL*Y.a[i][j]+1LL*X.a[i][k]*a[k][j]%m)%m;
        *this=Y;
    }

    matrix(){
        init();
    }
};
matrix A,B;
int u[5]={1,3,9,1,2};

void matpow(int x){
    if(x==1)
        B=A;
    else{
        matpow(x>>1);
        B*=B;
        if(x&1)
            B*=A;
    }
}

int main(){
    read(n),read(m);
    if(n<=3){
        write(u[n-1]%m);
        return 0;
    }
    A.a[2][0]=-1;
    A.a[0][0]=A.a[0][2]=A.a[0][3]=A.a[0][4]=0;
    A.a[1][0]=A.a[1][1]=A.a[1][3]=A.a[1][4]=0;
    A.a[2][1]=0;
    A.a[3][0]=A.a[3][1]=A.a[3][2]=A.a[3][3]=0;
    A.a[4][0]=A.a[4][1]=A.a[4][2]=0;
    A.a[0][1]=A.a[1][2]=A.a[2][4]=1;
    A.a[3][4]=A.a[4][3]=A.a[4][4]=1;
    A.a[2][2]=A.a[2][3]=2;
    matpow(n-3);
    for(int i=0;i<5;++i)
        ans=(1LL*ans+1LL*B.a[2][i]*u[i]%m)%m;
    write((ans+m)%m);
    return 0;
}
