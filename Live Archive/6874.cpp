#include <iostream>
#include <cstdio>
#include <algorithm>
#include <set>
#include <cstring>
#include <cstdlib>
#include <cctype>
#include <map>
#include <string>
#include <sstream>
#include <vector>
#include <queue>
#include <stack>
#include <cmath>
#include <numeric>

#define repn( i , a , b ) for( int i = ( int ) a ; i < ( int ) b ; i ++ )
#define rep( i , n ) repn( i , 0 , n ) 
#define all( x )  x.begin() , x.end()
#define rall( x ) x.rbegin() , x.rend()
#define mp make_pair
#define fst first
#define snd second
using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;
const int MAXM = 205;

char line[2048];
int64 C[MAXM];
int N;

void flush(){ while (getchar() != '\n'); }

int64 parse_clause(){
	char *token;
	int64 clause = 0;
	int var;
	token = strtok(line, " v");
	while (token != NULL){
		if ( token[0] == '~' ){
			sscanf(token,"~X%d", &var);
			var--;
			clause |= ( 1LL << (var + N) );
		}
		else {
			sscanf(token, "X%d",&var);
			var--;
			clause |= ( 1LL << var );
		}
		token = strtok(NULL, " v");
	}
	return clause;
}

int main(){
	int runs;
	int M;
	int64 all;
	int64 test;
	bool ok;

	scanf("%d",&runs);
	while (runs--){
		scanf("%d %d",&N,&M);
		flush();

		all = (1LL << N) - 1;
		for ( int i=0; i < M; ++i ){
			gets(line);
			C[i] = parse_clause();
		}

		for ( int64 mask=0; mask < (1LL << N); ++mask ){
			test = mask | ((mask ^ all) << N);
			ok = true;
			for (int i=0; i < M && ok; ++i){
				ok &= ((test & C[i]) != 0LL) ;
			}
			if (ok) break;
		}
		if (ok) puts("satisfiable");
		else puts("unsatisfiable");
	}
	return 0;
}

