#include<cstdio>
#include<cstring>
#include<vector>
#include<queue>
#include<string>
#include<cstdlib>
#include<cctype>
#include<iostream>
using namespace std;

deque<int> ready;
queue<int> blocked;

struct inst {
	int type;
	int a;
	int b;
	inst(){}
	inst(int x,int y,int z){ type = x, a = y, b = z; }	
};

struct program {
	int pc;
	vector<inst> C;
};

const int ASG = 0;
const int PRT = 1;
const int LCK = 2;
const int UNL = 3;
const int END = 4;
int Time[7];
int n;
int t;
bool locked;
int var[30];
vector<program> P;

void print_inst( inst I ){
	cout << "Type = " << I.type << " a = " << I.a << " b = " << I.b << endl;
}

void print_Prog(int id){
	for ( int i=0; i < P[id].C.size(); ++i )
		print_inst( P[id].C[i] );
	cout<< endl;

}

bool read_inst( inst &I ){
	string s;
	getline( cin , s );
	if ( s == "end" ){   
		I.type = END; I.a = I.b = -1;
		return false; 
	}
	int pos = s.find('=');
	if ( pos != string::npos ){
		I.type = ASG;
		for ( int i=0; i < pos; ++i ){
			if ( isalpha(s[i]) ){
				I.a = s[i] - 'a'; 
				break;
			}
		}
		I.b = atoi( s.substr(pos+1).c_str() );
	}
	else if ( s == "unlock" ){
		I.type = UNL; I.a = -1; I.b = -1;
	}
	else if ( s == "lock" ){
		I.type = LCK; I.a = -1; I.b = -1;
	}
	else {
		int i = 0;
		I.type = PRT;
		while ( isspace(s[i]) ) i++;
		i += 5;
		while ( !isalpha(s[i]) ) i++;
		I.a = s[i] - 'a'; I.b = -1;
	}
	return true;
}

void read_program( int id ){
	inst i;
	while ( read_inst(i) ) P[id].C.push_back(i);
	P[id].C.push_back(i); 
	P[id].pc = 0;
}

bool exec_inst(int id, inst I ){ 
	if ( I.type == LCK ){
		if ( locked ) return false;
		else { locked = true; return true; }
	}
	if ( I.type == ASG ) var[ I.a ] = I.b;
	else if ( I.type == END ) return true;
	else if ( I.type == PRT ){ cout << id+1 << ": " << var[ I.a ] << endl; }
	else {
		locked = false;
		if ( !blocked.empty() ){
			ready.push_front( blocked.front() );
			blocked.pop();
		}
	}
	return true;
}

int execute( int id ){
	int tmp = t;
	int i;
	for ( i=P[id].pc; tmp > 0 && i < P[id].C.size(); ){
		if ( !exec_inst( id , P[id].C[i] ) ){
			P[id].pc = i;
			return 2;
		}
		tmp -= Time[ P[id].C[i].type ];
		i++;
	}
	if ( i >= P[id].C.size() ) return 0;
	P[id].pc = i;
	return 1;
}

void simulate(){
	for ( int i=0; i < n; ++i) ready.push_back(i);
	locked = false;
	int p,res;
	for ( int i=0; i < 26; ++i ) var[i] = 0;
	while ( !ready.empty() ){
		p = ready.front();
		ready.pop_front();
		res = execute(p);
		if ( res == 1 ){ //NOT FINISHED, NOT LOCKED
			ready.push_back(p);
		}
		else if ( res == 2 ){ //LOCKED
			blocked.push(p);
		}
	}
}

int main(){
	string s;
	cin >> n;
	P.resize(n);
	for ( int i=0; i < 5; ++i ) cin >> Time[i];
	cin >> t;
	getline(cin,s);
	for ( int i=0; i < n; ++i )
		read_program(i);
	//for ( int i=0; i < n; ++i ) print_Prog(i);
	simulate();
	return 0;
}
