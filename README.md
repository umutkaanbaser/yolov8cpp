# Run yoloV8 in C++ | C++'da yoloV8 nasıl çalışır
In this document, we looked at how we can run Yolov8 in the C++ environment. The <a href="https://github.com/umutkaanbaser/yolov8cpp/tree/main/include/inference">inference</a> codes used in this document were taken from the <a href="https://github.com/ultralytics/ultralytics">ultralytics repository</a>. The sample video used was taken from <a href="https://www.pexels.com/video/video-of-famous-landmark-on-a-city-during-daytime-1721294/">pexel.com</a>.

Bu belgemizde Yolov8'i C++ ortamında nasıl çalıştırabileceğimize baktık. Bu belgede kullanılan <a href="https://github.com/umutkaanbaser/yolov8cpp/tree/main/include/inference">inference</a> kodları <a href="https://www.github.com/ultralytics/ultralytics">ultralytics deposu</a> adresinden alınmıştır ve Kullanılan örnek video <a href="https://www.pexels.com/video/video-of-famous-landmark-on-a-city-during-daytime-1721294/">pexel.com </a> adresinden alınmıştır.

### How to Run | Nasıl Çalıştırılır 
You can use yolov8 in c++ with this project architecture.

Bu proje mimarisini kendi yolov8 projelerinizde kullanabilirsiniz.
```
mkdir build && cd build
cmake ..
make
./yolo_cpp
```

### 1. Convert To .onnx | .onnx'e Dönüştür
To run yolov8 model in the C++ environment, we first need to convert it to .onnx format.

yolov8 modelini C++ ortamında kullanmak için öncelikle .onnx biçimine dönüştürmemiz gerekmektedir.
```
yolo export model=yolov8n.pt format=onnx opset=12
```
or | yada
```python
from ultralytics import YOLO

model = YOLO("yolov8n.pt")  

path = model.export(format="onnx",opset=12)  
```

### 2. Create a copy from Inference | Inference'dan Bir Kopya Oluştur
Immediately afterwards, when we create a copy of the Inference class in our C++ coding, we declare .onnx address.

Hemen ardından oluşturuğumuz .onnx dosyasının adresini, Inference'dan bir kopya oluşturup içine veririz. 
```c++
 Inference inf("../model/yolov8n.onnx", cv::Size(640, 640), "", true); 
```
Here, right after declaring the address of our model, we state the input size of the model as the second variable with <b><i>cv::Size</i></b>. <br/>
As the third variable, we declare the <b><i>classes</i></b> ('classes.txt') on which the model was trained.<br/>
As the 4th variable, we mention <b><i>GPU usage</i></b> (true,false). <br/>


Burada modelimizin adresini belirledikten hemen sonra <b><i>cv::Size</i></b> ile ikinci değişken olarak modelin giriş boyutunu belirtiyoruz. <br/>
Üçüncü değişken olarak modelin eğitildiği <b><i>sınıfları</i></b> ('classes.txt') bildiririz.<br/>
4. değişken olarak <b><i>GPU kullanımından</i></b> (doğru, yanlış) bahsediyoruz. <br/>

### 3. Run Model | Modeli Çalıştır
We ran our model under the detectImage function. The Inference class runs the  model with opencv and converts the tensor output into understandable values, just like in Python.

Modelimizi DetectImage fonksiyonu altında çalıştırdık. Inference sınıfı, modeli opencv ile çalıştırır ve tıpkı Python'da olduğu gibi tensör çıktısını anlaşılır değerlere dönüştürür.
```c++
std::vector<Detection> detectImage(cv::Mat &img,Inference &model){
    std::vector<Detection> output = model.runInference(img);
    return output;    
}
```
The <i><b>runInference</b></i> method takes a cv::Mat object into it. Then, <i><b>Detection</b></i> class list is returned as output. Detection contains information such as box, confidence, class within the class.

<i><b>runInference</b></i> yöntemi, içine bir cv::Mat nesnesi alır. Daha sonra çıktı olarak <i><b>Detection</b></i> sınıf listesi döndürülür. Detection, sınıf içindeki box, confidence, class gibi bilgileri içerir.

### 4. Get Results | Sonuçları Alma
Inference converts OpenCV's tensor output into a Detection object that we can use more easily.

Inference, OpenCV'nin tensör çıktısını daha kolay kullanabileceğimiz bir Detection nesnesine dönüştürür.
```c++
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
```
We draw the results we obtained with the drawDetections function on our image.

DrawDetections fonksiyonu ile elde ettiğimiz sonuçları imajımızın üzerine çiziyoruz.

### Change Class List | Class Dizisini Değiştirme
In the inference.h file, the classes vector is found on line 39. You can enter your classes here. Or you can empty this vector completely and declare it with a .txt file when creating a copy.

inference.h dosyasında 39. satırda sınıflar vektörü bulunmaktadır. Sınıflarınızı buraya girebilirsiniz. Veya kopya oluştururken bu vektörü tamamen boşaltıp .txt dosyasıyla bildirebilirsiniz.
```c++
std::vector<std::string> classes{"person", "bicycle", "car", "motorcycle", .... # you can change this vector.
```
or
```c++
// in inference.h
std::vector<std::string> classes{}; # set this vector empty. And give class text file adress to Inference initilazer.

// in main.cpp
Inference inf("../model/yolov8n.onnx", cv::Size(640, 640), "../model/classes.txt", true); 
```

