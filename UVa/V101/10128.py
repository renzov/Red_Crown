def precalc():
	fact = [0] * 14
	global binom
	binom = []
	global dp
	dp = []
	
	for _ in range(14):
		binom.append( [0] * 14 )
		dp.append( [0] * 14 )
	
	# calculate factorials
	fact[0] = 1
	for i in range(1, 14):
		fact[i] = fact[i - 1] * i
	
	# calculate binomial coefficients
	binom[0][0] = 1
	for i in range( 1, 14 ):
		binom[i][0] = 1
		for j in range( 1, i ):
			binom[i][j] = binom[i - 1][j - 1] + binom[i - 1][j]
		binom[i][i] = 1
	
	# calculate the number of ways there are left peaks
	dp[0][0] = 1
	for i in range( 1, 14 ):
		for j in range( 1, i ):
			for k in range( 1, i + 1 ):
				dp[i][j] += ( dp[k - 1][j - 1] * binom[i - 1][k - 1] * fact[i  - k])
		dp[i][i] = 1



def main():
	precalc()
	T = int( input() )
	for _ in range(T):
		data = input().split()
		N = int( data[0] )
		P = int( data[1] )
		R = int( data[2] )
		ans = 0

		for i in range(1, N + 1):
			ans += dp[i - 1][P - 1] * dp[N - i][R - 1] * binom[N - 1][i - 1]
		
		print(ans)
		
main()
