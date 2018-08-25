#include<cstdio>
#define re register

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

namespace ScapegoatTree{
    const int maxn=100010;
    const double alpha=0.75;

    struct node{
        node* ch[2];
        int cost,pre,size,valid,exist;
    };

    struct tree{
        protected:
            node mempool[maxn],*memtop;
            node *null,*root;
            node *rec[maxn],*vec[maxn];
            int rectop,vectop;
            long long sumc,sump;

            inline node* newNode(int x,int y){
                node* p=rectop>=0?rec[rectop--]:++memtop;
                p->ch[0]=p->ch[1]=null;
                p->cost=x,p->pre=y,p->size=p->valid=p->exist=1;
                return p;
            }

            node** insNode(node*& p,int x,int y){
                if(p==null){
                    p=newNode(x,y);
                    return &null;
                }
                else{
                    p->size++,p->valid++;
                    node** res=insNode(p->ch[x>p->cost],x,y);
                    if(p->ch[0]->size>alpha*p->size||p->ch[1]->size>alpha*p->size)
                        res=&p;
                    return res;
                }
            }

            void breakDown(node*& p){
                if(p==null)
                    return;
                else{
                    breakDown(p->ch[0]);
                    if(p->exist)
                        vec[++vectop]=p;
                    else
                        rec[++rectop]=p;
                    breakDown(p->ch[1]);
                }
            }

            node* buildUp(int l,int r){
                if(l>r)
                    return null;
                else{
                    int mid=l+r>>1;
                    node* p=vec[mid];
                    p->ch[0]=buildUp(l,mid-1);
                    p->ch[1]=buildUp(mid+1,r);
                    p->size=p->ch[0]->size+p->ch[1]->size+1;
                    p->valid=p->ch[0]->valid+p->ch[1]->valid+1;
                    return p;
                }
            }

            inline void rebuild(node*& p){
                vectop=-1;
                breakDown(p);
                p=buildUp(0,vectop);
            }

            inline bool find(int x){
                for(node* p=root;p!=null;p=p->ch[x>p->cost])
                    if(x==p->cost&&p->exist)
                        return true;
                return false;
            }
        public:
            inline void init(){
                memtop=mempool;
                null=memtop;
                null->ch[0]=null->ch[1]=null;
                null->cost=null->pre=null->size=null->valid=null->exist=0;
                root=null;
                rectop=-1;
                sumc=sump=0;
            }

            inline void Insert(int x,int y){
                if(find(x))
                    return;
                else{
                    sumc+=x,sump+=y;
                    node** res=insNode(root,x,y);
                    if(*res!=null)
                        rebuild(*res);
                }
            }

            inline void Delete(int x){
                x=x==2?root->valid:1;
                for(node* p=root;p!=null;){
                    p->valid--;
                    int ln=p->ch[0]->valid+p->exist;
                    if(x==ln&&p->exist){
                        sumc-=p->cost,sump-=p->pre;
                        p->exist=0;
                        return;
                    }
                    else
                        if(x>ln)
                            x-=ln,p=p->ch[1];
                        else
                            p=p->ch[0];
                }
                if(root->valid<alpha*root->size)
                    rebuild(root);
            }

            inline void printAns(){
                write(sumc);
                putchar(32);
                write(sump);
            }

            tree(){
                init();
            }
    };
}

ScapegoatTree::tree st;

int main(){
    freopen("LGP2073.in","r",stdin);
    freopen("LGP2073.out","w",stdout);
    for(;;){
        int opt,x,y;
        read(opt);
        if(opt==-1)
            break;
        else
            if(opt==1)
                read(x),read(y),st.Insert(x,y);
            else
                st.Delete(opt);
    }
    st.printAns();
    fclose(stdin);
    fclose(stdout);
    return 0;
}
