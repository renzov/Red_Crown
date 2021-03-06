#include<bits/stdc++.h>
using namespace std;

class MagicSubset {
  public:
  int findBest(vector <int> values) {
		int pos = 0;
		int neg = 0;
		for ( int i=1; i < (int)values.size(); ++i ){
			if ( values[i] > 0 ) pos += values[i];
			else if ( values[i] < 0 ) neg += values[i];
		}
		return max( 0, max( pos, max( -neg - values[0] , -pos - values[0] )  )  );
  }
};
// BEGIN CUT HERE
#include <cstdio>
#include <ctime>
#include <iostream>
#include <string>
#include <vector>
namespace moj_harness {
	using std::string;
	using std::vector;
	int run_test_case(int);
	void run_test(int casenum = -1, bool quiet = false) {
		if (casenum != -1) {
			if (run_test_case(casenum) == -1 && !quiet) {
				std::cerr << "Illegal input! Test case " << casenum << " does not exist." << std::endl;
			}
			return;
		}
		
		int correct = 0, total = 0;
		for (int i=0;; ++i) {
			int x = run_test_case(i);
			if (x == -1) {
				if (i >= 100) break;
				continue;
			}
			correct += x;
			++total;
		}
		
		if (total == 0) {
			std::cerr << "No test cases run." << std::endl;
		} else if (correct < total) {
			std::cerr << "Some cases FAILED (passed " << correct << " of " << total << ")." << std::endl;
		} else {
			std::cerr << "All " << total << " tests passed!" << std::endl;
		}
	}
	
	int verify_case(int casenum, const int &expected, const int &received, std::clock_t elapsed) { 
		std::cerr << "Example " << casenum << "... "; 
		
		string verdict;
		vector<string> info;
		char buf[100];
		
		if (elapsed > CLOCKS_PER_SEC / 200) {
			std::sprintf(buf, "time %.2fs", elapsed * (1.0/CLOCKS_PER_SEC));
			info.push_back(buf);
		}
		
		if (expected == received) {
			verdict = "PASSED";
		} else {
			verdict = "FAILED";
		}
		
		std::cerr << verdict;
		if (!info.empty()) {
			std::cerr << " (";
			for (size_t i=0; i<info.size(); ++i) {
				if (i > 0) std::cerr << ", ";
				std::cerr << info[i];
			}
			std::cerr << ")";
		}
		std::cerr << std::endl;
		
		if (verdict == "FAILED") {
			std::cerr << "    Expected: " << expected << std::endl; 
			std::cerr << "    Received: " << received << std::endl; 
		}
		
		return verdict == "PASSED";
	}

	int run_test_case(int casenum__) {
		switch (casenum__) {
		case 0: {
			int values[]              = {1,10,4,-6,3};
			int expected__            = 17;

			std::clock_t start__      = std::clock();
			int received__            = MagicSubset().findBest(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int values[]              = {3,-5,1,-6};
			int expected__            = 8;

			std::clock_t start__      = std::clock();
			int received__            = MagicSubset().findBest(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int values[]              = {0,0,0,0,0,0,0,0,0};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = MagicSubset().findBest(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int values[]              = {-100};
			int expected__            = 100;

			std::clock_t start__      = std::clock();
			int received__            = MagicSubset().findBest(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int values[]              = {100};
			int expected__            = 0;

			std::clock_t start__      = std::clock();
			int received__            = MagicSubset().findBest(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int values[]              = {-3,1,-4,1,5,-9,2,6,-5,3,5};
			int expected__            = 23;

			std::clock_t start__      = std::clock();
			int received__            = MagicSubset().findBest(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int values[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MagicSubset().findBest(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int values[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MagicSubset().findBest(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int values[]              = ;
			int expected__            = ;

			std::clock_t start__      = std::clock();
			int received__            = MagicSubset().findBest(vector <int>(values, values + (sizeof values / sizeof values[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
		default:
			return -1;
		}
	}
}

#include <cstdlib>
int main(int argc, char *argv[]) {
	if (argc == 1) {
		moj_harness::run_test();
	} else {
		for (int i=1; i<argc; ++i)
			moj_harness::run_test(std::atoi(argv[i]));
	}
}
// END CUT HERE
