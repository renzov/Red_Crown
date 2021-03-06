#include<cstdio>
#include<vector>
#include<map>
#include<string>
#include<queue>
using namespace std;

vector<int> G[ 25 ];
map<string,int> h;

int n;
int m;
int res;

int used[ 25 ] = { 0 };

void backtrack(int pos,int count,int left){
  if (left == 0 || pos >= n){
	 if (count > res) res = count;
	 return;
  }
  
  if ((left + count) <= res) return;
  for ( ; used[pos] && pos < n ; ++pos);
  /* Take (pos) */
  if (pos < n){
	 used[pos]++;
	 left--;
	 for (int i=0; i < G[pos].size(); ++i){
	 if ( used[ G[pos][i] ] == 0) left--; 
		used[ G[pos][i] ]++;
	 }
	 backtrack(pos+1,count+1,left);
	 /* No take (pos) */
	 for (int i=0; i < G[pos].size(); ++i){
		used[ G[pos][i] ]--;
		if ( used[ G[pos][i] ] == 0) left++;
	 }
	 backtrack(pos+1,count,left);
	 used[pos]--;
	 left++;
  }
}

int get_id(char *cad){
  string t(cad);
  if (h.find(t) == h.end()){
	 h[t] = m++;
  }
  return h[t];
}

int main(){
  int u;
  char cad[25];
  int mem[ 25 ][ 4 ];

  m = 0;
  scanf("%d",&n);
  
  for (int i=0; i < n; ++i){
	 for (int j=0; j < 3; ++j){
		scanf("%s",cad);
		u = get_id(cad);
		mem[i][j] = u;
	 }
  }

  for (int i=0; i < n-1; ++i){
	 for (int j=i+1; j < n; ++j){
		  if ( mem[i][0] == mem[j][0] || mem[i][0] == mem[j][1] || mem[i][0] == mem[j][2] 
			 || mem[i][1] == mem[j][0] || mem[i][1] == mem[j][1] || mem[i][1] == mem[j][2]
			 || mem[i][2] == mem[j][0] || mem[i][2] == mem[j][1] || mem[i][2] == mem[j][2] ){
			 G[i].push_back(j);
			 G[j].push_back(i);
		}
	 }	
  }
  res = 0;
  backtrack(0,0,n);
  printf("%d\n",res);

  return 0;
}