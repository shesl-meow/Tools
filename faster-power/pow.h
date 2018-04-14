#progma once

template<class T> T pow(T base,int power){
	T res=1;
	while( power ){
		if( power&1 ) res *= base;
		base *= base;
		power >>= 1;
	}
	return res;
}
