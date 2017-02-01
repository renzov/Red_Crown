#include<iostream>
#include<algorithm>
using namespace std;

char getGrade(int s,bool up){
  if ( s >= 90 ) return 'A';
  if ( s >= 80 ) return 'B';
  if ( s >= 70 ) return 'C';
  if ( s >= 60 ) return 'D';
  return 'F';
}

int main(){

  int runs;
  int t2,t1,f,a;
  int ct1,ct2,ct3;
  int sum;
  bool up;

  cin >> runs;
  for (int k=1; k <= runs; ++k){
		cin >>  t1 >> t2 >> f >> a >> ct1 >> ct2 >> ct3;
		sum = t1 + t2 + f + a;
		if (ct2 > ct1) swap(ct1,ct2);
		if (ct3 > ct1) swap(ct1,ct3);
		if (ct3 > ct2) swap(ct2,ct3);
		sum += ((ct1 + ct2)/2);
		up = ((ct1 + ct2) % 2) == 1;
		cout << "Case " << k << ": " << getGrade(sum,up) << endl;
  }
  return 0;
}