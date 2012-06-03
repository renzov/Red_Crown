#include<cstdio>
#include<climits>
#include<cstdlib>
#include<numeric>
#include<algorithm>
using namespace std;

int n,t;
int T[15];
int L[55];
int up[15];
int low[15];

inline int Min(int x,int y){ return x<=y? x:y; }
inline int Max(int x,int y){ return x>=y? x:y; }
int lcm( int x , int y ){ return ( x * y ) / __gcd(x,y); }

int main(){
  int mul,ll,uu;
  while (scanf("%d %d",&n,&t) && n){
	 for ( int i=0; i < n; ++i ){
		scanf("%d",L+i);
	 }
	 for (int i=0; i < t; ++i){
		scanf("%d",T+i);
		up[i] = INT_MAX;
		low[i] = 0;
	 }
	 for ( int i=0; i <= (n-4); ++i ){
		for ( int j=i+1; j <=(n-3); ++j ){
		  for ( int k=j+1; k <= (n-2); ++k ){
			 for ( int l=k+1; l <= (n-1); ++l ){
				mul = lcm( L[i] , L[j] ); 
				mul = lcm( L[k] , mul );  
				mul = lcm( L[l] , mul ); 
				for ( int p=0; p < t; ++p ){
				  ll = (T[p]/mul)*mul;
				  if ( ll < T[p] ) uu = ll + mul;
				  else uu = ll;
				  low[p] = Max( low[p] , ll );
				  up[p] = Min( up[p] , uu );
				}
			 }
		  }
		}
	 }
	 for ( int i=0; i < t; ++i ) printf("%d %d\n",low[i],up[i]);
  }

  return 0;
}