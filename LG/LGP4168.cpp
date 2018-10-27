#include<cstdio>
#include<algorithm>
#define re register
#define maxn 40000
#define maxblock 200
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
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m,size,x;
int a[maxn+1],value[maxn+1],id[maxn+1],cnt[maxblock+1][maxn+1],ans[maxblock+1][maxblock+1];

inline void swap(int& x,int& y){
    int tmp=x;
    x=y;
    y=tmp;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        value[i]=a[i];
    }
    std::sort(value+1,value+n+1);
    value[0]=std::unique(value+1,value+n+1)-value-1;
    for(re int i=1;i<=n;++i)
        a[i]=std::lower_bound(value+1,value+value[0]+1,a[i])-value;
    for(;(size+1)*(size+1)<=n;++size);
    for(re int i=1;(i-1)*size+1<=n;++i)
        for(re int j=(i-1)*size+1;j<=i*size&&j<=n;++j)
            id[j]=i;
    for(re int i=1;(i-1)*size+1<=n;++i){
        int res=0;
        for(re int j=min(i*size,n);j>=1;--j){
            ++cnt[i][a[j]];
            if(cnt[i][a[j]]>cnt[i][res]||(cnt[i][a[j]]==cnt[i][res]&&a[j]<res))
                res=a[j];
            if(id[j]!=id[j-1])
                ans[id[j]][i]=res;
        }
    }
    for(re int i=1;i<=m;++i){
        int l,r;
        cltstream::read(l);
        l=(l+x-1)%n+1;
        cltstream::read(r);
        r=(r+x-1)%n+1;
        if(l>r)
            swap(l,r);
        if(id[l]==id[r]){
            int res=0;
            for(re int j=l;j<=r;++j){
                ++cnt[0][a[j]];
                if(cnt[0][a[j]]>cnt[0][res]||(cnt[0][a[j]]==cnt[0][res]&&a[j]<res))
                    res=a[j];
            }
            cltstream::write(x=value[res],'\n');
            for(re int j=l;j<=r;++j)
                cnt[0][a[j]]=0;
        }
        else{
            int res=ans[id[l]+1][id[r]-1];
            for(re int j=l;j<=id[l]*size;++j){
                ++cnt[0][a[j]];
                int p=cnt[0][a[j]]+cnt[id[r]-1][a[j]]-cnt[id[l]][a[j]];
                int q=cnt[0][res]+cnt[id[r]-1][res]-cnt[id[l]][res];
                if(p>q||(p==q&&a[j]<res))
                    res=a[j];
            }
            for(re int j=(id[r]-1)*size+1;j<=r;++j){
                ++cnt[0][a[j]];
                int p=cnt[0][a[j]]+cnt[id[r]-1][a[j]]-cnt[id[l]][a[j]];
                int q=cnt[0][res]+cnt[id[r]-1][res]-cnt[id[l]][res];
                if(p>q||(p==q&&a[j]<res))
                    res=a[j];
            }
            cltstream::write(x=value[res],'\n');
            for(re int j=l;j<=id[l]*size;++j)
                cnt[0][a[j]]=0;
            for(re int j=(id[r]-1)*size+1;j<=r;++j)
                cnt[0][a[j]]=0;
        }
    }
    return 0;
}
