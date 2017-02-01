#include<cstdio>
#include<algorithm>
using namespace std;

const int MAXN = 100005;

int next[MAXN][4];
bool vis[MAXN][4];

int main(){
	int n, g;
	int runs;
	scanf("%d", &runs);
	while ( runs-- ){
		scanf("%d %d", &n, &g);
		g--;
		for ( int i=0; i < n; ++i )
			for ( int j=0; j < 4; ++j ){
				vis[i][j] = false;
				scanf("%d", &next[i][j]);
				next[i][j]--;
			}
		int res = 0;
		bool found;
		int act , dir;
		int prev, dirp;
		for ( int j=0; j < 2; ++j ){
			for ( int i=0; i < n; ++i ){
				if ( !vis[i][j & 1] ){
					prev = i, dirp = j;
					found = i == g;
					while ( !vis[prev][dirp & 1] ){
						vis[prev][dirp & 1] = true;
						act = next[prev][dirp];						
						if ( act == g ) found = true;
						for ( dir=0; dir < 4 && next[act][dir] != prev; dir++ );
						prev = act, dirp = dir ^ 2;
					}
					if ( !found ) res++;
				}
			}
		}
		printf("%d\n", res);
	}
	return 0;
}
