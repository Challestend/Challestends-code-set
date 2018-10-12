#include<cstdio>
#define re register
#define maxn 100000
#define maxm 100000
#define maxblock 320
#define maxval 100000
#define ID(a) (((a)-1)/size+1)

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
int a[maxn+1],ufs[maxn+1],val[maxn+1];
int pos[maxblock+1][maxval+1],cnt[maxblock+1][maxval+1];

int find(int x){
    return ufs[x]==x?x:ufs[x]=find(ufs[x]);
}

inline void init(int x){
    for(re int i=(x-1)*size+1;i<=x*size&&i<=n;++i){
        if(!pos[x][a[i]]){
            ufs[i]=i;
            val[i]=a[i];
            pos[x][a[i]]=i;
        }
        else
            ufs[i]=pos[x][a[i]];
        ++cnt[x][a[i]];
    }
}

inline void breakDown(int x){
    for(re int i=(x-1)*size;i<=x*size&&i<=n;++i){
        a[i]=val[find(i)];
        pos[x][a[i]]=cnt[x][a[i]]=0;
    }
}

inline void solve(int x,int y){
    for(re int i=y+1;i<=maxval;++i)
        if(pos[x][i]){
            if(!pos[x][i-y]){
                val[pos[x][i]]-=y;
                pos[x][i-y]=pos[x][i];
                pos[x][i]=0;
                cnt[x][i-y]=cnt[x][i];
                cnt[x][i]=0;
            }
            else{
                ufs[pos[x][i]]=pos[x][i-y];
                pos[x][i]=0;
                cnt[x][i-y]+=cnt[x][i];
                cnt[x][i]=0;
            }
        }
}

inline void update(int l,int r,int x){
    breakDown(ID(l));
    for(re int i=l;i<=ID(l)*size&&i<=r;++i)
        a[i]-=(a[i]>x)*x;
    init(ID(l));
    if(ID(l)<ID(r)){
        breakDown(ID(r));
        for(re int i=(ID(r)-1)*size+1;i<=r;++i)
            a[i]-=(a[i]>x)*x;
        init(ID(r));
    }
    for(re int i=ID(l)+1;i<=ID(r)-1;++i)
        solve(i,x);
}

inline int getcnt(int l,int r,int x){
    int res=0;
    for(re int i=l;i<=ID(l)*size&&i<=r;++i)
        res+=(val[find(i)]==x);
    if(ID(l)<ID(r))
        for(re int i=(ID(r)-1)*size+1;i<=r;++i)
            res+=(val[find(i)]==x);
    for(re int i=ID(l)+1;i<=ID(r)-1;++i)
        res+=cnt[i][x];
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(;(size+1)*(size+1)<=n;++size);
    for(re int i=1;i<=n;++i)
        cltstream::read(a[i]);
    for(re int i=1;(i-1)*size+1<=n;++i)
        init(i);
    for(re int i=1;i<=m;++i){
        int opt,l,r,x;
        cltstream::read(opt);
        cltstream::read(l);
        cltstream::read(r);
        cltstream::read(x);
        if(opt==1)
            update(l,r,x);
        else
            cltstream::write(getcnt(l,r,x),'\n');
    }
    return 0;
}
