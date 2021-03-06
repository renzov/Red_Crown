#include<set>
#include<queue>
#include<cstdio>
using namespace std;

int frec[7505] = {0};
set<int> G[7505];
int a[ 7505 ];

int main(){
  int n = 1;
  int u,v;

  while (scanf("%d",&a[n]) != EOF){ frec[ a[n] ]++; n++; }

  priority_queue< int , vector<int> , greater<int> > q;

  for (int i=1; i <= n; ++i){
	 if (frec[i] == 0) q.push(i);
  }

  for (int i=1; i < n; ++i){
	 v = q.top();
	 q.pop();
	 u = a[i];
	 G[u].insert(v);
	 G[v].insert(u);
	 frec[ a[i] ]--;
	 if (frec[ a[i] ] == 0) q.push( a[i] );
  }

  set<int>::iterator it;

  for (int i=1; i <= n; ++i){
	 printf("%d:",i);
	 for (it=G[i].begin(); it != G[i].end() ; ++it){
		printf(" %d",*it);
	 }
	 putchar('\n');
  }
  return 0;
}