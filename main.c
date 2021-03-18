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
double toDouble(char num[]);
void getData(Data* items,int dataPos);
int getDataLen(int dataPos);
void sortForOrderList(double *arr,int* orders);
void Slide_related(double *arr);
double getMagnitudeOrder(List* DataList);
void init(List* DataList);
void testData(List* DataList);
void initData(List* DataList);
int main() {
    int order;
    List DataList[12];
    init(DataList);
    initData(DataList);
    order = getMagnitudeOrder(DataList);
    //testData(DataList);
    return 0;
}
void initData(List* DataList){
    for (int i = 0; i < 12; i++) {
        getData(DataList[i].items,i+24);
    }
}
void testData(List* DataList){
    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 15000; ++j) {
            printf(" (%lf) + (%lf)i \n",DataList[0].items[j].Re,DataList[0].items[j].Im);
        }
    }
}
void init(List* DataList){
    for (int i = 0; i < 12; i++) {
        DataList[i].items = malloc(sizeof(Data)*(getDataLen(i+24)/2));
        DataList[i].len = getDataLen(i+24)/2;
    }
    printf("数据表创建成功");
}
double toDouble(char num[]) {
    int i = 0,base,flag = 0;
    int len = strlen((num));
    if(num[0] == '-'){
        flag = 1;
        for (int j = 0; j < len - 1; j++) {
            num[j] = num[j+1];
        }
    }
    double dnum1 = 0,dnum2 = 0;
    while(num[i] && num[i] != '.') {
        dnum1 = 10 * dnum1 + num[i] - '0';
        ++i;
    }
    if(num[i] == '.') {
        ++i; // 跳过'.'
        base = 1;
        while(num[i] != '\0') {
            dnum2 = 10 * dnum2 + num[i] - '0';
            base *= 10;
            ++i;
        }
        dnum2 /= base;
    }
    return flag == 0? dnum1 + dnum2:-(dnum1+dnum2);
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
        printf("打开失败,请检查路径\n");
    }else{
        printf("打开成功\n");
    }
    while (fscanf(fp, "%s", buff) != EOF){
        //printf("%d: %lf\n",j+1,toDouble(buff));
        //printf("%d | %d ==> %s\n",count,j,buff);
        if(j%2 == 0){
            items[count].Re = toDouble(buff);
        }else{
            items[count].Im = toDouble(buff);
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
    }else{
        printf("打开%d文件成功\n",dataPos);
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
void Slide_related(double *arr){

}
double getMagnitudeOrder(List * DataList){
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
//    for (int i = 0; i < 12; i++) {
//        printf("order %d ==> %lf\n",i,sums[i]);
//        printf("凭什么不往下运行");
//    }
    sortForOrderList(sums,orders);
    for (int i = 0; i < 12; i++) {
        printf("roll %d ==> order %d ==> num:%lf\n",i,orders[i],sums[i]);
    }

}