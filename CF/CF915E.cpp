#include<cstdio>
#include<set>
#define re register
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

int n,m,ans;
struct node{
    int l,r,val;

    node(re int _l,re int _r=-1,re int _val=-1){
        l=_l;
        r=_r;
        val=_val;
    }
};
std::set<node> s;

inline bool operator<(re node p,re node q){
    return p.l<q.l;
}

inline _it split(re int pos){
    re _it it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    --it;
    re int l=it->l,r=it->r,val=it->val;
    s.erase(it);
    s.insert(node(l,pos-1,val));
    return s.insert(node(pos,r,val)).first;
}

inline void IntervalAssign(re int l,re int r,re int x){
    re _it itr=split(r+1),itl=split(l);
    for(_it p=itl;p!=itr;++p)
        ans-=(p->r-p->l+1)*p->val;
    s.erase(itl,itr);
    s.insert(node(l,r,x));
    ans+=(r-l+1)*x;
    cltstream::write(ans,'\n');
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    s.insert(node(1,n,1));
    ans=n;
    for(re int i=1;i<=m;++i){
        re int l,r,x;
        cltstream::read(l);
        cltstream::read(r);
        cltstream::read(x);
        IntervalAssign(l,r,x-1);
    }
    return 0;
}
