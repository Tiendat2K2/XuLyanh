#include <opencv2/opencv.hpp>
#include <iostream>

using namespace std;
using namespace cv;

void displayHistogram(Mat& image, const string& windowName) {
    int histSize = 256;
    float range[] = { 0, 256 };
    const float* histRange = { range };
    bool uniform = true, accumulate = false;
    Mat hist;

    calcHist(&image, 1, 0, Mat(), hist, 1, &histSize, &histRange, uniform, accumulate);

    int hist_w = 512, hist_h = 400;
    int bin_w = cvRound((double)hist_w / histSize);
    Mat histImage(hist_h, hist_w, CV_8UC3, Scalar(0, 0, 0));

    normalize(hist, hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());

    for (int i = 1; i < histSize; i++) {
        line(histImage, Point(bin_w * (i - 1), hist_h - cvRound(hist.at<float>(i - 1))),
            Point(bin_w * (i), hist_h - cvRound(hist.at<float>(i))),
            Scalar(255, 0, 0), 2, 8, 0);
    }

    imshow(windowName, histImage);
}

int main() {
    // Đọc ảnh xám
    Mat image = imread("anh.jpg", IMREAD_GRAYSCALE);

    if (image.empty()) {
        cout << "Không thể đọc ảnh!\n";
        return -1;
    }

    // Hiển thị ảnh gốc
    imshow("Ảnh gốc", image);

    // Nâng cấp chất lượng ảnh bằng cân bằng lược đồ xám
    Mat equalizedImage;
    equalizeHist(image, equalizedImage);

    // Hiển thị ảnh đã nâng cấp
    imshow("Ảnh đã nâng cấp", equalizedImage);

    // Hiển thị histogram của ảnh gốc và ảnh đã nâng cấp
    displayHistogram(image, "Histogram ảnh gốc");
    displayHistogram(equalizedImage, "Histogram ảnh đã nâng cấp");

    waitKey(0);
    return 0;
}