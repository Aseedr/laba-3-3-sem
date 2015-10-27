#include <iostream>

class TripleIntClass {
private:
	int ***triple_matrix;
	int matrix_length;
	int matrix_width;
	int matrix_height;
public:
	TripleIntClass();
	TripleIntClass(int, int, int);
	TripleIntClass(const TripleIntClass &);
	~TripleIntClass();
	void EnterMatrix();
	void ShowMatrix();
	void MatrixSort();
	void ChangeElement(int, int, int);
	int ShowElement(int, int, int);
	friend void CompareMattrix(TripleIntClass &first, TripleIntClass &second);
};

TripleIntClass::TripleIntClass(int l, int w, int h) {
	matrix_length = l;
	matrix_width = w;
	matrix_height = h;
	triple_matrix = new int**[l];
	if (triple_matrix == nullptr) {
		std::cout << "No free memory!";
		return;
	}
	for (int i = 0; i < w; i++) {
		triple_matrix[i] = new int*[w];
		if (triple_matrix[i] == nullptr) {
			for (int z = i - 1; z >= 0; z--) {
				delete triple_matrix[z];
			}
			delete[] triple_matrix;
			std::cout << "No free memory!";
			return;
		}
		for (int j = 0; j < h; j++) {
			triple_matrix[i][j] = new int[h];
			if (triple_matrix[i][j] == nullptr) {
				for (int x = i; x >= 0; x--) {
					if (x == i) {
						for (int z = j; z >= 0; z--) {
							delete[] triple_matrix[x][z];
						}
					}
					else {
						for (int z = 0; z <= h; z++) {
							delete[] triple_matrix[x][z];
						}
					}
					delete[] triple_matrix[x];
				}
				delete[] triple_matrix;
				std::cout << "No free memory!";
				return;
			}
		}
	}
}

TripleIntClass::TripleIntClass(const TripleIntClass &old) {
	matrix_length = old.matrix_length;
	matrix_width = old.matrix_width;
	matrix_height = old.matrix_height;
	triple_matrix = new int**[matrix_length];
	for (int i = 0; i < matrix_length; i++) {
		triple_matrix[i] = new int*[matrix_width];
		for (int j = 0; j < matrix_width; j++) {
			triple_matrix[i][j] = new int[matrix_height];
		}
	}
	for (int i = 0; i < matrix_length; i++) {
		for (int j = 0; j < matrix_width; j++) {
			for (int k = 0; k < matrix_height; k++) {
				triple_matrix[i][j][k] = old.triple_matrix[i][j][k];
			}
		}
	}
}

void TripleIntClass::EnterMatrix() {
	for (int i = 0; i < matrix_length; i++) {
		for (int j = 0; j < matrix_width; j++) {
			for (int k = 0; k < matrix_height; k++) {
				std::cout << "Enter matrix" << "[" << i + 1 << "][" << j + 1 << "][" << k + 1 << "]: ";
				std::cin >> triple_matrix[i][j][k];
				fflush(stdin);
			}
		}
	}
}

void TripleIntClass::ShowMatrix() {
	using namespace std;
	std::cout << '\n';
	for (int i = 0; i < matrix_length; i++) {
		for (int j = 0; j < matrix_width; j++) {
			cout << "   ";
			for (int k = 0; k < matrix_height; k++) {
				std::cout << " " << triple_matrix[i][j][k];
			}
		}
		std::cout << endl;
	}
	std::cout << endl;
}

TripleIntClass::~TripleIntClass() {
	for (int i = 0; i < matrix_length; i++) {
		for (int j = 0; j < matrix_width; j++) {
			delete[] triple_matrix[i][j];
		}
		delete[] triple_matrix[i];
	}
	delete[] triple_matrix;
}

void TripleIntClass::MatrixSort() {
	int temp = 0;
	for (int i = 0; i < matrix_length; i++)
	{
		for (int j = 0; j < matrix_width; j++)
		{
			for (int k = 0; k < matrix_height - 1; k++)
			{
				for (int q = k + 1; q < matrix_height; q++)
				{
					if (triple_matrix[i][j][k] < triple_matrix[i][j][q])
					{
						temp = triple_matrix[i][j][k];
						triple_matrix[i][j][k] = triple_matrix[i][j][q];
						triple_matrix[i][j][q] = temp;
					}
				}
			}
		}
	}
}

void CompareMattrix(TripleIntClass &first, TripleIntClass &second) {
	using namespace std;
	int compare_mark = 0, mattrix_strings_count = 0;
	mattrix_strings_count = first.matrix_length * first.matrix_width * first.matrix_height;
	if (first.matrix_length == second.matrix_length
		&& first.matrix_width == second.matrix_width
		&& first.matrix_height == second.matrix_height) {
		for (int i = 0; i < first.matrix_length; i++) {
			for (int j = 0; j < first.matrix_width; j++) {
				for (int k = 0; k < first.matrix_height; k++)
				if (first.triple_matrix[i][j][k] == second.triple_matrix[i][j][k]) {
					compare_mark++;
				}
			}
		}
	}
	else {
		cout << "\nThis matrixs are not the same!\n" << endl;
		return;
	}
	if (compare_mark == mattrix_strings_count) {
		cout << "\nMatrix 1 same as mattrix 2\n" << endl;
		return;
	}
	else {
		cout << "\nThis matrixs are not the same!\n" << endl;
		return;
	}
}

void TripleIntClass::ChangeElement(int w, int h, int s) {
	using namespace std;
	--w; --h; --s;
	int change = 0;
	cout << "\nNow you can change this element, enter 1 for change 2 for discard: ";
	cin >> change;
	if (change == 1) {
		cout << "Enter new element: ";
		fflush(stdin);
		cin >> triple_matrix[w][h][s];
		cout << "\nElement changed!" << endl;
	}
	else if (change == 2) {
		return;
	}
	else {
		cout << "\nBad answer, discarding changes.\n" << endl;
		return;
	}
	return;
}

int  TripleIntClass::ShowElement(int w, int h, int s) {
	using namespace std;
	--w; --h; --s;
	if (w <= matrix_length && h <= matrix_width && s <= matrix_height) {
		if (s <= matrix_height) {
			cout << "\nThe element is: ";
			cout << triple_matrix[w][h][s] << endl;
		}
		else {
			cout << "\nMatrix don't have elements on this position" << endl;
			return 1;
		}
	}
	else {
		cout << "\nMatrix don't have elements on this position" << endl;
		return 1;
	}
	return 0;
}

int main() {
	using namespace std;
	int size = 0, size1 = 0, size2 = 0;
	int pos_w = 0, pos_h = 0, pos_s = 0;
	cout << "Enter size of string: ";
	cin >> size;
	cout << "Enter size of matrix 1: ";
	cin >> size1;
	cout << "Enter size of matrix 2: ";
	cin >> size2;
	fflush(stdin);
	system("cls");

	TripleIntClass arr(size, size1, size2);
	TripleIntClass arr2(size, size1, size2);
	cout << "Enter elements of first matrix:\n" << endl;
	arr.EnterMatrix();
	system("cls");

	cout << "Enter elements of second matrix:\n" << endl;
	arr2.EnterMatrix();
	system("cls");

	cout << "Source text of first matrix:" << endl;
	arr.ShowMatrix();
	cout << "Source text of second matrix:" << endl;
	arr2.ShowMatrix();
	CompareMattrix(arr, arr2);
	system("pause");
	system("cls");

	cout << "Enter row of matrix for display: ";
	cin >> pos_w;
	cout << "Enter string of matrix for display: ";
	cin >> pos_h;
	cout << "Enter letter of matrix for display: ";
	cin >> pos_s;
	fflush(stdin);
	if (arr.ShowElement(pos_w, pos_h, pos_s) == 0) {
		arr.ChangeElement(pos_w, pos_h, pos_s);
		arr.ShowMatrix();
	}
	system("pause");
	system("cls");

	cout << "First matrix before sorting of strings:" << endl;
	arr.ShowMatrix();
	arr.MatrixSort();
	cout << "First matrix after sorting of strings:" << endl;
	arr.ShowMatrix();
	system("pause");
	system("cls");

	return 0;
}
