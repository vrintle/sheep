'''

BEGINNER'S CHEATSHEET
---------------------

#oneliners

arr.sort()
arr.append()
shuffle(arr)
len(arr)
st = set()
st.add(1)
x in st
chr(65) # 'A'
ord('A') # 65

#multiliners

import sys
with open("testcases/graph_0.txt", "w") as F:
    sys.stdout = F

'''

from random import randint, shuffle
T = 10
N = 10
A = 100
print(T)
for _ in range(T):
	n = randint(1, N)
	print(n)
	arr = []
	for i in range(n):
		arr.append(randint(1, A))
	for i in range(n - 1):
		print(arr[i], end=' ')
	print(arr[n - 1])
