1.最大连续子序列之和
给定K个整数的序列{ N1, N2, …, NK }，其任意连续子序列可表示为{ Ni, Ni+1, …, Nj }，其中 1 <= i <= j <= K。最大连续子序列是所有连续子序中元素和最大的一个， 例如给定序列{ -2, 11, -4, 13, -5, -2 }，其最大连续子序列为{ 11, -4, 13 }，最大和为20。

状态转移方程： sum[i]=max(sum[i-1]+a[i],a[i])
代码清单：


[cpp] view plaincopy

#include “stdio.h”  
  
main(){  
    int i,sum = 0, max = 0;  
    int data[] = {  
        1,-2,3,-1,7  
    };  
    for(i = 0; i < sizeof(data)/sizeof(data[0]); i++){  
        sum += data[i];  
        if(sum > max)  
            max = sum;  
        if(sum < 0)  
            sum = 0;          
    }  
    printf(”%d”,max);  
}  



2.数塔问题

数塔问题 ：要求从顶层走到底层，若每一步只能走到相邻的结点，则经过的结点的数字之和最大是多少？
转移方程：sum[i] = max(a[左孩子] , a[右孩子]) + a[i]


[cpp] view plaincopy

#include “stdio.h”  
#define N 5  
main(){  
    int i,j;  
    int data[N][N] = {  
            {9,0,0,0,0},  
            {12,15,0,0,0},  
            {10,6,8,0,0},  
            {2,18,9,5,0},  
            {19,7,10,4,16}  
        };  
        for(i = N-1; i > 0; i–)  
            for(j = 0; j < i; j++)  
                data[i-1][j] += data[i][j] > data[i][j+1] ? data[i][j] : data[i][j+1];  
          
        printf(”%d”,data[0][0]);  
          
          
}  


3.01背包问题
有N件物品和一个容量为V的背包。第i件物品的费用是c[i]，价值是w[i]。求解将哪些物品装入背包可使价值总和最大。

转移方程：dp[i][j] = max(dp[i-1][j],dp[i-1][j-weight[i]] + value[i]


[cpp] view plaincopy

#include “stdio.h”  
#define max(a,b) ((a)>(b)?(a):(b))  
  
  
  
main(){  
      
    int v = 10 ;    
    int n = 5 ;      
       
    int value[] = {0, 8 , 10 , 4 , 5 , 5};       
    int weight[] = {0, 6 , 4 , 2 , 4 , 3};     
    int i,j;      
    int dp[n+1][v+1];  
    for(i = 0; i < n+1; i++)  
        for(j = 0; j < v+1; j++)  
            dp[i][j] = 0;  
  
  
    for(i = 1; i <= n; i++){  
        for(j = 1; j <= v; j++){  
            if(j >= weight[i])  
                dp[i][j] = max(dp[i-1][j],dp[i-1][j-weight[i]] + value[i]);  
            else  
                dp[i][j] = dp[i-1][j];  
        }  
    }  
  
    printf(”%d”,dp[n][v]);  
}  


4.最长递增子序列(LIS)
给定一个序列 An = a1 ,a2 ,  … , an ，找出最长的子序列使得对所有 i < j ，ai < aj 。

转移方程：b[k]=max(max(b[j]|a[j]<a[k],j<k)+1,1);

代码清单：


[cpp] view plaincopy

#include “stdio.h”  
  
main(){  
    int i,j,length,max=0;  
    int a[] = {  
        1,-1,2,-3,4,-5,6,-7  
    };  
    int *b;  
    b = (int *)malloc(sizeof(a));  
    length = sizeof(a)/sizeof(a[0]);  
  
    for(i = 0; i < length; i++){  
        b[i] = 1;  
        for(j = 0; j < i; j++){  
            if(a[i] > a[j] && b[i] <= b[j]){  
                b[i] = b[j] + 1;  
            }  
        }  
    }  
    for(i = 0; i < length; i++)  
        if(b[i] > max)  
            max = b[i];  
          
    printf(”%d”,max);  
}  


5.最长公共子序列(LCS)
一个序列 S ，如果分别是两个或多个已知序列的子序列，且是所有符合此条件序列中最长的，则 S 称为已知序列的最长公共子序列。

转移方程：

dp[i,j] = 0                                          i=0 || j=0

dp[i,j] = dp[i-1][j-1]+1                        i>0,j>0, a[i] = b[j]       

dp[i,j] = max(dp[i-1][j],dp[i][j-1])        i>0,j>0, a[i] != b[j]

[cpp] view plaincopy

#include “stdio.h”  
#define M 8  
#define N 6  
  
          
void printLSC(int i, int j,char *a, int status[][N]){  
    if(i == 0 || j== 0)  
        return;  
    if(status[i][j] == 0){  
        printLSC(i-1,j-1,a,status);  
        printf(”%c”,a[i]);  
    }else{  
        if(status[i][j] == 1)  
            printLSC(i-1,j,a,status);  
        else  
            printLSC(i,j-1,a,status);  
    }  
}  
main(){  
    int i,j;  
  
    char a[] = {‘ ’,‘A’,‘B’,‘C’,‘B’,‘D’,‘A’,‘B’};  
    char b[] = {‘ ’,‘B’,‘D’,‘C’,‘B’,‘A’};  
    int status[M][N]; //保存状态  
    int dp[M][N];  
  
    for(i = 0; i < M; i++)  
        for(j = 0; j < N; j++){  
            dp[i][j] = 0;  
            status[i][j] = 0;  
        }  
              
    for(i = 1; i < M; i++)  
        for(j = 1; j < N; j++){  
            if(a[i] == b[j]){  
                dp[i][j] = dp[i-1][j-1] + 1;  
                status[i][j] = 0;  
            }  
            else if(dp[i][j-1] >= dp[i-1][j]){  
                dp[i][j] = dp[i][j-1];  
                status[i][j] = 2;  
            }  
            else{  
                dp[i][j] = dp[i-1][j];  
                status[i][j] = 1;  
            }  
                  
                  
        }  
    printf(”最大长度：%d”,dp[M-1][N-1]);  
    printf(”\n”);  
    printLSC(M-1,N-1,a,status);  
    printf(”\n”);  
  
}