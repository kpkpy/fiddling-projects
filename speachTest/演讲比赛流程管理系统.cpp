//
// Created by KPY on 6/9/2022.
//
#include <iostream>
using namespace  std;
#include <unistd.h>
#include "speechManager.h"

#ifndef DEBUG
//#define DEBUG

int main(){

    SpeechManager sm;

    #ifdef DEBUG
    for(map<int, Speaker>::iterator it = sm.m_Speaker.begin(); it!=sm.m_Speaker.end(); it++){
        cout << "**: " << it->first << "name: " << it->second.m_Name << "score: " << it->second.m_Score[0] << endl;
    }
    #endif

    sm.show_Menu();

    int choice = 0;//user input

    while(true){

        sm.show_Menu();

        cout << endl;
        cout << ">: " ;
        cin >> choice;

        switch (choice)
        {
        case 1: //start
            sm.startSpeech();
            break;
        case 2: //history
            sm.showRecord();
            break;
        case 3: // clear
            
            break;
        case 0: // quit
            sm.exitSystem();
            break;
        default:
            system("clear");
            break;
        }
        choice = 0;
    }
    return 0;
    cout << "hello world!" << endl;
}

#endif