#include<cstdio>
#include<string>
#include<cstring>
#include<map>
#include<vector>
using namespace std;

int n;

int dp[205][2];
vector<int> G[205];
bool unique[205][2];

int solve(int u,bool cover){
  if ( G[u].size() == 0 ) return cover;
  if (dp[u][cover] != -1) return dp[u][cover]; 
  int i;
  int v;
  int sum;
  int res1,res2;
  if (cover){
	 sum = 0;
	 for (i=0; i < G[u].size(); ++i){
		v = G[u][i];
		sum += solve(v,false);
		unique[u][cover] &= unique[v][false];
	 }
	 dp[u][cover] = sum + 1;
  }
  else {
	 sum = 0;
	 for (i=0; i < G[u].size(); ++i){
		v = G[u][i];
		res1 = solve(v,false);
		res2 = solve(v,true);
		if ( res1 > res2 ){ sum += res1; unique[u][cover] &= unique[v][false]; }
		else if (res2 > res1){ sum += res2; unique[u][cover] &= unique[v][true]; }
		else { sum += res1; unique[u][cover] = false; }
	 }
	 dp[u][cover] = sum;
  }
  return dp[u][cover];
}

int main(){
  char name[105];
  string a;
  int u,v;
  int m;
  int i;
  int res1,res2;
  scanf("%d",&n);
  while (n){
	 map<string,int> hash;
	 scanf("%s",name);
	 hash[ string(name) ] = 0; m = 1;
	 for (i=0; i < n-1; ++i){
		unique[i][0] = unique[i][1] = true;
		dp[i][0] = dp[i][1] = -1;
		scanf("%s",name);
		a = string(name);
		if ( hash.find(a) == hash.end() ){ hash[a] = m++; }
		u = hash[a];
		scanf("%s",name);
		a = string(name);
		if ( hash.find(a) == hash.end() ){ hash[a] = m++; }
		v = hash[a];
		G[v].push_back(u);
	 }
	 unique[n-1][0] = unique[n-1][1] = true;
	 dp[n-1][0] = dp[n-1][1] = -1;
	 res1 = solve(0,false);
	 res2 = solve(0,true);
	 if (res1 == res2) printf("%d No\n",res1);
	 else if (res1 > res2){
		printf("%d %s\n",res1,(unique[0][false]) ? "Yes":"No");
	 }
	 else {
		printf("%d %s\n",res2,(unique[0][true]) ? "Yes":"No");
	 }
	 scanf("%d",&n);
	 if ( n ) for (i=0; i < n; ++i) G[i].clear();
  }
  return 0;
}