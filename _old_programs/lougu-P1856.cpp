#include<cstdio>
#include<algorithm>
#define maxn 5000
#define max(a,b) ((a)>=(b)?(a):(b))
#define min(a,b) ((a)<=(b)?(a):(b))
#define abs(a) ((a)>=0?(a):(-(a)))
using namespace std;

int n,n0,ans;
struct segment{
    int x,y1,y2,y3,y4,tp;
};
segment seg[(maxn<<1)+1];
int f[(maxn<<1)+1]={-2e9};
struct node{
    int segcnt,lc,rc,cover,add,cl[2];
};
node a[(maxn<<3)+1];

node operator+(node& a,node &b){
    node c;
    c.segcnt=a.segcnt+b.segcnt-(a.rc&&b.lc);
    c.lc=a.lc;
    c.rc=b.rc;
    c.cover=min(a.cover,b.cover);
    c.cl[0]=a.cl[0]+b.cl[0];
    c.cl[1]=a.cl[1]+b.cl[1];
    return c;
}

node operator+=(node& a,node& b){
    a=a+b;
    return a;
}

int read(){
    int sn=1,x=0;
    char c=getchar();
    for(;c!=45&&(c<48||c>57);c=getchar());
    if(c==45){
        sn=-1;
        c=getchar();
    }
    for(;c>=48&&c<=57;x=(x<<3)+(x<<1)+(c^48),c=getchar());
    return sn*x;
}

void write(int x){
    if(x<0){
        putchar(45);
        x=-x;
    }
    if(x>=10)
        write(x/10);
    putchar(x%10^48);
}

bool cmp(segment p,segment q){
    return p.x<q.x||(p.x==q.x&&p.tp>q.tp);
}

int getrank(int v){
    for(int L=1,R=n0;;){
        int mid=L+R>>1;
        if(v==f[mid])
            return mid;
        else
            if(v<f[mid])
                R=mid-1;
            else
                L=mid+1;
    }
}

void build(int cur,int l,int r){
    if(l==r)
        a[cur].cl[0]=f[l+1]-f[l];
    else{
        int mid=l+r>>1;
        build(cur<<1,l,mid);
        build(cur<<1|1,mid+1,r);
        a[cur]=a[cur<<1]+a[cur<<1|1];
    }
}

void pushdown(int cur){
    a[cur<<1].cover+=a[cur].add;
    a[cur<<1].add+=a[cur].add;
    a[cur<<1|1].cover+=a[cur].add;
    a[cur<<1|1].add+=a[cur].add;
    a[cur].add=0;
}

void update(int L,int R,int x,int cur,int l,int r){
    if(l>=L&&r<=R){
        a[cur].cover+=x;
        a[cur].add+=x;
        if(x>0)
            a[cur].segcnt=a[cur].lc=a[cur].rc=1,a[cur].cl[1]=a[cur].cl[0];
        else
            if(l<r)
                a[cur]=a[cur<<1]+a[cur<<1|1];
    }
    else{
        int mid=l+r>>1;
        pushdown(cur);
        if(L<=mid)
            update(L,R,x,cur<<1,l,mid);
        if(R>mid)
            update(L,R,x,cur<<1|1,mid+1,r);
        a[cur]=a[cur<<1]+a[cur<<1|1];
    }
}

int main(){
    n=read();
    for(int i=1;i<=n;++i){
        int p=read(),q=read(),r=read(),s=read();
        seg[(i<<1)-1].x=p;
        seg[(i<<1)-1].y1=q;
        seg[(i<<1)-1].y2=s;
        seg[(i<<1)-1].tp=1;
        seg[i<<1].x=r;
        seg[i<<1].y1=q;
        seg[i<<1].y2=s;
        seg[i<<1].tp=-1;
        f[(i<<1)-1]=q;
        f[i<<1]=s;
    }
    sort(f+1,f+(n<<1)+1);
    for(int i=1;i<=(n<<1);++i)
        if(f[i]>f[n0])
            f[++n0]=f[i];
    sort(seg+1,seg+(n<<1)+1,cmp);
    for(int i=1;i<=(n<<1);++i)
        seg[i].y1=getrank(seg[i].y1),seg[i].y2=getrank(seg[i].y2);
    build(1,1,n0-1);
    seg[0].x=seg[1].x;
    for(int i=1;i<=(n<<1);++i){
        printf("%d %d(%d) %d(%d) %d\n",seg[i].x,seg[i].y1,f[seg[i].y1],seg[i].y2,f[seg[i].y2],seg[i].tp);
        int p=a[1].cl[1];
        update(seg[i].y1,seg[i].y2-1,seg[i].tp,1,1,n0);
        ans+=abs(a[1].cl[1]-p);
        if(seg[i].x>seg[i-1].x)
            ans+=a[1].segcnt*(seg[i].x-seg[i-1].x)<<1;
        printf("%d %d\n\n",a[1].cl[1],a[1].segcnt);
    }
    write(ans);
    return 0;
}
