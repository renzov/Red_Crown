#include<cstdio>
#include<algorithm>
#include<set>
using namespace std;

set<int> angles;

int main(){

	/* Simulate the clock for half a day and 
		and take all the angles	
	*/
	int hour = 0;
	int minu = 0;
	int ang, nxtM;
	angles.insert( 0 );
	for ( int i=0; i < 360; ++i ){
		
		nxtM = (minu + 1) % 60;
		if ( nxtM % 12 == 0 )
			hour = (hour + 1) % 60;

		minu = nxtM;
		if ( minu > hour )
			ang = 6 * min( minu - hour, 60 + hour - minu ); 
		else 
			ang = 6 * min( hour - minu, 60 + minu - hour );
		
		angles.insert( ang );
	}

	/* Process the testcases */

	while ( scanf("%d", &ang) != EOF ){
		if ( angles.find( ang ) != angles.end() ) puts("Y");
		else puts("N");
	}
	
	return 0;
}

