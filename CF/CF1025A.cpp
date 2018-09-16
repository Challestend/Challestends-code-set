#include<cstdio>
#define maxn 100000

int n,ans;
char s[maxn+5];
int a[26];

int main(){
    scanf("%d",&n);
    scanf("%s",s+1);
    for(int i=1;i<=n;++i)
        ++a[s[i]-'a'];
    for(int i=0;i<26;++i)
        if(a[i]>1)
            ans=1;
    if(ans)
        puts("Yes");
    else
        puts("No");
    return 0;
}
