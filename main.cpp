#include <iostream>
#include <opencv2/opencv.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>

// #include "tools.hpp"

using namespace std;
using namespace cv;

#define SIZE_IMG 32
#define SIZE_TEST 100
#define SIZE_TRAIN 1000

float sigmoid_C1(float a) {
  // A modifier.
  return a;
}

Mat convolution_C1(Mat &image, float coefficients[6][5][5], int size, int num_layer, float bias) {
  int cumul = 0;
  Mat result = Mat::zeros(cv::Size(size - 4, size - 4), CV_8U);
  for (int i = 2; i < size - 2; i++) {
    for (int j = 2; j < size - 2; j++) {
      cumul = 0;
      for (int k = -2; k < 3; k++) {
        for (int l = -2; l < 3; l++) {
          cumul += image.at<unsigned char>(i + k, j + l) * coefficients[k + 2][l + 2][num_layer];
        }
      }
      result.at<unsigned char>(i - 2, j - 2) = (unsigned char)sigmoid_C1(cumul / 25);
    }
  }
  return result;
}

int main() {

  // On charge une image pour tester

  string str_type_3(to_string(3));
  string str_number(to_string(5));
  Mat image = imread("test_set/" + str_type_3 + "/" + str_number + ".jpg", 0);
  if (image.empty()) {
    std::cout << "image non trouvée" << std::endl;
  }
  cout << image << endl << endl;

  // Les paramètres que l'on va modifier, sur lesquels on va faire du training.
  float coefficients_C1[6][5][5];
  float bias_C1[6];

  // initialisation des paramètres
  for (int i = 0; i < 6; i++) {
    bias_C1[i] = 1;
    for (int j = 0; j < 5; j++) {
      for (int k = 0; k < 5; k++) {
        coefficients_C1[i][j][k] = 1;
      }
    }
  }

  // On calcule un layer du C1
  Mat image_convol = convolution_C1(image, coefficients_C1, 32, 1, bias_C1[1]);
  cout << image_convol << endl;

  return 0;
}
