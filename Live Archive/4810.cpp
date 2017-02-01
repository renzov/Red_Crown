#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#include <bits/stdc++.h>
 
using namespace __gnu_pbds;
using namespace std;
 
typedef
tree<
  pair<int,int>,
  null_type,
  less<pair<int,int> >,
  rb_tree_tag,
  tree_order_statistics_node_update>
ordered_set;

int main(){
	ordered_set S;
	string word, line;
	while (1){
		getline(cin,line);
		if (line[0] == '*') break;
		stringstream in(line);
		bool ok = true;
		in >> word;
		char first = toupper( word[0] );
		while ( in >> word && ok ){
			ok &= (toupper(word[0]) == first);
		}
		if (ok) cout << "Y\n";
		else cout << "N\n";
	}
	return 0;
}
