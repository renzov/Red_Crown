#include<cstdio>
#include<algorithm>
#include<vector>
using namespace std;
const int MAXV = 1000005;
bool noprime[MAXV];
vector<int> primes;
void sieve(const int &maxV){
	for ( int i=3; i*i < maxV; i += 2 )
		if ( !noprime[i] ){
			for ( int j=i*i ; j < maxV; j += (i << 1) )
				if ( !noprime[j] ) noprime[j] = true;
		}
	primes.push_back(2);
	for ( int i=3; i <= maxV; i += 2 )
		if ( !noprime[i] ) primes.push_back(i);
}

int main(){
	int x;
	scanf("%d", &x);
	sieve(x);
	int res = 0;
	int l;
	int r = primes.size() - 1;

	while ( x > 3 ){
		while ( primes[r] > x ) r--;
		l = 0;
		while ( (primes[l] + primes[r]) != x ){
			if ( (primes[l] + primes[r]) < x ) l++;
			else r--;
		}
		res++;
		x = primes[r] - primes[l];
	}
	printf("%d\n", res);
	return 0;
}
