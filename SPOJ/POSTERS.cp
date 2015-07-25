#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;

const int MAXN = 40005;

pair< int , pair<int,int> > evt[2*MAXN];
bool vis[MAXN];

int main(){

	int runs,N;
	int x,y;
	int last,top;
	int res;
	scanf("%d",&runs);

	while (runs--){
		scanf("%d",&N);
		for ( int i=0; i < N; ++i ){
			vis[i+1] = false;
			scanf("%d %d",&x,&y);
			evt[2*i] = make_pair( x-1 , make_pair( 1, -(i+1) ) );
			evt[2*i + 1] = make_pair( y , make_pair( 0, -(i+1) ) );
		}
		res = 0;
		sort( evt , evt + 2*N );
		set<int> swp;
		for ( int i=0; i < 2*N ; ){
			last = evt[i].first;
			//printf("Point %d\n",last);
			while ( i < 2*N && evt[i].first == last){
				if (evt[i].second.first == 0){
					//printf("Remove %d\n",-evt[i].second.second);
					swp.erase( -evt[i].second.second );
				}
				else {
					//printf("Insert %d\n",-evt[i].second.second);
					swp.insert( -evt[i].second.second );
				}
				i++;
			}
			if (!swp.empty()){
				top = *swp.rbegin();
				if (!vis[top]) res++, vis[top] = true;
			}
		}
		printf("%d\n",res);
	}
	
	return 0;
}
