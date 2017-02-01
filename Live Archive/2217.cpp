#include <cstdio>
#include <queue>
#include <cctype>
#include <cstdlib>
#include <climits>
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int main(){
	char c;
	int N,K;
	while ( scanf("%d %d", &N, &K) != EOF ){
		if ( N < K ){
			puts("0");
			while (N--) scanf(" %c", &c);
			continue;
		}
		int sum = 0;
		int occ = 0;
		deque<int> buf;
		int p;
		for ( p = 1 ; p <= K; ++p ){
			scanf(" %c", &c);
			if ( isdigit(c) ){ 
				buf.push_back(c-'0');
				sum += (c-'0');
			}
			else { 
				buf.push_back(-1);
				occ++;
			}
		}
		int best = (occ)? INT_MAX:sum;
		int res = 1;
		for ( ; p <= N ; ++p ){
			scanf(" %c", &c);
			if ( isdigit(c) ){ 
				buf.push_back(c-'0');
				sum += (c-'0');
			}
			else { 
				buf.push_back(-1);
				occ++;
			}

			if ( buf.front() < 0 ){
				occ--;
			}
			else {
				sum -= buf.front();
			}
			buf.pop_front();
			if (!occ && best > sum){
				best = sum;
				res = p - K + 1;
			}
		}
		if ( best < INT_MAX ) printf("%d\n", res);
		else puts("0");
	}
	return 0;
}
