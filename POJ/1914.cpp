#include<cstdio>
#include<cmath>
#include<cstring>
#include<cstdlib>

long long det( long long M[3][3] ){
	return M[0][0]*( M[1][1]*M[2][2] - M[1][2]*M[2][1] ) - M[0][1]*( M[1][0]*M[2][2] - M[1][2]*M[2][0] ) + M[0][2]*( M[1][0]*M[2][1] - M[1][1]*M[2][0] );
}

double roundd( double num ){
	if ( fabs(num) < 0.0005 ) return 0.0;
	return num;
} 

int main(){
	long long a[3][3];
	long long b[3];
	long long t[3][3];
	long long A1,A2,A3,A;
	double r1,r2,r3;
	int runs;
	scanf("%d",&runs);
	while ( runs-- ){
		for ( int i=0; i < 3; ++i )
			scanf("%lld %lld %lld %lld",&a[i][0],&a[i][1],&a[i][2],&b[i]);
		A = det(a);   memcpy( t , a , sizeof(a) ); for ( int j=0; j < 3; ++j ) t[j][0] = b[j];
		A1 = det(t);  memcpy( t , a , sizeof(a) ); for ( int j=0; j < 3; ++j ) t[j][1] = b[j];
		A2 = det(t);  memcpy( t , a , sizeof(a) ); for ( int j=0; j < 3; ++j ) t[j][2] = b[j];
		A3 = det(t);
		printf("%lld %lld %lld %lld\n",A1,A2,A3,A);
		if ( !A ) puts("No unique solution");
		else {
			r1 = roundd( (double)A1 / A );
			r2 = roundd( (double)A2 / A );
			r3 = roundd( (double)A3 / A );
			printf("Unique solution: %0.3lf %0.3lf %0.3lf\n",r1,r2,r3);	
		}
		puts("");
	}

	return 0;
}
