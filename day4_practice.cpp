#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    cv::Mat img = cv::imread("Photo.jpg");

    if(img.empty()){
        std::cout <<"Error: could't load the image."<<"\n";
        return -1;
    }
    //Gray - needed for several operation
    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    //1. gaussian
    cv::Mat gaussian;
    cv::GaussianBlur(img, gaussian, cv::Size(15,15), 0); // cv::Size(15,15) means kernal size, 0 mean sigmna = 0 that mean opencv calculate the blurs it self

    //2. MedianBlur
    cv::Mat MedianBlur;
    cv::medianBlur(img, MedianBlur, 15);

    //3. Edge detection
    cv::Mat edges;
    cv::Canny(gray, edges, 100, 200); // 100 mean low threshold, lower value = more edge detected,.... 200 means high threshold, higher value = fewer, stronger edge only

    //4. threshold
    cv::Mat thresh;
    cv::threshold(gray, thresh, 127, 255, cv::THRESH_BINARY); // 127 mean lowest value cutoff point and 255 mean highest value cutoff points

    //5.adaptiveThreshold
    cv::Mat adaptive;
    cv::adaptiveThreshold(gray, adaptive, 255, cv::ADAPTIVE_THRESH_GAUSSIAN_C, cv::THRESH_BINARY, 11, 2);
    //6. Morphological ops
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(5,5));
    cv::Mat dilated, eroded, opened, closed;
    cv::dilate(thresh, dilated, kernel);
    cv::erode(thresh, eroded, kernel);
    cv::morphologyEx(thresh, opened, cv::MORPH_OPEN, kernel);
    cv::morphologyEx(thresh, closed, cv::MORPH_CLOSE, kernel);


    //7. Contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;
    cv::findContours(thresh, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

    std::cout << "Contours found: " << contours.size() << "\n";

    cv::Mat contourImg = cv::Mat::zeros(img.size(), img.type());
    cv::drawContours(contourImg, contours, -1, cv::Scalar(0,255,0), 2);




    //Displaycv
    cv::imshow("original", img);
    cv::imshow("Gray", gray);
    cv::imshow("Gaussian Blur", gaussian);
    cv::imshow("Median Blur", MedianBlur);
    cv::imshow("Edges (Canny)", edges);
    cv::imshow("Threshold", thresh);
    cv::imshow("Adaptive Thresh", adaptive);
    cv::imshow("Dilated", dilated);
    cv::imshow("Eroded", eroded);
    cv::imshow("Opened", opened);
    cv::imshow("Closed", closed);
    cv::imshow("contours", contourImg);
    
    cv::waitKey(0);

    return 0;
}
