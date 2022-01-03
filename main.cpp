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

// void fill_the_data(float *test_set_3, float *test_set_4, float *train_set_3, float *train_set_4) {

//   for (int i = 0; i < SIZE_TEST; i++) {
//     string str_type_3(to_string(3));
//     string str_number(to_string(i));

//     Mat image = imread("test_set/" + str_type + "/" + str_number + ".jpg", 0);
//     if (image.empty()) {
//       std::cout << "image non trouvée" << std::endl;
//     }

//     cout << image << endl;

//     fill imshow("imge chargée", image);
//     waitKey(0);
//   }
// }

float sigmoid_C1(float a) {
  // A modifier.
  return a;
}

Mat convolution_C1(Mat &image, float coefficients[5][5][6], int size, int num_layer) {
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

  // uint test_set_3[32][32][SIZE_TEST];
  // uint test_set_4[32][32][SIZE_TEST];
  // uint train_set_3[32][32][SIZE_TRAIN];
  // uint train_set_4[32][32][SIZE_TRAIN];

  // Les paramètres que l'on va modifier, sur lesquels on va faire du training.
  float coefficients_first_convolution[5][5][6];

  string str_type_3(to_string(3));
  string str_number(to_string(5));

  Mat image = imread("test_set/" + str_type_3 + "/" + str_number + ".jpg", 0);
  if (image.empty()) {
    std::cout << "image non trouvée" << std::endl;
  }

  cout << image << endl << endl;

  Mat image_convol = convolution_C1(image, coefficients_first_convolution, 32, 1);

  cout << image_convol << endl;

  imshow("imge chargée", image);
  waitKey(0);

  // fill_the_data(test_set_3, test_set_4, train_set_3, train_set_4);

  return 0;
}
