#progma once

//O(sqrt(n)) algorithm
bool isPrime(int n)
{
	if( n<=1 ) return false;
	else if( n<=3 ) return true;
	else if( !(n%2 && n%3) ) return false;
	
	for(int i=5; i*i<n; i+=6)
		if( !(n%i && n%(i+2)) ) return false;
	return true;
}

//Generalize method
bool gisPrime(int num)
{
	if(num<=1) return false;
	int sqrn = 0;
	for(sqrn=0; sqrn*sqrn<=num; sqrn++);
	bool *PrimeList = new bool[sqrn];
	for(int i=2; i<sqrn; ++i) PrimeList[i]=true;
	//initialize
	
	for(int i=2; i*i<sqrn; ++i)
		if(PrimeList[i])
			for(int j=i*i; j<sqrn; j+=i)
				PrimeList[j] = false;
	
	for(int i=2; i<sqrn; ++i)
		if(PrimeList[i])
			if(num%i==0){
				delete []PrimeList;
				return false;
			}
	
	delete []PrimeList;
	return true;
}
