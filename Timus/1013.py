N = int( input() )
K = int( input() )
M = int( input() )

def mat_mul( A:[[int]], B:[[int]], C:[[int]] ):
	for i in range(2):
		for j in range(2):
			C[i][j] = 0
			for k in range(2):
				C[i][j] += (A[i][k] * B[k][j])
				C[i][j] %= M

def fast_exp(  mat:[[int]], n:int, R:[[int]] ):
	if n == 1:
		for i in range(2):
			for j in range(2):
				R[i][j] = mat[i][j]
	elif n % 2 == 0:
		tmp = [[0,0], [0,0]]
		fast_exp( mat, n // 2, tmp )
		mat_mul( tmp, tmp, R )
	else:
		tmp = [[0,0], [0,0]]
		fast_exp( mat, n - 1, tmp )	
		mat_mul( mat, tmp, R )
		

# f(n) = (k - 1)*f(n - 1) + (k - 1)*f(n - 2), n >= 2
# f(0) = 1
# f(1) = k - 1

g0 = 1 % M
g1 = (K - 1) % M
if N == 1:
	print( g1 )
else:
	mat = [[K - 1, K - 1], [1, 0]]
	res = [[0,0], [0,0]]
	fast_exp(mat, N - 1, res)
	print((g1 * res[0][0] + g0 * res[0][1]) % M )

