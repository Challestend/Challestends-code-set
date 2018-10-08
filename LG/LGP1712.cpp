#include<cstdio>
#include<algorithm>
#define re register
#define maxn 500000
#define maxm 200000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))

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

int n,m,ans=2e9;
int pos[maxn<<1|1];
std::pair<int,int> a[maxn|1];
int maxw[maxn<<3|1],add[maxn<<3|1];

inline bool cmp(std::pair<int,int> p,std::pair<int,int> q){
    return p.second-p.first<q.second-q.first;
}

void update(int L,int R,int x,int cur,int l,int r){
    if(l>=L&&r<=R){
        maxw[cur]+=x;
        add[cur]+=x;
    }
    else{
        int mid=(l+r)>>1;
        maxw[cur<<1]+=add[cur];
        add[cur<<1]+=add[cur];
        maxw[cur<<1|1]+=add[cur];
        add[cur<<1|1]+=add[cur];
        add[cur]=0;
        if(L<=mid)
            update(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update(L,R,x,cur<<1|1,mid+1,r);
        maxw[cur]=max(maxw[cur<<1],maxw[cur<<1|1]);
    }
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i].first);
        pos[++pos[0]]=a[i].first;
        cltstream::read(a[i].second);
        pos[++pos[0]]=a[i].second;
    }
    std::sort(pos+1,pos+pos[0]+1);
    for(re int i=1;i<=n;++i){
        a[i].first=std::lower_bound(pos+1,pos+pos[0]+1,a[i].first)-pos;
        a[i].second=std::lower_bound(pos+1,pos+pos[0]+1,a[i].second)-pos;
    }
    std::sort(a+1,a+n+1,cmp);
    for(re int head=0,tail=0;tail<n;){
        for(;maxw[1]<m;++tail,update(a[tail].first,a[tail].second,1,1,1,pos[0]));
        for(;maxw[1]>=m;++head,update(a[head].first,a[head].second,-1,1,1,pos[0]));
        ans=min(ans,pos[a[tail].second]-pos[a[tail].first]-pos[a[head].second]+pos[a[head].first]);
    }
    cltstream::write(ans<2e9?ans:-1);
    return 0;
}
