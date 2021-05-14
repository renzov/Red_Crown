/*
    Solution for NEERC'2010 Problem X: Xtrapolation
    (C) Roman Elizarov
*/

#include <stdio.h>

void main() {
	long long sum = 0;
	while (1) {
		int num;
		scanf("%d", &num);
		if (num == 0)
			break;
		sum += num;
		printf("%lld\n", sum);
		fflush(stdout);
	}
}
