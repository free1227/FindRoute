// sthNew.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include<iostream>

using namespace std;

int readfile(char ** const buff, const unsigned int spec, const char * const filename){
    FILE *fp;
    int i,Line,lineIndex;
    for(i=0;i<spec;i++){
        buff[i] = new char[20];
    }

    char *ori = "C:\\";
    char *result = (char*)malloc(strlen(ori)+strlen(filename)+1);//+1 for the zero-terminator   
    if (result == NULL) exit (1);
    strcpy(result, ori);  
    strcat(result, filename); 
    //cout<<result<<endl;

    if(!(fp = fopen(result,"r"))){
        cout<<"error"<<endl;
        exit(1);
    }else{
        Line = 0;
        lineIndex = 0;
        while(!feof(fp)){
            //fread(buff[Line],sizeof(char),20,fp);
            //buff[Line][20] = '\0';
            
            while((buff[Line][lineIndex] = fgetc(fp)) != 0x0a && buff[Line][lineIndex] != -1){
                lineIndex++;
            }
            buff[Line][lineIndex] = '\0';
            //cout<<buff[Line]<<endl;
            Line++;
            lineIndex=0;
        }
    }
    fclose(fp);
    return Line;
}

int readCondition(char ** const buff, const char * const filename){
    FILE *fp;
    *buff = new char[600];
    int i = 0;
    char *ori = "C:\\";
    char *result = (char*)malloc(strlen(ori)+strlen(filename)+1);//+1 for the zero-terminator   
    if (result == NULL) exit (1);
    strcpy(result, ori);  
    strcat(result, filename);
    if(!(fp = fopen(result,"r"))){
        cout<<"error"<<endl;
        exit(1);
    }else{
        while(!feof(fp)){
            buff[0][i] = fgetc(fp);
            i++;
        }
        buff[0][i-1] = '\0';
    }
    // cout<<buff[0]<<endl;
    fclose(fp);
    return i;
}


void time(const char * const head){
    time_t nowTime;
    if(!strcmp(head,"begin")){
        cout<<"begin"<<endl;
        time(&nowTime);
        cout<<ctime(&nowTime)<<endl;
    }else if(!strcmp(head,"end")){
        cout<<"end"<<endl;
        time(&nowTime);
        cout<<ctime(&nowTime)<<endl;
    }  
}

int _tmain(int argc, _TCHAR* argv[])
{
    time("begin");
    char *graph[5000];
    char *condition;
    int edge_num,condition_num;
    edge_num = readfile(graph,5000,"topo.csv");
    condition_num = readCondition(&condition,"demand.csv");
    search_route(graph, edge_num, condition);
    
    time("end");
    getch();
    return 0;
}


