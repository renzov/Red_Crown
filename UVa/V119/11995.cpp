#include<cstdio>
#include<queue>
#include<stack>
#include<vector>
using namespace std;

int main(){
  int n,t;
  int v;
  while (scanf("%d",&n) != EOF){
	 queue<int> q;
	 priority_queue<int> pq1;
	 stack<int> s;
	 bool error = false;
	 bool isPQ1 = true;
	 bool isStack = true;
	 bool isQueue = true;
	 int cnt = 0;
	 for (int i=0; i < n; ++i){
		scanf("%d %d",&t,&v);
		if ( t==1 ){ 
			 if ( isStack ) s.push( v );
			 if ( isQueue ) q.push( v );
			 if ( isPQ1 ) pq1.push( v );
		}
		else {
			 if ( isStack ){  
				  if ( s.empty() ) error = true;  
				  else { isStack = v == s.top(); s.pop(); } 
				
			 }
			 if ( isQueue ){  
				if ( q.empty() ) error = true; 
				else { isQueue = v == q.front(); q.pop(); } 
			 }
			 if ( isPQ1 ){ 
				if ( pq1.empty() ) error = true;
				else { isPQ1 = v == pq1.top(); pq1.pop(); }  
			 }
		}
	 }
	 
	 if ( isStack ) cnt++;
	 if ( isQueue ) cnt++;
	 if ( isPQ1 ) cnt++;
	 
	 if (error) puts("impossible");
	 else if ( cnt == 0 ) puts("impossible");
	 else if ( cnt > 1 ) puts("not sure");
	 else {
		  if ( isStack ) puts("stack");
		  else if ( isQueue ) puts("queue");
		  else puts("priority queue");
	 }
  }
  return 0;
}