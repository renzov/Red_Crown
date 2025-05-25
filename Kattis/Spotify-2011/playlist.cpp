#include<iostream>
#include<string>
#include<map>
#include<vector>
using namespace std;
const int MAXN = 128;

int K = 0;
map<string, int> H;
vector<int> G[MAXN];
vector<int> R[MAXN];
int color[MAXN];

int total = 0;
int S3[MAXN][MAXN][MAXN];
int path[MAXN][MAXN][MAXN];
int S2[MAXN][MAXN];
int S1[MAXN];
bool forbid[MAXN];
int ans[11];

int get_id( string &s ){
	if ( !H.count(s) )
		return K++;
	return H[s];
}

int main(){
	int u, v, w, x;
	int a, b, c;
	int N, t, res;
	string name;

	// Read the input -- create G and the reverse graph R
	cin >> N;
	for ( u = 0; u < N; ++u ){
		cin >> name >> t; 
		color[u] = get_id(name);
		for ( int i = 0; i < t; ++i ){
			cin >> v;
			v--;
			G[u].push_back(v);
			R[v].push_back(u);
		}
	}
	
	bool found = false;	
	// count number of paths of length 4 testing each as middle vertex
	for ( u = 0; u < N && !found; ++u ){
		// count number of 4-paths starting from u in the reverse graph: O(t^3)
		for ( int i = 0; i < (int)R[u].size(); ++i ){
			v = R[u][i];
			if ( color[u] == color[v] ) continue;
			for ( int j = 0; j < (int)R[v].size(); ++j ){
				w = R[v][j];
				if ( color[w] == color[v] || color[w] == color[u] ) continue;
				for ( int k = 0; k < (int)R[w].size(); ++k ){
					x = R[w][k];
					if ( color[x] == color[w] || color[x] == color[v] || color[x] == color[u] ) continue;
					// a new path found - sort the colors
					a = min( color[v], min( color[w], color[x] ) );
					c = max( color[v], max( color[w], color[x] ) );
					b = color[v] + color[w] + color[x] - a - c;
					// count this path - for inclusion-exclusion
					total++;					
					S3[a][b][c]++;
					S2[a][b]++, S2[a][c]++, S2[b][c]++;
					S1[a]++, S1[b]++, S1[c]++;
					// store the path as bitset
					path[a][b][c] = x | (w << 7) | (v << 14); 
				}
			} 
		}
		// test every 4-path starting from u in G as solution: O(t^3)
		for ( int i = 0; i < (int)G[u].size() && !found; ++i ){
			v = G[u][i];
			if ( color[u] == color[v] ) continue;
			for ( int j = 0; j < (int)G[v].size() && !found; ++j ){
				w = G[v][j];
				if ( color[w] == color[v] || color[w] == color[u] ) continue;
				for ( int k = 0; k < (int)G[w].size() && !found; ++k ){
					x = G[w][k];
					if ( color[x] == color[w] || color[x] == color[v] || color[x] == color[u] ) continue;
					// a path was found
					a = min( color[v], min( color[w], color[x] ) );
					c = max( color[v], max( color[w], color[x] ) );
					b = color[v] + color[w] + color[x] - a - c;
					// Find how many paths do not contain a, b or c in the reverse graph
					res = total - S1[a] - S1[b] - S1[c] + S2[a][b] + S2[a][c] + S2[b][c] - S3[a][b][c];
					if ( res > 0 ){
						found = true;
						forbid[ color[u] ] = forbid[a] = forbid[b] = forbid[c] = true;
						ans[0] = x, ans[1] = w, ans[2] = v, ans[3] = u;
					}
				}
			}
		}
			
		if ( !found ){	// clean variables for next iteration

		}

	}

	if ( found ) {
		found = false;
		for ( int i = 0; i < K && !found; ++i ){
			if ( forbid[i] ) continue;
			for ( int j = i + 1; j < K && !found; ++j ){
				if ( forbid[j] ) continue;
				for ( int k = 0; k < K && !found; ++k ){
					if ( forbid[k] ) continue;
					if ( S3[i][j][k] > 0 ){
						found = true;
						ans[8] = path[i][j][k] & ( (1 << 7) - 1 );
						path[i][j][k] >>= 7;
						ans[7] = path[i][j][k] & ( (1 << 7) - 1 );
						path[i][j][k] >>= 7;
						ans[6] = path[i][j][k] & ( (1 << 7) - 1 );
					}
				}
			}		
		}
		reverse(  )
	}
	else {
		cout << "fail\n";
	}


	return 0;
}
