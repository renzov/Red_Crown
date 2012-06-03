#include<cstdio>
#include<vector>
#include<cstring>
#include<cstdlib>
#include<climits>
using namespace std;

char L[258];
vector< vector<int> > dp;
vector< vector<int> > next;
int n,m;

void print_sol( int sum , int pos ){
  int i;
  int t = 0;
  //printf("sum = %d - pos = %d - next %d\n",sum,pos,next[pos][sum]);
  if (pos >= n) return;
  for (i=pos; i < n && i <= next[pos][sum]; ++i){ 
	 putchar(L[i]); 
	 t = t*10 + (L[i]-'0');
  }
  if ( i < n ){
	 putchar('+');
	 print_sol( sum - t , i );
  }
}

int solve( int sum , int pos ){
	if ( pos >= n ){
		return sum ? INT_MAX:0;
	}
	if ( L[pos] == '0' ) return INT_MAX;
	if (sum <= 0) return INT_MAX;
	if (dp[pos][sum] != -1) return dp[pos][sum];
	int i;
	int tmp;
	int maxi = INT_MAX;
	int num = 0;
	dp[pos][sum] = INT_MAX;
	for (i=pos;num <= sum && i < n && i < (pos + 5); ++i){
		num = num*10 + ( L[i] - '0' );
		tmp = solve( sum - num , i + 1 );
		if ( tmp < INT_MAX && tmp  < maxi){
		  maxi = tmp;
		  next[pos][sum] = i;
		}
	}
	if (maxi < INT_MAX)
	 dp[pos][sum] = maxi + 1;
	return dp[pos][sum];
}

int main(){
  int runs = 0;
  char *p;
  while (1){
	 runs++;
	 scanf("%s",L);
	 if (strcmp("0=0",L) == 0) break;
	 p = strchr(L,'=');
	 m = atoi(p+1);
	 *p = '\0';
	 n = strlen(L);
	 dp = vector< vector<int> >( n , vector<int>(m+1,-1) );
	 next = vector< vector<int> >( n , vector<int>(m+1,-1) );
	 int res = solve( m , 0 );
	 printf("%d. ",runs);
	 if ( res >= INT_MAX) puts("IMPOSSIBLE");
	 else {
		print_sol( m , 0 );
		printf("=%d\n",m);
	 }
  }
  return 0;
}