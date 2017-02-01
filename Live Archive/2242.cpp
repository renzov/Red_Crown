#include<cstdio>
#include<queue>
#include<vector>
#include<algorithm>
#include<cctype>
#include<set>
#include<string>
#include<iostream>
using namespace std;

const int MAX = 100;
char F[40][40];
bool present[30];
int X1[30];
int X2[30];
int Y1[30];
int Y2[30];
bool G[30][30];
char vertex[30];
char sol[30];
bool used[30];
int n;
set<string> S;

bool check(int m,int u){
  for (int i=0; i < m; ++i){
	 if (G[u][sol[i]-'A']) return false;
  }
  return true;
}

void backtrack(int p){
	 if (p==n){
		sol[p] = '\0';
		string s = string(sol);
		reverse(s.begin(),s.end());
		S.insert(s);
		return;
	 }
	 for (int i=0; i < n; ++i){
		if (!used[i] && check(p,vertex[i]-'A')){
		  used[i] = true;
		  sol[p] = vertex[i];
		  backtrack(p+1);
		  used[i] = false;
		}
	 }
}

int main(){
  int h,w;
  while (scanf("%d %d",&h,&w) != EOF){
	 for (int i=0; i < h; ++i){
		  scanf("%s",F[i]);
	 }
	 
	 for (int i=0; i < 26; ++i){
		present[i] = false;
		for(int j=0; j < 26; ++j) G[i][j] = false;
		X1[i] = MAX;
		X2[i] = -MAX;
		Y1[i] = MAX;
		Y2[i] = -MAX;
	 }
	 for (int i=0;i < h; ++i)
		for (int j=0; j < w; ++j){
			 if (isalpha( F[i][j] )){
				  present[ F[i][j]-'A' ] = true;;
				  X1[ F[i][j]-'A' ] = min( X1[ F[i][j]-'A' ] , j );
				  X2[ F[i][j]-'A' ] = max( X2[ F[i][j]-'A' ] , j );
				  Y1[ F[i][j]-'A' ] = min( Y1[ F[i][j]-'A' ] , i );
				  Y2[ F[i][j]-'A' ] = max( Y2[ F[i][j]-'A' ] , i );
			 }
		} 
	 char c;
	 n = 0;
	 for (int i=0; i<26; ++i){
		  if (present[i]){
				c = (char)('A' + i);
				vertex[n] = c;
				used[n] = false;
				n++;
				for (int j=X1[i]; j <= X2[i]; ++j) 
				  if (isalpha( F[ Y1[i] ][ j ]) && F[ Y1[i] ][ j ] != c){
						G[ F[ Y1[i] ][ j ] - 'A' ][ i ] = true;
				  }
				for (int j=X1[i]; j <= X2[i]; ++j) 
				  if (isalpha(F[ Y2[i] ][ j ]) && F[ Y2[i] ][ j ] != c){
						G[ F[ Y2[i] ][ j ] - 'A' ][ i ] = true;
				  }
				for (int j=Y1[i]; j <= Y2[i]; ++j) 
				  if (isalpha(F[ j ][ X1[i] ]) && F[ j ][ X1[i] ] != c){
						G[ F[ j ][ X1[i] ] - 'A' ][ i ] = true;
				  }
				for (int j=Y1[i]; j <= Y2[i]; ++j) 
				  if (isalpha(F[ j ][ X2[i] ]) && F[ j ][ X2[i] ] != c){
						G[ F[ j ][ X2[i] ] - 'A' ][ i ] = true;
				  }
		  }
	 }
	 S.clear();
	 backtrack(0);
	 set<string>::iterator it = S.begin();
	 while (it != S.end()){ cout << *it << "\n"; it++; }
  }

  return 0;
}