#include "lss_46_02.h"

void print(double *A, double *B, int n)
{
	int i, j;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			printf("%lf ", A[i*n + j]);
		}
		printf(" = %lf", B[i]);
		printf("\n");
	}
	printf("\n");
}

double approximate(double num)
{
	return floor(num/epsilon) * epsilon;
}

size_t lss_memsize_46_02(int n)
{
	return n*sizeof(double);
}

int lss_46_02(int n, double *A, double *B, double *X, double *tmpmem)
{
	double max, tmp = 0, tmp2, tmp3;
	int i, j, max_index, max_B, counter, counter_1, counter_2, counter_3, k = 0;
	//print(A, B, n);
	
	if (debug){
		printf("\ndebug\n");
	}

	for (i = 0; i < n; i++)
	{
		if (debug)
		{
			printf("\n   poisk maximalnogo elemenda v stobce %i: \n ", i);
		}
		max = fabs(A[i*n + i]);
		max_index = i*n + i;
		for (j = i + 1; j < n; j++)
		{
			if (fabs(A[j*n + i]) < epsilon)
			{
				continue;
			}

				if (max - fabs(A[j*n + i]) < epsilon)
			{
				max = fabs(A[j*n + i]);
				max_index = j*n + i;
				max_B = j;
			}
		}
		if (debug)
		{
			printf("\n   maximalniy element v stolbce %i: [%d,%d] \n",i, i, (max_index - i) / n);
		}

		if (debug)
		{
			print(A, B, n);
		}

		if (max_index != i*n + i)
		{
			for (counter = 0; counter < n - i; counter++)
			{
				tmp = A[i*n + i + counter];
				A[i*n + i + counter] = A[max_index + counter];
				A[max_index + counter] = tmp;
				
			}
			tmp = B[i];
			B[i] = B[max_B];
			B[max_B] = tmp;
			//print(A, B, n);
		}
		
		
		max = A[i*n + i];
		
		if (fabs(max) >= epsilon)
		{
			if (debug){
				printf("\n   normalizaciya stroki %i:\n", i);
			}
			A[i*n + i] = 1;
			for (counter_1 = i + 1; counter_1 < n; counter_1++)
			{
				A[i*n + counter_1] = approximate(A[i*n + counter_1] / max);
			}

			B[i] = approximate( B[i] / max);

			for (counter_2 = i + 1; counter_2 < n; counter_2++)
			{
				tmp2 = A[counter_2*n + i];
				A[counter_2*n + i] = 0;
				if (tmp2 != 0)
				{
					for (counter_3 = i + 1; counter_3 < n; counter_3++)
					{
						A[counter_2*n + counter_3] = approximate(A[counter_2*n + counter_3] - tmp2*A[i*n + counter_3]);
					}
					B[counter_2] = approximate(B[counter_2] - tmp2*B[i]);
				}
			}

			if (debug)
			{
				print(A, B, n);
			}
		}
		else
		{
			if (debug){
				printf("\n   nelzay normalizovati stroku %i ! \n", i);
			}
			continue;
		}


		
	}


	//print(A, B, n);
	if (debug)
	{
		printf("\n   obratniy hod Gaussa\n");
	}

	for (i = n - 1; i >= 0; i--)
	{

		if(fabs(A[i*n+i]) < epsilon && fabs(B[i]) > epsilon)
		{
			if (debug)
			{
				printf("\n   net resheniy!\n");
			}
			return 1;
		}
		
		X[i] = 0;
		tmp3 = B[i];

		for (j = n - 1; j > i; j--)
		{
			tmp3 = tmp3 - A[i*n + j] * X[j];
		}

		if (fabs(tmp3) >= epsilon)
			X[i] = tmp3;

		if(fabs(A[i*n+i]) < epsilon && fabs(X[i]) > epsilon)
		{
			if (debug)
			{
				printf("\n   net resheniy!\n");
			}
			return 1;
		}
	}
	
	if (debug)
	{
		printf("\n   vektor resheniy: \n");
		for (i = 0; i < n; i++)
		{
			printf("%lf ", X[i]);
		}
		printf("\n");
	}
	//print(A,B,n);

	return 0;
}
