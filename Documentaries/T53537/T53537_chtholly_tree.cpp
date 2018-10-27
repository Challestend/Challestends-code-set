#include<cstdio>
#include<set>
#define re register
#define maxn 100000
#define maxm 100000
#define mod 998244353
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define _it std::set<node>::iterator
#define FILE(filename) freopen(filename".in","r",stdin);freopen(filename".ans","w",stdout);

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

int n,m;
struct node{
    int l,r;
    mutable int val;

    node(int _l,int _r=-1,int _val=-1){
        l=_l;
        r=_r;
        val=_val;
    }
};
std::set<node> s;

inline bool operator<(node x,node y){
    return x.l<y.l;
}

inline _it split(int pos){
    re _it it=s.lower_bound(node(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    else{
        --it;
        re int l=it->l,r=it->r,val=it->val;
        s.erase(it);
        s.insert(node(l,pos-1,val));
        return s.insert(node(pos,r,val)).first;
    }
}

inline void IntervalCut(int l,int r,int x){
    re _it itr=split(r+1),itl=split(l);
    for(;itl!=itr;++itl)
        if(itl->val>x)
            itl->val-=x;
}

inline void IntervalAssignToMin(int l,int r){
    re _it itr=split(r+1),itl=split(l);
    re int res=2e9;
    for(re _it p=itl;p!=itr;res=min(res,p->val),++p);
    s.erase(itl,itr);
    s.insert(node(l,r,res));
}

inline void IntervalPre(int l,int r,int x){
    re _it itr=split(r+1),itl=split(l);
    re int pos=0,res=-2e9;
    for(;itl!=itr;++itl)
        if(itl->val<x&&itl->val>res){
            pos=itl->l;
            res=itl->val;
        }
    if(pos>0)
        cltstream::write(pos,'\n');
    else
        puts("GREAT");
}

int main(){
    FILE("T53537");
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        re int x;
        cltstream::read(x);
        s.insert(node(i,i,x));
    }
    for(re int i=1;i<=m;++i){
        re int opt,l,r,x;
        cltstream::read(opt);
        cltstream::read(l);
        cltstream::read(r);
        switch(opt){
            case 1:
                cltstream::read(x);
                IntervalCut(l,r,x);
                break;
            case 2:
                IntervalAssignToMin(l,r);
                break;
            case 3:
                cltstream::read(x);
                IntervalPre(l,r,x);
                break;
        }
    }
    re int ans=0;
    for(re _it p=s.begin();p!=s.end();(ans+=1LL*(p->r-p->l+1)*p->val%mod)%=mod,++p);
    cltstream::write(ans,'\n');
    return 0;
}
