#include<cstdio>
#define maxn 200000+10
#define max(a,b) ((a)>=(b)?(a):(b))

int n;
int a[maxn],f[maxn],h[maxn];

void swap(int& a,int& b){
    int tmp=a;
    a=b;
    b=tmp;
}

void push(int x){
    h[++h[0]]=x;
    for(int p=h[0],q=p>>1;q>=1;)
        if(f[h[p]]>f[h[q]]){
            swap(h[p],h[q]);
            p=q;
            q=p>>1;
        }
        else
            break;
}

int pop(){
    int x=h[1];
    h[1]=h[h[0]--];
    for(int p=1,q=p<<1;q<=h[0];){
        if(q<h[0]&&f[h[q+1]]>f[h[q]])
            ++q;
        if(f[h[q]]>f[h[p]]){
            swap(h[p],h[q]);
            p=q;
            q=p<<1;
        }
        else
            break;
    }
    return x;
}

int main(){
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
        scanf("%d",&a[i]),f[i]=1;
    push(1);
    for(int i=2;i<=n;++i){
        for(;h[0]&&2*a[h[1]]<a[i];pop());
        if(h[0])
            f[i]=f[h[1]]+1;
        push(i);
    }
    for(int i=1;i<=n;++i)
        f[0]=max(f[0],f[i]);
    printf("%d",f[0]);
    return 0;
}
