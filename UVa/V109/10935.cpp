#include<queue>
#include<cstdio>
using namespace std;

int main(){
  int n;
  while (scanf("%d",&n) && n){
	 queue<int> q;
	 for (int i=0; i<n; ++i) q.push(i+1);
	 printf("Discarded cards:");
	 bool first = true;
	 while (n-- > 1){
		if ( !first ) putchar(',');
		printf(" %d",q.front());
		q.pop();
		first = false;
		q.push( q.front() ); q.pop();
	 }
	 putchar('\n');
	 printf("Remaining card: ");
	 printf("%d\n",q.front());
  }

  return 0;
}