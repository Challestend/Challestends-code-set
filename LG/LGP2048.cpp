#include<cstdio>
#include<queue>
#define re register
#define maxn 500000
#define maxlog 18
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,k,L,R;
int lg[maxn+1],a[maxn+1],st[maxn+1][maxlog+1];

inline int rmq(int l,int r){
    int x=lg[r-l+1];
    return a[st[l][x]]>=a[st[r-(1<<x)+1][x]]?st[l][x]:st[r-(1<<x)+1][x];
}

struct node{
    int val,x,y,l,r;

    inline void init(int _x,int _l,int _r){
        x=_x;
        l=_l;
        r=_r;
        y=rmq(l,r);
        val=a[y]-a[x];
    }
};
node N;
std::priority_queue<node> h;
long long ans;

inline bool operator<(node p,node q){
    return p.val<q.val;
}

int main(){
    cltstream::read(n);
    cltstream::read(k);
    cltstream::read(L);
    cltstream::read(R);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        a[i]+=a[i-1];
        st[i][0]=i;
    }
    for(re int i=2;i<=n;++i)
        lg[i]=lg[i>>1]+1;
    for(re int i=1;i<=maxlog;++i)
        for(re int j=1;j+(1<<i)-1<=n;++j)
            st[j][i]=a[st[j][i-1]]>=a[st[j+(1<<(i-1))][i-1]]?st[j][i-1]:st[j+(1<<(i-1))][i-1];
    for(re int i=1;i<=n;++i)
        if(i+L-1<=n){
            N.init(i-1,i+L-1,min(i+R-1,n));
            h.push(N);
        }
    for(re int i=1;i<=k;++i){
        N=h.top();
        int res=N.val,x=N.x,y=N.y,l=N.l,r=N.r;
        h.pop();
        ans+=res;
        if(l<=y-1){
            N.init(x,l,y-1);
            h.push(N);
        }
        if(y+1<=r){
            N.init(x,y+1,r);
            h.push(N);
        }
    }
    cltstream::write(ans,'\n');
    return 0;
}
