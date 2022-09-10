//
// Created by KPY on 6/9/2022.
//

#pragma once
#include <iostream>
#include <vector>
#include <map>
#include <deque>
#include "speaker.h"
using namespace std;
#ifndef SPEACHTEST_SPEECHMANAGER_H
#define SPEACHTEST_SPEECHMANAGER_H

class SpeechManager{
public:

    //constructor
    SpeechManager();

    //展示菜单
    void show_Menu();

    //生成选手12个
    void createSpeaker();

    //开始比赛
    void startSpeech();

    //显示得分
    void showScore();

    //退出系统
    void exitSystem();

    //destructor
    ~SpeechManager();

    //init speech
    void initSpeech();

    //save result
    void saveRecord();

    //load history
    void loadRecord();

    //show record 
    void showRecord();



//private:

    //第一轮比赛选手编号
    vector<int> v1;
    //第二轮比赛选手编号
    vector<int> v2;
    //胜出前三名选手编号
    vector<int> vVictory;

    //历史记录
    map<int, vector<string> > m_Record;
    //文件是否为空
    bool fileIsEmpty;

    //比赛裁判数量
    int nJudje;

    //编号及对应选手
    map<int, Speaker> m_Speaker;

    //比赛轮数
    int m_Index;

    void SpeechDraw();

    void SpeechContest();




};
#endif //SPEACHTEST_SPEECHMANAGER_H
