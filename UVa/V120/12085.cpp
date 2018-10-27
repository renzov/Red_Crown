#include<cstdio>
#include<cstdlib>
#include<cstring>
using namespace std;

int N;
char num[25];
char A[25];
char B[25];

void ll2str( long long x, int m, char *s ){
	s[m] = '\0';
	while ( m-- ){
		s[m] = (char)((x % 10) + '0');
		x /= 10;
	}
}

void process(){
	
	scanf("%s", num);
	long long start = atoll(num);
	long long end = start;
	int size = strlen(num);
	long long temp;
	for ( int i=1; i < N; ++i ){
		scanf("%s", num);
		temp = atoll(num);
		if ( end + 1 == temp ){
			end = temp;
		}
		else {
			// We print one new interval
			if ( start == end ){
				ll2str( start, size, A );
				printf("%s\n", A);
			} 
			else {
				ll2str( start, size, A );
				ll2str( end, size, B );
				// find longest commom preffix
				// We already know that A != B
				for ( int i=0; A[i]; ++i ){
					if ( A[i] != B[i] ){
						printf("%s-%s\n", A, B + i);
						break;
					}
				}
			}
			start = end = temp;	
		}
	}
	// print the last interval
	if ( start == end ){
		ll2str( start, size, A );
		printf("%s\n", A);
	} 
	else {
		
		ll2str( start, size, A );
		ll2str( end, size, B );
		// find longest commom preffix
		// We already know that A != B
		for ( int i=0; A[i]; ++i ){
			if ( A[i] != B[i] ){
				printf("%s-%s\n", A, B + i);
				break;
			}
		}
	}
}

int main(){
	int cases = 0;
	while ( scanf("%d", &N) && N ){
		printf("Case %d:\n", ++cases);
		process();
		puts("");
	}
	return 0;
}
