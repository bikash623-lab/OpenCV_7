#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    cv:: Mat img = cv::imread("Photo.jpg");

    if(img.empty()){
        std::cerr<<"Error: couldn't able to load image\n";
        return -1;
    }

    std::cout<<"Width: " << img.cols <<"\n";
    std::cout<<"Height: " << img.rows <<"\n";
    std::cout<<"Channels: "<<img.channels() <<"\n";

    cv:: Mat resized;
    cv:: resize(img, resized, cv::Size(1080, 1080));

    cv:: Mat gray;
    cv:: cvtColor(img, gray, cv::COLOR_BGR2GRAY);


    cv:: Mat rotated;
    cv::rotate(img, rotated, cv::ROTATE_90_COUNTERCLOCKWISE);


    cv:: Mat flipped;
    cv:: flip(img, flipped, 0);

    cv::rectangle(img, cv::Point(20, 20), cv::Point(600,600), cv::Scalar(0,255,0), 2);
    cv::circle(img, cv::Point(300, 230), 200, cv::Scalar(0, 0, 255), 2);
    cv::putText(img, "Bikash_Malla", cv::Point(50,50), cv::FONT_HERSHEY_SIMPLEX, 1.0, cv::Scalar(255,0,0), 2);


    // cv::imshow("original", img);
    // cv::imshow("resized", resized);
    // cv::imshow("rotated", rotated);
    // cv::imshow("flipped", flipped);

    cv::imshow("Drawing", img);

    cv::waitKey(0);

    return 0;
}
