
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int getPR(int* A,int elements, int startPos,int direction)
{
	//-1 for P, 1 for R
	bool notLess = true;
	int PRVal = startPos + direction;
	for (int c = startPos;(c > 1) && (c < elements-1) && notLess;c+=direction)
	{
		if (A[c + direction] > A[c])
			PRVal = c + direction;
		else
			notLess = !notLess;
	}
	return PRVal;
}

int calcPit(int* A,int elements)
{
	//calc deepest pit in input array

	if (elements < 2)  //too few to calculate so bail out
		return -1;

	//first identify pit centres and calc the depth
	//  could identify peaks too but problem definition uses < and > not >= ,<=
	// this ignores the subsequences as they cannot be larger than a full sequence
	int deepestPit = -1;
	for (int c = 1;c < elements;++c)
	{
		if ((A[c - 1] > A[c]) && (A[c] < A[c + 1]))
		{
			int P = getPR(A,elements, c, -1);
			int R = getPR(A, elements, c, 1);
			//as the differences could wrap use 64 bits
			__int64 PQ = (__int64)A[P] - (__int64)A[c];
			__int64 RQ = (__int64)A[R] - (__int64)A[c];
			int depth = MIN(PQ, RQ);
			if (depth > deepestPit)
				deepestPit = depth;
		}
	}
	return deepestPit;
}

