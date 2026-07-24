#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

int main(){
    // Open Camera
    cv:: VideoCapture cap(0);
    if(!cap.isOpened()){
        std::cout<<"Error:couldn't open camera.";
        return -1;
    }

    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280)
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    std::cout<<"Width:"<<cap.get(cv::CAP_PROP_FRAME_WIDTH) <<"\n";
    std::cout<<"Heigth:"<<cap.get(cv::CAP_PROP_FRAME_HEIGHT)<<"\n";
    std::cout<<"FPS:"<<cap.get(cv::CAP_PROP_FPS)<<"\n";


    
}