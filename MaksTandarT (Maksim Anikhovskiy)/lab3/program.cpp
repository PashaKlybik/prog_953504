#include <iostream>

void printMatrix (char **matrix, int N, int M) {
  for (int i = 0; i < N; i++) {
    for (int j = 0; j < M; j++) {
      std::cout << matrix[i][j] << "   ";
    }

    std::cout << std::endl;
  }
}

char ** expandMatrix (char **matrix, int &N, int &M, int rows, int cols) {
  char **newMatrix = new char*[N + rows]; // новая матрица --> внутри копия
  for (int i = 0; i < N + rows; i++) {
    newMatrix[i] = new char[M + cols];
  }
  for(int i = 0; i < N + rows; i++) {
    for (int j = 0; j < M + cols; j++){
      newMatrix[i][j] = '*';
    }
  }

  for (int i = 0; i < N; i++){
    for(int j = 0; j < M; j++){
      newMatrix[i][j] = matrix[i][j];
    }
  }

  N += rows;
  M += cols;
  return newMatrix;
}

char ** inputMatrix(char **matrix, int &N, int &M){
  int I, J, A;

  while (true) {
    std::cout << "Enter the i, j and a: ";
    std::cin >> I >> J >> A;
    if(I == 0 && J == 0 && A == 0) break;

    if(I + 1 > N) { // добавление строк и ввод
      matrix = expandMatrix(matrix, N, M, I + 1 - N, 0);  
    }
    if(J + 1 > M) { // добавление строк и ввод
      matrix = expandMatrix(matrix, N, M, 0, J + 1 - M);  
    }

    matrix[I][J] = (char)(((int)'0')+A);
  }

  return matrix;
}

int main() {
  int N = 1, M = 1; 
  char **matrix = new char*[N];
  matrix[0] = new char[M];
  matrix[0][0] = '*';
	
  while (true) {
    matrix = inputMatrix(matrix, N, M);
  
    printMatrix(matrix, N, M);

    bool trigger = false;
    std::cout << "Do you want to change your matrix? (1 - YES, 0 - NO): ";
    std::cin >> trigger;

    if(!trigger) break;
  }

  system("pause");
	return 0;
}