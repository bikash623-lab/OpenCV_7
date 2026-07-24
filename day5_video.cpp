#include <iostream>
#include <chrono> // for timing
#include <opencv2/opencv.hpp>

int main(){
    // Open video or camera
    cv::VideoCapture cap(0); // 0 = default webcam, 1 = 2nd camera, 2 = 3rd camera

    if(!cap.isOpened()){
        std::cout <<"Error: could't open the camera.";
        return -1;
    }

    //Set resolution
    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280);
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720);

    // Print properties
    std::cout<<"Width"<<cap.get(cv::CAP_PROP_FRAME_WIDTH)<<"\n";
    std::cout<<"Height"<<cap.get(cv::CAP_PROP_FRAME_HEIGHT)<<"\n";
    std::cout<<"FPS"<<cap.get(cv::CAP_PROP_FPS) <<"\n";

    auto prevTime = std::chrono::steady_clock::now();
    cv::Mat frame;
    while(true){
        cap >> frame; //grab frame
        if(frame.empty()) break; // end of stream

        // calculate FPS
        auto currTime = std::chrono::steady_clock::now();
        double fps = 1.0 / std::chrono::duration<double>(currTime-prevTime).count();
        prevTime = currTime;
        //Process each frame
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv::Mat blurred;
        cv::GaussianBlur(frame, blurred, cv::Size(15,15), 0);

        cv::Mat edges;
        cv::Canny(frame, edges, 50, 150);
        cv::Mat thresh;
        cv:threshold(gray, thresh, 127, 255, cv::THRESH_BINARY);

        // draw FPS on frame
        cv::putText(frame,
            "FPS: " + std::to_string((int)fps),
            cv::Point(20, 40),
            cv::FONT_HERSHEY_SIMPLEX,
            1.0,
            cv::Scalar(0, 255, 0),
            2);

        cv::imshow("Original", frame);
        cv::imshow("Edges", edges);
        cv::imshow("Gray", gray);
        cv::imshow("Blurred", blurred);
        cv::imshow("Thresh", thresh);

        if(cv::waitKey(30) == 27) break; //ESC = quit

    }
    cap.release();
    cv::destroyAllWindows();
    return 0;

}