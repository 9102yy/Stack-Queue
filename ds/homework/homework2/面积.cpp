#include <bits/stdc++.h>

#include "../../Queue/Queue.h"
using namespace std;
const int INF = 0x3f3f3f3f;
int myfind(vector<int> vec, int i, int j)
{
	int result = INF;
	for(int x = i; x <= j; x++)
	{
		if(result > vec[x])
			result = vec[x];
	}
	return result;
}
int mycalcu(vector<int> hight)
{
	int result = -1;
	stack<int> st;
	hight.push_back(0);
	int top,stemp;
	for(int i = 0; i < hight.size(); i++)
	{
		if(st.empty() || hight[st.top()] <= hight[i])
		{
			// ������ջ 
			st.push(i); 
		}
		else
		{
			while(!st.empty() && hight[st.top()] > hight[i])
			{
				// ���㵱ǰ�� i Ϊ���� 
				top = st.top(); 
				st.pop(); 
				stemp = (i - top) * hight[top]; 
				if(stemp > result) 
					result = stemp; 
			}
			st.push(i);
		}
	}
	
	
	return result;
} 

int main()
{
	freopen("case2.txt","r",stdin);
	
	Queue<int> myqueue;
	vector<int> myvec;
	string str;
	getline(cin, str);
	 //  heights = [2,1,5,6,2,3]  
	 //  ��һ������ 11 , 13 -> 15 

	for(int i = 11; i < str.size(); i += 2)
	{
		int temp = str[i] - '0';
		myvec.push_back(temp);
	} 
	
	// ����ջ����  
	cout<<mycalcu(myvec)<<endl;
	
	// ����ѭ������ 
	int result = -1, retemp;
	int size = myvec.size();
	int begin, end;
	for(int i = 0, j = size - 1; i <= j; i++, j--)
	{
		// i , j �Ƿ�Χ���������еĿ����� 
		// �ȴ� i �� j ������� 
		begin = i; 
		int min = INF;
		for(end = i; end <= j; end++)
		{
			myqueue.enqueue(myvec[end]);
			if(min > myvec[end]) min = myvec[end];
			// ��һ���ּ������ʱ��Сֵ��֪,����ֱ�ӽ��м��� 
			retemp = min * (end - begin + 1);
			if(retemp > result) result = retemp;
		}
		// ��ʼ�˳����� 
		end = j;
		for(begin = i; begin < end; begin++)
		{
			myqueue.dequeue();
			min = myfind(myvec,begin,end);
			retemp = min * (end - begin + 1);
			if(retemp > result) result = retemp;
		}
	} 
	cout<<result<<endl;
	return 0;
} 
