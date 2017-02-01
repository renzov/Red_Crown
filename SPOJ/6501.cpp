#include<cstdio>
#include<queue>
using namespace std;

int main(){
  int n;
  int s;
  int e;
  int i;
  int ant;
  int mid;
  priority_queue<int> a;
  priority_queue< int, vector<int> , greater<int> > b;
  scanf("%d",&n);
  scanf("%d",&e);
  printf("%d\n",e);
  a.push(e);
  s = 1;
  ant = 1;
  for (i=1; i < n; ++i){
		scanf("%d",&e);
		s++;
		if (s&1) mid = (s+1) >> 1;
		else mid = s >> 1;
		if (mid == ant){
		  if (e < a.top()){
			 b.push(a.top()); a.pop(); a.push(e);
		  }
		  else {
			 b.push( e );
		  }
		}
		else {
			 ant = mid;
			 b.push( e );
			 a.push( b.top() );
			 b.pop();
		}
		printf("%d\n",a.top());
  }
  return 0;
}