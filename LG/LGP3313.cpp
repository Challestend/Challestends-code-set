#include<cstdio>
#define re register
#define maxn 100000
#define maxc 100000
#define maxc 100000
#define maxlog 16
#define max(a,b) ((a)>=(b)?(a):(b))

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

namespace SegmentTree{
    struct node{
        node *lc,*rc;
        int cnt,sumw,maxw;
    };

    struct tree{
        node mempool[maxlog*maxn+1],*memtop,*null,*root[maxc+1];
        node *rec[maxlog*maxn+1];
        int rectop;

        tree(){
            memtop=mempool;
            null=memtop;
            null->lc=null->rc=null;
            null->cnt=null->sumw=null->maxw=0;
            for(re int i=0;i<=maxc;++i)
                root[i]=null;
            rectop=0;
        }

        inline node* newNode(re int x=0){
            re node* p=rectop?rec[rectop--]:++memtop;
            p->lc=p->rc=null;
            p->cnt=1;
            p->sumw=p->maxw=x;
            return p;
        }

        void insNode(re int L,re int x,re node*& p,re int l,re int r){
            if(l==r){
                if(p==null)
                    p=newNode(x);
                else
                    p->sumw=p->maxw=x;
            }
            else{
                if(p==null)
                    p=newNode();
                re int mid=(l+r)>>1;
                if(L<=mid)
                    insNode(L,x,p->lc,l,mid);
                else
                    insNode(L,x,p->rc,mid+1,r);
                p->cnt=p->lc->cnt+p->rc->cnt;
                p->sumw=p->lc->sumw+p->rc->sumw;
                p->maxw=max(p->lc->maxw,p->rc->maxw);
            }
        }

        void delNode(re int L,re node*& p,re int l,re int r){
            if(l==r){
                rec[++rectop]=p;
                p=null;
            }
            else{
                re int mid=(l+r)>>1;
                if(L<=mid)
                    delNode(L,p->lc,l,mid);
                else
                    delNode(L,p->rc,mid+1,r);
                p->cnt--;
                if(!p->cnt){
                    rec[++rectop]=p;
                    p=null;
                }
                else{
                    p->sumw=p->lc->sumw+p->rc->sumw;
                    p->maxw=max(p->lc->maxw,p->rc->maxw);
                }
            }
        }

        int getsum(re int L,re int R,re node*& p,re int l,re int r){
            if(p==null||(l>=L&&r<=R))
                return p->sumw;
            else{
                re int mid=(l+r)>>1,res=0;
                if(L<=mid)
                    res+=getsum(L,R,p->lc,l,mid);
                if(R>mid)
                    res+=getsum(L,R,p->rc,mid+1,r);
                return res;
            }
        }

        int getmax(re int L,re int R,re node*& p,re int l,re int r){
            if(p==null||(l>=L&&r<=R))
                return p->maxw;
            else{
                re int mid=(l+r)>>1,res=0;
                if(L<=mid)
                    res=max(res,getmax(L,R,p->lc,l,mid));
                if(R>mid)
                    res=max(res,getmax(L,R,p->rc,mid+1,r));
                return res;
            }
        }
    };
}

int n,m,ec,vc;
int w[maxn+1],c[maxn+1];
int des[(maxn<<1)+1],suc[(maxn<<1)+1],las[maxn+1];
int f[maxn+1],dep[maxn+1],size[maxn+1],hes[maxn+1],id[maxn+1],top[maxn+1];
SegmentTree::tree st;

inline void connect(re int x,re int y){
    des[++ec]=y;
    suc[ec]=las[x];
    las[x]=ec;
}

void dfs1(re int cur,re int ftr){
    f[cur]=ftr;
    dep[cur]=dep[f[cur]]+1;
    size[cur]=1;
    re int maxsize=0;
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur]){
            dfs1(des[i],cur);
            size[cur]+=size[des[i]];
            if(maxsize<size[des[i]]){
                maxsize=size[des[i]];
                hes[cur]=des[i];
            }
        }
}

void dfs2(re int cur,re int curtop){
    id[cur]=++vc;
    st.insNode(id[cur],w[cur],st.root[c[cur]],1,n);
    top[cur]=curtop;
    if(!hes[cur])
        return;
    dfs2(hes[cur],curtop);
    for(re int i=las[cur];i;i=suc[i])
        if(des[i]!=f[cur]&&des[i]!=hes[cur])
            dfs2(des[i],des[i]);
}

inline void swap(re int& x,re int& y){
    re int tmp=x;
    x=y;
    y=tmp;
}

int pthsum(re int x,re int y){
    re int _c=c[x],res=0;
    for(;top[x]!=top[y];){
        if(dep[top[x]]>dep[top[y]])
            swap(x,y);
        res+=st.getsum(id[top[y]],id[y],st.root[_c],1,n);
        y=f[top[y]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    return res+st.getsum(id[x],id[y],st.root[_c],1,n);
}

int pthmax(re int x,re int y){
    re int _c=c[x],res=0;
    for(;top[x]!=top[y];){
        if(dep[top[x]]>dep[top[y]])
            swap(x,y);
        res=max(res,st.getmax(id[top[y]],id[y],st.root[_c],1,n));
        y=f[top[y]];
    }
    if(dep[x]>dep[y])
        swap(x,y);
    return max(res,st.getmax(id[x],id[y],st.root[_c],1,n));
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(re int i=1;i<=n;++i){
        cltstream::read(w[i]);
        cltstream::read(c[i]);
    }
    for(re int i=1;i<n;++i){
        re int x,y;
        cltstream::read(x);
        cltstream::read(y);
        connect(x,y);
        connect(y,x);
    }
    dfs1(1,0);
    dfs2(1,1);
    for(re int i=1;i<=m;++i){
        re char opt=gc();
        for(;opt<'A'||opt>'Z';opt=gc());
        opt=gc();
        re int x,y;
        cltstream::read(x);
        cltstream::read(y);
        switch(opt){
            case 'C':
                st.delNode(id[x],st.root[c[x]],1,n);
                st.insNode(id[x],w[x],st.root[c[x]=y],1,n);
                break;
            case 'W':
                st.insNode(id[x],w[x]=y,st.root[c[x]],1,n);
                break;
            case 'S':
                cltstream::write(pthsum(x,y),'\n');
                break;
            case 'M':
                cltstream::write(pthmax(x,y),'\n');
                break;
        }
    }
    return 0;
}
