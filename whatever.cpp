#include<cstdio>

int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}

int main(){
    int n=5000;
    for(int i=1;i<=n;++i)
        for(int j=i+1;j<=n;++j)
            if(i*j%(i+j)==0)
                printf("%d %d %d %d %d\n",i,j,i+j,i*j,j*j);
}
