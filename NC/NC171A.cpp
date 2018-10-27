#include<cstdio>
#define re register
#define max(a,b) ((a)>=(b)?(a):(b))

namespace cltstream{
    #define size 1048576
    char cltin[size+1],*ih=cltin,*it=cltin;
    inline char gc(){
        #ifdef ONLINE_JUDGE
            if(ih==it){
                it=(ih=cltin)+fread(cltin,1,size,stdin);
                if(ih==it)
                    return EOF;
            }
            return *ih++;
        #else
            return getchar();
        #endif
    }

    char cltout[size+1],*oh=cltout,*ot=cltout+size;
    inline void pc(char c){
        if(c==-1)
            fwrite(cltout,1,oh-cltout,stdout);
        else{
            if(oh==ot){
                fwrite(cltout,1,size,stdout);
                oh=cltout;
            }
            *oh++=c;
        }
    }
    #undef size

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
            pc(45),x=-x;
        if(!x)
            pc(48);
        else{
            int digit[22];
            for(digit[0]=0;x;digit[++digit[0]]=x%10,x/=10);
            for(;digit[0];pc(digit[digit[0]--]^48));
        }
        pc(text);
    }
}

int a,opt,b,c;

int main(){
    cltstream::read(a);
    cltstream::read(opt);
    cltstream::read(b);
    cltstream::read(c);
    switch(opt){
        case 1:
            if(a>b)
                cltstream::write(0,'\n');
            else
                if(c<=0)
                    cltstream::write(-1,'\n');
                else
                    cltstream::write((b-a)/c+1,'\n');
            break;
        case 2:
            if(a<b)
                cltstream::write(0,'\n');
            else
                if(c>=0)
                    cltstream::write(-1,'\n');
                else
                    cltstream::write((b-a)/c+1,'\n');
            break;
        case 3:
            if((a<b&&c<=0)||(a>b&&c>=0))
                cltstream::write(-1,'\n');
            else
                if(a==b)
                    cltstream::write(0,'\n');
                else
                    cltstream::write((b-a)%c?-1:(b-a)/c,'\n');
            break;
    }
    cltstream::pc(-1);
    return 0;
}
