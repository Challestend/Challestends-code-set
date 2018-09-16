#include<cstdio>

int a,b,c;
int main(){
    long long l=1,r=int(1e9)<<1;
    scanf("%d%d",&a,&b);
    while(r-l>1){
        c=(l+r)>>1;
        if(c-b<a)
            l=c;
        else
            if(c-b>a)
                r=c;
            else
                return printf("%d\n",c);
    }
    if(l!=r)
        return printf("%d\n",r);
}
