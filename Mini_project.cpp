#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    cv::Mat img = cv::imread("Shape.jpg");

    if(img.empty()){
        std::cout<<"Error: couldn't load the image." <<"\n";
        return -1;
    }

    cv::Mat resized;
    cv::resize(img, resized, cv::Size(1080, 1080));

    cv:: Vec3b pixel = img.at<cv::Vec3b>(100,300);
    std::cout <<"Reading pixel(100, 300)" <<"\n";
    std::cout <<"Blue:" <<(int)pixel[0];
    std::cout <<"Green:" <<(int)pixel[1];
    std::cout <<"Red:" <<(int)pixel[2];


    cv::Mat modify = img.clone();
    for(int row = 100; row < 110; row++){
        for(int col = 100; col < 110; col++){
            modify.at<cv::Vec3b>(row, col) = cv::Vec3b(0, 0, 255);
        }
    }

    cv:: Mat BlueOnly = img.clone();
    for(int row = 0; row < BlueOnly.rows; row++){
        for(int col = 0; col < BlueOnly.cols; col++){
            cv::Vec3b& p = BlueOnly.at<cv::Vec3b>(row, col);
            p[0] = 0;
            p[2] = 0;
        }
    }

    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    cv::Mat Blurred;
    cv::GaussianBlur(img, Blurred, cv::Size(5,5), 0);

    cv::Mat Median;
    cv::medianBlur(img, Median, 15);

    cv::Mat edges;
    cv::Canny(gray, edges, 30, 100);

    cv::Mat thresh;
    cv::threshold(gray, thresh, 127, 255, cv::THRESH_BINARY_INV);

    // close grap
    cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));
    cv::Mat closededge;
    cv::dilate(edges, closededge, kernel, cv::Point(-1, -1), 2);

    //Find Contours
    std::vector<std::vector<cv::Point>> contours;
    std::vector<cv::Vec4i> hierarchy;

    cv::findContours(closededge, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);
    std::cout<< "Object found: " << contours.size() << "\n";
    

    cv::Mat result = img.clone();
    int objCount = 0;
    for(int i = 0; i < contours.size(); i++){
        
        // filter small contours (noise)
        if(cv::contourArea(contours[i]) < 100) continue;
        objCount++;

        // get bounding box
        cv::Rect box = cv::boundingRect(contours[i]);
        cv::rectangle(result, box, cv::Scalar(0, 0, 255), 2);


        // draw label
        cv::putText(result,"Object" + std::to_string(objCount), cv::Point(box.x, box.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0, 0, 255), 1);
    }

    cv::imshow("Original", img);
    cv::imshow("Resize", resized);
    cv::imshow("Pixel_Modify", modify);
    cv::imshow("BlueOnly", BlueOnly);
    cv::imshow("Gray", gray);
    cv::imshow("Edge", edges);
    cv::imshow("Thresh", thresh);
    cv::imshow("Result", result);
    
    cv::waitKey(0);


    return 0;


}