#include <iostream>
#include <vector>

struct MatrixIndex {
  int row_idx{};
  int col_idx{};
};

void printMatrix(int num_rows, int num_cols) {
  std::cout << "------------------\n  ";
  for (int i = 0; i < num_cols; ++i) std::cout << i << "\t";
  std::cout << "\n";
  int idx = 0;
  for (int row = 0; row < num_rows; ++row) {
    std::cout << row << " ";
    for (int col = 0; col < num_cols; ++col) {
      std::cout << idx++ << "\t";
    }
    std::cout << "\n";
  }
  std::cout << "------------------\n";
}

MatrixIndex convertIdxToRowCol(int num_rows, int num_cols, int idx) {
  // if vector is empty, return false;
  if (num_rows == 1) return {0, idx};
  if (num_cols == 1) return {idx, 0};
  int row_idx = idx / num_cols;
  int col_idx = idx % num_cols;

  return {row_idx, col_idx};
}

bool searchMatrix(const std::vector<std::vector<int>>& matrix, int target) {
  // if vector is empty, return false;
  if (matrix.empty()) return false;
  int row_size = matrix.size();
  int col_size = matrix[0].size();
  int mat_size = row_size * col_size;
  std::cout << "mat size: " << mat_size << " row:" << row_size << " col:" << col_size << "\n";
  int begin = 0;
  int end = mat_size - 1;

  int idx = mat_size / 2;
  int mid_value = matrix[idx / col_size][idx % col_size];
  if (mid_value == target) return true;
  int num_iter = 0;
  while (begin < end && mid_value != target) {
    if (mid_value > target) {
      end = idx - 1;
    } else if (mid_value < target) {
      begin = idx + 1;
    }

    idx = begin + (end - begin) / 2;
    if (idx >= mat_size) break;

    int row_idx = idx / col_size;
    int col_idx = idx % col_size;
    // if (col_size == 1) {
    //   row_idx = idx;
    // }
    mid_value = matrix[row_idx][col_idx];
    std::cout << "idx: " << idx << "\t"
              << "row idx: " << row_idx << "\t"
              << "col idx: " << col_idx << "\t"
              << "mid value: " << mid_value << "\t"
              << "begin: " << begin << " end: " << end << "\n";
    if (num_iter++ > mat_size) break;
  }

  if (mid_value == target) return true;
  return false;
}

int main() {
  // std::vector<std::vector<int>> mat = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}, {10, 11, 12}};
  // std::vector<std::vector<int>> mat = {{1, 3, 5}};
  // std::vector<std::vector<int>> mat = {{1}, {3}, {5}};
  // std::vector<std::vector<int>> mat = {{1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 50}};
  std::vector<std::vector<int>> mat = {{-10, -10}, {-9, -9}, {-8, -6}, {-4, -2}, {0, 1}, {3, 3}, {5, 5}, {6, 8}};

  auto res = searchMatrix(mat, 0);
  std::cout << std::boolalpha << res << "\n";
  // int idx = 3;
  // int num_rows = 3;
  // int num_cols = 5;
  // printMatrix(num_rows, num_cols);
  // for (const auto idx : {2, 4, 8, 12, 14}) {
  //   auto res = convertIdxToRowCol(num_rows, num_cols, idx);
  //   std::cout << "res for " << idx << ": (" << res.row_idx << ", " << res.col_idx << ")\n";
  // }

  return 0;
}
