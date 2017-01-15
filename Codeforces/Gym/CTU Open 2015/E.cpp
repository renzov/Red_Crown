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

const int MAXN = 1000005;

vector<int> L[MAXN];
vector<int> R[MAXN];
int P[MAXN];

int q[MAXN];
int seen[MAXN] = {0};
int qf, qt;

int main(){
	int t = 0;
	int N;
	int u, v;
	int idx;
	while ( scanf("%d", &N) && N ){
		t++;
		for ( int i=0; i < N; ++i ){ 
			scanf("%d", P + i);
			if ( P[i] + i < N ) L[ P[i] + i ].push_back( i );
			if ( i - P[i] >= 0 ) R[ i - P[i] ].push_back( i );
		}
		
		qf = qt = 0;
		seen[0] = t;
		q[qt++] = 0;
		
		while ( qf < qt ){
			u = q[qf++];
			idx = u + P[u];
			if ( idx < N ){
				for ( int i=0; i < (int) R[idx].size(); ++i ){
					v = R[idx][i];
					if ( seen[v] < t ){
						seen[v] = t;
						q[qt++] = v;
					}
				}
			}
			idx = u - P[u];
			if ( idx >= 0 ){
				for ( int i=0; i < (int) L[idx].size(); ++i ){
					v = L[idx][i];
					if ( seen[v] < t ){
						seen[v] = t;
						q[qt++] = v;
					}
				}
			}
		}
		for ( int i=N-1; i >= 0; i-- )
			if ( seen[i] == t ){
				printf("%d\n", i);
				break;
			}
		for ( int i=0; i < N; ++i ) L[i].clear(), R[i].clear();		
	}
	return 0;
}

