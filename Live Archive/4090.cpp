#include<cstdio>
#include<map>
#include<string>
#include<vector>
#include<cctype>
#include<sstream>
#include<iostream>
using namespace std;

int n;
int S,F;

struct result {
  int s,f;
  result(){ s = f = 0; }
  result(int ss,int ff){ s = ss; f = ff; }
  result operator + ( const result &that ) const {
	 return result( s + that.s , f + that.f );
  }
  bool operator<(const result &that) const {
	 if ( (s*S + f*F) != (that.s*S + that.f*F) ) return (s*S + f*F) < (that.s*S + that.f*F);
	 return (s + f)  < (that.s + that.f);
  }
};

vector<int> G[ 100002 ];
bool done[100002][2];
bool pai[100002];
result dp[100002][2];

result solve(int u,bool cover){
  if ( G[u].size() == 0 ){
	 if (cover) return result();
	 return result(1,0);
  }
  if ( done[u][cover] ) return dp[u][cover];
  done[u][cover] = true;
  result t1; /* sin comprar ticket grupal */
  result t2; /* comprando ticket grupal */
  int i;
  int v;
  for (i=0; i < G[u].size(); ++i){
	 v = G[u][i];
	 t1 = t1 + solve( v , false );
	 t2 = t2 + solve( v , true );
  }
  t2 = t2  + result(0,1);
  if (!cover) t1 = t1 + result(1,0);
  if ( t1 < t2 ) dp[u][cover] = t1;
  else dp[u][cover] = t2;
  return dp[u][cover];
}

int main(){
  string line;
  getline(cin,line);
  string a,b;
  int u,v;
  int i;
  int runs=0;

  while ( 1 ){
	 runs++;
	 stringstream first(line);
	 first >> S >> F;
	 if ( !S && !F ) break;
	 for (i=0; i < n; ++i){
		G[i].clear();
		pai[i] = false;
		done[i][0] = done[i][1] = false;
	 }
	 n = 0;
	 map<string,int> hash;
	 while ( 1 ){
		getline(cin,line);
		stringstream in(line);
		in >> a;
		if (isdigit(a[0])) break;
		if ( hash.find(a) == hash.end() ) hash[a] = n++;
		u = hash[a];
		while (in >> b){
		  if ( hash.find(b) == hash.end() ) hash[b] = n++;
		  v = hash[b];
		  pai[v] = true;
		  G[u].push_back(v);
		}
	 }
	 result tmp;
	 result res;
	 for (i=0; i < n; ++i){
		if (!pai[i]){
			tmp = solve( i , false );
			res = res + tmp;
		}
	 }
	 printf("%d. %d %d %d\n",runs,res.s,res.f,res.s*S + res.f*F);
  }
  return 0;
}