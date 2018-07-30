#include "predict.h"
#include <stdio.h>
#include <string>
#include <math.h>
#define NC 3600
#define k  100           //92.15  208.7 100 211.05
#define TIME 86400
#define NUM 18  //20 211.05 18 212
//22 86400 75.06
//20 86400 75.06
//18 86400 74.739
//将allot中的数据合理提取出来
int allotdraw(int num,int allot[][100],int save[][2])
{
	int z = 0;
	while(0 !=save[z][0])
	{
		save[z][0] = 0;
		save[z][1] = 0;
		z++;
	}
	int i = 1;
	int r = 0;
	save[0][0]=allot[num][1];
	while(0 != allot[num][i])
	{
		if(save[r][0] != allot[num][i])
		{
			r++;
			save[r][0] = allot[num][i];
			save[r][1]+=1;
		}
		else
		{
			save[r][1]+=1;
		}
		i++;
	}
	return r+1;
}

//寻找存在的虚拟机中内存或者cpu最大的并返回其对应下标
int findmax(int* count,int* str)
{
	int maxnum =-1;
	int maxvalue = 0;
	for(int i =14;i>=0;i--)
	{
		if(0 != count[i]&&str[i]>maxvalue)
		{
			maxnum = i;
			maxvalue = str[i];
		}
	}
	return maxnum;

}
//分配函数
int allot(int* count,char* std,int cpustd,int memstd,int allot[100][100])
{
	int N = 0;
	int stddatacpu[15] = {1,1,1,2,2,2,4,4,4,8,8,8,16,16,16};
	int stddatamem[15] = {1,2,4,2,4,8,4,8,16,8,16,32,16,32,64};
	int* stddata =NULL;
	if('C' == std[0]||'c' == std[0])
	{
		stddata = stddatacpu;
		N =cpustd;
	}
	else
	{
		stddata = stddatamem;
		N =memstd;
	}
	allot[100][100]={0};
	int storage[100][2] = {0};
	for(int i=0;i<100;i++)
	{
		allot[i][0] = N;
		storage[i][0] = cpustd;
		storage[i][1] = memstd;
	}
	int r=0,t=14,n;
	while(-1 != findmax(count,stddata))
	{	
		t = findmax(count,stddata);
		r = 0;
		int sub = count[t];
		for(n=0;n<sub;n++)
		{
			while(1)
			{
				if(stddatacpu[t]<=storage[r][0]&&stddatamem[t]<=storage[r][1])
				{	int z = 1;
					allot[r][0]-=stddata[t];
					storage[r][0]-=stddatacpu[t];
					storage[r][1]-=stddatamem[t];
					while(0 !=allot[r][z])
					{
						z++;
					}
					allot[r][z] = t+1;					
					count[t]--;
					break;
				}
				else
				{
					r++;
				}
			}
		}
	}
	//int j = 1;
	//for(int i=0;i<10;i++)
	//{
	//	printf("%d  ",allot[i][0]);
	//	while(0 !=allot[i][j])
	//	{
	//		printf("%d  ",allot[i][j]);
	//		j++;
	//	}
	//	j = 1;
	//	printf("\n");
	//}
	return r;
}
//建模函数
int  pre(double* numy,int* numx,int endtime)
{
	int  b0        = 0;
	double sumw    = 0;
	double sumwx   = 0;
	double sumwy   = 0;
	double sumwxy  = 0;
	double sumwxx = 0;
	double weight[10000]={0};
	endtime/=NC;
	while(0 != numy[b0])
	{
		weight[b0] = exp(-pow(numx[b0]-endtime,2)/(2*pow(k,2)));
		b0++;
	}
	b0 = 0;
	int i = 0;
	printf("%lf&&**&*&*&*  \n",weight[0]);
	while(0 != weight[i])
	{
		printf("%lf ",weight[i]);
		i++;
	}
	printf("\n");
	while(0 != numy[b0] )
	{
		sumw+=weight[b0];
		sumwx+=weight[b0]*numx[b0];
		sumwy+=weight[b0]*numy[b0];
		sumwxy+=weight[b0]*numx[b0]*numy[b0];
		sumwxx+=weight[b0]*numx[b0]*numx[b0];
		b0++;
	}
	printf("b0 = %d  \n sumw=%lf  \nsumwx=%lf   \n  sumwy=%d \n  sumwxy= %lf \nsunwxx= %lf\n",b0,sumw,sumwx,sumwy,sumwxy,sumwxx);
	double argue0 = (sumwx*sumwy-sumw*sumwxy)/(pow(sumwx,2)-sumw*sumwxx);
	double argue1 = (sumwy-argue0*sumwx)/sumw;
	double result = endtime*argue0+argue1-numy[b0-1];
	//格式result输出结果
	printf("%lf  \n",result);
	double t = result - (int)result;
	if(0 > result)return 0;
	if(0.5 <= t)return (int)result+1;
	else return (int)result;
}

//计算输入时间直接差多少秒
int timecal(int yearbe,int monthbe,int daybe,int hourbe,int minbe,int secbe,int yearend,int monthend,int dayend,int hourend,int minend,int secend)
{
	int sum = 0;
	if(secend >= secbe)
	{
		secend-=secbe;
	}
	else
	{
		secend = 60+secend-secbe;
		minend--;
	}
	if(minend >=minbe)
	{
		minend-=minbe;
	}
	else
	{
		minend = 60+minend-minbe;
		hourend--;
	}
	if(hourend >= hourbe)
	{
		hourend-=hourbe;
	}
	else
	{
		hourend = 24+hourend-hourbe;
		dayend--;
	}
	if(dayend >= daybe)
	{
		dayend-=daybe;
	}
	else
	{
		dayend = 30+dayend-daybe;
		monthend--;
	}
	if(monthend >= monthbe)
	{
		monthend-=monthbe;
	}
	else
	{
		monthend =12+monthend-monthbe;
		yearend--;
	}
	yearend-=yearbe;
	sum = yearend*365*24*60*60+monthend*30*24*60*60+dayend*24*60*60+hourend*60*60+minend*60+secend;
	return sum;
}

//预测主体函数	
void predict_server(char * info[MAX_INFO_NUM], char * data[MAX_DATA_NUM], int data_num, char * filename)
{
	char * result_file = (char *)"17\n\n0 8 0 20";
	
	//获取input中的物理机cpu和内存标准
	int cpustd = 0;
	int memstd = 0;
	sscanf(info[0],"%d %d %*d",&cpustd,&memstd);
	
	//获取测试用例虚拟机类型数量vmsum和cpu内存标准vm[][]
	int vm[15][4]={0};
	int q =3;
	int vmsum = 0;
	sscanf(info[2],"%d",&vmsum);
	while(0 != strcmp(info[q],"\r\n"))
	{
		sscanf(info[q],"flavor%d %d %d",&vm[q-3][0],&vm[q-3][1],&vm[q-3][2]);
		q++;
	}

	//获取分配参数std（cpu/mem）
	char* std = NULL;
	std =info[q+1];

	//获取train数据和时间type[],time[]
	int w = 0;
	int type[100000]={0};
	int time[100000]={0};
	int yearba  = 0;
	int monthba = 0;
	int dayba   = 0;
	int hourba  = 0;
	int minba   = 0;
	int secba   = 0;
	sscanf(data[0],"%*s\tflavor%d\t%d-%d-%d %d:%d:%d",&type[0],&yearba,&monthba,&dayba,&hourba,&minba,&secba);
	int year  = 0;
	int month = 0;
	int day   = 0;
	int hour  = 0;
	int min   = 0;
	int sec   = 0;
	while(w < data_num)
	{
		sscanf(data[w],"%*s\tflavor%d\t%d-%d-%d %d:%d:%d",&type[w],&year,&month,&day,&hour,&min,&sec);
		time[w] = timecal(yearba,monthba,dayba,0,0,0,year,month,day,hour,min,sec);
	w++;
	}
	
	//获取预测时间t
	int yearbe  =0;
	int monthbe =0;
	int daybe   =0;

	int yearend  =0;
	int monthend =0;
	int dayend   =0;
	int t =0;
	int tbe = 0;
	sscanf(info[q+3],"%d-%d-%d",&yearbe,&monthbe,&daybe);
	sscanf(info[q+4],"%d-%d-%d",&yearend,&monthend,&dayend);
	t   =timecal(yearba,monthba,dayba,0,0,0,yearend,monthend,dayend,0,0,0);
	tbe =timecal(yearba,monthba,dayba,0,0,0,yearbe,monthbe,daybe,0,0,0);
	


	//预测输入预测时间内的虚拟机数量并将其加入vm[15][4](具体数量放入vm[][3])
	int round = 0;
	while(0 != vm[round][0])
	{
		int l1 = vm[round][0];
		double numy[10000] = {0};
		int  numx[10000] = {0};
		int r1 = 0;
		int n1 = 0;
		int temp1 = 1;
		int next = 0;

		//剔除其中每天每种类型超过20台的所有数据，把那天的type量置-1
		for(int lc = 1;lc*TIME<=tbe;lc++)
		{
			int flag = 0;
			//判断具体某一天某一种类型l的虚拟机台数并把数量放入flag
			while((lc-1)*TIME<=time[next]&&time[next]<=lc*TIME)
			{
				if(l1 == type[next])
				{
					flag++;
				}
				next++;
			}

			//如果台数大于等于20，就把这一天这种类型虚拟机的类型值全部改为-1
			if(flag >= NUM)
			{
				int templp = next-1;
				while((lc-1)*TIME<=time[templp]&&time[templp]<=lc*TIME)
				{
					if(l1 == type[templp])
					{
						time[templp] = 0; ;
					}
					templp--;
				}
			}

	}


		while(0 != type[n1])
		{
			if(l1 == type[n1])
			{
				if(0 == time[n1])
				{
					n1++;
					continue;
				}
				numy[r1] = temp1;
				numx[r1] = time[n1]/NC;
				temp1 +=1;
				r1++;
			}
			n1++;
		}
		vm[round][3] = pre(numy,numx,t);
		round++;
	}

	//为allot函数产生count[]数组方便其运算分配
	int count[15] = {0};
	for(int t = 0;t<15;t++)
	{
		switch(vm[t][0])
		{
			case 1:count[0]+=vm[t][3];continue;
			case 2:count[1]+=vm[t][3];continue;
			case 3:count[2]+=vm[t][3];continue;
			case 4:count[3]+=vm[t][3];continue;
			case 5:count[4]+=vm[t][3];continue;
			case 6:count[5]+=vm[t][3];continue;
			case 7:count[6]+=vm[t][3];continue;
			case 8:count[7]+=vm[t][3];continue;
			case 9:count[8]+=vm[t][3];continue;
			case 10:count[9]+=vm[t][3];continue;
			case 11:count[10]+=vm[t][3];continue;
			case 12:count[11]+=vm[t][3];continue;
			case 13:count[12]+=vm[t][3];continue;
			case 14:count[13]+=vm[t][3];continue;
			case 15:count[14]+=vm[t][3];continue;
			default:continue;
		}
	}
	
	//调用分配函数获取分配结果放入sum[][]中
	int sum[100][100] = {0};
	int allotplus = 0;
	allotplus = 1+allot(count,std,cpustd,memstd,sum);
	for(int p =0;p<10;p++)
	{
		int h = 1;
		while(0 !=sum[p][h])
		{
			printf("%d ",sum[p][h]);
			h++;
		}
			printf("\n");
	}
	printf("***************************************");
	
	//将测试结果放入result[]中
	char result[10000]={0};
	int u =0;
	int vmplus = 0;
	for(u = 0;u<vmsum;u++)
	{
		vmplus+=vm[u][3];
	}
	sprintf(result,"%d\n",vmplus);
	char base[10000]={0};
	for(u = 0;u<vmsum;u++)
	{
		sprintf(base,"flavor%d %d\n",vm[u][0],vm[u][3]);
		strcat(result,base);
		memset(base,0,strlen(base));
	}
	strcat(result,"\n");
	
	//result[3+vmsum*10] = allotplus;
	sprintf(base,"%d\n",allotplus);
	strcat(result,base);
	memset(base,0,strlen(base));

	int save[100][2]={0};
	u = 0;
	for(u;u<allotplus;u++)
	{
		sprintf(base,"%d",u+1);
		strcat(result,base);
		memset(base,0,strlen(base));
		int re =allotdraw(u,sum,save);
		for(int b =0;b<re;b++)
		{
			sprintf(base," flavor%d %d",save[b][0],save[b][1]);
			strcat(result,base);
			memset(base,0,strlen(base));
		}
		strcat(result,"\n");
	}
	result_file = result;
	puts(result);
	write_result(result_file, filename);
}
