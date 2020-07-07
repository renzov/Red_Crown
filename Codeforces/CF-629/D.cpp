#include<cstdio>
#include<vector>
using namespace std;
const int MAXN = 200005;
vector<int> pos[MAXN];
int A[MAXN];
int res[MAXN];

void process(){
	int N;

	scanf("%d", &N);
	int lastColor = -1;
	int size = 0;
	int L = 0;
	for ( int i=1; i <= N; ++i ){ 
		scanf("%d", A + i);
		if ( A[i] == lastColor ){
			pos[size - 1].push_back(i);
		}
		else {
			size++;
			pos[size - 1].push_back(i);
		}
		lastColor = A[i];
	}
	if ( A[N] == A[1] && size > 1 ){	
		for ( int i=0; i < (int)pos[0].size(); ++i )
			pos[size - 1].push_back( pos[0][i] );
		L++;
	}

	int start = -1;

	for ( int i=L; start < 0 && i < size; ++i ){
		if ( (int)pos[i].size() > 1 ){
			start = i;
		}
	}

	int idx;
	int S = size - L;
	if ( S == 1 ){
		puts("1");
		for ( int i=1; i <= N; ++i )
			res[i] = 0;
	}
	else if ( !(S & 1) ){
		puts("2");
		lastColor = 0;
		for ( int i=L; i < size; ++i ){
			for ( int j=0; j < pos[i].size(); ++j ){
				idx = pos[i][j];
				res[idx] = lastColor;
			}
			lastColor ^= 1;
		}
	}
	else {
		if ( start == -1 ){
			puts("3");
			res[1] = 2;
			lastColor = 0;
			for ( int i=2; i <= N; ++i ){
				res[i] = lastColor;
				lastColor ^= 1;
			}
		}
		else {
			puts("2");
			for ( int j=0; j < (int)pos[start].size(); ++j ){
				idx = pos[start][j];
				res[idx] = 0;
			}
			res[idx] = 1; // the last to 1
			lastColor = 0;
			for ( int i=start+1; i < size; ++i ){
				for ( int j=0; j < (int)pos[i].size(); ++j ){
					idx = pos[i][j];
					res[idx] = lastColor;
				}
				lastColor ^= 1;
			}
			for ( int i=L; i < start; ++i ){
				for ( int j=0; j < (int)pos[i].size(); ++j ){
					idx = pos[i][j];
					res[idx] = lastColor;
				}
				lastColor ^= 1;
			}
		}
	}
	for ( int i=1; i <= N; ++i ){
		if (i > 1) putchar(' ');
		printf("%d", res[i] + 1);
	}
	puts("");

	for ( int i=0; i < size; ++i )
		pos[i].clear();
}

int main(){

	int runs;
	scanf("%d", &runs);
	while ( runs-- ) process();
	return 0;
}
