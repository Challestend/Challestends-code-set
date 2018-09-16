#include<cstdio>
#include<cmath>
using namespace std;

int n,m;

int main(){
    scanf("%d%d",&n,&m);
    int p=0,q=-1;
    for(int i=1;i<=n;i++){
        char s[6];
        int x;
        scanf("%s%d",s,&x);
        switch(s[0]){
            case 'A':p&=x;q&=x;break;
            case 'O':p|=x;q|=x;break;
            case 'X':p^=x;q^=x;break;
        }
    }
    int m0=log2(m);
    for(int i=m0;i>=0;i--)
    	if(!(p>>i&1)&&(q>>i&1)&&m>=(1<<i)){
    		p|=(1<<i);
    		m-=(1<<i);
		}
    printf("%d",p);
    return 0;
}
