t = int(raw_input())

while t!=0:
	t-=1;

	n = int(raw_input())
	ndig = len(str(n))

	a = n/(10**((ndig+1)/2))
	c = n%(10**(ndig/2))

	ar = int(str(a)[::-1])

	if c>=ar:
		if ndig%2==0:
			a+=1
			ar = int(str(a)[::-1])
			next = a*(10**(ndig/2))+ar
		else:
			b = n%(10**((ndig+1)/2))/(10**(ndig/2))
			if b==9:
				b=0
				a+=1
				ar = int(str(a)[::-1])
			else:
				b+=1
			next = a*(10**((ndig+1)/2))+b*(10**(ndig/2))+ar
	else:
		if ndig%2==0:
			next = a*(10**(ndig/2))+ar
		else:
			b = n%(10**((ndig+1)/2))/(10**(ndig/2))
			next = a*(10**((ndig+1)/2))+b*(10**(ndig/2))+ar
	print next
