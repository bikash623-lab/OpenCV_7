#include <iostream>
#include <opencv2/opencv.hpp>
#include <vector>
#include <chrono>

int main(){
    cv:: VideoCapture cap(0); // yesle camera open grxa
    if(!cap.isOpened()){ //yo line chai camera open xa ki nai vanxa
        std::cout<<"Error: couldn't able to open camera.";
        return -1;
    }


    cap.set(cv::CAP_PROP_FRAME_WIDTH, 1280); // yesle chai cap carry garne image or say image or video chai 1280 garako ho
    cap.set(cv::CAP_PROP_FRAME_HEIGHT, 720); // same here

    std::cout<<"Width:"<<cap.get(cv::CAP_PROP_FRAME_WIDTH)<< "\n"; // hamle image or video with 
    std::cout<<"Height:"<<cap.get(cv::CAP_PROP_FRAME_HEIGHT)<< "\n";// height
    std::cout<<"FPS:"<<cap.get(cv::CAP_PROP_FPS)<< "\n"; // frame per second

    // define video writer
    int fourcc = cv::VideoWriter::fourcc('m', 'p', '4', 'v'); //mp4 codec
    cv::VideoWriter writer("Output.mp4", fourcc, 30.0, cv::Size(1280, 720));

    // Fps counter
    auto prevTime = std::chrono::steady_clock::now();
    // cap vnyako basically remote control jasto jasle video camera marfhat image carry grxa
    


    cv:: Mat frame;
    while(true){
        cap >> frame; // grab images
        if(frame.empty()) break; // frame vanne container khali xa vnya 

        // calculate FPS
        auto currTime = std::chrono::steady_clock::now();
        double fps = 1.0/std::chrono::duration<double>(currTime - prevTime).count();
        prevTime = currTime;

        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        cv::Mat blurred;
        cv::GaussianBlur(gray, blurred, cv::Size(5,5), 0);

        cv::Mat edges;
        cv::Canny(blurred, edges, 30, 100);

        cv::Mat kernel = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(3,3));

        cv::Mat closed;
        cv::dilate(edges, closed, kernel, cv::Point(-1,-1), 2);

        std::vector<std::vector<cv::Point>> contours;
        std::vector<cv::Vec4i> hierarchy;

        cv::findContours(closed, contours, hierarchy, cv::RETR_EXTERNAL, cv::CHAIN_APPROX_SIMPLE);

        cv::Mat result = frame.clone();
        int objCount = 0;
        for(int i = 0; i < contours.size(); i++){
            if(cv::contourArea(contours[i]) < 1000) continue;
            objCount++;

            cv::Rect box = cv::boundingRect(contours[i]); // this mean create bounding box around that object.
            cv::rectangle(result, box, cv::Scalar(0, 0, 255), 2);
            cv::putText(result, "Object" + std:: to_string(objCount) + "   "  "FPS:" + std::to_string((int) fps), cv::Point(box.x, box.y - 10), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,255,0), 1 );
        }
        cv::imshow("Detector", result);
        //cv::putText(frame, "FPS" + std::to_string((int)fps), cv::Point(20,40), cv::FONT_HERSHEY_SIMPLEX, 0.5, cv::Scalar(0,0,255), 2);
        
        //write to file
        writer.write(result);
        //cv::imshow("Camera", frame);
        if(cv::waitKey(1) == 27) break;
    }

    writer.release();
    cap.release();
    cv::destroyAllWindows();
    return 0;
}