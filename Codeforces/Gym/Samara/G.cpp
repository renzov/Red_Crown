#include<iostream>
#include<algorithm>
#include<cstdio>
using namespace std;
#define forn(i,n) for(int i=0; i < (int)(n); ++i)

pair<int,int> a[2005];
int res[2005]={0};

int main(){
  int n,k;
  int mini;
  freopen("input.txt","r",stdin);
  freopen("output.txt","w",stdout);
  cin >> k >> n;
  forn(i,n){ cin >> a[i].first; a[i].second = i;  }
  sort( a , a + n );
  forn( i , n ){
	 if ( !k ) break;
	 mini = min( a[i].first , k );
	 res[ a[i].second ] = mini;
	 k-=mini;
  }
  forn(i,n){
	 if ( i ) cout << " ";
	 cout << res[i];
  }
  cout << endl;
}
