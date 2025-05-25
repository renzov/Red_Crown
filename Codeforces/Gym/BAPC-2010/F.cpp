#include<iostream>
#include<vector>
#include<queue>
#include<string>
using namespace std;
const int MAXD = 210;

int maze[MAXD][MAXD];
int dx[] = {-1, 1, 0, 0};
int dy[] = {0, 0, 1, -1};
char C[] = {'N', 'S', 'E', 'W'};
int inv[] = {1, 0, 3, 2};

vector< vector<int> > G;
int N;	
int t;

inline char direction( const int &dir ){ return C[dir]; }

int create_vertex(){
	G.push_back( vector<int>() );
	return N++;
}

void dfs( const int &x, const int &y, const int &u, const int &op ){
	string dir;
	// get the moves of the current position
	cin >> dir;
	vector<int> moves;
	// transform the moves to int
	for ( int i = 0; i < (int)dir.size(); ++i ){
		switch (dir[i]){
			case '*' : t = u; break; 
			case 'N' : moves.push_back(0); break;
			case 'S' : moves.push_back(1); break;
			case 'E' : moves.push_back(2); break;
			case 'W' : moves.push_back(3); break;
		}
	}

	int idx, nx, ny, v;
	for ( int i = 0; i < moves.size(); ++i ){
		idx = moves[i];
		nx = x + dx[idx];
		ny = y + dy[idx];
		if ( maze[nx][ny] == -1 ){
			v = maze[nx][ny] = create_vertex();
			G[u].push_back(v);
			cout << direction( moves[i] ) << endl;
			fflush(NULL);
			dfs( nx, ny, maze[nx][ny], moves[i] );
		}
		else {
			v = maze[nx][ny];
			G[u].push_back(v);
		}
	}
	// backtracking to father
	if ( op >= 0 ){	// vertex is not root
		cout << direction( inv[op] ) << endl;
		cin >> dir; // read the string , this string is not used
	}
}

int bfs(){
	vector<int> d( N , -1 );
	d[0] = 0;
	queue<int> Q;
	Q.push(0);

	int u, v;
	while ( !Q.empty() ){
		u = Q.front();
		Q.pop();
		for ( int i = 0; i < (int)G[u].size(); ++i ){
			v = G[u][i];
			if ( d[v] == -1 ){
				d[v] = d[u] + 1;
				Q.push(v);
			}
		}
	}
	if ( t == -1 ) return -1;
	return d[t];
}

void process(){
	maze[101][101] = create_vertex();
	dfs( 101, 101, maze[101][101], -1 );
	cout << bfs() << endl;
	fflush(NULL);
}

void setup(){
	G = vector< vector<int> >();
	N = 0;
	for ( int i = 0; i < MAXD; ++i )
		fill( maze[i], maze[i] + MAXD, -1 );
	t = -1;
}

int main(){
	int runs;
	cin >> runs;
	while ( runs-- ){
		setup();
		process();
	}
	return 0;
}
