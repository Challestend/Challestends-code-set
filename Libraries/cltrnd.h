namespace cltrnd{
    unsigned long long r1,r2,r3,r4,r5;

    template <typename _tp>
    inline void srnd(_tp r0){
        r1=r0;
        r2=(~r0)^0x2333333333333ULL;
        r3=r0^0x1234598766666ULL;
        r4=(~r0)+51;
    }

    inline unsigned long long rnd(){
        r5=((r1<<6)^r1)>>13;
        r1=((r1&429496729447258ULL)<<18)^r5;
        r5=((r2<<2)^r2)>>27;
        r2=((r2&429496728894765ULL)<<2)^r5;
        r5=((r3<<13)^r3)>>21;
        r3=((r3&429496728011566ULL)<<7)^r5;
        r5=((r4<<3)^r4)>>12;
        r4=((r4&429496716850294ULL)<<13)^r5;
        return r1^r2^r3^r4;
    }

    template <typename _tp>
    inline void swp(_tp& x,_tp& y){
        _tp tmp=x;
        x=y;
        y=tmp;
    }

    template <typename _tp>
    inline void rnd_shuffle(_tp p[],int begin,int end){
        for(register int i=begin;i<=end;++i){
            int tmp=rnd()%(end-begin+1)+begin;
            swp(p[i],p[tmp]);
        }
    }
}
