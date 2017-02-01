#include<cstdio>
const int ALL = (1<<7) - 1;
int seq[15];
int rep[15]={63,6,91,79,102,109,125,7,127,111};
int n;

bool match( int number, int mask, int burn ){
	if ( burn & mask ) return false; //No burn led should be present
	int tmp = ~number & ALL; 	 //Get bit thar should NOT be present
	if ( tmp & mask ) return false;	 //MisMatch
	tmp = number & (~burn & ALL); 
	if ( (tmp & mask) != mask ) return false;
	return true;
}

int get_binary(char *s){
	int res = 0;
	for ( int i=0; i < 7; ++i ){
		if ( s[i] == 'Y' ) res |= ( 1 << i );
	}
	return res;
}

bool process( int begin ){
	//printf("Begin process : %d\n",begin);
	int burn = 0;
	int mask;
	for ( int i=0; i < n; ++i,--begin){
		if ( !match( rep[begin] , seq[i] , burn ) ) return false;
		// get the new burn seqments
		mask = ~seq[i] & ALL;   //Get the bits that are not present
		mask &= rep[begin];	//Get the bits that should be present
		burn |= mask;
		//printf("seq = %X - After match con %d -> burn = %X\n",seq[i],begin,burn);
	}
	return true;
}

int main(){
	char led[10];
	while ( scanf("%d",&n) && n ){
		for ( int i=0; i < n; ++i ){
			scanf("%s",led);
			seq[i] = get_binary(led);
		}
		//Trial and error
		bool found = false;
		for ( int i=9; i >= (n-1) && !found ; i-- ){
			if ( process( i ) ){ 
				found = true;
				//printf("found i = %d\n",i);
			}
		}
		if (found) puts("MATCH");
		else puts("MISMATCH");
	}
	return 0;
}
