#include<cstdio>
#include<climits>
#include<vector>
#include<algorithm>
using namespace std;
const int MAXN = 2048;
typedef pair<int,int> pii;
typedef pair< pii, pii > cut;
typedef pair< pii, pii > event;

int N;
vector<event> Ex, Ey;

vector<cut> merge( const cut &c, const vector<cut> &A, const vector<cut> &B ){
	vector<cut> res (1, c);
	int i=0, j = 0;
	while ( i < A.size() && j < B.size() ){
		if ( A[i] < B[j] ){
			res.push_back( A[i] ); i++;
		}
		else {
			res.push_back( B[j] ); j++;
		}
	}
	while ( i < A.size() ){ res.push_back( A[i] ); i++; }
	while ( j < B.size() ){ res.push_back( B[j] ); j++; }
	return res;
}

vector<cut> partition( const int &Xmin, const int &Xmax, const int &Ymin, const int &Ymax ){
	int open;
	int x, y, x1, x2, y1, y2, type;
	event e;
	open = 0;
	for ( int i=0; i < Ey.size(); ++i ){
		e = Ey[i];
		y = e.first.first, type = e.first.second;
		x1 = e.second.first, x2 = e.second.second;
		if ( type == 1 && ( y < Ymin || Ymax <= y ) ) continue;
		if ( type == 0 && ( y <= Ymin || Ymax < y ) ) continue;
		if ( Xmin <= x1 && x2 <= Xmax ){
			if ( type ) open++;
			else open--;
			if ( !open && y < Ymax ){ // cut found
				return merge( 	cut( pii(Xmin, y), pii(Xmax, y) ), 
								partition(Xmin, Xmax, Ymin, y), 
								partition(Xmin, Xmax, y, Ymax) 
							);
			}
		}
	}

	open = 0;
	for ( int i=0; i < Ex.size(); ++i ){
		e = Ex[i];
		x = e.first.first, type = e.first.second;
		y1 = e.second.first, y2 = e.second.second;
		if ( type == 1 && ( x < Xmin || Xmax <= x ) ) continue;
		if ( type == 0 && ( x <= Xmin || Xmax < x ) ) continue;
		if ( Ymin <= y1 && y2 <= Ymax ){
			if ( type ) open++;
			else open--;
			if ( !open && x < Xmax ){
				return merge(	cut( pii(x, Ymin), pii(x, Ymax) ), 
								partition( Xmin, x, Ymin, Ymax ), 
								partition( x, Xmax, Ymin, Ymax ) 
							);
			}
		}
	}
	return vector<cut>();
}

void process(){
	int Xmin = INT_MAX;
	int Xmax = INT_MIN;
	int Ymin = INT_MAX;
	int Ymax = INT_MIN;
	int x1, x2, y1, y2;

	Ex.clear(), Ey.clear();

	for ( int i=0; i < N; ++i ){
		scanf("%d %d %d %d", &x1, &y1, &x2, &y2);
		Xmin = min( Xmin, x1 );
		Xmax = max( Xmax, x2 );
		Ymin = min( Ymin, y1 );
		Ymax = max( Ymax, y2 );
		Ex.push_back( event( pii(x1, 1), pii(y1, y2) ) );
		Ex.push_back( event( pii(x2, 0), pii(y1, y2) ) );
		Ey.push_back( event( pii(y1, 1), pii(x1, x2) ) );
		Ey.push_back( event( pii(y2, 0), pii(x1, x2) ) );
	}
	
	sort( Ex.begin(), Ex.end() );
	sort( Ey.begin(), Ey.end() );
	vector<cut> res = partition( Xmin, Xmax, Ymin, Ymax );
	// print the answer
	cut c;
	for ( int i=0; i < res.size(); ++i ){
		c = res[i];
		printf("%d %d %d %d\n", c.first.first, c.first.second, c.second.first, c.second.second);
	}
	puts("");
}

int main(){
	while ( scanf("%d", &N) && N )
		process();
	return 0;
}
