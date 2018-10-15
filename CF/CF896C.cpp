#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#define re register
#define maxn 100000
#define _it std::set<node>::iterator

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

int n,m,seed,maxval;
struct node{
    int l,r;
    mutable long long val;

    node(int _l,int _r=-1,long long _val=-1){
        l=_l;
        r=_r;
        val=_val;
    }
};
std::set<node> s;
std::vector<std::pair<long long,int> > vec;

inline int rnd(){
    int res=seed;
    seed=(7LL*seed+13)%1000000007;
    return res;
}

inline void swap(int& l,int& r){
    int tmp=l;
    l=r;
    r=tmp;
}

int cltpow(int x,int y,int mod){
    if(y==1)
        return x;
    int res=cltpow(x,y>>1,mod);
    res=1LL*res*res%mod;
    if(y&1)
        res=1LL*res*x%mod;
    return res;
}

inline bool operator<(node p,node q){
    return p.l<q.l;
}

inline _it split(int pos){
    _it it=std::lower_bound(s.begin(),s.end(),node(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    --it;
    int l=it->l,r=it->r;
    long long val=it->val;
    s.erase(it);
    s.insert(node(l,pos-1,val));
    return s.insert(node(pos,r,val)).first;
}

inline void IntervalAdd(int l,int r,int x){
    _it itr=split(r+1),itl=split(l);
    for(re _it p=itl;p!=itr;++p)
        p->val+=x;
}

inline void IntervalAssign(int l,int r,int x){
    _it itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,x));
}

inline long long IntervalXth(int l,int r,int x){
    _it itr=split(r+1),itl=split(l);
    vec.clear();
    for(re _it p=itl;p!=itr;++p)
        vec.push_back(std::make_pair(p->val,p->r-p->l+1));
    std::sort(vec.begin(),vec.end());
    for(re unsigned i=0;i<vec.size();++i){
        x-=vec[i].second;
        if(x<=0)
            return vec[i].first;
    }
    return 0;
}

inline int IntervalXpow(int l,int r,int x,int y){
    _it itr=split(r+1),itl=split(l);
    int res=0;
    for(re _it p=itl;p!=itr;++p)
        res=(1LL*res+1LL*(p->r-p->l+1)*cltpow(p->val%y,x,y)%y)%y;
    return res;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    cltstream::read(seed);
    cltstream::read(maxval);
    for(re int i=1;i<=n;++i)
        s.insert(node(i,i,rnd()%maxval+1));
    for(re int i=1;i<=m;++i){
        int opt=rnd()%4+1,l=rnd()%n+1,r=rnd()%n+1,x,y;
        if(l>r)
            swap(l,r);
        switch(opt){
            case 1:
                x=rnd()%maxval+1;
                IntervalAdd(l,r,x);
                break;
            case 2:
                x=rnd()%maxval+1;
                IntervalAssign(l,r,x);
                break;
            case 3:
                x=rnd()%(r-l+1)+1;
                cltstream::write(IntervalXth(l,r,x),'\n');
                break;
            case 4:
                x=rnd()%maxval+1;
                y=rnd()%maxval+1;
                cltstream::write(IntervalXpow(l,r,x,y),'\n');
                break;
        }
    }
    return 0;
}
