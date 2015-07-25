#include<cstdio>
#include<algorithm>
#include<set>

using namespace std;

const int MAXN = 105;

pair<int, pair<int,int> > evt[2*MAXN];

int main(){
	int x,y;
	int runs;
	int N;

	scanf("%d",&runs);
	
	while (runs--){
		scanf("%d",&N);
		for ( int i=0; i < N ; ++i ){
			scanf("%d %d",&x,&y);
			evt[2*i] = make_pair(x,make_pair(0,-(i+1)));
			evt[2*i + 1] = make_pair(y,make_pair(1,-(i+1)));
		}
		sort(evt,evt + 2*N);
		set<int> swp;
		int res = 0;
		for ( int i=0; i < 2*N; ++i ){
			if ( evt[i].second.first == 0 ){
				swp.insert( -evt[i].second.second );
				res = max(res,(int)swp.size());
			}
			else {
				swp.erase( -evt[i].second.second );
			}
		}
		printf("%d\n",res);
	}
	return 0;
}
