#include<cstdio>
#define max(a,b) ((a)>=(b)?(a):(b))

template <typename T>
inline void read(T& x){
    int sn=1;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45)
        sn=-1,c=getchar();
    for(x=0;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    x*=sn;
}

template <typename T>
inline void write(T x){
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

namespace SplayTree{
    const int maxn=4500010;

    struct node{
        node *fa,*ch[2];
        int size,val,sum,ls,rs,ms,upd,rev;
    };

    struct tree{
        protected:
            node mempool[maxn],*memtop;
            node *null,*root;

            inline void pushDown(node*& p){
                if(p->upd){
                    for(int i=0;i<2;++i)
                        if(p->ch[i]!=null){
                            p->ch[i]->val=p->val;
                            p->ch[i]->sum=p->ch[i]->size*p->val;
                            p->ch[i]->ls=p->ch[i]->rs=p->ch[i]->ms=p->ch[i]->sum;
                            p->ch[i]->upd=1;
                        }
                    p->upd=0;
                }
                if(p->rev){
                    node *tmp=p->ch[0];
                    p->ch[0]=p->ch[1];
                    p->ch[1]=tmp;
                    p->ch[0]->rev^=1;
                    p->ch[1]->rev^=1;
                    p->rev=0;
                }
            }

            inline void pushUp(node*& p){
                p->size=p->ch[0]->size+p->ch[1]->size+1;
                p->sum=p->ch[0]->sum+p->ch[1]->sum+p->val;
                if(p->ch[0]!=null)
                    p->ls=p->ch[0]->ls;
                else
                    p->ls=p->val+(p->ch[1]->ls>=0)*p->ch[1]->ls;
                if(p->ch[1]!=null)
                    p->rs=p->ch[1]->rs;
                else
                    p->rs=p->val+(p->ch[0]->rs>=0)*p->ch[0]->rs;
                if(p->val>=0)
                    p->ms=(p->ch[0]->rs>=0)*p->ch[0]->rs+(p->ch[1]->ls>=0)*p->ch[1]->ls+p->val;
                else
                    p->ms=max(p->ch[0]->rs,p->ch[1]->ls);
                p->ms=max(max(p->ls,p->rs),p->ms);
            }

            inline void connect(node*& x,node*& y,int side){
                x->fa=y;
                y->ch[side]=x;
            }

            inline node* create(int v,node*& x,int side){
                node *p=++memtop;
                p->ch[0]=p->ch[1]=null;
                p->size=1;
                p->val=p->sum=p->ls=p->rs=p->ms=v;
                p->upd=p->rev=0;
                connect(p,x,side);
                pushUp(x);
                return p;
            }

            inline int getSide(node*& p){
                return p->fa->ch[1]==p;
            }

            inline void rotate(node*& x){
                node *y=x->fa,*z=y->fa;
                int sx=getSide(x),sy=getSide(y);
                connect(x->ch[sx^1],y,sx);
                connect(y,x,sx^1);
                connect(x,z,sy);
                pushUp(y),pushUp(x);
            }

            inline void splay(node*& x,node* y){
                for(node *p=y->fa,*q=x->fa;q!=p;rotate(x),q=x->fa)
                    if(q->fa!=p)
                        rotate(getSide(q)==getSide(x)?q:x);
            }

            inline node* findRank(int x){
                for(node *p=root;;){
                    pushDown(p);
                    int ln=p->ch[0]->size+1;
                    if(x==ln)
                        return p;
                    else
                        if(x>ln){
                            x-=ln;
                            p=p->ch[1];
                        }
                        else
                            p=p->ch[0];
                }
            }

            void print(node*& p,int x){
                if(p==null)
                    return;
                print(p->ch[0],0);
                write(p->val);
                if(x==0||(x==1&&p->ch[1]!=null))
                    putchar(',');
                print(p->ch[1],x&1);
            }
        public:
            inline void init(){
                memtop=mempool;
                null=memtop;
                null->fa=null->ch[0]=null;
                create(0,null,1);
                null->ch[1]=null;
                null->size=0;
                root=memtop;
                create(0,root,1);
            }

            inline void inserts(int pos,int tot){
                node *p=findRank(pos+2);
                splay(p,root);
                root=p;
                p=findRank(pos+1);
                splay(p,root->ch[0]);
                for(int i=1;i<=tot;++i){
                    int x;
                    read(x);
                    create(x,p,1);
                    p=p->ch[1];
                    rotate(p);
                }
                pushUp(root);
            }

            inline void deletes(int pos,int tot){
                node *p=findRank(pos+tot+1);
                splay(p,root);
                root=p;
                p=findRank(pos);
                splay(p,root->ch[0]);
                p->ch[1]=null;
                pushUp(p);
                pushUp(root);
            }

            inline void updates(int pos,int tot,int c){
                node *p=findRank(pos+tot+1);
                splay(p,root);
                root=p;
                p=findRank(pos);
                splay(p,root->ch[0]);
                p=p->ch[1];
                p->val=c;
                p->sum=p->size*c;
                p->ls=p->rs=p->ms=c;
                p->upd=1;
                p=p->fa;
                pushUp(p);
                pushUp(root);
            }

            inline void reverses(int pos,int tot){
                node *p=findRank(pos+tot+1);
                splay(p,root);
                root=p;
                p=findRank(pos);
                splay(p,root->ch[0]);
                p->ch[1]->rev^=1;
            }

            inline void getsums(int pos,int tot){
                node *p=findRank(pos+tot+1);
                splay(p,root);
                root=p;
                p=findRank(pos);
                splay(p,root->ch[0]);
                write(p->ch[1]->sum);
                putchar(10);
            }

            inline void getmaxsums(){
                write(root->ms);
                putchar(10);
            }

            inline void check(){
                printf("%d number(s) in total.\n",root->size-2);
                putchar('<');
                print(root,1);
                putchar('>');
                putchar(10);
                putchar(10);
            }

            tree(){
                init();
            }
    };
}

int n,m;
SplayTree::tree st;
char opt[16];

int main(){
    read(n),read(m);
    st.inserts(0,n);
    st.check();
    for(int i=1;i<=m;++i){
        scanf("%s",opt);
        int x,y,z;
        switch(opt[2]){
            case 'S':
                read(x),read(y);
                st.inserts(x,y);
                break;
            case 'L':
                read(x),read(y);
                st.deletes(x,y);
                break;
            case 'K':
                read(x),read(y),read(z);
                st.updates(x,y,z);
                break;
            case 'V':
                read(x),read(y);
                st.reverses(x,y);
                break;
            case 'T':
                read(x),read(y);
                st.getsums(x,y);
                break;
            case 'X':
                st.getmaxsums();
                break;
        }
        st.check();
    }
    return 0;
}
