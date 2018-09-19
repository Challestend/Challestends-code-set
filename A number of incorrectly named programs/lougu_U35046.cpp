#include<cstdio>

int curtime,lpmax,curlp,lpinc,expmax,curexp,expinc,curpt,lpneed,expgain,ptgain,target,ans;

int main(){
    scanf("%d%d",&ptgain,&lpneed);
    scanf("%d%d%d%d%d",&lpmax,&curlp,&expmax,&curexp,&expgain);
    scanf("%d%d%d%d",&lpinc,&expinc,&curtime,&target);
    curlp+=curtime;
    for(;curpt<target;){
        if(curlp>=lpneed){
            int cnt=curlp/lpneed;
            curlp-=cnt*lpneed;
            curexp+=cnt*expgain;
            curpt+=cnt*ptgain;
        }
        else{
            ++ans;
            curlp+=lpmax;
        }
        for(;curexp>=expmax;){
            curexp-=expmax;
            expmax+=expinc;
            curlp+=lpmax+lpinc;
            lpmax+=lpinc;
        }
    }
    printf("%d",ans);
    return 0;
}
