#include<cstdio>
#include<stack>
using namespace std;
int c[1005];
int main(){
  int n;
  int act;
  bool ok;
  int p;
  while (scanf("%d",&n) && n){
		for (int i=0; i <  n; ++i) scanf("%d",c+i);
		stack<int> s;
		act = 1;
		ok = true;
		p = 0;
		while (act <= n && ok){
			 if ( !s.empty() && s.top() == act ){
				  act++;
				  s.pop();
			 }
			 else {
				  if (p < n && c[p] == act){
						p++;
						act++;
				  }
				  else {
					 if (s.empty() && p < n) s.push(c[p++]);
					 else if (!s.empty() && p < n && s.top() > c[p]){
						  s.push(c[p++]);
					 }
					 else {
						  ok = false;
					 }
				  }
			 }
		}
		if (ok) puts("yes");
		else puts("no");
  }
  return 0;
}