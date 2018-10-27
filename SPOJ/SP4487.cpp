#include<cstdio>
#define re register
#define maxn 100000
#define max(a,b) ((a)>=(b)?(a):(b))

namespace cltstream{
    #define size 1048576
    char cltin[size+1],*ih=cltin,*it=cltin;
    inline char gc(){
        #ifdef ONLINE_JUDGE
            if(ih==it){
                it=(ih=cltin)+fread(cltin,1,size,stdin);
                if(ih==it)
                    return EOF;
            }
            return *ih++;
        #else
            return getchar();
        #endif
    }

    char cltout[size+1],*oh=cltout,*ot=cltout+size;
    inline void pc(char c){
        if(c==-1)
            fwrite(cltout,1,oh-cltout,stdout);
        else{
            if(oh==ot){
                fwrite(cltout,1,size,stdout);
                oh=cltout;
            }
            *oh++=c;
        }
    }
    #undef size

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
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        pc(text);
    }
}

namespace SplayTree{
    struct node{
        node *ftr,*ch[2];
        int size;
        int val,ms,ls,rs,sum;
    };

    struct tree{
        #define gs(a) (a->ftr->ch[1]==a)

        node mempool[(maxn<<1)+1],*memtop,*null,*root;

        inline void connect(node*& x,node*& y,int side){
            x->ftr=y;
            if(y!=null)
                y->ch[side]=x;
        }

        inline void newNode(int v,node*& x,int side){
            re node* p=++memtop;
            connect(p,x,side);
            p->ch[0]=p->ch[1]=null;
            p->size=1;
            p->val=p->ms=p->ls=p->rs=p->sum=v;
        }

        inline void pushUp(node*& p){
            if(p==null)
                return;
            p->size=p->ch[0]->size+p->ch[1]->size+1;
            p->ms=p->ls=p->rs=p->sum=p->val;
            p->ms=max(max(p->ch[0]->ms,p->ms),p->ch[0]->rs+p->ls);
            p->ls=max(p->ch[0]->ls,p->ch[0]->sum+p->ls);
            p->rs=max(p->rs,p->sum+p->ch[0]->rs);
            p->sum+=p->ch[0]->sum;
            p->ms=max(max(p->ms,p->ch[1]->ms),p->rs+p->ch[1]->ls);
            p->ls=max(p->ls,p->sum+p->ch[1]->rs);
            p->rs=max(p->ch[1]->rs,p->ch[1]->sum+p->rs);
            p->sum+=p->ch[1]->sum;
        }

        inline void rotate(node*& x){
            re node *y=x->ftr,*z=y->ftr;
            if(y==null)
                return;
            re int sx=gs(x),sy=gs(y);
            connect(x->ch[sx^1],y,sx);
            connect(y,x,sx^1);
            if(z!=null)
                connect(x,z,sy);
            pushUp(y);
            pushUp(x);
        }

        inline void splay(node*& x,node*& y){
            y=y->ftr;
            for(re node* z=x->ftr;z!=y;rotate(x),z=x->ftr)
                if(z->ftr!=y)
                    rotate(gs(z)==gs(x)?z:x);
        }

        inline node* findRank(int x){
            for(re node* cur=root;cur!=null;){
                re int ln=cur->ch[0]->size;
                if(x==ln)
                    return cur;
                else
                    if(x<ln)
                        cur=cur->ch[0];
                    else{
                        x-=ln;
                        cur=cur->ch[1];
                    }
            }
            return null;
        }

        inline void Insert(int pos,int v){
            re node* p=findRank(pos+1);
            splay(p,root);
            root=p;
            re node* q=p->ch[0];
            for(;q->ch[1]!=null;q=q->ch[1]);
            splay(q,p->ch[0]);
            newNode(v,q,1);
            pushUp(q);
            pushUp(p);
        }

        inline void Delete(int pos){
            re node* p=findRank(pos+1);
            splay(p,root);
            if(p->ch[0]==null){
                root=p->ch[1];
                root->ftr=null;
                return;
            }
            if(p->ch[1]==null){
                root=p->ch[0];
                root->ftr=null;
                return;
            }
            re node* l=p->ch[0];
            for(;l->ch[1]!=null;l=l->ch[1]);
            splay(l,p->ch[0]);
            re node* r=p->ch[1];
            for(;r->ch[0]!=null;r=r->ch[0]);
            splay(r,p->ch[1]);
            root=l;
            root->ftr=null;
            connect(r,root,1);
        }

        inline void Modify(int pos,int v){
            re node* p=findRank(pos+1);
            splay(p,root);
            root=p;
            p->val=v;
            pushUp(p);
        }

        inline int Query(int l,int r){
            re node *lsn=findRank(l),*rsn=findRank(r+2);
            splay(rsn,root);
            root=rsn;
            splay(lsn,root->ch[0]);
            return lsn->ch[1]->ms;
        }

        void print(node*& p){
            printf("%d/%d\n",p->size,null->size);
            if(p==null)
                return;
            else{
                print(p->ch[0]);
                printf("val=%d,ls=%d,rs=%d,ms=%d\n",p->val,p->ls,p->rs,p->ms);
                print(p->ch[1]);
            }
        }

        tree(){
            memtop=mempool;
            null=memtop;
            null->ftr=null->ch[0]=null->ch[1]=null;
            null->size=null->val=null->ms=null->ls=null->rs=null->sum=0;
            root=++memtop;
            root->size=1;
            root->ftr=root->ch[0]=root->ch[1]=null;
            root->val=root->ms=root->ls=root->rs=root->sum=0;
            newNode(0,root,1);
            splay(root->ch[1],root);
        }
    };
}

int n,m;
SplayTree::tree st;

int main(){
    cltstream::read(n);
    re SplayTree::node* cur=st.root;
    for(re int i=1;i<=n;++i){
        re int x;
        cltstream::read(x);
        st.newNode(x,cur,1);
        cur=cur->ch[1];
    }
    puts("FAQ!!!!!!!!");
    st.print(st.root);
    puts("FAQ AGAIN!!");
    return 0;
}
