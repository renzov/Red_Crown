#include<cstdio>
using namespace std;

const int MAXN = 1000000;

int div[MAXN+5];
int mert[MAXN+5];
int mo[MAXN];

void sieve(){
	int i,j;
	for ( i = 4; i <= MAXN; i += 2 ) div[i] = 2;
	for ( i = 3; i <= 1000; i += 2 ){
		if ( div[i] == 0 )
			for ( j = i*i; j <= MAXN; j += (i<<1))
				div[j] = i;
	}
	mert[1] = 1, mo[1] = 1;
	int cnt, cp, p, temp;
	bool sq;
	for ( i=2; i <= MAXN; ++i ){
		if ( div[i] == 0 ){ 
			mert[i] = mert[i-1] - 1, mo[i] = -1;
			continue;		
		}
		temp = i;
		cp = 0;
		sq = false;		
		while ( !sq && div[temp] != 0 ){
			cnt = 0;
			cp++;
			p = div[temp];			
			while ( !(temp % p) ){
				cnt++;
				temp /= p;			
			}
			if ( cnt > 1 ) sq = true;
		}
		if ( temp != 1 ) cp++;
		if ( sq ) mert[i] = mert[i-1], mo[i] = 0;
		else {
			if ( cp & 1 ) mert[i] = mert[i-1] - 1, mo[i] = -1;
			else mert[i] = mert[i-1] + 1, mo[i] = 1;
		}
	} 
}

int main(){
	sieve();
	int N;
	while ( scanf("%d", &N) && N ){
		printf("%8d%8d%8d\n", N, mo[N], mert[N]);
	}
	return 0;
}



