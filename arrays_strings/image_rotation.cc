
#include <fstream>
#include <vector>

#include "../include/ostream_overload.h"

using Image = std::vector<std::vector<char>>;

Image readImage() {
  Image image_out;
  std::size_t max_width = 0;
  std::ifstream image("resources/heart.txt");
  if (image.is_open()) {
    std::string line;
    while (getline(image, line)) {
      // std::cout << line << "\n";
      const std::vector<char> line_vec(line.begin(), line.end());
      if (line_vec.size() > max_width) max_width = line_vec.size();
      image_out.push_back(line_vec);
    }
    image.close();
  }

  // Ensure the number of columns of all rows is the same by adding necessary extra character (here is space) to the end
  // of each column.
  for (auto& row : image_out) {
    if (row.size() < max_width) {
      const int how_many = max_width - row.size();
      std::fill_n(std::back_inserter(row), how_many, ' ');
    }
  }

  return image_out;
}

void assignColumn(std::size_t col_idx, const std::vector<char>& values, Image& image) {
  for (std::size_t row_idx = 0; row_idx < values.size(); ++row_idx) {
    image[row_idx][col_idx] = values[row_idx];
  }
}

Image rotateImage(const Image& image_in) {
  // rotate 90 degrees
  std::size_t height = image_in.size();
  std::size_t width = image_in[0].size();

  Image image_out(width, std::vector<char>(height, '0'));
  for (std::size_t row_idx = 0; row_idx < height; ++row_idx) {
    const auto& row = image_in[row_idx];
    auto col_idx = height - 1 - row_idx;
    assignColumn(col_idx, row, image_out);
  }

  return image_out;
}

void rotateImageInPlace(const Image& image_in) {
  // rotate 90 degrees
}

int main() {
  Image image = readImage();
  std::cout << image << "\n";
  auto image_rotated = rotateImage(image);
  std::cout << image_rotated << "\n";

  return 0;
}
