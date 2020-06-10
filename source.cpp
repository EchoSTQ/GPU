#define _CRT_SECURE_NO_WARNINGS

#define sizeT 100
#define Lim 200
#define Cross 444

#include<stdio.h>
#include<time.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include <stdio.h>
#include<iostream>
#include<cstring>
#include<string>
#include<cstdio>
#include<algorithm>
#include<stack>
#include<iomanip>
#include<fstream>

using namespace std;

int x[10], y[10], z[10];
int k = 1;
int tot = 0, n, m;
int num[109];
double delta[1009];
struct ob {
	int count;
	int t[10];
	int m[10];
}a[50][50];
struct good {
	int ans;
	double a[1009];
	int count[1009];
}s[3009], tmp[2009];
int facx[1009], facy[1009];
void unit(double * x)
{
	double sum = 0;
	double multi = 100;
	int i;
	for (i = 1; i <= tot; i++)
	{
		sum += x[i] * x[i];
	}
	sum = sqrt(sum);
	for (i = 1; i <= tot; i++)
	{
		x[i] = x[i] * multi / sum;
	}
}

void unit2(double * x)
{
	double sum = 0;
	double multi = 70;
	int i;
	for (i = 1; i <= tot; i++)
	{
		sum += x[i] * x[i];
	}
	sum = sqrt(sum);
	for (i = 1; i <= tot; i++)
	{
		x[i] = x[i] * multi / sum;
	}
}
int mt[109], gt[109];
int sx[10009], sy[10009];

int max(int x, int y)
{
	if (x <= y)return y;
	else return x;
}
int getlen(int& array)
{
	return (sizeof(array) / sizeof(int));
}
void Calculate(int x)
{
	memset(mt, 0, sizeof(mt));
	memset(gt, 0, sizeof(gt));
	int Max = 0;
	int i, j;
	for (i = 1; i <= tot; i++)
	{
		sx[s[x].count[i]] = facx[i];//第几个工序对应属于第几个物件
		sy[s[x].count[i]] = facy[i];//这个工序对应物件的第几个工序
	}
	for (i = 1; i <= tot; i++)
	{
		int tmp = 0;
		int chosen;
		int time = 100000;
		int chosen_time;
		//        int len=sizeof(a[sx[i]][sy[i]].m)/sizeof(int);
		int len = a[sx[i]][sy[i]].count;

		for (j = 0; j < len; j++)
		{
			if (mt[a[sx[i]][sy[i]].m[j]] < time)
			{
				time = mt[a[sx[i]][sy[i]].m[j]];
				chosen = a[sx[i]][sy[i]].m[j];
				chosen_time = j;
			}
		}
		tmp = max(mt[chosen], gt[sx[i]]);
		tmp += a[sx[i]][sy[i]].t[chosen_time];
		Max = max(tmp, Max);
		mt[chosen] = tmp;
		gt[sx[i]] = tmp;
	}
	s[x].ans = Max;
}


struct put {
	int start;
	int num;
	int count;
	int end;
}print[109][109];

void outputs()
{
	FILE *fp = fopen("output.txt", "w");
	int x = 2;
	int b[109];
	memset(mt, 0, sizeof(mt));
	memset(gt, 0, sizeof(gt));
	memset(b, 0, sizeof(b));
	int Max = 0;
	int i, j;
	for (i = 1; i <= tot; i++)
	{
		sx[s[x].count[i]] = facx[i];
		sy[s[x].count[i]] = facy[i];
	}
	for (i = 1; i <= tot; i++)
	{
		int tmp;
		int chosen;
		int chosen_time;
		int time = 100000;
		//int len=sizeof(a[sx[i]][sy[i]].m)/sizeof(int);
		int len = a[sx[i]][sy[i]].count;
		for (j = 0; j < len; j++)
		{
			if (mt[a[sx[i]][sy[i]].m[j]] < time)
			{
				time = mt[a[sx[i]][sy[i]].m[j]];
				chosen = a[sx[i]][sy[i]].m[j];
				chosen_time = j;
			}
		}
		tmp = max(mt[chosen], gt[sx[i]]);
		b[chosen]++;
		print[chosen][b[chosen]].start = tmp;
		print[chosen][b[chosen]].num = sx[i];
		print[chosen][b[chosen]].count = sy[i];
		print[chosen][b[chosen]].end = tmp + a[sx[i]][sy[i]].t[chosen_time];
		tmp += a[sx[i]][sy[i]].t[chosen_time];
		Max = max(tmp, Max);
		mt[chosen] = tmp;
		gt[sx[i]] = tmp;
		cout << Max << endl;
	}
	for (i = 1; i <= m; i++) {
		fprintf(fp, "M%d", i);
		for (j = 1; j <= b[i]; j++) {
			fprintf(fp, " (%d,%d-%d,%d)", print[i][j].start, print[i][j].num, print[i][j].count, print[i][j].end);
		}
		fprintf(fp, "\n");
	}
	fprintf(fp, "End %d\n", Max);
	fclose(fp);
}


int best[1009];
double * cmper = NULL;

int cmp1(const void * a, const void * b)
{
	return *(cmper + *(int*)a) - *(cmper + *(int*)b);
}

int cmp2(const void * a, const void *b)
{
	return s[*(int*)a].ans - s[*(int*)b].ans;
}

int cmp3(const void * a, const void *b)
{
	return *(int*)a - *(int*)b;
}

int cmp4(const void * a, const void *b)
{
	return x[*(int*)b] - x[*(int*)a];
}

int cmp5(const void * a, const void *b)
{
	return x[*(int*)a] - x[*(int*)b];
}
void GeneticAlgorithm()
{
	tot = num[n];
	int i, j;
	for (i = 1; i <= sizeT; i++)
	{
		for (j = 1; j <= tot; j++)
		{
			s[i].a[j] = rand();
			s[i].count[j] = j;
		}
		unit(s[i].a);
		cmper = s[i].a;
		qsort(s[i].count + 1, tot, sizeof(int), cmp1);//按照a大小给count排序
		for (j = 1; j <= n; j++)
		{
			qsort(s[i].count + num[j - 1] + 1, num[j] - num[j - 1], sizeof(int), cmp3);
		}//给各个物件的工序排序
		Calculate(i);
	}
	int counter = 0;
	while (counter <= Lim)//????????????????????????????????
	{
		////遗传
		cout << "counter = " << counter << endl;
		for (i = 1; i <= Cross; i++)
		{
			int x = rand() % sizeT + 1, y = rand() % sizeT + 1;
			int cur = i + sizeT;
			s[cur].ans = 0;
			for (j = 1; j <= tot; j++)
			{
				s[i + sizeT].a[j] = s[x].a[j] - s[y].a[j];//??????????????????????
				s[i + sizeT].count[j] = j;
			}
			unit(s[i + sizeT].a);
			cmper = s[cur].a;
			qsort(s[cur].count + 1, tot, sizeof(int), cmp1);
			for (j = 1; j <= n; j++)
			{
				qsort(s[cur].count + num[j - 1] + 1, num[j] - num[j - 1], sizeof(int), cmp3);//???????????????
			}
		}
		/////变异
		for (i = 1; i <= sizeT + Cross; i++)
		{
			int cur = i + sizeT + Cross;
			for (j = 1; j <= tot; j++)
			{
				delta[j] = rand() - (RAND_MAX / 2);
				delta[j] = delta[j] * (rand() % 2);
			}
			unit2(delta);
			for (j = 1; j <= tot; j++)
				s[i + sizeT + Cross].a[j] = s[i].a[j] + delta[j];
			cmper = s[cur].a;//???
			s[cur].ans = 0;
			qsort(s[cur].count + 1, tot, sizeof(int), cmp1);
			for (j = 1; j <= n; j++) {
				qsort(s[cur].count + num[j - 1] + 1, num[j] - num[j - 1], sizeof(int), cmp3);
			}
		}
		/////选择
		for (i = sizeT + 1; i <= (sizeT + Cross) * 2; i++) {
			Calculate(i);
		}
		for (i = 1; i <= (sizeT + Cross) * 2; i++) best[i] = i;
		qsort(best + 1, (sizeT + Cross) * 2, sizeof(int), cmp2);
		for (i = 1; i <= sizeT; i++) tmp[i] = s[best[i]];
		for (i = 1; i <= sizeT; i++) { s[i] = tmp[i]; unit(s[i].a); }
		counter++;
	}

	outputs();
}

int main()
{
	clock_t s_time, e_time;
	s_time = clock();

	freopen("Mk02.txt", "r", stdin);
	memset(a, 0, sizeof(a));
	srand(time(NULL) + 990227);
	tot = 0;
	memset(s, 0, sizeof(s));
	memset(best, 0, sizeof(best));
	memset(num, 0, sizeof(num));
	int i, j;
	char  ch;
	int flag = 0;
	i = 1;
	j = 1;

	cin >> n >> m;
	char ch1;
	int tmp = 0;
	getchar();
	//getchar();
	while (i <= n)
	{
		cin >> tmp;
		getchar();
		for (j = 1; j <= tmp; j++)
		{
			int tmp1;
			cin >> tmp1;
			getchar();
			a[i - 1][j].count = tmp1;
			for (k = 0; k < tmp1; k++)
			{
				cin >> a[i - 1][j].m[k] >> a[i - 1][j].t[k];
			}
			for (int l = 0; l < k; l++)
			{
				for (int kl = 0; kl < k - l - 1; kl++) {
					if (a[i - 1][j].t[kl] > a[i - 1][j].t[kl + 1])
					{
						int tmp = a[i - 1][j].t[kl];
						a[i - 1][j].t[kl] = a[i - 1][j].t[kl + 1];
						a[i - 1][j].t[kl + 1] = tmp;
						tmp = a[i - 1][j].m[kl];
						a[i - 1][j].m[kl] = a[i - 1][j].m[kl + 1];
						a[i - 1][j].m[kl + 1] = tmp;

					}
				}
			}
			//getchar();
			facx[++tot] = i - 1;
			facy[tot] = j;
		}
		num[i] = tmp;
		num[i] += num[i - 1];
		i++;

		//            while(1){
		//                int k=0;
		//                while ((ch1=getchar())!=':') {
		//                    if (ch1<='9'&&ch1>='0') {
		//                        tmp=10*tmp+ch1-'0';
		//                    }
		//                    else {
		//                        a[i-1][j].m[k]=tmp;
		//                        k++;
		//                        tmp=0;
		//                    }
		//                }
		//                a[i-1][j].m[k]=-1;
		//                cin>>a[i-1][j].t;
		//                facx[++tot]=i-1;
		//                facy[tot]=j;
		//                ch=getchar();
		//                if(ch=='\n'||ch=='\r')
		//                {
		//                    ch=getchar();
		//                    break;
		//                }
		//                    j++;
		////                    scanf("%d %d",&a[i-1][j].m,&a[i-1][j].t);
		////                    facx[++tot]=i-1;
		////                    facy[tot]=j;
		////                    ch=getchar();
		////
		////                    if(ch=='\n'||ch=='\r')
		////                    break;
		////                      j++;
		//                }

	}
	GeneticAlgorithm();

	e_time = clock();
	cout << "Total time:" << (double)(e_time - s_time) / CLOCKS_PER_SEC << "S" << endl;
	return 0;
}



