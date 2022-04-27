#include <iostream>

using namespace std;

#define max 101

struct sparse_matrix
{
	int row;
	int col;
	int val;
};

int len; // len of sparse matrix

sparse_matrix a[max];// a is sparse matrix 
sparse_matrix b[max];/* b is set to the transpose of a */
int c[max][max];//c is input matrix

/*
Nếu a[i][j] > 0
1. chèn vào a[0]. row = i;
			a[0]. col = j;
			a[0].val = b[i][j];
2. tăng số phần tử trong mảng
*/

void InIt(int matrixIn[][max], int r, int c)
{
	a[0].row = r;
	a[0].col = c;
	int dem = 0;
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			if (matrixIn[i][j] != 0)
				dem++;
	a[0].val = dem;
	len = 1;
}

void insert(int r, int c, int value)
{
	::a[len].row = r;
	::a[len].col = c;
	::a[len].val = value;
	len++;
}

void nhapMang(int a[][max],int &m, int& n)
{
	cout << "Nhap m: " << endl;
	cin >> m;
	cout << "Nhap n: " << endl;
	cin >> n;
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			cin >> a[i][j];
	InIt(a, m, n);
}

void readFile(int a[][max], int& m, int& n)
{
	FILE* f = fopen("in.inp", "rt");
	fscanf(f, "%d %d", &m, &n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			fscanf(f, "%d ", &a[i][j]);
	InIt(a, m, n);
	fclose(f);
}

void printsp(sparse_matrix a[])
{
	cout << "\nDimension of Sparse Matrix: "
		<< len << " x " << 3;
	cout << "\nSparse Matrix: \nRow Column Value\n";

	for (int i = 0; i < len; i++) {

		cout << a[i].row << " "
			<< a[i].col << " "
			<< a[i].val << "\n";
	}
}

void print(int a[][max], int m, int n)
{
	cout << "The given matrix is: " << endl;
	for (int i = 0; i < m; i++)
	{
		for (int j = 0; j < n; j++)
			cout << a[i][j] << " ";
		cout << endl;
	}
	cout << endl;
}

/*
1. Read trip, count;   trip: matrix in triplet format     count: no. of nonzero element in trip 
2. set i = 0;
3. for i < count + 1
4.	swap(a[i].row, a[i].col)
5. end for
6. sort trip row-wise 
	-fist based on 0th col
	-if entry in 0th col is same, 
		sort base on entry of 1th col
*/

void transpose(sparse_matrix a[], sparse_matrix b[])
{
	int n, i, j, currentb;
	n = a[0].val;//count no. of non zero element
	//swap(a[i].row, a[i].col)
	b[0].row = a[0].col; /* rows in b = columns in a */
	b[0].col = a[0].row; /*columns in b = rows in a */
	b[0].val = n;
	if (n > 0) {/*non zero matrix */
		currentb = 1;
		for (i = 0; i < a[0].col; i++)/* transpose by columns in a */
			for (j = 1; j <= n; j++)
				/* find elements from the current column */
				if (a[j].col == i) {
					/* element is in current column, add it to b */
					b[currentb].row = a[j].col;
					b[currentb].col = a[j].row;
					b[currentb].val = a[j].val;
					currentb++;
				}
	}
}

int main()
{
	int  m, n;
	nhapMang(c, m, n);
	print(c, m, n);
	for (int i = 0; i < m; i++)
		for (int j = 0; j < n; j++)
			if (c[i][j] != 0)
				insert(i, j, c[i][j]);
	cout << "Sparse matrix is: " << endl;
	printsp(a);
	transpose(a, b);
	cout << "The transpose of sparse matrix is: " << endl;
	printsp(b);
	return 0;

}