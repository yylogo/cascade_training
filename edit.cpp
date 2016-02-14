#include <opencv2/opencv.hpp>
#include <stdio.h>
#include "sub_str.h"

using namespace cv;
using namespace std;

/* 参数 */
#define ITER_MAX 2000
const Size max_size(1280, 720);

/* 全局传递变量 */
bool pass_select_mark = 0;
Rect pass_select_box;

/* 全局变量 */
string file_name;
Mat img_source, img_print;
Size img_size, new_size(0, 0);
vector<vector<Rect> > img_boxes;

/* 主要程序 */
void para_init();
void iter_img();

/* 辅助子程序 */
void on_mouse(int event, int x, int y, int flags, void* userdata);
Mat open_image(int id);
char *get_image_name(int id);

/* 功能子函数 */
void save_to_file(int id);


int main(void) {
    para_init();
    namedWindow("Select");
    setMouseCallback("Select", on_mouse);
    iter_img();
}

void iter_img() {
    vector<Rect> boxes;
    for (int i = 1; i <= ITER_MAX; ++i) {
        boxes.clear();
        img_source = open_image(i);
        img_print = img_source.clone();
        imshow("Select", img_print);
        cout << "正在处理第" << i << "副图像" << endl;
        cout << "（输入回车确定，输入R重置目标框）" << endl;
        while(1){
            int ch = waitKey(200);
            //回车检测
            if(ch == 1048586){
                break;
            }
            //r输入检测
            if(ch == 1048690){
                boxes.clear();
                img_print = img_source.clone();
                imshow("Select", img_print);
            }
            if(ch == 1048696){
                exit(0);
            }
            if(pass_select_mark){
                pass_select_mark = 0;
                boxes.push_back(pass_select_box);
                rectangle(img_print, pass_select_box, Scalar(0, 0, 255));
            }
        }//while(1) 的结束
        img_boxes.push_back(boxes);
        save_to_file(i);
    }
}

void save_to_file(int id) {
    string str_tmp = get_image_name(id), str_new = "";
    vector<string> str_vec;
    str_vec = split(str_tmp, '.');
    for (int i = 0; i < ((int)str_vec.size()) - 1; ++i) {
        if(i != 0){
            str_new += ".";
        }
        str_new += str_vec[i];
    }
    str_new += "new.";
    str_new += str_vec[str_vec.size() - 1];
    imwrite(str_new, img_source(img_boxes[id - 1][0]));
    //写入图片文件
    //写入info文件
}

void para_init() {
    cout << "准备数据的辅助程序：" << endl;
    cout << "输入图片名字（printf的格式）：" << endl;
    //cin >> file_name;
    file_name = "data/img%d.jpg";
    cout << file_name << endl;
    Mat tmp = open_image(1);
    new_size = img_size = tmp.size();
    if(img_size.height >= max_size.height){
        new_size.height = max_size.height;
        new_size.width = max_size.height * img_size.width / img_size.height;
    }else if(img_size.width >= max_size.width){
        new_size.width = max_size.width;
        new_size.height = max_size.width * img_size.height / img_size.width;
    }
}

char *get_image_name(int id){
    static char str[50];
    sprintf(str, file_name.c_str(), id);
    return str;
}

Mat open_image(int id) {
    Mat pic;
    char *str = get_image_name(id);
    pic = imread(str);
    if(pic.empty()){
        cout << "The image " << str << " open failed. " << endl;
    }
    if(new_size.width != 0){
        resize(pic, pic, new_size);
    }
    return pic;
}

void on_mouse(int event, int x, int y, int flags, void* userdata)
{
    static int px, py;
    static bool selected = 0;
    if(selected){
        Rect rec(Point(x, y), Point(px, py));
        Mat temp = img_print.clone();
        rectangle(temp, rec, Scalar(0, 0, 255));
        imshow("Select", temp);
    }
    if(event == CV_EVENT_LBUTTONDOWN){
        selected = 1;
        px = x, py = y;
    }else if(event == CV_EVENT_LBUTTONUP){
        selected = 0;

        /* 全局传递 */
        pass_select_mark = true;
        pass_select_box = Rect(Point(x, y), Point(px, py));
    }
}
