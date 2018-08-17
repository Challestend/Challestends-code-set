#include<cstdio>
#define abs(a) ((a)>=0?(a):-(a))
using namespace std;

int n,h,a,b,k;

int main(){
    scanf("%d%d%d%d%d",&n,&h,&a,&b,&k);
    for(int i=1;i<=k;++i){
        int x1,y1,x2,y2;
        scanf("%d%d%d%d",&x1,&y1,&x2,&y2);
        if(x1==x2)
            printf("%d\n",abs(y2-y1));
        else{
            int res=0;
            if(y1<a)
                res+=a-y1,y1=a;
            else
                if(y1>b)
                    res+=y1-b,y1=b;
            if(y2<a)
                res+=a-y2,y2=a;
            else
                if(y2>b)
                    res+=y2-b,y2=b;
            printf("%d\n",res+abs(x2-x1)+abs(y2-y1));
        }
    }
    return 0;
}
