#include<iostream>
#include<algorithm>
using namespace std;

void base(long long x, int *X, int &n){
  n = 0;
  while ( x >= 3 ){
	 X[n++] = x%3;
	 x /= 3;
  }
  X[n++] = x;
}

void solve(int *A,int *B,int *C,int n){
  for (int i=0; i < n; ++i){
	 if ( C[i] >= A[i] ) B[i] = C[i] - A[i];
	 else B[i] = 3 + C[i] - A[i];
  }
}

int main(){

  long long a,c;
  int n,m;
  int B[105];
  int A[105];
  int C[105];
  cin >> a >> c;
  base( a , A , n );
  base( c , C , m );
  for (int i=n; i < max(n,m); ++i) A[i] = 0;
  for (int i=m; i < max(n,m); ++i) C[i] = 0;
  if ( n < m ) n = m;
  else if (m < n) m = n;
  solve( A , B , C , n );
  long long res = 0;
  long long j;
  for (int i=0,j=1; i < n; ++i,j*=3){
	 res += j*B[i];
  }
  cout << res << endl;
  return 0;
}