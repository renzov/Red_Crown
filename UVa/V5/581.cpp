#include<vector>
#include<cstdio>
#include<cctype>

using namespace std;

char w[129][35];
int dx[]={0,1,1,1,0,-1,-1,-1};
int dy[]={-1,-1,0,1,1,1,0,-1};
char direc[ 8 ][3] = { "N", "NE", "E", "SE", "S", "SW", "W", "NW" }; 
int n;
int c;
vector< vector<char> > M;

bool search(int y,int x,int d,int p){
  for (int i=0; w[p][i]; ++i){
	 if (x < 0 || x >= c || y < 0 || y >= n) return false;
	 if ( w[p][i] != M[y][x]) return false;
	 x += dx[d];
	 y += dy[d];
  }
  return true;
}

void find_word(int p){
  bool found = false;
  int dir;
  int pos;
  for (int j=0; j < c && !found; ++j){
		for (int i=0; i < n && !found && M[i][j]; ++i){
			 if ( M[i][j] == w[p][0] ){
				  for (int k=0; k < 8 && !found; ++k){
						if ( search(i,j,k,p) ){
						  found = true;
						  dir = k;
						  pos = j*n + i;
						}
				  }
			 }
		}
  }
  printf("%s",w[p]);
  if (!found) puts(" NOT FOUND");
  else printf(" %d %s\n",pos,direc[dir]);
}

int main(){
  char line[130];
  int runs;
  int m;
  int t;
  int p;
  
  scanf("%d",&runs);
  while (runs--){
	 scanf("%d",&n);
	 M.clear();
	 if (n <= 0){
		scanf("%d",&m);
		for (int i=0; i < m; ++i) scanf("%s",w[i]);
		scanf("%d",&t);
		while (getchar() != '\n');
		for (int i=0; i < t; ++i){
				gets(line);
		}
		for (int i=0; i < m; ++i){
			printf("%s NOT FOUND\n",w[i]);
		}
	 }
	 else {
		  M.resize(n);
		  scanf("%d",&m);
		  for (int i=0; i < m; ++i) scanf("%s",w[i]);
		  scanf("%d",&t);
		  while (getchar() != '\n');
		  p = 0;
		  for (int i=0; i < t; ++i){
			 gets(line);
			 for (int j=0; line[j]; ++j){
				if (isalpha( line[j] )){
				  M[p].push_back( line[j] );
				  p = (p + 1)%n;
				}
			 }
		  }
		  c = M[0].size();
		  for (int i=1; i < n; ++i){
				if (M[i].size() < c){
				  M[i].push_back( (char)0 );
				}
		  }
		  for (int i=0; i < m; ++i){
			 find_word(i);
		  }
	 }
	 if (runs) putchar('\n');
  }

  return 0;
}