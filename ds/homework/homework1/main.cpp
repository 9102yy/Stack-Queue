#include"../../Vector/Vector.h"
#include"../复数类/Complex.h"
#include<time.h>
#define ClOCKS_PER_SEC 1000;
using namespace std;
void myprint(Complex e) {
	printf("%.2f+(%.2fi) ", e.real, e.imag);
}
bool mycmp(Complex e1, Complex e2) {
	if (e1.real == e2.real && e1.imag == e2.imag) return true;
	return false;
}
bool mycompare(Complex e1, Complex e2) {  // 升序算法  
	if (e1.value > e2.value) return true;
	else if (e1.value == e2.value) {
		if (e1.real > e2.real) return true;
		else return false;
	}
	else return false;
}
bool mycompare2(Complex e1, Complex e2) {  // 降序算法 
	if (e1.value < e2.value) return true;
	else if (e1.value == e2.value) {
		if (e1.real < e2.real) return true;
		else return false;
	}
	else return false;
}

int mysearch(Vector<Complex> A, double e, Rank lo, Rank hi) //有序向量区间查找
{
	while (lo < hi) {
		Rank mi = (lo + hi) >> 1;
		((e <= A[mi].value)) ? hi = mi : lo = mi + 1;
	}
	return lo;
}
Vector<Complex> partqurry(Vector<Complex> A, int lo, int hi)
{
	int i = mysearch(A, lo, 0, A.size());
	int j = mysearch(A, hi, 0, A.size());
	Vector<Complex> vresult(A, i, j);
	return vresult;
}
int main()
{
	Complex pre(1, 1);
	Vector<Complex> a(20, 5, pre);
	for (int i = 0; i < a.size(); i++)
	{
		a[i].comrand();
		a[i].abscomplex();
	}

	printf("---------------第一部分---------------------\n");


	// 测试 向量类置乱 
	printf("置乱前：\n");
	a.traverse(myprint); cout << endl;
	a.unsort();
	printf("置乱后：\n");
	a.traverse(myprint); cout << endl;

	//测试  向量类插入
	printf("插入前：\n");
	a.traverse(myprint); cout << endl;
	a.insert(a[5]);
	printf("插入后：\n");
	a.traverse(myprint); cout << endl;

	//测试  向量类删除 
	printf("删除前：\n");
	a.traverse(myprint); cout << endl;
	a.remove(1, 3);
	printf("删除后：\n");
	a.traverse(myprint); cout << endl;

	//测试  向量类查找
	int frand = rand() % a.size();
	printf("查找%d的秩所在的位置\n", frand);
	int result = a.find(a[frand], 0, a.size(), mycmp);
	printf("找到结果为%d\n", result);


	a.insert(a[0]); // 使得必定重复 
	//测试  向量类唯一化 (无序去重) 
	printf("去重前：\n");
	a.traverse(myprint); cout << endl;
	a.deduplicate(mycmp);
	printf("去重后：\n");
	a.traverse(myprint); cout << endl;

	cout << endl; cout << endl; cout << endl;

	printf("---------------第二部分---------------------\n");
	Vector<Complex> b(a, 0, a.size());
	//测试  向量类排序 

	printf("冒泡排序前：\n");
	a.traverse(myprint); cout << endl;
	a.bubbleSort(0, a.size(), mycompare);
	printf("冒泡排序后：\n");
	a.traverse(myprint); cout << endl;

	printf("归并排序前：\n");
	b.traverse(myprint); cout << endl;
	b.mergeSort(0, a.size(), mycompare);
	printf("归并排序后：\n");
	b.traverse(myprint); cout << endl;

	cout << endl; cout << endl;
	Vector<Complex> c(16000, 7000, pre);
	for (int i = 0; i < c.size(); i++)
	{
		c[i].comrand();
		c[i].abscomplex();
	}

	Vector<Complex> d(c, 0, c.size());

	clock_t start, end;
	double s;

	printf("乱序情况下：\n");
	start = clock();
	c.bubbleSort(0, c.size(), mycompare);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("冒泡排序：%lf seconds\n", s);

	start = clock();
	d.mergeSort(0, d.size(), mycompare);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("归并排序：%lf seconds\n", s);


	printf("顺序情况下：\n");
	start = clock();
	c.bubbleSort(0, c.size(), mycompare);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("冒泡排序：%lf seconds\n", s);

	start = clock();
	d.mergeSort(0, d.size(), mycompare);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("归并排序：%lf seconds\n", s);

	printf("逆序情况下：\n");
	start = clock();
	c.bubbleSort(0, c.size(), mycompare2);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("冒泡排序：%lf seconds\n", s);

	start = clock();
	d.mergeSort(0, d.size(), mycompare2);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("归并排序：%lf seconds\n", s);

	cout << endl; cout << endl; cout << endl;

	printf("---------------第三部分---------------------\n");
	a.mergeSort(0, a.size(), mycompare); // 用 a 作为原向量操作，升序排列  
	a.traverse(myprint); cout << endl;

	int m1 = 10, m2 = 200; // 为查询的范围  
	printf("查询结果为 \n");
	Vector<Complex> vecresult = partqurry(a, m1, m2);

	vecresult.traverse(myprint); cout << endl;
}


