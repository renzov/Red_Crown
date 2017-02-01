#include<cstdio>
#include<cctype>
#include<stack>
using namespace std;
struct matrix {
  int r,c;
  matrix(){}
  matrix(int x,int y){ r = x; c = y; }
};


char line[ 10000 ];
matrix M[ 30 ];
bool found[ 30 ] = {0};
int main(){

  int n;
  matrix a,b;
  char m;
  int r,c;
  bool error;
  scanf("%d",&n);
  for (int i=0; i<n; ++i){
		scanf(" %c %d %d",&m,&r,&c);
		M[ m - 'A' ] = matrix(r,c);
		found[ m - 'A' ] = true;
  }
  int res;
  while (scanf("%s",line) != EOF){
	 stack< matrix > s;
	 error = false;
	 res = 0;
	 for (int i=0; line[i] && !error ; ++i){
		if ( isalpha( line[i] ) ){
		  if ( found[ line[i] - 'A'] ) s.push( M[ line[i] - 'A'] );
		  else error = true;
		}
		else if ( line[i] == ')' ){
		  b = s.top(); s.pop();
		  a = s.top(); s.pop();
		  if ( a.c != b.r ) error = true;
		  else {
			 s.push( matrix( a.r , b.c ) );
			 res += (a.r*a.c*b.c);
		  }
		}
	 }
	 if (error) puts("error");
	 else printf("%d\n",res);
  }
  return 0;
}