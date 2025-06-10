# insertion sort
# input: line-separated integers

{ A[NR] = $0 }

END{
	isort(A, NR)
	for (i = 1; i <= NR; i++)
		print A[i]
}

function isort(A, n,  i,j,t) {
	for (i = 2; i <= n; i++) {
		for (j = i; j > 1 && A[j] < A[j-1]; j--) {
			t = A[j]
			A[j] = A[j-1]
			A[j-1] = t
		}
	}
}
