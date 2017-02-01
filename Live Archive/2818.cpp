#include<cstdio>
#include<algorithm>
#include<sstream>
#include<string>
#include<climits>
#include<iostream>
using namespace std;
string s;
int n,m;
int G[50][50];
long long CI[50][50];
int line[ 55 ];

void read_line(){
  m = 0;
  int v;
  getline(cin,s);
  stringstream in(s);
  while ( in >> v ){
	 v--;
	 line[m++] = v;
  }
}

int main(){
  char c;
  int v;
  cin >> n;
  for (int i=0; i < n; ++i){
	 for (int j=0; j < n; ++j){ 
		G[i][j] = INT_MAX;
	 }
	 G[i][i] = 0;
  }
  getline(cin,s);
  for (int u=0; u < n; ++u){
		read_line();
		for (int i=0; i < m ; ++i)
		  G[u][ line[i] ] = 1;
  }
  // floyd
  for (int k=0; k<n; ++k)
	 for (int i=0; i < n; ++i)
		for (int j=0; j < n; ++j)
		  if ( G[i][k] != INT_MAX && G[k][j] != INT_MAX )
			 G[i][j] = min( G[i][j] , G[i][k] + G[k][j] );

  /* Finding the complements */
  for (int u=0; u < n; ++u){
	 for (int v=u+1; v < n; ++v){
		CI[u][v] = 0LL;
		for (int k=0; k < n; ++k){
		  if ( k != u && k != v ){
			 if ( (G[u][k] + G[k][v]) != G[u][v] )
				CI[u][v] |= (1LL << k);
		  }
		}
		CI[v][u] = CI[u][v];
	 }
  }

  int runs;
  long long inter;
  cin >> runs;
  getline(cin,s);
  while (runs--){
	 read_line();
	 inter = (1LL << n) - 1LL;
	 for (int i=0; i < m && inter; ++i){
		for (int j=i+1; j < m && inter; ++j){
		  inter &= CI[ line[i] ][ line[j] ];
		}
	 }
	 if ( inter ) puts("no");
	 else puts("yes");
  }
  return 0;
}