#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

string BUY("BUY");
string SELL("SELL");
string CANCEL("CANCEL");

struct Order {
	int i;
	int q;
	int p;
};

typedef map<int,Order*> mio;
typedef pair<int,mio*> pmio;

map <int,pmio,greater<int> > buy;
map <int,pmio,less<int> > sell;

ifstream in("exchange.in");
ofstream out("exchange.out");

template <class PR> void cancel(Order& o, map<int,pmio,PR>& m) {
	if (o.q == 0 || m.find(o.p) == m.end())
		return;
	//out << "CANCELED " << o.q << endl;
	pmio& mm = m[o.p];
	mm.first -= o.q;
	mm.second->erase(o.i);
	o.q = 0;
	if (mm.second->empty()) {
		delete mm.second;
		m.erase(o.p);
	}
}

template <class MY, class OTHER> void trade(
	Order& o, 
	map <int,pmio,MY>& my,
	map <int,pmio,OTHER>& other) 
{
	while (o.q > 0) {
		map<int,pmio,OTHER>::iterator obegin = other.begin();
		if (obegin == other.end())
			break;
		pair<int,pmio> best = *obegin;
		int p = best.first;
		OTHER cmp;
		if (cmp(o.p, p))
			break;
		pmio& mm = other[p];
		Order& head = *(mm.second->begin()->second);
		int q = min(o.q, head.q);
		out << "TRADE " << q << " " << p << endl;
		o.q -= q;
		head.q -= q;
		mm.first -= q;
		if (head.q == 0) {
			mm.second->erase(head.i);
			//out << "DONE " << head.i << endl;
		}
		if (mm.second->empty()) {
			delete mm.second;
			other.erase(p);
			//out << "DONE @ " << p << endl;
                }
	}
	if (o.q > 0) {
		pmio& mm = my[o.p];
		mm.first += o.q;
		if (!mm.second)
			mm.second = new mio;
		(*mm.second)[o.i] = &o;
	}
}                                                                        

template <class PR> void qitem(map<int,pmio,PR>& m, int def) {
	int q = 0;
	int p = def;
	map<int,pmio,PR>::iterator begin = m.begin();
	if (begin != m.end()) {
	        pair<int,pmio> best = *begin;
	        p = best.first;
	        q = best.second.first;

	}
	out << " " << q << " " << p;
}

void quote() {
	out << "QUOTE";
	qitem(buy, 0);
	out << " -";
	qitem(sell, 99999);
	out << endl;
}

int main() {
	int n;
	in >> n;
	Order* o = new Order[n];
	for (int i = 0; i < n; i++) {
		string s;
		in >> s;
		if (s == BUY || s == SELL) {
			int q;
			int p;
			in >> q >> p;
			o[i].i = i;
			o[i].q = q;
			o[i].p = p;	
			if (s == BUY)
				trade(o[i], buy, sell);
			else
				trade(o[i], sell, buy);
		} else if (s == CANCEL) {
		        int j;
		        in >> j;
		        cancel(o[j - 1], buy);
		        cancel(o[j - 1], sell);
		}
		quote();
	}
	return 0;
}