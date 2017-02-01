#include<cstdio>
#include<list>
#include<vector>
#include<algorithm>
using namespace std;

const int MAXN = (1 << 10); 
char M[MAXN + 5][MAXN + 5];
bool E[MAXN + 5];
bool used[ MAXN ];
int main(){
	int N;

	while ( scanf("%d", &N) != EOF ){
		for ( int i=0; i < N; ++i ){ 
			scanf("%s", M[i]);	
			E[i] = false;
		}
		list<int> W;
		list<int> L;
		
		for ( int i=1; i < N; ++i )
			if ( M[0][i] == '1' ) W.push_back( i );
			else L.push_back(i);
		
		bool ok, first;
		while ( N > 1 ){	
			vector<int> rem; //list of remaining players after greedy matching

			for ( list<int>::iterator i=W.begin(); i != W.end(); ++i ) used[*i] = false;			

			for ( list<int>::iterator i=L.begin(); i != L.end(); ++i ){
				ok = false;
				for ( list<int>::iterator j=W.begin(); j != W.end(); ++j ){
					if ( !used[*j] && M[*j][*i] == '1' ){
						printf("%d %d\n", *i + 1, *j + 1);
						E[ *i ] = used[ *j ] = true;
						ok = true;
						break;
					}
				}
				if ( !ok ){
					rem.push_back( *i );
				}
			}
			first = true;
			for ( list<int>::iterator i=W.begin(); i != W.end(); ++i ) 
				if ( !used[ *i ] ){ 
					if ( !first ) { 
						rem.push_back( *i );
					}
					else {
						printf("%d %d\n", 1, *i + 1);
						E[ *i ] = true;
						first = false;
					}
				}
			
			for ( int i=0, x,y; (i+1) < (int)rem.size(); i+= 2 ){
				x = rem[i], y = rem[i+1];
				printf("%d %d\n", x+1, y+1);
				if ( M[x][y] == '1' ){
					E[y] = true;
				}
				else {
					E[x] = true;
				}
			}
			// Erasing Elimanated players
			for ( list<int>::iterator i=W.begin(); i != W.end(); ){
				if ( E[ *i ] ){
					i = W.erase(i);
				}
				else {
					i++;
				}
			}			
			for ( list<int>::iterator i=L.begin(); i != L.end(); ){
				if ( E[ *i ] ){
					i = L.erase(i);
				}
				else {
					i++;
				}
			}
			N >>= 1;
		}
	}
	return 0;
}
