#include<cstdio>
#include<queue>
#include<vector>
using namespace std;

int main(){
  int e;
  int runs;
  int n,m;
  int mid;
  char order[5];

  scanf("%d",&runs);
  while (runs--){
		priority_queue<int> a;
		priority_queue< int, vector<int> , greater<int> > b;
		scanf("%d",&n);
		scanf("%d",&e);
		a.push(e);
		int s = 1;
		int ant = 1;
		n--;
		while (n--){
		  scanf("%d",&e);
		  s++;
		  if ( s&1 ){
			 mid = (s + 1)>>1;
		  }
		  else {
			 mid = s >> 1;
		  }
		  if ( mid == ant ){
			 if (e < a.top()){
				b.push(a.top()); a.pop(); a.push(e);
			 }
			 else {
				b.push(e);
			 }
		  }
		  else {
			 ant = mid;
			 if (e < a.top()){
				a.push(e);
			 }
			 else {
				b.push(e); a.push(b.top()); b.pop();
			 }
		  }
		}
		scanf("%d",&m);
		while (m--){
			scanf("%s",order);
			if (order[0] == 'a'){
				scanf("%d",&e);
				s++;
				if ( s&1 ){
				  mid = (s + 1)>>1;
				}
				else {
				  mid = s >> 1;
				}
				if ( mid == ant ){
				  if (e < a.top()){
					 b.push(a.top()); a.pop(); a.push(e);
				  }
				  else {
					 b.push(e);
				  }
				}
				else {
				  ant = mid;
				  if (e < a.top()){
					 a.push(e);
				  }
				  else {
					 b.push(e); a.push(b.top()); b.pop();
				  }
				}
			}
			else {
				printf("%d\n",a.top());
			}
		}
  }
  return 0;
}