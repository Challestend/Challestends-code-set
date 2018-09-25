#include<cstdio>
#include<cstring>
#define re register
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) ((a)>=0?(a):(-(a)))

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

int a,b;
int num[11],v[10][11][2],f[10][11][2];

void breakDown(int x){
    if(x)
        for(num[0]=0;x;num[++num[0]]=x%10,x/=10);
    else
        num[num[0]=1]=0;
}

int dfs(int pre,int pos,int touchLimit,int leadingZero){
    if(!touchLimit&&v[pre][pos][leadingZero])
        return f[pre][pos][leadingZero];
    if(!pos)
        return 1;
    int res=0;
    if(touchLimit){
        for(re int i=0;i<=num[pos];++i)
            if(leadingZero||abs(i-pre)>=2)
                res+=dfs(i,pos-1,touchLimit&&i==num[pos],leadingZero&&!i);
    }
    else{
        for(re int i=0;i<10;++i)
            if(leadingZero||abs(i-pre)>=2)
                res+=dfs(i,pos-1,touchLimit,leadingZero&&!i);
        v[pre][pos][leadingZero]=1;
        f[pre][pos][leadingZero]=res;
    }
    return res;
}

int main(){
    cltstream::read(a);
    cltstream::read(b);
    breakDown(a-1);
    a=dfs(0,num[0],1,1);
    memset(v,0,sizeof(v));
    memset(f,0,sizeof(f));
    breakDown(b);
    b=dfs(0,num[0],1,1);
    cltstream::write(b-a);
    return 0;
}
