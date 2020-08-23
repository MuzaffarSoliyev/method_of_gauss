#include "lss_46_02.h"

int main(int argc, char* argv[])
{
	int n, i, j, res, err;
	clock_t beginTime, endTime;
	int flagP = 0, flagT = 0;
	int k = 1;
	double *A, *B, *X, *tmp;
	char *filenameIn = "lss_46_02_in.txt";
	char *filenameOut = "lss_46_02_out.txt";
	FILE *in, *out;
	beginTime = clock();
	debug = error = 0;

	if (argc >= 3) {
		if (argv[1][0] != '-')
		{
			filenameIn = argv[1];
			filenameOut = argv[2];
			k = 3;
		}
		else
		{
			k = 1;
		}
	}
	for (; k < argc; k++)
	{
		if (stringComp(argv[k], "-p") == 1)
		{
			flagP = 1;
		}
		else if (stringComp(argv[k], "-h") == 1 || stringComp(argv[k], "-?") == 1)
		{
			printf("Usage: lss [input_file_name] [output_file_name] [options] \nWhere options include : \n-d    print debug messages[default OFF] \n- e    print errors[default OFF] \n- p    print matrix[default OFF] \n- t    print execution time[default OFF] \n- h, -? print this and exit \nDefault input_file_name value is lss_00_00_in.txt, default output_file_name value is lss_00_00_out.txt.");
		}
		else if (stringComp(argv[k], "-d") == 1)
		{
			debug = 1;
		}
		else if (stringComp(argv[k], "-e") == 1)
		{
			err = 1;
		}
		else if (stringComp(argv[k], "-t") == 1)
		{
			flagT = 1;
		}
		else
		{
			if (err)
			{
				printf(stderr, "Parametr zadan ne pravilno\n");
			}
			return -5;
		}
	}

	in = fopen(filenameIn, "r");
	out = fopen(filenameOut, "w");
	if (out == NULL)
	{
		if (err)
		{
			printf(stderr, "Oshibka pri otkritii vhodnogo fayla\n");
		}
		return -4; 
	}

	if (in == NULL) 
	{
		if (err)
		{
			printf(stderr, "Oshibka pri otkritii vhodnogo fayla\n");
		}
		return -1; 
	}
	if (fscanf(in, "%d", &n) != 1 || n < 0)
	{
		fclose(in);
		if (err)
		{
			printf(stderr, "Oshibka pri razmernosti matrici libo razmer matrichi menishe nulya\n");
		}
		return -1;
	}



	A = (double*)malloc(n*n * sizeof(double));
	B = (double*)malloc(n * sizeof(double));
	X = (double*)malloc(n * sizeof(double));
	tmp = NULL;

	if (A == NULL || B == NULL || X == NULL)
	{
		fclose(in);
		if (err)
		{
			printf(stderr, "Oshibka pri vidilenii pamyati\n");
		}
		return -2;
	}
	for (j = 0; j < n*n; j++)
	{
		if (fscanf(in, "%lf", &A[j]) != 1)
		{
			fclose(in);
			if (err)
			{
				printf(stderr, "Oshibka pri schitivanii\n");
			}
			return -3;
		}
	}

	for (j = 0; j < n; j++)
	{
		if (fscanf(in, "%lf", &B[j]) != 1)
		{
			fclose(in);
			if (err)
			{
				printf(stderr, "Oshibka pri schitivanii\n");
			}
			return -3;
		}
	}

	fclose(in);

	if (flagP)
	{
		print(A, B, n);
	}



	res = lss_46_02(n, A, B, X, tmp);

	if (res == 1)
	{
		fprintf(out, "%d", 0);
	}
	else if (res == 0)
	{
		fprintf(out, "%d\n", n);
		for (i = 0; i < n; i++)
		{
			fprintf(out, "%1.9lf\n", X[i]);
		}
	}

	fclose(out);
	free(X);
	free(B);
	free(A);


	if (flagT)
	{
		endTime = clock();
		printf("%lf\n", (double)(endTime - beginTime) / CLOCKS_PER_SEC);
	}

	return 0;
}

size_t stringLength(const char *str)
{
	size_t length = 0;
	while (str[length] != '\0')
	{
		length++;
	}
	return length;

}

int stringComp(const char *str1, const char *str2)
{

	size_t i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i] || abs((int)(stringLength(str1) - stringLength(str2))) != 0) {
			return -1;
		}
		i++;
	}
	return 1;
}