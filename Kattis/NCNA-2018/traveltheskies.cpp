#include<cstdio>
#include<vector>
using namespace std;
typedef pair<int,int> pii;

const int MAXD = 16;
const int MAXK = 16;

struct flight {
	int cap;
	int from;
	int to;

	flight(){}
	flight( const int &c, const int &f, const int &t ){
		cap = c, from = f, to = t;
	}
};

vector<flight> Fday[MAXD];
vector<pii> Pday[MAXD];

int bag[MAXK] = {0};

int main(){
	int K, N, M;
	int u, v, d, z;

	scanf("%d %d %d", &K, &N, &M);

	while ( M-- ){
		scanf("%d %d %d %d", &u, &v, &d, &z);
		u--, v--, d--;
		Fday[d].push_back( flight( z, u, v ) );
	}

	for ( int i=0; i < K*N; ++i ){
		scanf("%d %d %d", &u, &d, &z);
		u--, d--;
		Pday[d].push_back( pii( z, u ) );
	}

	bool ok = true;
	for ( d = 0; d < N && ok; ++d ){
		// First put the arriving people
		for ( int i=0; i < (int)Pday[d].size(); ++i ){
			z = Pday[d][i].first;
			u = Pday[d][i].second;
			bag[ u ] += z;	// z people at airport u
		}
		// see if we can satisfy the flights for that day
		for ( int i=0; i < (int)Fday[d].size(); ++i ){
			u = Fday[d][i].from;
			z = Fday[d][i].cap;
			if ( bag[u] >= z )	bag[u] -= z;
			else ok = false;
		}
		// we transfer the people of the flights
		for ( int i=0; i < (int)Fday[d].size(); ++i ){
			v = Fday[d][i].to;
			z = Fday[d][i].cap;
			bag[v] += z;
		}
	}
	if ( ok ) puts("optimal");
	else puts("suboptimal");
	return 0;
}
