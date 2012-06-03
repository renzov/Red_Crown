#include<cstdio>
#include<vector>
using namespace std;
int n;
int a[15];
int sum;
int S[3];

vector<int> s[ 400 ];
bool used[ 15 ] = {0};
bool join[ 400 ] = {0};

bool backtrack( int p , int acc ){
  if ( p >= 3 ) return true;
  if ( acc == sum ){ return backtrack( p + 1 , 0 );}
  /* Take all the permutations */
  int i;
  for ( i=0; i < n; ++i ){
	 if ( ((S[p]>>i)&1) && !used[i] ){
		if ( ((acc + a[i]) < sum) && join[acc+a[i]] ) continue;
		join[acc+a[i]] = used[i] = true;
		if ( backtrack( p , acc + a[i] ) ){
		  used[i] = join[ acc + a[i] ] = false;
		  return true;
		}
		used[i] = join[ acc + a[i] ] = false;
	 }
  }
  return false;
}

int process(){
  int i,j,k;
  while ( sum > 0 ){
	 if ( s[sum].size() >= 3 ){
		for ( i=0; i < (s[sum].size()); ++i ){
		  for ( j=i+1; j < (s[sum].size()); ++j ){
			 if ( s[sum][i] & s[sum][j] ) continue; //Only use 1 time
			 for ( k=j+1; k < s[sum].size(); ++k ){
				if ( (s[sum][i] & s[sum][k]) || (s[sum][j] & s[sum][k]) ) continue; //Only use 1 time
				S[0] = s[sum][i]; S[1] = s[sum][j]; S[2] = s[sum][k];
				if ( backtrack(0,0) ) return sum;
			 }
		  }
		}
	 }
	 sum--;
  }
  return 0;
}

int main(){
  int i,j;
  int t;
  int res;
  int cases = 0;
  while ( scanf("%d",&n) && n ){
	 sum = 0; cases++;
	 for ( i = 0; i < n; ++i ){ scanf("%d",a+i); sum+=a[i]; }
	 //Clear
	 sum /= 3;
	 for ( i=0; i <= sum; ++i ) s[i].clear();
	 //Creating sets
	 for ( i = 1; i < (1<<n); ++i ){
		if ( i == (i&-i) ) continue; //Avoid unit sets
		t = 0;
		for ( j = 0; j < n; ++j ){
		  if ( (i>>j) & 1 ){
			 t += a[j];
		  }
		}
		if ( t <= sum ) s[t].push_back(i);
	 }
	 res = process();
	 printf("Case %d: %d\n",cases,res);
  }
  return 0;
}