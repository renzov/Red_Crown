#include<cstdio>
#include<climits>
#include<algorithm>
#include<iostream>
using namespace std;
const int MAX = 100005;
#define forn(i,n) for ( int i=0; i < (int)(n); ++i )
long long a[ MAX ];
long long b[ MAX ];
long long ss[ MAX ];
int n;

int main(){
  int best;
  long long sum;
  int na,nb;
  long long bsum = -INT_MAX;
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  scanf("%d",&n);
  forn(i,n){ scanf("%I64d %I64d",a+i,b+i); }
  sort( a , a + n );
  sort( b , b + n );
  ss[n-1] = a[n-1];
  int idL,idU;
  for ( int i=n-2; i >= 0 ; --i ) ss[i] = ss[i+1] + a[i];
  forn(i,n){
	 idL = lower_bound( b , b + n , b[i] ) - b;
	 idL--;
	 idU = upper_bound( a , a + n , b[i] ) - a;
	 nb = idL + 1;
	 na = n - idU;
	 if ( na ){ sum = (n - na - nb)*b[i] + ss[idU]; }
	 else { sum = ( n - na - nb )*b[i]; }
	 if ( sum > bsum ){ bsum = sum; best = i; }
  }
  cout << b[best] << " " << bsum << endl;
  return 0;
}