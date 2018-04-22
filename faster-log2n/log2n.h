#pragma once

static const unsigned int b[]={
	0x2,0xC,0xF0,0xFF00,0xFFFF0000,0xFFFFFFFF00000000};
static const unsigned int S[]={1,2,4,8,16,32};

unsigned int log2n(unsigned int v,const int n=5)
{
	register unsigned int r = 0;
	for(int i=n; i>=0; --i)
		if(v&b[i])
		{
			v >>= S[i];
			r |= S[i];
		}
}

unsigned int log2n_32(unsigned int v)
{
	return log2n(v,4);
}

unsigned int log2n_64(unsigned int v)
{
	return log2n(v,5);
}

//if your CPU branches slowly
unsigned int log2n_ubr32(unsigned int v)
{
	register unsigned int r;
	register unsigned int shift;
	r = (v > 0xFFFF) << 4; v>>=r;
	shift = (v > 0xFF) <<3; v>>=shift; r|=shift;
	shift = (v > 0xF) <<2; v>>=shift; r|=shift;
	shift = (v > 0x3) <<1; v>>=shift; r|=shift;
	r |= (v >> 1);
	return r;
}
unsigned int log2n_ubr64(unsigned int v)
{
	register unsigned int r;
	register unsigned int shift;
	r = (v > 0xFFFFFFFF) << 5; v>>=r;
	shift = (v > 0xFFFF) << 4; v>>=shift; r|=shift;
	shift = (v > 0xFF) << 3; v>>=shift; r|=shift;
	shift = (v > 0xF) << 2; v>>=shift; r|=shift;
	shift = (v > 0x3) << 1; v>>=shift; r|=shift;
	r |= (v >> 1);
	return r;
}

//if your number is power of 2

//there is algorithm for 32bits number.
static const unsigned int b1[]={
	0xAAAAAAAA,0xCCCCCCCC,0xF0F0F0F0,0xFF00FF00,0xFFFF0000};
unsigned int log2n_32p2(unsigned int v)
{
	register unsigned int r = (v & bb[0]) != 0;
	for(int i=4; i>0; --i)
		r |= ((v & bb[i]) != 0) << i;
}
//and there is algorithm for 64bits number.
static const unsigned int bb[]={
	0xAAAAAAAAAAAAAAAA,0xCCCCCCCCCCCCCCCC,0xF0F0F0F0F0F0F0F0,
	0xFF00FF00FF00FF00,0xFFFF0000FFFF0000,0xFFFFFFFF00000000};
unsigned int log2n_64p2(unsigned int v)
{
	register unsigned int r = (v & bb[0]) != 0;
	for(int i=5; i>0; --i)
		r |= ((v & bb[i]) != 0) << i;
}
