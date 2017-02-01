#include<cstdio>
#include<map>
using namespace std;
int p[100002];

int make_set(int x){ p[x] = x; }
int find_set(int x){ return ( p[x] != x )? (p[x]=find_set(p[x])):x; }
int union_set(int x,int y){ p[y] = x; }
int n;

int main(){
  int x,y;
  int res;
  char line[50];
  int runs = 0;
  while ( scanf("%d",&x) != EOF ){
	 runs++;
	 map<int,int> h;
	 n = 0;
	 res = 0;
	 while (x >= 0){
		scanf("%d",&y);
		if (h.find(x) == h.end()){ h[x] = n; make_set(n); n++; }
		if (h.find(y) == h.end()){ h[y] = n; make_set(n); n++; }
		x = h[x]; y = h[y];
		x = find_set(x); y = find_set(y);
		if ( x != y ) union_set(x,y);
		else res++;
		scanf("%d",&x);
	 }
	 printf("%d\n",res);
  }
  return 0;
}