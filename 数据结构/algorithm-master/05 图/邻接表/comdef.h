#include <stdio.h>
#include <iostream>
#include <iomanip>
#include <string.h>
#include <malloc.h>
#include <process.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OVERFLOW -1
typedef int Status;
#define INIFINITY 1000   			    // ���ֵ
#define MAX_VERTEX_NUM 20    			//��󶥵���
typedef enum{DG,DN,UDG,UDN} GraphKind; 	//ͼ����������  {����ͼ,������,����ͼ,������}
typedef char VertexType;                //������Ϣ
typedef int  InfoType;                  //Ȩ