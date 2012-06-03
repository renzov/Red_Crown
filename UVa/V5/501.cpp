#include<cstdio>
#include<queue>
using namespace std;
const int MAX = 30005;
int a[MAX];

int main(){
  
  int k;
  int n,m;
  int t;

  scanf("%d",&k);
  while (k--){
	 scanf("%d %d",&m,&n);
	 priority_queue< int  > q;
	 priority_queue< int , vector<int> , greater<int> > s;
	 for (int i=0; i < m; ++i) scanf("%d",a+i);
	 int p = 0;
	 for (int i=0; i < n; ++i){ 
		scanf("%d",&t);
		while ( t > p ){
		  if ( q.empty() ){ s.push( a[p] ); }
		  else if (q.top() > a[p]){
				s.push( q.top() );  q.pop();
				q.push( a[p] );
		  }
		  else { s.push( a[p] ); }
		  p++;
		}
		printf("%d\n",s.top());
		q.push( s.top() );
		s.pop();
	 }
	 if (k) putchar('\n');
  }
  return 0;
}