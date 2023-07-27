include <iostream>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

// Tính histogram của ảnh xám
void computeHistogram(const Mat& image, vector<int>& histogram) {
    histogram.assign(256, 0);

    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            uchar pixelValue = image.at<uchar>(i, j);
            histogram[pixelValue]++;
        }
    }
}
// Cân bằng lược đồ xám
void histogramEqualization(Mat& image) {
    vector<int> histogram;
    computeHistogram(image, histogram);
    // Tính hàm phân phối tích lũy (CDF)
    vector<int> cdf(256, 0);
    cdf[0] = histogram[0];
    for (int i = 1; i < 256; ++i) {
        cdf[i] = cdf[i - 1] + histogram[i];
    }
    // Chuẩn hóa CDF
    float normalizationFactor = 255.0f / (image.rows * image.cols);
    for (int i = 0; i < 256; ++i) {
        cdf[i] = static_cast<int>(round(cdf[i] * normalizationFactor));
    }
    // Áp dụng cân bằng lược đồ xám cho ảnh
    for (int i = 0; i < image.rows; ++i) {
        for (int j = 0; j < image.cols; ++j) {
            uchar pixelValue = image.at<uchar>(i, j);
            image.at<uchar>(i, j) = static_cast<uchar>(cdf[pixelValue]);
        }
    }
}
int main() {
    // Đọc ảnh xám từ file
    Mat grayImage = imread("anh.jpg", IMREAD_GRAYSCALE);
    if (grayImage.empty()) {
        cout << "Không thể đọc ảnh!" << endl;
        return -1;
    }