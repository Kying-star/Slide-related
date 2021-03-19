#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
typedef  struct {
    double Im;
    double Re;
}Data;
typedef  struct {
    Data *items;
    int len;
}List;
void getData(Data* items,int dataPos);
int getDataLen(int dataPos);
void sortForOrderList(double *arr,int* orders);
void Slide_related(List y,List* PSS);
void getMagnitudeOrder(List* DataList,int* orderlist);
void init(List* DataList);
void testData(List* DataList,int row,int num);
void initData(List* DataList);
void isOk(int*order,List* DataList,List* PssList);
void initPss(List* PssList);
void initPssData(List* PssList);
int getPssDataLen(int PssPos);
void getPssData(Data* items,int pssPos);
int main() {
    int orders[12];
    List DataList[12];
    List PssList[3];
    init(DataList);
    initData(DataList);
    initPss(PssList);
    initPssData(PssList);
    getMagnitudeOrder(DataList,orders);
    isOk(orders,DataList,PssList);
    //testData(PssList,3,2048);
    return 0;
}
void getPssData(Data* items,int pssPos){
    FILE *fp = NULL;
    int len = 0,j=0,count=0;
    char buff[255];
    char catStrFirst[200] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/PSS";
    char catStrLast[4] = ".txt";
    char catStr[10],allStr[400];
    sprintf(catStr, "%d%s", pssPos, catStrLast);
    char str[300] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/PSS0.txt";
    strcpy(allStr,strcat(catStrFirst,catStr));
    allStr[strlen(str)] = '\0';
    if((fp=fopen(allStr,"r")) == NULL)
    {
        exit(-1);
    }
    while (fscanf(fp, "%s", buff) != EOF){
        //printf("%d: %lf\n",j+1,toDouble(buff));
        //printf("%d | %d ==> %s\n",count,j,buff);
        if(j%2 == 0){
            items[count].Re = atof(buff);
        }else{
            items[count].Im = atof(buff);
        }
        if(j != 0 && j%2 == 1){
            //printf("%d => (%lf) + (%lf)i \n",count,items[count].Re, items[count].Im);
            count++;
        }
        j++;
    }
    fclose(fp);
}
void initPssData(List* PssList){
    for (int i = 0; i < 3; i++) {
        getPssData(PssList[i].items,i);
    }
}
int getPssDataLen(int PssPos){
    FILE *fp = NULL;
    int len = 0;
    char buff[255];
    char catStrFirst[200] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/PSS";
    char catStrLast[4] = ".txt";
    char catStr[10],allStr[400];
    sprintf(catStr, "%d%s", PssPos, catStrLast);
    char str[300] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/PSS0.txt";
    strcpy(allStr,strcat(catStrFirst,catStr));
    // 判断位数
    allStr[strlen(str)] = '\0';
    if((fp=fopen(allStr,"r")) == NULL)
    {
        printf("打开PSS文件失败,请检查路径\n");
    }
    while (fscanf(fp, "%s", buff) != EOF){
        len++;
    }
    return len;
}
void initPss(List* PssList){
    for (int i = 0; i < 3; i++) {
        PssList[i].items = malloc(sizeof(Data)*(getPssDataLen(i)/2));
        PssList[i].len = getPssDataLen(i)/2;
    }
    printf("-- PSS数据表创建成功 -- \n");
}
void initData(List* DataList){
    for (int i = 0; i < 12; i++) {
        getData(DataList[i].items,i+24);
    }
}
void testData(List* DataList,int row,int num){
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < num; ++j) {
            printf("%d ==> (%lf) + (%lf)i \n",i,DataList[i].items[j].Re,DataList[i].items[j].Im);
        }
    }
}
void init(List* DataList){
    for (int i = 0; i < 12; i++) {
        DataList[i].items = malloc(sizeof(Data)*(getDataLen(i+24)/2));
        DataList[i].len = getDataLen(i+24)/2;
    }
    printf("-- 数据表创建成功 -- \n");
}
void getData(Data * items,int dataPos){
    FILE *fp = NULL;
    int len = 0,j=0,count=0;
    char buff[255];
    char catStrFirst[200] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/data";
    char catStrLast[4] = ".txt";
    char catStr[10],allStr[400];
    sprintf(catStr, "%d%s", dataPos, catStrLast);
    char str[300] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/data0.txt";
    char str2[300] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/data10.txt";
    strcpy(allStr,strcat(catStrFirst,catStr));
    strcpy(allStr,strcat(catStrFirst,catStr));
    // 判断位数
    if(dataPos<10){
        allStr[strlen(str)] = '\0';
    }else{
        allStr[strlen(str2)] = '\0';
    }
    if((fp=fopen(allStr,"r")) == NULL)
    {
        printf("文件%d打开失败,请检查路径\n",dataPos);
        exit(-1);
    }
    while (fscanf(fp, "%s", buff) != EOF){
        //printf("%d: %lf\n",j+1,toDouble(buff));
        //printf("%d | %d ==> %s\n",count,j,buff);
        if(j%2 == 0){
            items[count].Re = atof(buff);
        }else{
            items[count].Im = atof(buff);
        }
        if(j != 0 && j%2 == 1){
            //printf("%d => (%lf) + (%lf)i \n",count,items[count].Re, items[count].Im);
            count++;
        }
        j++;
    }
    fclose(fp);
}
int getDataLen(int dataPos){
    FILE *fp = NULL;
    int len = 0;
    char buff[255];
    char catStrFirst[200] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/data";
    char catStrLast[4] = ".txt";
    char catStr[10],allStr[400];
    sprintf(catStr, "%d%s", dataPos, catStrLast);
    char str[300] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/data0.txt";
    char str2[300] = "/Users/kying-star/Documents/文档/大学/大二下/移动通信/实验课1-移动通信/lab_1/data/data10.txt";
    strcpy(allStr,strcat(catStrFirst,catStr));
    strcpy(allStr,strcat(catStrFirst,catStr));
    // 判断位数
    if(dataPos<10){
        allStr[strlen(str)] = '\0';
    }else{
        allStr[strlen(str2)] = '\0';
    }
    if((fp=fopen(allStr,"r")) == NULL)
    {
        printf("打开失败,请检查路径\n");
    }
    while (fscanf(fp, "%s", buff) != EOF){
        len++;
    }
    return len;
}
void sortForOrderList(double *arr,int* orders){
    double temp = 0;
    int order = 0;
    for (int i = 0; i < 12-1; i++) {
        for (int j = 0; j < 12-1-i; j++) {
            if(arr[j]<arr[j+1]){
                temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
                order = orders[j];
                orders[j] = orders[j+1];
                orders[j+1] = order;
            }
        }
    }
}
void Slide_related(List y,List* PSS){
    double Max = 0;
    int pos;
    Data tmp;
    tmp.Re = 0;
    tmp.Im = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < y.len; j++) {
            tmp.Im = 0;
            tmp.Re = 0;
            for (int k = 0; k < PSS[i].len; k++) {
                tmp.Re+=(y.items[k+j].Re)*(PSS[i].items[k].Re) - (y.items[k+j].Im)*(PSS[i].items[k].Im);
                tmp.Im+=(y.items[k+j].Im)*(PSS[i].items[k].Re) + (y.items[k+j].Re)*(PSS[i].items[k].Im);
            }
//            printf("%lf + %lf i\n",tmp.Re,tmp.Im);
            if(sqrt(pow(tmp.Re,2)+pow(tmp.Im,2)) - Max > 0 ){
                // printf("因为%lf - %lf = %lf >0 所以此时位置换为%d\n",sqrt(pow(tmp.Re,2)+pow(tmp.Im,2)),Max,sqrt(pow(tmp.Re,2)+pow(tmp.Im,2))-Max,j);
                pos = j;
                Max = sqrt(pow(tmp.Re,2)+pow(tmp.Im,2));
            }
        }
        printf("此时阀值为800000\n");
        if ( Max > 800000 ) {
            printf("数值%lf大于门限\n",Max);
            printf("最大相关 = %lf, 此时位置 = %d\n", Max,pos);
            break;
        }else {
            printf("数值%lf小于门限\n",Max);
            printf("未达到阀值\n");
        }
    }
}
void getMagnitudeOrder(List * DataList,int* orderlist){
    double sums[12];
    double sum = 0;
    int orders[12] = {0,1,2,3,4,5,6,7,8,9,10,11};
    for (int i = 0; i < 12; i++) {
        sum = 0;
        for (int j = 0; j < DataList[i].len; j++) {
            sum+=sqrt(pow(DataList[i].items[j].Re,2)+pow(DataList[i].items[j].Im,2));
        }
        sums[i] = sum;
    }
    sortForOrderList(sums,orders);
    printf("强度排行\t\t数据来源组\t\t\t 信号强度\n");
    for (int i = 0; i < 12; i++) {
       // printf("roll %2d ==> order %2d ==> num : %10lf\n",i,orders[i],sums[i]);
        printf("roll %2d ==> order data%2d.txt ==> num : %10lf\n",i+1,orders[i]+24,sums[i]);
    }
    for (int i = 0; i < 12; i++) {
        orderlist[i] = orders[i];
    }
}
void isOk(int* order,List* DataList,List* PssList){
    Slide_related(DataList[order[0]], PssList);
}