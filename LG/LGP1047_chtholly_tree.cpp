#include<cstdio>
#include<algorithm>
#include<vector>
#include<set>
#define re register
#define maxn 10000
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

    node(int _l,int _r=-1,int _val=-1){
        l=_l;
        r=_r;
        val=_val;
    }
};
std::set<node> s;

inline bool operator<(node p,node q){
    return p.l<q.l;
}

inline _it split(int pos){
    _it it=std::lower_bound(s.begin(),s.end(),node(pos));
    if(it!=s.end()&&it->l==pos)
        return it;
    --it;
    int l=it->l,r=it->r,val=it->val;
    s.erase(it);
    s.insert(node(l,pos-1,val));
    return s.insert(node(pos,r,val)).first;
}

inline void IntervalAssign(int l,int r,int x=0){
    _it itr=split(r+1),itl=split(l);
    s.erase(itl,itr);
    s.insert(node(l,r,x));
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    s.insert(node(0,n,1));
    for(re int i=1;i<=m;++i){
        int x,y;
        cltstream::read(x);
        cltstream::read(y);
        IntervalAssign(x,y);
    }
    for(_it p=s.begin();p!=s.end();++p)
        ans+=(p->r-p->l+1)*p->val;
    cltstream::write(ans,'\n');
    return 0;
}
