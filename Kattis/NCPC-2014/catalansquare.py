def catalan(N:int) -> int:
	n = 2 * N
	res = 1

	for i in range(N + 1, n + 1):
		res *= i
	for i in range(2, N + 2):
		res //= i

	return res


def main():
	# main obs: S_N = C_{N + 1}, and we use the binomial definition of Catalan number to make it O(N) big nums

	N = int( input() )
	if N == 0:
		print(1)
	else:
		print(catalan(N + 1))
	


main()
