#include<cstdio>
#include<set>
#include<cstring>
#include<climits>
using namespace std;

int v[7];
int dp[2][100005] = {0};

int main(){

  int runs;
  int m,n;
  int x;
  int next;
  bool found;
  scanf("%d",&runs);
  while (runs--){
	 found = false;
	 scanf("%d %d",&m,&n);
	 for (int i=0; i < n; ++i) scanf("%d",v+i);
	 set<int> state[2];
	 x = 0;
	 state[0].insert(0);
	 dp[0][0] = INT_MAX;
	 for (int i=0; i < n && !found; ++i){
		state[1-x].clear();
		for (set<int>::iterator it=state[x].begin(); it != state[x].end() && !found; it++){
		  next = *it;
		  for (int j=1; j <= dp[x][*it]; ++j){
			 next += v[i];
			 if (next > m) break;
			 if ( state[1-x].find(next) == state[1-x].end() ){
				state[1-x].insert(next);
				dp[1-x][next] = j;
			 }
			 else if ( dp[1-x][next] < j ) dp[1-x][next] = j;
			 if (next == m) found = true;
		  }
		}
		x = 1 - x;
	 }
	 if (found) puts("YES");
	 else puts("NO");
	 if (runs) putchar('\n');
  }
  return 0;
}