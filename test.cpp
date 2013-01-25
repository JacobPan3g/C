// source code of submission 731830, Zhongshan University Online Judge System
#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

int find(char x,char str[])                         //寻找字符在指定字符串中的位置
{
    int index;
    for (int i = 0; i < 5; i++)
    {
        if (str[i] == x)
        {
            index = i;
            return index;
        }
    }
}
int main()
{
    char p[160][5], cor[106][5],temp[5],res[5];
    char chr[5] = {'A','B','C','D','E'};
    int n,i,j,k,r,t;
    int num,cnt = 1;
    for(i = 0;i<5;i++)
        p[0][i] = chr[i];
    while(next_permutation(chr,chr+5))             //首先得到所有的全排列，保存在p[160][5]中
    {
        for(int i =0;i<5;i++)
            p[cnt][i] = chr[i];
        cnt++;                                     //cnt为全排列数，cnt = 5! = 120
    }
    while(cin>>n,n)
    {
        for(i = 0;i<n;i++)
            for(k = 0;k<5;k++)
                cin>>cor[i][k];
        int min = 10000;
        for(i = 0;i<cnt;i++)
        {
            for(k = 0;k<5;k++)                      //针对每一个全排列得到逆序数和
                temp[k] = p[i][k];
            num = 0;

            for(j = 0;j<n;j++)                      //这里是求逆序数和
            {
                for(r = 0;r<4;r++)
                    for(t = r+1;t<5;t++)
                    {
                        if(find(cor[j][r],temp)>find(cor[j][t],temp))  
                            num ++;
                    }
            }
            if(min>num)                              //min保存所有全排列中最小的逆序数和
            {
                min = num; 
                memcpy(res,temp,sizeof(temp));
            }
        }
    for(i = 0;i<5;i++)              //p数组的全排列已经按字典序排列，故res中保存的就是相同逆序数和下字典序最小的全排列
        cout<<res[i];
    cout<< " is the median ranking with value " << min << "." << endl;
    }
    return 0;
}
