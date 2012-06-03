#include<cstdio>
#include<queue>
#include<algorithm>
using namespace std;

bool present[30][30];
int indeg[30];
int X1[30];
int X2[30];
int Y1[30];
int Y2[30];
int XP[30];
int YP[30];

pair< int , int > res[30];

inline bool inside( int i , int  j ){
  return XP[i]>X1[j] && XP[i]<X2[j] && YP[i]>Y1[j] && YP[i]<Y2[j];
}

int main(){
  int n;
  int m;
  int u;
  int cases = 0;
  while ( scanf("%d",&n) && n ){
	 cases++;
	 for ( int i=0; i < n ; ++i ){
		indeg[i] = 0;
		for ( int j=0; j < n; ++j )
		  present[i][j] = false;
	 }
	 for ( int i=0; i < n; ++i ){
		scanf("%d %d %d %d",X1+i,X2+i,Y1+i,Y2+i);
	 }
	 bool ok = true;
	 bool found;
	 for ( int i=0; i < n; ++i ){
		scanf("%d %d",XP+i,YP+i);
		found = false;
		for ( int j=0; j < n; ++j ){
		  if ( inside( i , j ) ){ indeg[j]++; present[j][i] = true; found = true; }
		}
		ok &= found;
	 }
	 printf("Heap %d\n",cases);
	 
	 
		m = 0;
		queue<int> q;
		for ( int i=0; i < n; ++i ) if ( indeg[i] == 1 ) q.push(i);
		while ( !q.empty() ){
		  u = q.front();  q.pop();
		  for ( int j=0; j < n; ++j ){
			 if ( present[u][j] ){
				res[m++] = make_pair( u , j );
				for ( int i=0; i < n; ++i ){
				  if ( i != u && present[i][j] ){
					 present[i][j] = false; indeg[i]--;
					 if ( indeg[i] == 1 ) q.push(i);
				  }
				}
				break;
			 }
		  }
		}
		if ( m == 0 ) puts("none");
		else {
		  sort( res , res + n );
		  for ( int i=0; i < m; ++i ){
			 if ( i > 0 ) putchar(' ');
			 printf("(%c,%d)",(char)(res[i].first+'A'),res[i].second+1);
		  }
		  putchar('\n');
		}
	 
	 puts("");
  }
  return 0;
}
