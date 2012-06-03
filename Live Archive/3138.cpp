#include<cstdio>
#include<vector>
using namespace std;
vector<int> T[ 1002 ];
vector< vector<int> > L;
int S[1002];
int st;
int C[1002];

void dfs(int u){
  S[st++] = u;
  for (int i=0; i < T[u].size(); ++i) dfs(T[u][i]);
}

vector<int> find_best( vector<int> A , vector<int> B ){
  int n = A.size();
  int m = B.size();
  vector< vector<int> > dp( n+1 , vector<int>(m+1) );
  vector< vector<char> > pre( n+1 , vector<char>(m+1) ); 
  
  int a,b;
  dp[n][m] = 0;
  for (int j=m-1; j >= 0; --j){ dp[n][j] = dp[n][j+1] + C[ B[j] ]*( m - j ); pre[n][j] = 2; }
  for (int i=n-1; i >= 0; --i){ dp[i][m] = dp[i+1][m] + C[ A[i] ]*( n - i ); pre[i][m] = 1; }
  for (int i=n-1; i >= 0; --i){
	 for (int j=m-1; j >= 0; --j){
		a = dp[i+1][j] + C[ A[i] ]*( n - i + m - j );
		b = dp[i][j+1] + C[ B[j] ]*( n - i + m - j );
		if ( a <= b ){
		  dp[i][j] = a; pre[i][j] = 1;
		}
		else {
		  dp[i][j] = b; pre[i][j] = 2;
		}
	 }
  }
  vector<int> res( n + m );
  a=b=0;
  for (int i=0; i < (n+m); ++i){
	 if ( pre[a][b] == 1 ){ res[i] = A[a]; a++; }
	 else { res[i] = B[b]; b++; }
  }
  return res;
}

int main(){
  int n,r;
  int u,v;
  int res;
  while ( scanf("%d %d",&n,&r) && n ){
	 r--;
	 //Init
	 for (int i=0; i < n; ++i) T[i].clear();
	 L.clear();
	 st = 0;
	 for (int i=0; i < n; ++i) scanf("%d",C+i);
	 for (int i=0; i < n-1; ++i){
		scanf("%d %d",&u,&v);
		u--,v--;
		T[u].push_back(v);
	 }
	 dfs( r );
	 L.resize( n );
	 while ( st > 0 ){
		st--;
		u = S[st];
		if ( T[u].size() == 0 ){
		  L[u].push_back(u);
		}
		else {
		  L[u] = L[ T[u][0] ]; //Init as his leftmost son
		  for (int i=1; i < T[u].size(); ++i)
			 L[u] = find_best( L[u] , L[ T[u][i] ] );
		  L[u].push_back( u );
		}
	 }
	 res = 0;
	 for (int i=L[r].size() - 1,j=1; i >= 0 ; --i,++j){
		res += C[ L[r][i] ] * j;
	 }
	 printf("%d\n",res);
  }
  return 0;
}