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
#include <climits>

using namespace std;

typedef long long int64;
typedef long double ldouble;
typedef pair< int , int > pii;

int G[55][55];
map<string,int> H;
int maxId;

int find_id( string &s ){
	if ( H.find( s ) == H.end() ){
		return H[s] = ++maxId;
	}
	return H[s];
}

int main(){
	string A,B;
	int M,N, u,v;
	int cases = 0;
	while ( cin >> N >> M && N && M ){
		cases++;
		for ( int i=0; i < N; ++i ){
			fill( G[i] , G[i] + N, INT_MAX  );
			G[i][i] = 0;	
		}
		H.clear();
		maxId = -1;
		while ( M-- ){
			cin >> A  >> B;
			u = find_id( A );
			v = find_id( B );
			G[u][v] = G[v][u] = 1; 
		}
		for ( int k=0; k < N; ++k )
			for ( int i=0; i < N; ++i )
				for ( int j=0; j < N; ++j ){
					if ( G[i][k] < INT_MAX && G[k][j] < INT_MAX ){
						G[i][j] = min( G[i][j] , G[i][k] + G[k][j] );
					}
				}
		int maxD = 0;
		for ( int i=0; i < N; ++i ){
			for (int j=i+1; j < N; ++j)
				if ( maxD < G[i][j] ) maxD = G[i][j];
		}
		
		printf("Network %d: ", cases);
		if ( maxD < INT_MAX ) printf("%d\n", maxD);
		else printf("DISCONNECTED\n");
		puts("");
	}
	return 0;
}

