n = 9500
f = 1
x = 0

while n!=0:
	f = f*n
	x = x + f
	n = n-1
	
a = x
b = f

t = int(a/b)
x = str(t) + '.'

n = 34000

while n!=0:
	n = n-1

	a = (a-b*t)*10

	t = int(a/b)
	x = x+str(t)

print x