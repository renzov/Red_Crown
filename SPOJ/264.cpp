#include<cstdio>
#include<algorithm>
using namespace std;
const int MAX = 20005;
int p[MAX];
int dd[MAX];

inline int abs(int x){ return x<0? -x:x; }

void make_set(int x){
  p[x] = x;
  dd[x] = 0;
}

pair<int,int> find_set(int x){
  if (p[x]==x) return make_pair(p[x],dd[x]);
  else {
	 pair<int,int> px = find_set(p[x]);
	 dd[x] += px.second;
	 p[x] = px.first;
  }
  return make_pair(p[x],dd[x]);
}

void union_set(int x,int y){
	 p[x] = y;
	 dd[x] += abs(x-y)%1000;
}

int main(){
  int n;
  int runs;
  int x,y;
  char c;
  pair<int,int> px;
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 for (int i=1; i <= n; ++i) make_set(i);
	 while (1){
		scanf(" %c",&c);
		if (c == 'O') break;
		if (c=='E'){
			scanf("%d",&x);
			px = find_set(x); 
			printf("%d\n",px.second);
		}
		else {
		  scanf("%d %d",&x,&y);
		  px = find_set(x);
		  union_set(px.first,y);
		}
	 }
  }
  return 0;
}