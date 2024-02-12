# Run yoloV8 in C++ 
In this document, we looked at how we can run Yolov8 in the C++ environment. The <a href="https://github.com/umutkaanbaser/yolov8cpp/tree/main/include/inference">inference</a> codes used in this document were taken from the <a href="https://github.com/ultralytics/ultralytics">ultralytics repository</a>. The sample video used was taken from <a href="https://www.pexels.com/video/video-of-famous-landmark-on-a-city-during-daytime-1721294/">pexel.com</a>.

### 1. Convert To .onnx
To run our model in the C++ environment, we first need to convert it to .onnx format.
```
yolo export model=yolov8n.pt format=onnx opset=12
```
or
```python
from ultralytics import YOLO

model = YOLO("yolov8n.pt")  

path = model.export(format="onnx",opset=12)  
```

### 2. Create a copy from Inference
Immediately afterwards, when we create a copy of the Inference class in our C++ coding, we declare its address.
```c++
 Inference inf("../model/yolov8n.onnx", cv::Size(640, 640), "", true); 
```
Here, right after declaring the address of our model, we state the input size of the model as the second variable with <b><i>cv::Size</i></b>. <br/>
As the third variable, we declare the <b><i>classes</i></b> ('classes.txt') on which the model was trained.<br/>
As the 4th variable, we mention <b><i>GPU usage</i></b> (true,false). <br/>

### 3. Run Model
We ran our model under the detectImage function. The Inference class runs the  model with opencv and converts the tensor output into understandable values, just like in Python.
```c++
std::vector<Detection> detectImage(cv::Mat &img,Inference &model){
    std::vector<Detection> output = model.runInference(img);
    return output;    
}
```
The <i><b>runInference</b></i> method takes a cv::Mat object into it. Then, <i><b>Detection</b></i> class list is returned as output. Detection contains information such as box, confidence, class within the class.
