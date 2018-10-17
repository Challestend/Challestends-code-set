#include<cstdio>
#include<algorithm>
#define re register
#define maxn 50000
#define maxblock 230
#define maxval 100000000
#define INF 2147483647
#define ID(a) (((a)-1)/size+1)

namespace cltstream{
    #ifdef ONLINE_JUDGE
        #define size 1048576
        char str[size+1],*head=str,*tail=str;
        inline char gc(){
            if(head==tail){
                tail=(head=str)+fread(str,1,size,stdin);
                if(head==tail)
                    return EOF;
            }
            return *head++;
        }
        #undef size
    #else
        #define gc getchar
    #endif

    template <typename _tp>
    inline void read(_tp& x){
        int sn=1;
        char c=gc();
        for(;c!=45&&(c<48||c>57)&&c!=EOF;c=gc());
        if(c==45&&c!=EOF)
            sn=-1,c=gc();
        for(x=0;c>=48&&c<=57&&c!=EOF;x=(x<<3)+(x<<1)+(c^48),c=gc());
        x*=sn;
    }

    template <typename _tp>
    inline void write(_tp x,char text=' '){
        if(x<0)
            putchar(45),x=-x;
        if(!x)
            putchar(48);
        else{
            int digit[20];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];putchar(digit[digit[0]--]^48));
        }
        putchar(text);
    }
}

int n,m,size;
int a[maxn+1],val[maxblock+1][maxblock+1],len[maxblock+1];

inline std::pair<int,int> getRank(int l,int r,int x){
    int L=ID(l),R=ID(r);
    std::pair<int,int> res(1,0);
    if(L==R){
        for(re int i=l;i<=r;++i){
            res.first+=(a[i]<x);
            res.second+=(a[i]<=x);
        }
    }
    else{
        for(re int i=l;i<=L*size;++i){
            res.first+=(a[i]<x);
            res.second+=(a[i]<=x);
        }
        for(re int i=(R-1)*size+1;i<=r;++i){
            res.first+=(a[i]<x);
            res.second+=(a[i]<=x);
        }
        for(re int i=L+1;i<=R-1;++i){
            res.first+=std::lower_bound(val[i],val[i]+len[i]+1,x)-val[i]-1;
            res.second+=std::upper_bound(val[i],val[i]+len[i]+1,x)-val[i]-1;
        }
    }
    return res;
}

inline int findRank(int l,int r,int x){
    if(x<1)
        return -INF;
    if(x>r-l+1)
        return INF;
    int L=0,R=maxval;
    for(;L<R;){
        int mid=(L+R)>>1;
        std::pair<int,int> rnk=getRank(l,r,mid);
        if(rnk.first<=x&&rnk.second>=x)
            return mid;
        else
            if(rnk.second<x)
                L=mid+1;
            else
                R=mid-1;
    }
    return L;
}

int main(){
    cltstream::read(n);
    cltstream::read(m);
    for(;(size+1)*(size+1)<=n;++size);
    for(re int i=1;i<=n;++i){
        cltstream::read(a[i]);
        val[ID(i)][++len[ID(i)]]=a[i];
    }
    for(re int i=1;(i-1)*size+1<=n;++i)
        std::sort(val[i],val[i]+len[i]+1);
    for(re int i=1;i<=m;++i){
        int opt,l,r,x;
        cltstream::read(opt);
        cltstream::read(l);
        cltstream::read(r);
        switch(opt){
            case 1:
                cltstream::read(x);
                cltstream::write(getRank(l,r,x).first,'\n');
                break;
            case 2:
                cltstream::read(x);
                cltstream::write(findRank(l,r,x),'\n');
                break;
            case 3:
                x=ID(l);
                val[x][std::lower_bound(val[x],val[x]+len[x]+1,a[l])-val[x]]=r;
                a[l]=r;
                std::sort(val[x],val[x]+len[x]+1);
                break;
            case 4:
                cltstream::read(x);
                cltstream::write(findRank(l,r,getRank(l,r,x).first-1),'\n');
                break;
            case 5:
                cltstream::read(x);
                cltstream::write(findRank(l,r,getRank(l,r,x).second+1),'\n');
                break;
        }
    }
    return 0;
}
