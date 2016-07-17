tam = [1,1,2,2]
last = 2
for i in range(16):
	last = last * 3
	tam.append(last)
	last = last * 2
	tam.append(last)
	last = last * 2
	tam.append(last)
	tam.append(last)

print sum(tam)
print tam

