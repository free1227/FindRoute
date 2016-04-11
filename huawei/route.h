

#define Edge_MAX 5000
void search_route(char *graph[5000], int edge_num, char *condition);

void makelimRoute(char ** const buff,int edgeNum,char *limitRoute);

bool checkCond(char ** const buff,int edgeNum,char* condition,int deep);

bool existPointToEnd(char ** const buff,int edgeNum,int End);

int delOnlyInOut(char ** const buff,int edgeNum,int Start,int End);

int delPoint(char ** const buff,int edgeNum,int point,bool noOut);

int filterMore(char ** const existRoute,int routeNum,char ** const buff,int edgeNum,int End);

bool overLW(char ** const buff,int edgeNum,int least);

bool isMember(int point,char * condition);

int getLimitNum(char * limitRoute);

int insertRoute(char ** const buff,int edgeNum,char *edge,bool order);

int getConditionNum(char *condition);

void deleteBuffer(char ** const buff,int edgeNum,int index,bool order);

void printEdge(char ** const buff,int edgeNum,char * describe);

int edgeOutorIn(char ** const tarArr,char ** const buff,int edgeNum,int point,bool out);

int getThatArea(char *tarStr,int pos);

int findLay(char ** routeList,int routeNum,char ** const buff,int edgeNum,int Start,char* limitRoute,int limitWeight,char* condition,bool* limitFlag);

int findRoute(char ** const realR,int * realN,char ** const tempR,int tempN,char ** const buff,int edgeNum,char * condition,int Start,int deep,int *times);

int filterInit(char ** const buff,int edgeNum,int start,int end);