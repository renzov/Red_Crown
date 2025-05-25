# dp[i][iszero] = number o valid numbers with i digits such that the last digit contains a zero or not
# the problem does not make it implicit but the most significant digit has to be different from zero

def main():
	N = int( input() )
	K = int( input() )

	dp = [ [0, 0], [0, 0] ]

	last = 0
	act = 1

	dp[last][0] = K - 1
	dp[last][1] = 0

	for i in range(1, N):
		dp[act][0] = (K - 1) * ( dp[last][0] + dp[last][1] )
		dp[act][1] = dp[last][0]
		act, last = last, act

	print( dp[last][0] + dp[last][1] )

main()
