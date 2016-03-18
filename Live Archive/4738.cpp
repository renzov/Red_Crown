#include<cstdio>
#include<algorithm>
#include<cctype>

using namespace std;
typedef pair<double,double> point;
const int MAXN = 1005;
const double PI = 3.141;

point A,B;
double T;
double DA[MAXN];
double DB[MAXN];
int N;
point P[MAXN];
bool type;
int ordA[MAXN];
int ordB[MAXN];

double Dist(const point &p1, const point &p2){
	return 	(p1.first - p2.first)*(p1.first - p2.first) + 
			(p1.second - p2.second)*(p1.second - p2.second);
}

bool comp( const int &i, const int &j ){
	if ( type ){
		return DB[i] < DB[j];
	}
	else {
		return DA[i] < DA[j];
	}
}

int simulate( int o1[], int o2[], double d1[], double d2[] ){
	int cover[MAXN];
	int act = 0, res = 0;
	fill( cover , cover + N, 0 );
	int i = 0;
	int j = 0;	
	double gap;

	while ( i < N && (PI * d1[ o1[i] ] <= T)  ){ 
		cover[ o1[i] ]++; act++;
		i++;
	}
	gap = (i)? d1[ o1[i-1] ]:0;
	while ( j < N && (PI * (d2[ o2[j] ] + gap) <= T) ){ 
		if ( !cover[ o2[j] ] ) act++;
		cover[ o2[j] ]++;
		j++;
	}
	res = act;
	while ( i >= 1 ){
		i--;
		gap = (i > 0)? d1[ o1[i-1] ]:0;
		cover[ o1[i] ]--;
		if ( !cover[ o1[i] ] ) act--;
		while ( j < N && PI * (d2[ o2[j] ] + gap) <= T ){
			if ( !cover[ o2[j] ] ) act++;			
			cover[ o2[ j ] ]++;
			j++;
		}
		res = max( res , act );
	}
	return res;
}

int main(){
	int res, cases = 0;
	while ( scanf("%d", &N) && N ){
		cases++;
		scanf("%lf %lf %lf %lf %lf", &A.first, &A.second, &B.first, &B.second, &T);
		for ( int i=0; i < N; ++i ){
			ordA[i] = ordB[i] = i;
			scanf("%lf %lf", &P[i].first, &P[i].second);
			DA[ i ] = Dist( A , P[ i ] );
			DB[ i ] = Dist( B , P[ i ] );		
		}
		type = false;
		sort( ordA , ordA + N, comp );
		type = true;
		sort( ordB , ordB + N, comp );
		res = simulate( ordA , ordB , DA , DB );
		res = max( res , simulate(ordB, ordA, DB, DA) );
		printf("%d. %d\n", cases, N - res);
	}
	return 0;
}
