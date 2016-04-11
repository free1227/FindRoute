#include "stdafx.h"
#include <iostream>

using namespace std;


void search_route(char *graph[Edge_MAX], int edge_num, char *condition){
	
	int Start = atoi(condition);
	int End = getThatArea(condition,1);
	
	//�����ռ�
	char *lessGraph[4800];
	int lessEdgeNum = 0;
	//���Ž����
	char *realResult[4800];
	int *realEdge = new int(0);
	//��ʱ�����
	char *tempResult[4800];
	int tempEdge = 0;
	//��Ѱ����
	int *findTimes = new int(10);
	//�ݹ�����
	int deep = 0;
	int i = 0;
	//��ʼ��
	for(i=0;i<4800;i++){
		realResult[i] = new char[20];
		tempResult[i] = new char[20];
	}

	deep = getConditionNum(condition);

	//cout<<"Start:"<<Start<<"End:"<<End<<endl;
	lessEdgeNum =  filterInit(graph,edge_num,Start,End);
	for(i=0;i<lessEdgeNum;i++){
		lessGraph[i] = graph[i];
	}
	//printEdge(lessGraph,lessEdgeNum,"���˵������յ㲻���ʵĵ�");
	findRoute(realResult,realEdge,tempResult,tempEdge,lessGraph,lessEdgeNum,condition,Start,deep,findTimes);
	printEdge(realResult,*realEdge,"�����Ϊ��");
	//for(i=0;i<*realEdge;i++){
	//	record_result(getThatArea(realResult[i],0));
	//}
	//�����ڴ�
	for(i=0;i<4800;i++){
		delete realResult[i];
		delete tempResult[i];
	}
}
/******************�߼�����*****************/

/*******************************************
���ܣ�ɾ��start�ĳ�����end����ߣ�ɾ���ر߱���Ȩ����С
�Ľ�������
����Ӷȣ�buff������*��ĸ���
*******************************************/
int filterInit(char ** const buff,int edgeNum,int start,int end){
	int Pointer1 = 0,Pointer2 = 0;
	//int *pointArr = new int[600];
	int *pointArr = (int*)malloc(sizeof(int)*600);
	int arrLen = 0;
	int aStart = 0,aEnd = 0;
	int existStart = 0,existEnd = 0;
	int outEdge = 0;
	char *edgeList[10];
	int i = 0,j = 0;
	while(Pointer1 < edgeNum){
		aStart = getThatArea(buff[Pointer1],1);
		aEnd = getThatArea(buff[Pointer1],2);
		if(aStart == end || aEnd == start || aStart == aEnd){
			Pointer2--;
		}else{
			for(i=0;i<arrLen;i++){
				if(pointArr[i] == aStart && existStart != 1){
					existStart = 1;
				}
				if(pointArr[i] == aEnd){
					existEnd = 1;
				}
			}
			if(existStart == 0){
				pointArr[arrLen] = aStart;
				arrLen++;
			}
			if(existEnd == 0){
				pointArr[arrLen] = aEnd;
				arrLen++;
			}
			existStart = 0;
			existEnd = 0;
		}
		Pointer1++;
		Pointer2++;
		buff[Pointer2] = buff[Pointer1];
	}
	Pointer1 = 0;
	edgeNum = Pointer2;
	while(Pointer1 < arrLen){
		outEdge = edgeOutorIn(edgeList,buff,edgeNum,pointArr[Pointer1],true);
		for(i=0;i<outEdge-1;i++){
			for(j=i+1;j<outEdge;j++){
				if(getThatArea(edgeList[i],2) == getThatArea(edgeList[j],2)){
                    getThatArea(edgeList[i],3) > getThatArea(edgeList[j],3) ? deleteBuffer(buff,edgeNum,getThatArea(edgeList[i],0),false) : deleteBuffer(buff,edgeNum,getThatArea(edgeList[j],0),false);
                    edgeNum--;
                }
			}
		}
		Pointer1++;
	}
	delete []pointArr;
	return edgeNum;
}
/*******************************************
���ܣ��ҵ�һ����·��
�Ľ�������
����Ӷȣ�����������
*******************************************/
int findRoute(char ** const realR,int * realN,char ** const tempR,int tempN,char ** const buff,int edgeNum,char * condition,int Start,int deep,int *times){
	//�յ�
	int End = getThatArea(condition,1);
	//����,���ڻ�ԭ
	char *backupBuff[4800];
	int backupEdgeNum = edgeNum;
	//����·����
	char *limitRoute = new char[1000];
	//����·���Ƿ��߹�
	bool *limitFlag = new bool;
	//һ���·����
	char *routeList[600];
	//��һ�����ķ��أ���Ϊ-1��Ϊ�ߵĸ���
	int nextLayResult = -1;
	//�ݹ����ķ���
	int recursiveReturn = -1;
	//�жϹ��˺�·����
	bool judgeFlag = false;
	//��ʱ�������Ȩ������ʵ�������Ȩ��
	int realW = 0,tempW = 0;
	//��һ�����
	int nextStart = 0;
	//deepΪ1ʱ�޸�condition��
	char *finalCondition = new char[20];
	//��֮�ж�
	int godWeight = 0;
	int i = 0;
	char changeStr[5];
	//��ʼ��
	strcpy(limitRoute,"");
	*limitFlag = true;
	//��buff������
	for(i=0;i<backupEdgeNum;i++){
		backupBuff[i] = new char[20];
		strcpy(backupBuff[i],buff[i]);
	}

	while(recursiveReturn == -1){
		//strcpy(limitRoute,"0,13,40,9");
		if(strlen(limitRoute) > 0){
			*limitFlag = false;
		}
		nextLayResult =  findLay(routeList,0,buff,edgeNum,Start,limitRoute,50000,condition,limitFlag);

		if(nextLayResult < 550 && nextLayResult > 0){

			//cout<<deep<<"�����·��";
			//printEdge(routeList,nextLayResult,"");
			
			if(deep != 0){
				edgeNum = filterMore(routeList,nextLayResult,buff,edgeNum,End);
				//printEdge(buff,edgeNum,"���˺��·����Ϊ��");

				if(edgeNum > 0){
					//�жϹ��˺��·�����Ƿ�������
					judgeFlag = existPointToEnd(buff,edgeNum,End) && checkCond(buff,edgeNum,condition,deep);
				}else{
					judgeFlag = false;
				}
				if(!judgeFlag){
					//�������Ƽ�
					makelimRoute(routeList,nextLayResult,limitRoute);

					for(i=0;i<backupEdgeNum;i++){
						buff[i] = backupBuff[i];
					}
					edgeNum = backupEdgeNum;

					continue;
				}else{
					//ֱ�����ӵ���ʱ�洢����
					for(i=0;i<nextLayResult;i++){
						//tempR[i+tempN] = routeList[i];
						strcpy(tempR[i+tempN],routeList[i]);
					}
					tempN += nextLayResult;
					//��ȡ��һ�����
					nextStart = getThatArea(routeList[i-1],2);

					//��Ȩ����һ����֮�ж�
					godWeight = 0;
					for(i=0;i<tempN;i++){
						godWeight += getThatArea(tempR[i],3);
						if(godWeight > 600){
							//�����ڴ�
							for(i=0;i<backupEdgeNum;i++){
								delete backupBuff[i];
							}			
							delete []limitRoute;
							delete []finalCondition;
							delete limitFlag;
							return -1;
						}
					}
					
					if(deep != 1){
						recursiveReturn = findRoute(realR,realN,tempR,tempN,buff,edgeNum,condition,nextStart,deep-1,times);
					}else{
						strcpy(finalCondition,"");
						//sprintf(changeStr,"%d",nextStart);
						_snprintf(changeStr,5,"%d",nextStart);
                        strcat(finalCondition,changeStr);
                        strcat(finalCondition,",");
                        //sprintf(changeStr,"%d",End);
						_snprintf(changeStr,5,"%d",End);
                        strcat(finalCondition,changeStr);
                        strcat(finalCondition,",");
                        //sprintf(changeStr,"%d",End);
						_snprintf(changeStr,5,"%d",End);
                        strcat(finalCondition,changeStr);
                        recursiveReturn = findRoute(realR,realN,tempR,tempN,buff,edgeNum,finalCondition,nextStart,deep-1,times);
					}

					if(recursiveReturn == -1){
						tempN = tempN - nextLayResult;
						makelimRoute(routeList,nextLayResult,limitRoute);
						for(i=0;i<backupEdgeNum;i++){
							buff[i] = backupBuff[i];
						}
						edgeNum = backupEdgeNum;

						continue;
					}
				}
			}else{
				//ֱ�����ӵ���ʱ�洢����
				for(i=0;i<nextLayResult;i++){
					//tempR[i+tempN] = routeList[i];
					strcpy(tempR[i+tempN],routeList[i]);
				}
				tempN += nextLayResult;
				//ת�浽�����
				if(*realN == 0){
					for(i=0;i<tempN;i++){
						//realR[i] = tempR[i];
						strcpy(realR[i],tempR[i]);
					}
					*realN = tempN;
				}else{
					realW = 0;
					for(i=0;i<*realN;i++){
						realW += getThatArea(realR[i],3);
					}
					tempW = 0;
					for(i=0;i<tempN;i++){
						tempW += getThatArea(tempR[i],3);
					}
					if(realW > tempW){
						for(i=0;i<tempN;i++){
							//realR[i] = tempR[i];
							strcpy(realR[i],tempR[i]);
						}
						*realN = tempN;
					}
				}

				if(*times == 0){
					//�����ڴ�
					for(i=0;i<backupEdgeNum;i++){
						delete backupBuff[i];
					}			
					delete []limitRoute;
					delete []finalCondition;
					delete limitFlag;
					return *realN;
				}else{
					*times = *times - 1;
					//�����ڴ�
					for(i=0;i<backupEdgeNum;i++){
						delete backupBuff[i];
					}			
					delete []limitRoute;
					delete []finalCondition;
					delete limitFlag;
					return -1;
				}
			}
			

			//�����ڴ�
			for(i=0;i<backupEdgeNum;i++){
				delete backupBuff[i];
			}			
			delete []limitRoute;
			delete []finalCondition;
			delete limitFlag;
			return 0;
		}else{
			//cout<<"NA"<<endl;
			//�����ڴ�
			for(i=0;i<backupEdgeNum;i++){
				delete backupBuff[i];
			}
			delete []limitRoute;
			delete []finalCondition;
			delete limitFlag;
			return -1;
		}
	}
	return recursiveReturn;
}
/*******************************************
���ܣ��ֲ������ҵ�start��condition�����·��
�Ľ����㷨
����Ӷȣ��㲻����
*******************************************/
int findLay(char ** routeList,int routeNum,char ** const buff,int edgeNum,int Start,char* limitRoute,int limitWeight,char* condition,bool* limitFlag){
	//���֧
	char *branch[8];
	//���֧��
	int branchNum = 0;
	//���֧Ȩ��
	int branWeightArr[8];
	//�ϵ���ת�������ӽڵ���������ʱ��
	int godJump = 0;
	//��ǰ��֧�յ�
	int curPoint = 0;
	//�����ߵ���СȨ��
	int leastWeight = 0;
	//Ҳ�Ǳ����ߵ���СȨ��
	int deepNeedWeight = 0;
	//��֧Ȩ�ز�
	int diffWeight = 0;
	//limitRoute���д˲�ĵ�
	int limOfLay = 0;
	//��һ�㷵��ֵ
	int nextLayreturn = 0;
	int i = 0,j = 0,k = 0;
	char changeStr[5];
	int tempNum = 0;
	char *tempChar = NULL;
	//����limitRoute
	char *nextLayLimit = new char[1000];
	char *backupLayLimit = new char[1000];
	//��ʼ��
	strcpy(nextLayLimit,"");
	strcpy(backupLayLimit,"");
	int limitPointNum = getLimitNum(limitRoute);
	switch(limitPointNum){
		case 0:
			limOfLay = -1;
			strcpy(nextLayLimit,"");
			break;
		case 1:
			limOfLay = -1;
			//����һ����Զ���ɴ�����Ʊ�,Ȩ������
			strcpy(nextLayLimit,"0,");
			strcat(nextLayLimit,strstr(limitRoute,",")+1);
			leastWeight = atoi(strrchr(limitRoute,',')+1);
			break;
		case 2:
			strcat(nextLayLimit,strstr(limitRoute,",")+1);
			limOfLay = atoi(nextLayLimit);
			leastWeight = atoi(strrchr(limitRoute,',')+1);
			break;
		default:
			break;
	}
	strcpy(backupLayLimit,nextLayLimit);
	

	branchNum = edgeOutorIn(branch,buff,edgeNum,Start,true); 
	for(i=0;i<branchNum;i++){
		branWeightArr[i] = getThatArea(branch[i],3);
	}

	for(i=0;i<branchNum;i++){
		curPoint = getThatArea(branch[i],2);

		//��������
		godJump++;
		if(godJump >= 3*branchNum){
			delete nextLayLimit;
			delete backupLayLimit;
			return -1;
		}

		//�������
		for(k=0;k<routeNum;k++){
			if(curPoint == getThatArea(routeList[k],2)){
				k = -1;
				break;
			}
		}
		if(k == -1){
			continue;
		}

		//Ȩ�ؿ���
		if(branWeightArr[i] > limitWeight){
			delete nextLayLimit;
			delete backupLayLimit;
			return branWeightArr[i]*550;
		}

		//���
		insertRoute(routeList,routeNum,branch[i],false);
		routeNum++;

		//�����Ʊ߼��
		if(curPoint == limOfLay){
			strcpy(nextLayLimit,backupLayLimit);
			if(isMember(curPoint,condition)){
				if(*limitFlag != true && getLimitNum(nextLayLimit) != 2){
					*limitFlag = true;
				}
				deleteBuffer(routeList,routeNum,getThatArea(branch[i],0),true);
				routeNum--;
				continue;
			}
		}else{
			if(isMember(curPoint,condition) && *limitFlag == false){
				deleteBuffer(routeList,routeNum,getThatArea(branch[i],0),true);
				routeNum--;
				continue;
			}
			if(strlen(nextLayLimit)>0){
				//����һ����Զ���ɴ�����Ʊ�,Ȩ������
				deepNeedWeight = 0;
				strcpy(nextLayLimit,"0,");
				leastWeight = atoi(strrchr(limitRoute,',')+1);
				for(k=0;k<routeNum-1;k++){
					deepNeedWeight += getThatArea(routeList[k],3);
				}
				deepNeedWeight = branWeightArr[i] + deepNeedWeight;
				leastWeight = leastWeight > deepNeedWeight ? leastWeight : deepNeedWeight;
				//sprintf(changeStr,"%d",leastWeight);
				_snprintf(changeStr,5,"%d",leastWeight);
				strcat(nextLayLimit,changeStr);
			}
		}

		if(isMember(curPoint,condition) && curPoint!=limOfLay && overLW(routeList,routeNum,leastWeight) && *limitFlag == true){
			delete nextLayLimit;
			delete backupLayLimit;
			return routeNum;
		}else{
			if(i < branchNum-1){
				diffWeight = branWeightArr[i+1] > limitWeight ? (limitWeight - getThatArea(branch[i],3)) : branWeightArr[i+1] - getThatArea(branch[i],3);
			}else{
				diffWeight = limitWeight - getThatArea(branch[i],3);
			}
			nextLayreturn = findLay(routeList,routeNum,buff,edgeNum,curPoint,nextLayLimit,diffWeight,condition,limitFlag);
			if(nextLayreturn < 550 && nextLayreturn > 0){
				delete nextLayLimit;
				delete backupLayLimit;
				return nextLayreturn;
			}else if(nextLayreturn >= 550){
				nextLayreturn = nextLayreturn/550;
				branWeightArr[i] += nextLayreturn;

				//��Ȩ������
				tempNum = branWeightArr[i];
				tempChar = branch[i];
				for(j=i;j<branchNum-1;j++){
					if(tempNum>branWeightArr[j+1]){
						branWeightArr[j] = branWeightArr[j+1];
						branch[j] = branch[j+1];
					}else{
						break;
					}
				}
				branWeightArr[j] = tempNum;
				branch[j] = tempChar;

				deleteBuffer(routeList,routeNum,getThatArea(branch[i],0),true);
				routeNum--;
				i--;
			}else if(nextLayreturn == -1){
				deleteBuffer(routeList,routeNum,getThatArea(branch[i],0),true);
				routeNum--;
				continue;
			}
		}
	}
	delete nextLayLimit;
	delete backupLayLimit;
	return -1;
}

/******************���ߺ���*****************/


/*******************************************
���ܣ���ȡ��","�ָ���һ���ַ�����pos��ָ������
�Ľ���strtok
����Ӷȣ��ַ�������
*******************************************/
int getThatArea(char *tarStr,int pos){
	int result = -1;
	int i = 0,num = 0;
	while(i < strlen(tarStr) && result <= 0){
		if(num == pos){
			result = atoi(tarStr+i);
			return result;
		}
		if(tarStr[i] == ','){
			num++;
		}
		i++;
	}
	return -1;
}

/*******************************************
���ܣ���ȡһ��������г��߻�������ߡ�trueΪ����,falseΪ���
�Ľ�������
����Ӷȣ�buff������
*******************************************/
int edgeOutorIn(char ** const tarArr,char ** const buff,int edgeNum,int point,bool out){
	int tarLen = 0,buffPoint = 0;
	int tempWeight = 0;
	int i = 0;
	int area = 0;
	area = out ? 1 : 2;
	while(buffPoint < edgeNum){
		if(getThatArea(buff[buffPoint],area) == point){
			tempWeight = getThatArea(buff[buffPoint],3);
			for(i=tarLen;i>0;i--){
				if(tarArr[i-1] != NULL && getThatArea(tarArr[i-1],3) > tempWeight){
					tarArr[i] = tarArr[i-1];
				}else{
					break;
				}
			}
			tarArr[i] = buff[buffPoint];
			tarLen++;
		}
		buffPoint++;
	}
	return tarLen;
}

/*******************************************
���ܣ����buff����
�Ľ�������
����Ӷȣ�buff������
*******************************************/
void printEdge(char ** const buff,int edgeNum,char * describe){
	int i = 0;
	cout<<describe<<endl;
	if(edgeNum != 0){
		for(i=0;i<edgeNum;i++){
			cout<<buff[i]<<endl;
		}
	}else{
		cout<<"�ռ�"<<endl;
	}
}

/*******************************************
���ܣ�ɾ��buff����
�Ľ�������
����Ӷȣ�buff������
*******************************************/
void deleteBuffer(char ** const buff,int edgeNum,int index,bool order){
	int i = 0;
	if(edgeNum > 0){
		if(!order){
			for(i=0;i<edgeNum;i++){
				if(getThatArea(buff[i],0) == index){
					break;
				}
			}
			for(;i<edgeNum-1;i++){
				buff[i] = buff[i+1];
			}
		}
		buff[edgeNum-1] = NULL;
	}
}

/*******************************************
���ܣ���ȡcondition�бؾ��������
�Ľ���strtok
����Ӷȣ��ؾ���ĸ���
*******************************************/
int getConditionNum(char *condition){
	int num = 0,i = 0;
	int one = 0;
	char *index = strrchr(condition,',');
	while(*(index+i) != '\0'){
		i++;
		one = atoi(index+i);
		if(one < 10){
			i++;
		}else{
			i = i + ceil(log10((float)one));
		}
		num++;
	}
	return num;
}

/*******************************************
���ܣ���ָ��buff���в���һ�����ݣ�trueΪ���������ұ����ظ�����
�Ľ�������
����Ӷȣ�buff������
*******************************************/
int insertRoute(char ** const buff,int edgeNum,char *edge,bool order){
	int i = 0,j = 0;
	int index = getThatArea(edge,0);
	if(!order){
		i = edgeNum;
	}else{
		for(i=0;i<edgeNum;i++){
			if(getThatArea(buff[i],0) == index){
			    //�����ظ�����
			    return -1;
			}
			if(getThatArea(buff[i],0) > index){
			    break;
			}
		}
		for(j=edgeNum;j>i;j--){
		    buff[j] = buff[j-1];
		}
	}
	buff[i] = edge;
	return 0;
}
/*******************************************
���ܣ�����limitRoute�ж��ŵĸ��������������϶���������
�Ľ�������
����Ӷȣ�����
*******************************************/
int getLimitNum(char * limitRoute){
	char *two = strstr(limitRoute,",");
	char *three = NULL;
	if(two != NULL){
		three = strrchr(two+1,',');
		if(three != NULL){
			return 2;
		}else{
			return 1;
		}
	}

	return 0;
}
/*******************************************
���ܣ��ж�һ�������Ƿ�����condition
�Ľ�������
����Ӷȣ�condition����
*******************************************/
bool isMember(int point,char * condition){
	int temp = 0;
	char *index = strrchr(condition,',');
	int i = 0;
	while(*(index+i) != '\0'){
        i++;
        temp = atoi(index+i);
        if(temp == point){
            return true;
        }
        if(temp < 10){
            i++;
        }else{
            i = i + ceil(log10((float)temp));
        }
    }
    return false;
}
/*******************************************
���ܣ��жϵ�ǰ·�����Ƿ�ﵽ��СȨ��
�Ľ�������
����Ӷȣ�buff������
*******************************************/
bool overLW(char ** const buff,int edgeNum,int least){
	int i = 0,sum = 0;
	for(i=0;i<edgeNum;i++){
		sum += getThatArea(buff[i],3);
		if(sum >= least){
			return true;
		}
	}
	return false;
}

int filterMore(char ** const existRoute,int routeNum,char ** const buff,int edgeNum,int End){
	int i = 0;
	int curPoint = 0;
	int newEdgeNum = edgeNum;
	int Start = 0;
	//ɾ��·����ص�
	if(routeNum > 0){
		for(i=0;i<routeNum;i++){
			curPoint = getThatArea(existRoute[i],1);
			newEdgeNum = delPoint(buff,newEdgeNum,curPoint,false);
		}
		curPoint = getThatArea(existRoute[i-1],2);
		newEdgeNum = delPoint(buff,newEdgeNum,curPoint,true);
	}
	//printEdge(buff,newEdgeNum,"ɾ��·����ص�");

	//ɾ��ֻ��������ֻ������
	if(newEdgeNum > 0){
		Start = getThatArea(existRoute[routeNum-1],2);
		newEdgeNum = delOnlyInOut(buff,newEdgeNum,Start,End);
		//printEdge(buff,newEdgeNum,"ɾ��ֻ��������ֻ��������");
		return newEdgeNum;
	}else{
		return 0;
	}
	
}

/*******************************************
���ܣ�ɾ��һ����ıߣ�trueΪֻɾ�����
�Ľ�������
����Ӷȣ�buff������
*******************************************/
int delPoint(char ** const buff,int edgeNum,int point,bool noOut){
	int i = 0;
	char *inEdge[600];
	char *outEdge[8];
	int inEdgeNum = 0,outEdgeNum = 0;
	if(edgeNum > 0){
		inEdgeNum = edgeOutorIn(inEdge,buff,edgeNum,point,false);
		outEdgeNum = edgeOutorIn(outEdge,buff,edgeNum,point,true);
		for(i=0;i<inEdgeNum;i++){
			deleteBuffer(buff,edgeNum,getThatArea(inEdge[i],0),false);
			edgeNum--;
		}
		if(!noOut){
			for(i=0;i<outEdgeNum;i++){
				deleteBuffer(buff,edgeNum,getThatArea(outEdge[i],0),false);
				edgeNum--;
			}
		}
		return edgeNum;
	}else{
		return 0;
	}
	
}

/*******************************************
���ܣ�ɾ��һ��ֻ�������ĵ���ֻ�������ĵ�
�Ľ�������
����Ӷȣ�buff������
*******************************************/
int delOnlyInOut(char ** const buff,int edgeNum,int Start,int End){
	int i = 0,j = 0;
	int bigPoint = 0,smallPoint = 0;
	int bigPos = -1,smallPos = -1;
	bool smallFlag = false;
	int *pointArr = new int[600];
	char *inEdge[600];
	char *outEdge[8];
	int arrLen = 0;
	for(i=0;i<edgeNum;i++){
		bigPoint = getThatArea(buff[i],1) > getThatArea(buff[i],2) ? getThatArea(buff[i],1) : getThatArea(buff[i],2);
		smallPoint = getThatArea(buff[i],1) + getThatArea(buff[i],2) - bigPoint;
		for(j=0;j<arrLen;j++){
			if(pointArr[j] > smallPoint){
				smallPos = smallFlag ? smallPos : j;
				smallFlag = true;
			}else if(pointArr[j] == smallPoint){
				smallPos = -1;
				smallFlag = true;
			}else{
				continue;
			}

			if(pointArr[j] > bigPoint){
				bigPos = j;
			}else if(pointArr[j] == bigPoint){
				bigPos = -1;
			}else{
				continue;
			}
			break;
		}

		if(j == arrLen){
			smallPos = smallFlag ? smallPos : j;
			bigPos = j;
		}

		if(bigPos != -1){
			for(j=arrLen-1;j>=bigPos;j--){
				if(smallPos != -1){
					pointArr[j+2] = pointArr[j];
				}else{
					pointArr[j+1] = pointArr[j];
				}
			}
			pointArr[bigPos] = bigPoint;
			arrLen++;
		}
		if(smallPos != -1){
			j = bigPos > 0 ? bigPos :(arrLen-1);
			for(;j>=smallPos;j--){
			    pointArr[j+1] = pointArr[j];
			}
			pointArr[smallPos] = smallPoint;
			arrLen++;
		}

		smallPos = -1;
		bigPos = -1;
		smallFlag = false;
	}
	for(i=0;i<arrLen;i++){
		if((edgeOutorIn(outEdge,buff,edgeNum,pointArr[i],true)&&edgeOutorIn(inEdge,buff,edgeNum,pointArr[i],false)) || pointArr[i] == End || pointArr[i] == Start){
			continue;
		}else{
			edgeNum = delPoint(buff,edgeNum,pointArr[i],false);
		}
	}
	delete []pointArr;
	return edgeNum;
}

/*******************************************
���ܣ��ж��Ƿ��е����յ�ı�
�Ľ�������
����Ӷȣ�buff������
*******************************************/
bool existPointToEnd(char ** const buff,int edgeNum,int End){
	char *inEdge[600];
	int inEdgeNum = 0;
	inEdgeNum = edgeOutorIn(inEdge,buff,edgeNum,End,false);
	if(inEdgeNum > 0){
		return true;
	}

	return false;
}
/*******************************************
���ܣ��ж�condition���Ƿ��е㱻�����ɾ��
�Ľ�������
����Ӷȣ�buff������*conditionnum
*******************************************/
bool checkCond(char ** const buff,int edgeNum,char* condition,int deep){
	int conditionNum = getConditionNum(condition);
	char *inEdge[600];
	char *outEdge[8];
	char *pointer = strrchr(condition,',');
	int i = 0,temp = 0;
	int outFlag = 0;
	while(*(pointer+i) != '\0'){
        i++;
        temp = atoi(pointer+i);
        if(!(edgeOutorIn(outEdge,buff,edgeNum,temp,true) || edgeOutorIn(inEdge,buff,edgeNum,temp,false))){
            outFlag++;
            if(outFlag>conditionNum-deep){
                return false;
            }
        }
        if(temp < 10){
            i++;
        }else{
            i = i + ceil(log10((float)temp));
        }
    }
	return true;
}

/*******************************************
���ܣ�����limitRoute
�Ľ�������
����Ӷȣ�buff������
*******************************************/
void makelimRoute(char ** const buff,int edgeNum,char *limitRoute){
	int routeWeight = 0;
	int i = 0;
	char *str = new char[5];
	strcpy(limitRoute,"");
	for(i=0;i<edgeNum;i++){
		routeWeight += getThatArea(buff[i],3);
		if(strlen(limitRoute) > 0){
			strcat(limitRoute,",");
		}
		//sprintf(str,"%d",getThatArea(buff[i],1));
		_snprintf(str,5,"%d",getThatArea(buff[i],1));
		strcat(limitRoute,str);
	}
	strcat(limitRoute,",");
	//sprintf(str,"%d",getThatArea(buff[i-1],2));
	_snprintf(str,5,"%d",getThatArea(buff[i-1],2));
	strcat(limitRoute,str);
	strcat(limitRoute,",");
	//sprintf(str,"%d",routeWeight);
	_snprintf(str,5,"%d",routeWeight);
	strcat(limitRoute,str);
	delete []str;
}