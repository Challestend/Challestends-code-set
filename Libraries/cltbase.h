namespace cltlib{
	#define re register

	template <typename _tp>
	inline void swp(re _tp& x,re _tp& y){
		_tp tmp=x;
		x=y;
		y=tmp;
	}

	template <typename _tp>
	inline _tp pow(re _tp x,re _tp y,re _tp mod){
		re int res=1;
		for(;y;){
			if(y&1)
				res=1LL*res*x%mod;
			x=1LL*x*x%mod;
			y>>=1;
		}
		return res;
	}

	#undef re
}
