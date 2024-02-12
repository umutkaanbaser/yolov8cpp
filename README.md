# Run yoloV8 in C++ | C++'da yolov8 nasıl çalıştırabiliriz ?
In this document, we looked at how we can run Yolov8 in the C++ environment. The <a href="https://github.com/umutkaanbaser/yolov8cpp/tree/main/include/inference">inference</a> codes used in this document were taken from the <a href="https://github.com/ultralytics/ultralytics">ultralytics repository</a>.

To run our model in the C++ environment, we first need to convert it to .onnx format.
```
yolo export model=yolov8n.pt format=onnx opset=12
```
veya
```python
from ultralytics import YOLO

model = YOLO("yolov8n.pt")  

path = model.export(format="onnx",opset=12)  
```

bu dökümanda yolov8'in c++ ortamında nasıl çalıştabiliriz ona baktık.
