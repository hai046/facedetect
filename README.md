# facedetect

###所在环境

Mac OSX  
eclipse CDT   
Xcode 



###,install

```
sudo port install opencv
```

header file 在目录**/opt/local/include**下，导入include 到工程中


###生成正样本图片

`test_facedetect.cpp#makeFacedetect` 
```c++
/**
 * 检索图片目录 path    然后根据现有的模型 cascadeName 识别出人脸，并建立正样本的描述文件  格式是 fileName num  x y w h x2 y2 w2 h2 ……【具体定义可以查官方文档】
 */
int makeFacedetect(string cascadeName, string path, string saveFilePath);
```


###生成xml文件

```shell
#!/usr/bin/env bash


NUM=`cat info.txt|wc -l`
echo $NUM

rm -rf vec.vec

#生成vec文件
opencv_createsamples -info info.txt -vec vec.vec -num $NUM   -bg bg.txt  



echo ""
echo ""
echo "traincascade……"
rm -rf opecv_data



#for i in $(seq 1  $NUM);do
#	echo "bodybg.png">>bg.txt
#done

mkdir opecv_data

#开始训练并在opecv_data目录下生成cascade.xml 文件
opencv_traincascade -data opecv_data -vec vec.vec -bg bg.txt  -numPos 200 -numNeg 100  -numStages  10  

```








