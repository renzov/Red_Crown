#include<cstdio>
#include<cstring>
#include<algorithm>
using namespace std;
char line[2000];
int memo[1002][4];
int n;
int solve( int i , int pre ){
  if ( i >= n ) return 0;
  if ( memo[i][pre] != -1 ) return memo[i][pre];
  int act = line[i] - '0';
  memo[i][pre] = solve( i + 1 , pre ) + 1; //Eliminamos
  if ( (pre*10 + act) != 13 ){
	 memo[i][pre] = min(memo[i][pre] , solve( i + 1 , act ));
  }
  return memo[i][pre];
}

int main(){
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%s",line);
  n = strlen( line );
  memset( memo , -1 , sizeof(memo) );
  printf("%d\n",solve(0,0));
  return 0;
}