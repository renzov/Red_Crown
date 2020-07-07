#include<cstdio>
#include<set>
#include<map>
using namespace std;
int N, M;
typedef pair<int,int> pii;
typedef pair<pii, int> piii;

map<int,int> frec;
map<int,int> pos;

set<piii> pocket;


int main(){
	int cases = 0;
	int res;
	int f, p, x;
	set<piii>::iterator it;

	while ( scanf("%d %d", &M, &N) == 2 && ( N || M ) ){
		res = 0;
		for ( int i=1; i <= N; ++i ){
			scanf("%d", &x);
			if ( frec.find(x) != frec.end() ){
				f = frec[x]++;	
				p = pos[x];
				//printf("Update x = %d\n", x);
				pocket.erase( piii( pii(f, -p ), x ) );
				pocket.insert( piii( pii( f + 1, -p ), x ) );
				//printf("pocket size = %d\n", (int)pocket.size());
			}
			else {
				int tmp = x;
				if ( (int)pocket.size() == M ){
					x = pocket.rbegin()->second;
					//printf("removed x = %d\n", x);
					res++;
					frec.erase(x), pos.erase(x);
					pocket.erase( *pocket.rbegin() );
					//printf("pocket size = %d\n", (int)pocket.size());					
				}
				x = tmp;
				frec[x] = 1, pos[x] = i;
				pocket.insert( piii( pii(1, -i), x ) );
				//printf("insert x = %d\n", x);
			}
		}	
		printf("Case %d: %d\n", ++cases, res);
		frec.clear();
		pos.clear();
		pocket.clear();
	}

	return 0;
}
