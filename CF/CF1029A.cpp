#include<cstdio>

int n,m;
char s[55];
int kmp[55];

int main(){
    scanf("%d%d",&n,&m);
    scanf("%s",s+1);
    for(int i=2,p=0;i<=n;++i){
        for(;p!=0&&s[p+1]!=s[i];p=kmp[p]);
        if(s[p+1]==s[i])
            ++p;
        kmp[i]=p;
    }
    printf("%s",s+1);
    for(int i=2;i<=m;++i)
        for(int j=kmp[n]+1;j<=n;++j)
            putchar(s[j]);
    return 0;
}
