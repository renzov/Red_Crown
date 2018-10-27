#include<cstdio>
#include<cstring>
#include<queue>
#include<stack>
#include<algorithm>
#include<cassert>
using namespace std;
const int MAXN = 256;
typedef pair<int,int> pii;
char E[MAXN];
char D[MAXN];
int val[MAXN];
int pot[] = {1, 10, 100, 1000, 10000, 100000, 1000000, 10000000, 100000000, 1000000000};

priority_queue<pii> q;

void parse(){
	// Parse the expression
	stack<int> mult;
	mult.push(1);
	int lastdig = -2;
	int lastsign = 1;
	for ( int i=0; E[i]; ++i ){
		if ( E[i] == '(' ){
			mult.push( lastsign * mult.top() );
			lastsign = 1; // undefined
		}
		else if ( E[i] == ')' ){
		 	mult.pop();
		}
		else if ( E[i] == '+' ){
			lastsign = 1;
		}
		else if ( E[i] == '-' ){
			lastsign = -1;
		}
		else { // E[i] == '#'
			if ( lastsign * mult.top() > 0 ){
				q.push( pii( val[i], i ) );
			}
			else {
				q.push( pii( -val[i], i ) );
			}
		}
	}
}

void process(){
	scanf("%s", E);	
	scanf("%s", D);
	int M = strlen(D);
	int N = strlen(E);
	// Sort the digits
	sort( D, D + M );
	val[N] = 0;
	for ( int i = N - 1; i >= 0 ; --i ){
		if ( E[i] == '#' ){
			val[ i ] = val[ i  + 1 ] + 1;
		}
		else {
			val[ i ] = 0;
		}
	}
	parse();
	int v, p;
	long long res = 0; 	
	assert( (int)q.size() == M );
	for ( int i=M - 1; i >= 0; --i ){
		v = q.top().first;
		p = q.top().second;
		if ( v < 0 ){ 
			res -= ( pot[-v - 1]*( D[i] - '0' ) );
		}
		else {
			res += ( pot[v - 1]*( D[i] - '0' ) );		
		}
		E[p] = D[i];
		q.pop();
	}
	printf("%s\n", E);
	printf("%lld\n", res);
}

int main(){
	int runs;
	scanf("%d", &runs);
	for ( int i=1; i <= runs; ++i ){
		printf("Case %d:\n", i);
		process();
	}
	return 0;
}
