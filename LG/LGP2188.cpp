#include<cstdio>
#include<cstring>
#define re register
#define abs(a) ((a)>=0?(a):(-(a)))

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

long long l,r,ansl,ansr;
int k;
int num[19],v[10][19][2];
long long f[10][19][2];

long long dfs(int pre,int pos,int touchLimit,int leadingZero){
    if(!touchLimit&&v[pre][pos][leadingZero])
        return f[pre][pos][leadingZero];
    if(!pos)
        return !leadingZero;
    long long res=0;
    if(touchLimit){
        for(re int i=0;i<=num[pos];++i)
            if(leadingZero||abs(pre-i)<=k)
                res+=dfs(i,pos-1,i==num[pos],leadingZero&&(!i));
    }
    else{
        for(re int i=0;i<=9;++i)
            if(leadingZero||abs(pre-i)<=k)
                res+=dfs(i,pos-1,0,leadingZero&&(!i));
        v[pre][pos][leadingZero]=1;
        f[pre][pos][leadingZero]=res;
    }
    return res;
}

int main(){
    cltstream::read(l);
    cltstream::read(r);
    cltstream::read(k);
    for(num[0]=0,--l;l;num[++num[0]]=l%10,l/=10);
    ansl=dfs(0,num[0],1,1);
    memset(v,0,sizeof(v));
    memset(f,0,sizeof(f));
    for(num[0]=0;r;num[++num[0]]=r%10,r/=10);
    ansr=dfs(0,num[0],1,1);
    cltstream::write(ansr-ansl,'\n');
    return 0;
}
