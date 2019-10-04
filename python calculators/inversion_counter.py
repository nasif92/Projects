
# putting this inside a function

#ask user for input while not 0
def inversion():
	condition = True
	alist = []
	num = 0
	while condition:
		num = int(input("Press maze value: "))
		if num == 0: 
			condition = False
		else:
			alist.append(num)

	sum = 0
	inv = 0
	for i in alist:
		if (i != alist[len(alist)-1]):
			j = alist.index(i) + 1
			for k in alist[j:]:
				if k < i:
					inv += 1
		sum += i
	print("Sum of the numbers: " + str(sum), "\nInversions: " + str(inv))

def main():
	string = "Put the numbers of the sliding tile puzzle: "
	print(string)
	inversion()
main()