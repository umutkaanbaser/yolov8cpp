#include <iostream>
#include <vector>
#include <getopt.h>

#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/core.hpp>

#include <inference.h>

using namespace std;
using namespace cv;

std::vector<Detection> detectImage(cv::Mat &img,Inference &model);

void drawDetections(cv::Mat &frame,std::vector<Detection> &Detections);

int main(int argc, char **argv)
{
    // yolo export model=yolov8n.pt format=onnx opset=12
    Inference inf("../model/yolov8n.onnx", cv::Size(640, 640), "", true);

    cv::String videoUrl = "../videos/example.mp4";

    cv::VideoCapture cap(videoUrl);

    cv::Mat frame;
    cv::Size showSize(640,480);
    bool state;
    for(;;){    
        state = cap.read(frame);
        if(!state) break;
        
        std::vector<Detection> detections = detectImage(frame,inf);
        drawDetections(frame,detections);
        

        cv::resize(frame,frame,showSize);
        cv::imshow("yolo-cpp", frame);
        char key = cv::waitKey(40);
        if(key == 'q') break;
    }
    
    cv::destroyAllWindows();
    cap.release();
    
}


std::vector<Detection> detectImage(cv::Mat &img,Inference &model){
    std::vector<Detection> output = model.runInference(img);
    return output;
        
}

void drawDetections(cv::Mat &img,std::vector<Detection> &Detections){
    for(Detection detection : Detections){
        cv::Rect box = detection.box;
        cv::Scalar color = detection.color;

        cv::rectangle(img, box, color, 2);
        std::string classString = detection.className + ' ' + std::to_string(detection.confidence).substr(0, 4);
        cv::Size textSize = cv::getTextSize(classString, cv::FONT_HERSHEY_DUPLEX, 1, 2, 0);
        cv::Rect textBox(box.x, box.y - 40, textSize.width + 10, textSize.height + 20);
        cv::putText(img, classString, cv::Point(box.x + 5, box.y - 10), cv::FONT_HERSHEY_DUPLEX, 1, color, 3, 0);
    }

}