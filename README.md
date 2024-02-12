# Run yoloV8 in C++ | C++'da yolov8 nasıl çalıştırabiliriz ?
In this document, we looked at how we can run Yolov8 in the C++ environment. The <a href="https://github.com/umutkaanbaser/yolov8cpp/tree/main/include/inference">inference</a> codes used in this document were taken from the <a href="https://github.com/ultralytics/ultralytics">ultralytics repository</a>. The sample video used was taken from <a href="https://www.pexels.com/video/video-of-famous-landmark-on-a-city-during-daytime-1721294/">pexel.com</a>.

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

Immediately afterwards, when we create a copy of the Inference class in our C++ coding, we declare its address.
```c++
 Inference inf("../model/yolov8n.onnx", cv::Size(640, 640), "", true); 
```
Here, right after declaring the address of our model, we state the input size of the model as the second variable. As the third variable, we declare the <b>classes</b> ('classes.txt') on which the model was trained. As the 4th variable, we mention <b>GPU usage</b> (true,false).

bu dökümanda yolov8'in c++ ortamında nasıl çalıştabiliriz ona baktık.
