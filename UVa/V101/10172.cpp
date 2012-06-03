#include<cstdio>
#include<queue>
#include<stack>
using namespace std;
int S,Q;
int N;

int main(){
  int runs;
  int m,t;
  int r;
  int res;
  int n;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d %d %d",&N,&S,&Q);
		queue<int> q[ N ];
		r = 0;
		for (int i=0; i < N; ++i){
			 scanf("%d",&m);
			 r += m;
			 for (int j=0; j < m; ++j){
				  scanf("%d",&t); t--; q[i].push(t);
			 }
		}
		stack<int> s;
		res = 0; n = 0;
		while (r > 0){
			 /* Unload */
			 while ( !s.empty() ){
				  if ( s.top() == n ){ s.pop(); r--; res++; }
				  else if ( q[n].size() < Q ){
						q[n].push(s.top()); s.pop(); res++;
				  }
				  else break;
			 }
			 /* Load */
			 while (!q[n].empty() && s.size() < S){
				s.push( q[n].front() );  q[n].pop();
				res++;
			 } 
			 if ( r > 0 ) res+=2;
			 n = (n + 1)%N;
		}
		printf("%d\n",res);
  }
  
  

  return 0;
}