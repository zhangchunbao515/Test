#ifndef h1
#define h1

# include <iostream>
#include <stdio.h>
#include <iomanip>
#include <string.h>
#include <malloc.h>
#include <process.h>
using namespace std;



#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFFASIBLE -1
#define OVERFLOW -2
typedef char VertexType;
typedef int VRType;
typedef int Status;          //���ص�״̬
typedef int ElemType ;       //��������

#define INFINITY 1000        //���ֵ 
#define MAX_VERTEX_NUM 25   //��󶥵���
typedef enum{DG,DN,UDG,UDN}GraphKind;   //{����ͼ,������,����ͼ,������}
//����ͼ������ͼ����Ȩ
typedef int* ShortPathTable;
typedef int* PathMatrix;

#endif
