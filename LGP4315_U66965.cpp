#include<iostream>
#include<cstring>
#include<cstdio>
#define maxn 2000010
#define ll long long
#define re register
#define FOR(i,l,r) for(re ll i=l;i<=r;i++)
using namespace std;

ll tag1[maxn<<2],tag2[maxn<<2],ans[maxn<<2],head[maxn<<1],a[maxn];
ll top[maxn],son[maxn],depth[maxn],fa[maxn],siz[maxn],id[maxn],dd[maxn];
ll n,m,k,t,num,cnt,x,y,z,w,q;
string s;

struct hz{
    ll next;
    ll to;
    ll dis;
    ll from;
}h[maxn<<1];

inline void in(ll &x){
    x=0;ll f=1;char c=getchar();
    while(c<'0'||c>'9'){
        if(c==-1) return;
        if(c=='-')f=-1;
        c=getchar();
    }
    while(c<='9'&&c>='0'){
        x=(x<<1)+(x<<3)+(c^'0');
        c=getchar();
    }
    x=x*f;
}

inline void out(ll a){
    if(a<0){
        a*=-1;
        putchar('-');
    }
    if(a>=10)out(a/10);
    putchar(a%10+'0');
}

inline void add(ll from,ll to,ll dis){
    h[++num].next=head[from];
    h[num].to=to;
    h[num].from=from;
    h[num].dis=dis;
    head[from]=num;
}

inline ll ls(ll k){
    return k<<1;
}

inline ll rs(ll k){
    return k<<1|1;
}

inline void push_up(ll k){
    ans[k]=max(ans[ls(k)],ans[rs(k)]);
}

inline void push_down(ll p){
    if(tag1[p]!=-1){
        tag1[ls(p)]=tag1[rs(p)]=tag1[p];
        ans[ls(p)]=ans[rs(p)]=tag1[p];
        tag2[ls(p)]=tag2[rs(p)]=0;
        tag1[p]=-1;
    }
    if(tag2[p]){
        tag2[ls(p)]+=tag2[p];
        tag2[rs(p)]+=tag2[p];
        ans[ls(p)]+=tag2[p];
        ans[rs(p)]+=tag2[p];
        tag2[p]=0;
    }

}

void update1(ll nl,ll nr,ll l,ll r,ll p,ll k){
    if(nl<=l&&r<=nr){
        ans[p]=k;
        tag1[p]=k;
        tag2[p]=0;
        return;
    }
    ll mid=(l+r)>>1;
    push_down(p);
    if(nl<=mid) update1(nl,nr,l,mid,ls(p),k);
    if(nr>mid) update1(nl,nr,mid+1,r,rs(p),k);
    push_up(p);
}

void update2(ll nl,ll nr,ll l,ll r,ll p,ll k){
    if(nl<=l&&r<=nr){
        ans[p]+=k;
        tag2[p]+=k;
        return;
    }
    ll mid=(l+r)>>1;
    push_down(p);
    if(nl<=mid) update2(nl,nr,l,mid,ls(p),k);
    if(nr>mid) update2(nl,nr,mid+1,r,rs(p),k);
    push_up(p);
}

ll query(ll q_x,ll q_y,ll l,ll r,ll p){
    if(q_x<=l&&r<=q_y)
      return ans[p];
    ll res=0;
    ll mid=(l+r)>>1;
    push_down(p);
    if(q_x<=mid) res=max(res,query(q_x,q_y,l,mid,ls(p)));
    if(q_y>mid) res=max(res,query(q_x,q_y,mid+1,r,rs(p)));
    return res;
}

void build(ll p,ll l,ll r){
    tag1[p]=-1;
    tag2[p]=0;
    if(l==r){
        ans[p]=dd[l];
        return;
    }
    ll mid=(l+r)>>1;
    build(ls(p),l,mid);
    build(rs(p),mid+1,r);
    push_up(p);
}

void dfs1(ll f,ll ff){
    depth[f]=depth[ff]+1;
    fa[f]=ff;
    siz[f]=1;
    ll maxson=-1;
    for(re ll i=head[f];i!=0;i=h[i].next){
        if(h[i].to==ff)
          continue;
        dfs1(h[i].to,f);
        a[h[i].to]=h[i].dis;
        siz[f]+=siz[h[i].to];
        if(siz[h[i].to]>maxson){
            maxson=siz[h[i].to];
            son[f]=h[i].to;
        }
    }
}

void dfs2(ll x,ll topf){
    top[x]=topf;
    id[x]=++cnt;
    dd[cnt]=a[x];
    if(!son[x])
      return;
    dfs2(son[x],topf);
    for(re ll i=head[x];i!=0;i=h[i].next){
        if(h[i].to==fa[x]||h[i].to==son[x])
          continue;
        dfs2(h[i].to,h[i].to);
    }
}

void updrange1(ll x,ll y,ll k){
    while(top[x]!=top[y]){
        if(depth[top[x]]<depth[top[y]])
          swap(x,y);
        update1(id[top[x]],id[x],1,n,1,k);
        x=fa[top[x]];
    }
    if(depth[x]>depth[y])
      swap(x,y);
    update1(id[x]+1,id[y],1,n,1,k);
}

void updrange2(ll x,ll y,ll k){
    while(top[x]!=top[y]){
        if(depth[top[x]]<depth[top[y]])
          swap(x,y);
        update2(id[top[x]],id[x],1,n,1,k);
        x=fa[top[x]];
    }
    if(depth[x]>depth[y])
      swap(x,y);
    update2(id[x]+1,id[y],1,n,1,k);
}

ll qrange(ll x,ll y){
    ll anss=0;
    while(top[x]!=top[y]){
        if(depth[top[x]]<depth[top[y]])
          swap(x,y);
        anss=max(anss,query(id[top[x]],id[x],1,n,1));
        x=fa[top[x]];
    }
    if(depth[x]>depth[y])
      swap(x,y);
    return max(anss,query(id[x]+1,id[y],1,n,1));
}

int main(){
    in(n);
    FOR(i,1,n-1){
        in(x),in(y),in(z);
        add(x,y,z);
        add(y,x,z);
    }
    dfs1(1,0);
    dfs2(1,1);
    build(1,1,n);
    cin>>s;
    int t0=0,ck=2;
    while(s!="Stop"){
        if(s[1]=='h'){
            in(x),in(k);
            x=depth[h[2*x+1].from]>depth[h[2*x+1].to]?h[2*x+1].from:h[2*x+1].to;
            update1(id[x],id[x],1,n,1,k);
        }
        if(s[1]=='o'){
            in(x),in(y),in(z);
            updrange1(x,y,z);
        }
        if(s[1]=='d'){
            in(x),in(y),in(z);
            updrange2(x,y,z);
        }
        if(s[1]=='a'){
            in(x),in(y);
            out(qrange(x,y));
            puts("");
        }
        cin>>s;
    }
}
