// luogu-judger-enable-o2
#include<functional>
#include<algorithm>
#include<iterator>
#include<cstring>
#include<cassert>
#include<cstdio>
using namespace std;
int seed=233;
inline void cmin(register int&a,register int&b){a=a<b?a:b;}
char s[2333333];
struct treap
{
    int l,r,cero;
    int dl,dr,dc;
    int mu,mc,rk;
    int sum,siz;
    treap*ls,*rs;
    void upd()
    {
        int uno=r-l+1;
        mu=uno;
        mc=cero;
        siz=1;
        sum=uno;
        if(ls)
        {
            cmin(mu,ls->mu);
            cmin(mc,ls->mc);
            siz+=ls->siz;
            sum+=ls->sum;
        }
        if(rs)
        {
            cmin(mu,rs->mu);
            cmin(mc,rs->mc);
            siz+=rs->siz;
            sum+=rs->sum;
        }
    }
    void pd()
    {
        if(dl||dr||dc)
        {
        #define PD(x) 	if(x)\
                        {\
                            int du=dr-dl;\
                            x->l+=dl;\
                            x->r+=dr;\
                            x->cero+=dc;\
                            x->dl+=dl;\
                            x->dr+=dr;\
                            x->dc+=dc;\
                            x->mu+=dr-dl;\
                            x->mc+=dc;\
                            x->sum+=x->siz*du;\
                        }
        PD(ls);
        PD(rs);
        dl=dr=dc=0;
        }
    }
    treap(){rk=seed=(seed*12345ll+19260817)%998244353;}
}a[1926817],*root,*ca=a;
inline treap*nouveau()
{
    return ++ca;
}
void split_l(treap*x,treap*&l,treap*&r,int key)
{
    if(!x){l=r=0;return;}
    x->pd();
    if(x->l<key)
    {
        split_l(x->rs,l,r,key);
        x->rs=l;
        x->upd();
        l=x;
    }
    else
    {
        split_l(x->ls,l,r,key);
        x->ls=r;
        x->upd();
        r=x;
    }
}
void split_r(treap*x,treap*&l,treap*&r,int key)
{
    if(!x){l=r=0;return;}
    x->pd();
    if(x->r<key)
    {
        split_r(x->rs,l,r,key);
        x->rs=l;
        x->upd();
        l=x;
    }
    else
    {
        split_r(x->ls,l,r,key);
        x->ls=r;
        x->upd();
        r=x;
    }
}
treap*merge(treap*a,treap*b)
{
    if(!a)return b;
    if(!b)return a;
    if(a->rk<b->rk)
    {
        a->pd();
        a->rs=merge(a->rs,b);
        a->upd();
        return a;
    }
    else
    {
        b->pd();
        b->ls=merge(a,b->ls);
        b->upd();
        return b;
    }
}
void intersec(int l,int r,treap*&a,treap*&b,treap*&c)
{
    split_r(a,a,b,l-1);
    split_l(b,b,c,r+2);
}
treap*rightMost(treap*x){for(;x->rs;x=x->rs)x->pd();x->pd();return x;}
treap*leftMost(treap*x){for(;x->ls;x=x->ls)x->pd();x->pd();return x;}
void updl(treap*x)
{
    treap*stk[55];
    register int cs=0;
    for(;x;x=x->ls)stk[++cs]=x;
    for(;cs;)stk[cs--]->upd();
}
void updr(treap*x)
{
    treap*stk[55];
    register int cs=0;
    for(;x;x=x->rs)stk[++cs]=x;
    for(;cs;)stk[cs--]->upd();
}
treap*combine(treap*a,treap*b)
{
    if(!b)return a;
    if(!a)
    {
        leftMost(b)->cero=23333333;
        updl(b);
        return b;
    }
    //printf("combine %d %d %d %d\n",a->l,a->r,b->l,b->r);
    treap*l=rightMost(a);
    treap*r=leftMost(b);
    r->cero=r->l-l->r-1;
    updl(b);
    return merge(a,b);
}
/*treap*extl(treap*&a,treap*&b)
{
    split_l(b,a,b,leftMost(b)->l+1);
}
treap*extr(treap*&a,treap*&b)
{
    split_l(a,a,b,rightMost(a)->l);
}*/
void eins(int l,int r)
{
    treap*a,*b,*c;
    a=root;
    intersec(l,r,a,b,c);
    //printf("%p %p\n",a,c);
    if(b)
    {
        treap*m=leftMost(b);
        if(m->l<l)
        {
            treap*x=nouveau();
            x->l=m->l;
            x->r=l-1;
            //printf("new: %d %d\n",x->l,x->r);
            a=combine(a,x);
        }
        m=rightMost(b);
        if(r<m->r)
        {
            treap*x=nouveau();
            x->l=r+1;
            x->r=m->r;
            //printf("new: %d %d\n",x->l,x->r);
            a=combine(a,x);
        }
    }
    root=combine(a,c);
    //printf("%d %d %p %p\n",root->l,root->r,root->ls,root->rs);
}
void zwei(int l,int r)
{
    treap*a,*b,*c;
    a=root;
    intersec(l,r,a,b,c);
    treap*x=nouveau();
    x->l=min(b?leftMost(b)->l:l,l);
    x->r=max(b?rightMost(b)->r:r,r);
    //printf("%d %d\n",x->l,x->r);
    x->upd();
    //printf("%p %p\n",a,c);
    a=combine(a,x);
    root=combine(a,c);
}
treap*getnil(treap*x)
{
    if(x->mu>0)return 0;
    if(x->r-x->l+1==0)return x;
    x->pd();
    treap*qwq=0;
    if(x->ls)qwq=getnil(x->ls);
    return qwq?qwq:getnil(x->rs);
}
treap*getstuck(treap*x)
{
    //if(!x)puts("WA");
    //printf("%d %d %d %d %p %p %p\n",x->l,x->r,x->cero,x->mc,x,x->ls,x->rs);
    if(x->mc>0)return 0;
    if(x->cero==0)return x;
    x->pd();
    treap*qwq=0;
    //puts("QAQ");
    if(x->ls)qwq=getstuck(x->ls);
    return qwq?qwq:getstuck(x->rs);
}
void clnil()
{
    for(treap*qwq;root&&(qwq=getnil(root));)
    {
        treap*a,*b,*c;
        a=root;
        int ll=qwq->l;
        split_l(a,a,b,ll);
        split_l(b,b,c,ll+1);
        root=combine(a,c);
    }
}
void clstuck()
{
    //puts("cling");
    for(treap*qwq;root&&(qwq=getstuck(root));)
    {
        //fprintf(stderr,"stuck: %d %d\n",qwq->l,qwq->r);
        treap*a,*b,*c;
        a=root;
        int ll=qwq->l,rr=qwq->r;
        split_l(a,a,b,ll);
        split_l(b,b,c,ll+1);
        rightMost(a)->r=rr;
        updr(a);
        root=combine(a,c);
    }
}
void drei(int l,int r)
{
    treap*a,*b,*c;
    a=root;
    split_l(a,a,b,l+1);
    split_l(b,b,c,r+1);
    if(b)
    {
        --b->dl;
        --b->l;
        --b->dc;
        --b->cero;
        b->pd();
        b->upd();
        a=combine(a,b);
    }
    root=combine(a,c);
    clstuck();
}
void fier(int l,int r)
{
    treap*a,*b,*c;
    a=root;
    split_r(a,a,b,l);
    split_r(b,b,c,r);
    if(b)
    {
        ++b->dr;
        ++b->r;
        --b->dc;
        --b->cero;
        b->pd();
        b->upd();
        a=combine(a,b);
    }
    root=combine(a,c);
    clstuck();
}
void fuenf(int l,int r)
{
    treap*a,*b,*c;
    a=root;
    split_r(a,a,b,l);
    split_r(b,b,c,r);
    if(b)
    {
        --b->dr;
        --b->r;
        ++b->dc;
        ++b->cero;
        b->pd();
        b->upd();
        a=combine(a,b);
    }
    root=combine(a,c);
    clnil();
}
void sechs(int l,int r)
{
    treap*a,*b,*c;
    a=root;
    split_l(a,a,b,l+1);
    split_l(b,b,c,r+1);
    if(b)
    {
        ++b->dl;
        ++b->l;
        ++b->dc;
        ++b->cero;
        b->pd();
        b->upd();
        a=combine(a,b);
    }
    root=combine(a,c);
    clnil();
}
int sieben(int l,int r)
{
    treap*a,*b,*c;
    int res=0;
    a=root;
    intersec(l,r,a,b,c);
    if(b)
    {
        treap*x=leftMost(b);
        res+=x->l-max(x->l,l);
        x=rightMost(b);
        res+=min(x->r,r)-x->r;
        //printf("%d %d\n",x->l,x->r);
        res+=b->sum;
    }
    a=merge(a,b);
    root=merge(a,c);
    return res;
}
int initl[1011111],initr[1011111],ci;
void build_tree(int n)
{
    treap*stk[55];
    register int cs=0;
    stk[0]=nouveau();
    stk[0]->rk=-1;
    for(int i=1;i<=n;++i)
    {
        treap*x=nouveau();
        x->l=initl[i];
        x->r=initr[i];
        x->cero=initl[i]-initr[i-1]-1;
        //printf(". %d %d %d\n",x->cero,x->l,x->r);
        int tmp=cs;
        for(;stk[cs]->rk>x->rk;)stk[cs--]->upd();
        if(cs!=tmp)x->ls=stk[cs+1];
        stk[cs]->rs=x;
        stk[++cs]=x;
    }
    for(;cs;)stk[cs--]->upd();
    root=stk[0]->rs;
}
inline int Fin()
{
    register char c;
    register int x;
    for(;(c=getchar())<48;);
    for(x=c^48;(c=getchar())>47;)x=x*10+c-48;
    return x;
}
int main()
{
	freopen("data.in","r",stdin);
	freopen("data.ans","w",stdout);
    int n,m;
    scanf("%d %d\n",&n,&m);
    fgets(s,2333330,stdin);
    for(int i=1;i<=n;++i)s[i]=s[(i-1)*2];
    int la=1;
    s[n+1]='0';
    for(int i=1;i<=n+1;++i)
    {
        if(s[i]=='0')
        {
            if(i>la)
            {
                ++ci;
                initl[ci]=la;
                initr[ci]=i-1;
            }
            la=i+1;
        }
    }
    initr[0]=-23333333;
    //for(int i=1;i<=ci;++i)printf("[%d %d]\n",initl[i],initr[i]);
    build_tree(ci);
    //print(root);
    for(int i=1;i<=m;++i)
    {
        int op,l,r;
        op=Fin();
        l=Fin();
        r=Fin();
        switch(op)
        {
            case 1:
                eins(l,r);
                break;
            case 2:
                zwei(l,r);
                break;
            case 3:
                drei(l,r);
                break;
            case 4:
                fier(l,r);
                break;
            case 5:
                fuenf(l,r);
                break;
            case 6:
                sechs(l,r);
                break;
            case 7:
                printf("%d\n",sieben(l,r));
                break;
        }
    }
    return 0;
}
