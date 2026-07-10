#include <iostream>
#include <opencv2/opencv.hpp>

int main(){
    cv::Mat img = cv::imread("Photo.jpg");

    if(img.empty()){
        std::cout<<"Error: Couldn't able to load." <<"\n";
        return -1;
    }

    std::cout <<"Width:"<<img.cols<< "\n";
    std::cout <<"Height:"<<img.rows<< "\n";
    std::cout <<"Channel:"<<img.channels()<<"\n";

    cv::Mat resized;
    cv::resize(img, resized, cv::Size(1080, 1080));

    cv::Mat gray;
    cv::cvtColor(img, gray, cv::COLOR_BGR2GRAY);

    cv::Mat flipped;
    cv::flip(img, flipped, 1);

    cv::Mat rotated;
    cv::rotate(img, rotated, cv::ROTATE_90_CLOCKWISE);


    cv::Rect region(50, 50, 500, 500);
    cv::Mat cropped = img(region);


    cv::Mat cropped = img(cv::Rect(50,50,500,500)).clone();


    cv::Mat RectBox = img.clone();
    cv::rectangle(RectBox, cv::Point(100,100), cv::Point(500, 500), cv::Scalar(0,0,255), 1);

    cv::Mat Circle_ = img.clone();
    cv::circle(Circle_, cv::Point(100,100), 50, cv::Scalar(255, 0, 0), 1);

    cv::Mat ImageText = img.clone();
    cv::putText(ImageText, "Bikash_Malla", cv::Point(100,100), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,255,0), 2);

    // Read pixel
    cv::Vec3b pixel = img.at<cv::Vec3b>(300, 300);
    std::cout<<"Read_Pixel"<<"\n";
    std::cout<<"Blue:"<<(int)pixel[0]<<"\n";
    std::cout<<"Green:"<<(int)pixel[1]<<"\n";
    std::cout<<"Red:"<<(int)pixel[2]<<"\n";


    //Moding the pixel
    cv::Mat PixelTest = img.clone();
    for(int row = 100; row <= 110; row++){
        for(int col = 100; col <= 110; col++){
            PixelTest.at<cv::Vec3b>(row, col) = cv::Vec3b(0,0,255); // directly modifying the pixel

        }
    }


    //keeping red only
    cv::Mat RedOnly = img.clone();
    for(int row = 0; row < RedOnly.rows; row++){
        for(int col = 0; col < RedOnly.cols; col++){
            cv::Vec3b& p = RedOnly.at<cv::Vec3b>(row, col); // removing the color not modifying with different number
            p[0] = 0;
            p[1] = 1;
        }
    }

    cv:: Mat roiTest = img.clone();
    cv::Rect roi(100, 100, 200, 200);
    roiTest(roi) = cv::Scalar(0, 0, 0);

    cv:: Mat bright = img + cv::Scalar(60,60,60);
    cv::Mat dark = img - cv::Scalar(60,60,60);

    cv::Mat blenned;
    cv::addWeighted(bright, 0.5, dark, 0.5, 0, blenned);

    cv::rectangle(img, cv::Point(100,100), cv::Point(500, 500), cv::Scalar(0,0,255), 1);

    cv::circle(img, cv::Point(100,100), 50, cv::Scalar(255, 0, 0), 1);

    cv::putText(img, "Bikash_Malla", cv::Point(100,100), cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0,255,0), 2);

    cv::imshow("Orginal", img);
    cv::imshow("Resized_", resized);
    cv::imshow("Gray", gray);
    cv::imshow("Flipped", flipped);
    cv::imshow("Rotated", rotated);
    cv::imshow("PixelTest", PixelTest);
    cv::imshow("RedOnly", RedOnly);
    cv::imshow("Roi", roiTest);
    cv::imshow("Bright", bright);
    cv::imshow("dark", dark);
    cv::imshow("blenned", blenned);
    cv::imshow("Cropped", cropped);
    cv::imshow("rect", RectBox);
    cv::imshow("cir", Circle_);

    cv::waitKey(0);







    return 0;
}