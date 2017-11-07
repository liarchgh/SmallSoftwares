#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <dirent.h>
#include <sys/stat.h>
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>
#include <fstream>

using namespace std;


int main() {
    printf("please write the path:\n");
    string path = "D:/Video/cartoon/ff";
    cin >> path;
    cout << path << endl;
    dirent *dd = readPath(path);
    while(!strcmp(dd->d_name, ".") || !strcmp(dd->d_name, "..")) {
        dd = readdir(dir);
    }

    //将第0层目录下的所有文件和目录文件存入root（一般只有目录文件）
    vector<string>root;
    while(dd) {
        root.push_back(dd->d_name);
        dd = readdir(dir);
    }
    //对目录进行排序 确定视频文件的文件名
    sort(root.begin(), root.end());
    for(int i = 0; i < root.size(); ++i) {
    //th1path是第1级目录 这里面有lua。。。文件夹需要进去
        string th1path = path + "/" + root[i];
        dirent * th1 = readPath(th1path);
        while(th1) {
            //进入到第1级目录
            //去除.和..
            while(!strcmp(th1->d_name, ".") || !strcmp(th1->d_name, "..")) {
                th1 = readdir(td);
            }
            //th1是当前第1级目录下的文件内容 若当前不是目录文件 th2path是第2级目录的路径
            string th2path = th1path + "/" + th1->d_name;
            string forVid = th1->d_name;
            string video;
            for(int i = 0; i < forVid.size(); ++i){
                if(forVid[i] == '.'){
                    ++i;
                    video.clear();
                    for(; forVid[i] != '.' && i < forVid.size(); ++i){
                        video = video + forVid[i];
                    }
                    break;
                }
            }
            dir = opendir(&th2path[0]);
            dd = readdir(dir);
            //若当前的第2级目录打开失败 则遍历第1级目录下的其他文件
            if(!dd){
                th1 = readdir(td);
                continue;
            }
            //第2级目录的路径拿到手 开始遍历之下的视频文件
            for(int j = 0; j < 4; ++j) {
                //now是当前要操作的文件的路径
                string now = th2path + "/";
                stringstream all;
                all << now << j << "." << video;
                now = all.str();
                cout << now << endl;

                //先测试 再打开当前文件
                ifstream file;
                file.open(&now[0]);
                if(file.good()) {
                    //若不关闭 之后无法移动
                    file.close();
                    //清空all
                    all.str("");
                    all << path + "/";
                    //补全文件名 方便播放器自动下一集
                    if(i < 10) {
                        all << "0";
                    }
                    all << i << j << "." << video;
                    string en;
                    en = all.str();
                    char * p1 = &now[0];
                    char * p2 = &en[0];
                    puts(p1);
                    puts(p2);
                    rename(p1, p2);
                } else {
                    file.close();
                }
            }
            break;
        }
    }
    return 0;
}

dirent * readPath(string path){
    DIR* td = opendir(&path[0]);
    return readdir(td);
}

/*
*/
