#include<cstdio>
using namespace std;
const int MAXS = 100005;
int N, M;
char S[MAXS];
int f[26];
// frequencies for the problem statement
int fA[26];
int xA[26];
int fB[26];
int xB[26];
inline bool isvowel( const char &c ){
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

void process(){
	int L;

	scanf("%d", &L);
	N = M = 0;
	
	int sum;
	int best;
	for ( int i=0; i < L; ++i ){
		scanf("%s", S);
		best = sum = 0;
		for ( int j=0; S[j]; j++ ){
			f[ S[j] - 'a' ]++;
			if ( isvowel(S[j]) ){	
				sum--;
				if ( sum < 0 ) sum = 0;
			}
			else {
				sum++;
				if ( best < sum ) best = sum;
			}
		}
		if ( sum <= 1 ){	// Alice string
			M++;
			for ( int i=0; i < 26; ++i )
				if ( f[i] ){
					fA[i] += f[i];
					xA[i]++;
					f[i] = 0;	// Clean up
				}
		}
		else {	// Bob string
			N++;
			for ( int i=0; i < 26; ++i )
				if ( f[i] ){
					fB[i] += f[i];
					xB[i]++;
					f[i] = 0;	// Clean up
				}
		}
	}

	for ( int i=0; i < 26; ++i ){
		xA[i] = xB[i] = 0;
		fA[i] = fB[i] = 0;
	}
}

int main(){
	int runs;
	scanf("%d", &runs);
	while ( runs-- )
		process();
	return 0;
}
