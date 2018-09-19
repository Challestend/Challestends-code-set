#include<cstdio>
#include<cstring>
#define maxn 2000
#define min(a,b) ((a)<=(b)?(a):(b))
using namespace std;

int lena,lenb;
char a[maxn+5],b[maxn+5];
int f[maxn+5][maxn+5];

int main(){
    scanf("%s%s",a+1,b+1);
    lena=strlen(a+1),lenb=strlen(b+1);
    for(int i=1;i<=lena||i<=lenb;++i)
        f[i][0]=f[0][i]=i;
    for(int i=1;i<=lena;++i)
        for(int j=1;j<=lenb;++j)
            if(a[i]==b[j])
                f[i][j]=f[i-1][j-1];
            else
                f[i][j]=min(min(f[i-1][j],f[i][j-1]),f[i-1][j-1])+1;
    printf("%d",f[lena][lenb]);
    return 0;
}
