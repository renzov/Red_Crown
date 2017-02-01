#include<cstdio>
#include<algorithm>
#include<queue>
using namespace std;
pair<int,int> a[10005];
typedef pair< int , pair<int,int> > triple;

int main(){
  int runs;
  int n;
  int L,P;
  int st,dist;
  int fuel;
  int pos;
  scanf("%d",&runs);
  while (runs--){
		scanf("%d",&n);
		for (int i=0; i < n; ++i){
		  scanf("%d %d",&a[i].first,&a[i].second);
		}
		a[n].first = L;
		a[n].second = 0;
		n++;
		a[n].first = 0;
		a[n].second = 0;
		n++;
		scanf("%d %d",&L,&P);
		sort(a,a+n);
		priority_queue< triple, vector<triple>, greater<triple> > q;
		q.push( make_pair( 0 , make_pair( 0 , P ) ) );
		int res = -1;
		while (!q.empty()){
		  triple top = q.top();
		  if (top.second.first >= L){ res = top.first; break; }
		  q.pop();
		  st = top.first;
		  pos = top.second.first;
		  fuel = top.second.second;
		  dist = a[pos + 1].first - a[pos].first;
		  if ( fuel >= dist ){
			 q.push( make_pair( st , make_pair( pos + 1 , fuel - dist ) ) );
		  }
		  if ( a[pos].second > 0 && (fuel + a[pos].second) >= dist ){
			 q.push( make_pair( st + 1 , make_pair( pos + 1 , fuel + a[pos].second - dist ) ) );
		  }
		}
		printf("%d\n",res);
  }

  return 0;
}