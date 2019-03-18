#include<bits/stdc++.h>
using namespace std;

class MinMaxMax {
  public:
  long long findMin(vector <int> a, vector <int> b, vector <int> w, vector <int> v) {
      
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
	
	int verify_case(int casenum, const long long &expected, const long long &received, std::clock_t elapsed) { 
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
			int a[]                   = {0};
			int b[]                   = {1};
			int w[]                   = {5};
			int v[]                   = {3,6};
			long long expected__      = 30;

			std::clock_t start__      = std::clock();
			long long received__      = MinMaxMax().findMin(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(w, w + (sizeof w / sizeof w[0])), vector <int>(v, v + (sizeof v / sizeof v[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 1: {
			int a[]                   = {0,0,1};
			int b[]                   = {1,2,2};
			int w[]                   = {10,11,12};
			int v[]                   = {6,5,4};
			long long expected__      = 186;

			std::clock_t start__      = std::clock();
			long long received__      = MinMaxMax().findMin(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(w, w + (sizeof w / sizeof w[0])), vector <int>(v, v + (sizeof v / sizeof v[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 2: {
			int a[]                   = {0,0,1};
			int b[]                   = {1,2,2};
			int w[]                   = {100,1,1};
			int v[]                   = {1,1,100};
			long long expected__      = 300;

			std::clock_t start__      = std::clock();
			long long received__      = MinMaxMax().findMin(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(w, w + (sizeof w / sizeof w[0])), vector <int>(v, v + (sizeof v / sizeof v[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 3: {
			int a[]                   = {0,1,2,3,4,5,6,7,8,9};
			int b[]                   = {1,2,3,4,5,6,7,8,9,10};
			int w[]                   = {1000000,1,1000000,1,1000000,1,1000000,1,1000000,1};
			int v[]                   = {1000000,1,1000000,1,1000000,1,1000000,1,1000000,1,1000000};
			long long expected__      = 50000005000000LL;

			std::clock_t start__      = std::clock();
			long long received__      = MinMaxMax().findMin(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(w, w + (sizeof w / sizeof w[0])), vector <int>(v, v + (sizeof v / sizeof v[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 4: {
			int a[]                   = {9,12,4,11,0,8,6,11,11,10,12,7,3,12,3,10,0,3,2,7, 0,10,8,1,11,9,2,0,3,6,4,2,3,5,9,0,6};
			int b[]                   = {0,5,6,5,10,2,1,2,3,4,6,9,9,10,5,5,6,4,12,5,12,7, 7,3,4,12,4,1,8,7,1,6,6,4,11,5,11};
			int w[]                   = {879651,656980,11,51564,206,420,917584,205,59290,3323, 644,1,13243,84162,154,561242,1,190,10,136901,420623, 353,573129,81,25,133670,72,528049,5,715560,82641,46, 1,527672,923948,1,13};
			int v[]                   = {5,1829,51302,3026,4,14,5189,3,25289,2,2967,15994,6};
			long long expected__      = 157740289;

			std::clock_t start__      = std::clock();
			long long received__      = MinMaxMax().findMin(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(w, w + (sizeof w / sizeof w[0])), vector <int>(v, v + (sizeof v / sizeof v[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}
		case 5: {
			int a[]                   = {4,16,0,10,11,21,11,21,20,6,13,10,10,3,20,15,16,9,6,14,13,8, 17,9,2,21,3,4,10,13,5,7,13,1,12,1,3,13,5,21,12,0,19,15,6,0, 5,13,1,8};
			int b[]                   = {17,1,8,2,1,7,6,12,18,21,7,20,18,7,6,7,17,20,15,10,14,16,2,6, 19,3,19,3,6,18,10,11,10,4,17,13,15,9,15,17,11,16,13,1,19,17, 19,17,10,2};
			int w[]                   = {327583,4194,990205,481090,868602,722789,547481,738569,188373, 973550,462208,74066,639614,693164,86808,442101,811939,995334, 551737,335601,147231,93330,799032,130164,839277,757103,234057, 909252,415269,945015,715797,549525,581349,130104,493780,553519, 755216,626951,743631,231151,205857,917585,553454,352015,873807, 573520,569698,317228,754891,875856};
			int v[]                   = {220468,844712,599675,53333,825995,711279,289092,415428,805292, 985205,197039,193974,95433,244829,558762,555423,725065,498922, 519543,4803,305565,61949};
			long long expected__      = 64390854062526LL;

			std::clock_t start__      = std::clock();
			long long received__      = MinMaxMax().findMin(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(w, w + (sizeof w / sizeof w[0])), vector <int>(v, v + (sizeof v / sizeof v[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}

		// custom cases

/*      case 6: {
			int a[]                   = ;
			int b[]                   = ;
			int w[]                   = ;
			int v[]                   = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = MinMaxMax().findMin(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(w, w + (sizeof w / sizeof w[0])), vector <int>(v, v + (sizeof v / sizeof v[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 7: {
			int a[]                   = ;
			int b[]                   = ;
			int w[]                   = ;
			int v[]                   = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = MinMaxMax().findMin(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(w, w + (sizeof w / sizeof w[0])), vector <int>(v, v + (sizeof v / sizeof v[0])));
			return verify_case(casenum__, expected__, received__, clock()-start__);
		}*/
/*      case 8: {
			int a[]                   = ;
			int b[]                   = ;
			int w[]                   = ;
			int v[]                   = ;
			long long expected__      = ;

			std::clock_t start__      = std::clock();
			long long received__      = MinMaxMax().findMin(vector <int>(a, a + (sizeof a / sizeof a[0])), vector <int>(b, b + (sizeof b / sizeof b[0])), vector <int>(w, w + (sizeof w / sizeof w[0])), vector <int>(v, v + (sizeof v / sizeof v[0])));
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
