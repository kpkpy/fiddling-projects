//
// Created by KPY on 6/9/2022.
//
#include "speechManager.h"
#include <iostream>
#include <fstream>
#include <ios>
#include <algorithm>
#include <math.h>
#include <unistd.h>
#include <numeric>

SpeechManager::SpeechManager() {
    //constructor

    initSpeech();

    createSpeaker();

    nJudje = 10;

    //load history
    loadRecord();
}

SpeechManager::~SpeechManager() {

}

void SpeechManager::startSpeech(){
    //第一轮比赛
    //1. 抽签
    SpeechDraw();

    //2. 比赛
    SpeechContest();

    //3. 显示晋级结果
    showScore();

    //第二轮比赛
    m_Index++;
    //1. 抽签
    SpeechDraw();
    //2. 比赛
    SpeechContest();
    //3. 显示最终结果
    showScore();
    //4. 保存分数
    saveRecord();

    cout<< "contest done" << endl;
}

void SpeechManager::show_Menu() {
    cout << "***************************" << endl;
    cout << "****** Welcome! ***********" << endl;
    cout << "****** 1. Start ***********" << endl;
    cout << "****** 2. History *********" << endl;
    cout << "****** 3. Clear ***********" << endl;
    cout << "****** 0. Quit ************" << endl;
    cout << "***************************" << endl;
    cout << endl;
}

void SpeechManager::initSpeech(){
    //保证所用到的容器为空
    v1.clear();
    v2.clear();
    vVictory.clear();
    m_Speaker.clear();

    m_Index = 1;
}

void SpeechManager::createSpeaker(){
    string nameSeed = "ABCDEFGHIJKL";
    for(int i=0; i< nameSeed.size(); i++){
        string name = "选手";
        name += nameSeed[i];

        Speaker sp;
        sp.m_Name = name;

        for(int j=0; j<2; j++){
            sp.m_Score[j] = 0;
        }

    //创建选手编号 加入v1
    this->v1.push_back(i+10001);

    //选手编号 和对应选手
    m_Speaker.insert(make_pair(i+10001, sp));
    
    }
}

void SpeechManager::exitSystem() {
    cout << "Exiting System" << endl;
    exit(0);
}

void SpeechManager::SpeechDraw() {
    cout << "第 " << this->m_Index << " 轮比赛正在抽签" << endl;
    cout << "---------------------" << endl;
    cout << "演讲顺序如下" << endl;
    if(this->m_Index == 1){ // 第一轮比赛
        random_shuffle(v1.begin(), v1.end());
        for(vector<int>::iterator it = v1.begin(); it!=v1.end(); it++){
            cout << *it << " " ;
        }
        cout << endl;
    }
    else{//第二轮比赛
        random_shuffle(v2.begin(), v2.end());
        for(vector<int>::iterator it = v2.begin(); it!=v2.end(); it++) {
            cout << *it << " " ;
        }
        cout << endl;
    }
    cout << "---------------------" << endl;

}

void SpeechManager::SpeechContest(){
    cout << "------第 " << m_Index << " 轮比赛开始--------" << endl;

    //小组容器
    multimap<double, int, greater<double> > groupScore;

    //记录一组人的数量
    int num =0 ;

    vector<int> v_Src;//比赛人员

    //判断第几轮
    if(this->m_Index==1){
        v_Src = v1;
    }
    else{
        v_Src = v2;
    }

    
    for(vector<int>::iterator it=v_Src.begin(); it!=v_Src.end(); it++){

        num++;

        deque<double> d;
        for(int i=0; i<nJudje; i++){
            //用随机数模拟得分
            double score = (rand()%401+600) /10.f;//random int between 600 - 1000
            //cout << score << " "; 
            d.push_back(score);
        }
        //cout <<endl;

        sort(d.begin(), d.end(), greater<double>()); // sort scores of nJudje
        d.pop_back();
        d.pop_front();

        double sum = accumulate(d.begin(), d.end(), 0.0f);
        double avg = sum/ double(d.size());
        

        this->m_Speaker[*it].m_Score[m_Index-1] = avg;

        //cout << "编号" << *it << "姓名" << this->m_Speaker[*it].m_Name << "平均分" << this->m_Speaker[*it].m_Score[0] << endl;

        //选出优胜
        //6人一组, 暂存容器
        groupScore.insert(make_pair(avg, *it)); //key: score , value : speaker number
        if(num % 6 ==0){
            cout << "第 " << num/6 << " 组比赛名次" << endl; 
            for(multimap<double, int , greater<double> >::iterator it= groupScore.begin(); it !=groupScore.end(); it++){
                cout << "number: " << it->second << "name" << this->m_Speaker[it->second].m_Name << "avg:" <<  this->m_Speaker[it->second].m_Score[this->m_Index-1] << endl;
            }

            int count = 0;
            for(multimap<double, int, greater<double> >::iterator it = groupScore.begin(); it!=groupScore.end()&&count<3; it++, count++){
                if(this->m_Index==1){
                    v2.push_back((*it).second);
                }
                else{
                    vVictory.push_back((*it).second);
                }
            }
            cout << "第" << m_Index << " 轮比赛完毕" << endl; 
            groupScore.clear();
        }
    }
cout << endl;
}

void SpeechManager::showScore(){
    cout << "-----" << m_Index <<"轮比赛结果-----" << endl;
    vector<int> v;
    if(this->m_Index==1){
        v = v2;
    }
    else{
        v = vVictory;
    }

    for(vector<int>::iterator it = v.begin(); it!=v.end(); it++){
        cout << "选手编号" << *it << "姓名 " << this->m_Speaker[*it].m_Name << "得分 " << this->m_Speaker[*it].m_Score[this->m_Index-1] << endl;
    }
}

void SpeechManager::saveRecord(){
    ofstream ofs;
    ofs.open("speech.csv", ios::out|ios::app); //打开 | 追加

    for(vector<int>::iterator it = vVictory.begin(); it!=vVictory.end(); it++){
        ofs << *it << "," << this->m_Speaker[*it].m_Score[1] << ",";
    }
    ofs << endl;
    ofs.close();
    cout << "file saved" << endl;
    fileIsEmpty = false;
}

void SpeechManager::loadRecord(){
    ifstream ifs("speech.csv", ios::in);
    if(!ifs.is_open()){
        this->fileIsEmpty = true;
        cout << "file not exists" << endl;
        return ;
    }

    //文件清空
    char ch; 
    ifs >> ch;
    if(ifs.eof()){
        cout << "file is empty" << endl;
        fileIsEmpty = true;
        return ;
    }

    //文件不为空
    fileIsEmpty = false;
    ifs.putback(ch);
    string data;
    while(ifs>>data){
        //10005,83.6125,10007,82.7375,10008,80.725
        //cout << data << endl;
        vector<string> v;
        int start = 0;
        int index = 0;
        int pos = -1;
        while(true){
            pos = data.find(",", start);
            if(pos == -1){
                //not find;
                break;
            }
            string tmp = data.substr(start, pos - start);
            //cout << tmp << endl;
            v.push_back(tmp);
            
            start = pos +1;
        }
        this->m_Record.insert(make_pair(index, v));
        index ++;
    }
    ifs.close();
//    for(map<int, vector<string> >::iterator it = m_Record.begin(); it != m_Record.end(); it++){
//        cout << it->first << " 冠军编号 " << it->second[0] << " 分数 " << it->second[1] << endl;
//    }
}

void SpeechManager::showRecord(){
    if(this->fileIsEmpty) cout << "file empty";
    for(int i=0; i<this->m_Record.size(); i++){
        cout << "第" << i+1 << "届冠军编号" << m_Record[i][0]<< " 均分 " << m_Record[i][1] << "   ";
        cout << "第" << i+1 << "届亚军编号" << m_Record[i][2]<< " 均分 " << m_Record[i][3] << "   ";
        cout << "第" << i+1 << "届季军编号" << m_Record[i][4]<< " 均分 " << m_Record[i][5] << "   ";
        cout << endl;
    }
}