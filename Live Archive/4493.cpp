#include<map>
#include<set>
#include<algorithm>
#include<cstdio>
using namespace std;
int main(){
  int P,C;
  int p;
  char c;
  int e;
  int runs = 0;
  while (scanf("%d %d",&P,&C) && (P||C)){
	 runs++;
	 printf("Case %d:\n",runs);
	 p = min(P,C);
	 set< pair<int,int> > S;
	 map<int,int> M;
	 for (int i=1; i <= p; ++i){
		S.insert( make_pair(i,i) );
		M[i] = i;
	 }
	 for (int i=p+1; i <= (p+C); ++i){
		scanf(" %c",&c);
		if ( c == 'N' ){
			 e = S.begin()->second;
			 printf("%d\n",e);
			 S.erase( S.begin() );
			 M[ e ] = i;
			 S.insert( make_pair( i , e ) );
		}
		else {
		  scanf("%d",&e);
		  if ( M.count(e) ){
				S.erase( S.find( make_pair( M[e] , e ) ) );
				S.insert( make_pair( -i , e ) );
				M[e] = -i;
		  }
		  else {
			 S.insert( make_pair(-i,e) );
			 M[e] = -i;
		  }
		}
	 }
  }

  return 0;
}