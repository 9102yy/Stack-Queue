#include"../../Vector/Vector.h"
#include"../������/Complex.h"
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
bool mycompare(Complex e1, Complex e2) {  // �����㷨  
	if (e1.value > e2.value) return true;
	else if (e1.value == e2.value) {
		if (e1.real > e2.real) return true;
		else return false;
	}
	else return false;
}
bool mycompare2(Complex e1, Complex e2) {  // �����㷨 
	if (e1.value < e2.value) return true;
	else if (e1.value == e2.value) {
		if (e1.real < e2.real) return true;
		else return false;
	}
	else return false;
}

int mysearch(Vector<Complex> A, double e, Rank lo, Rank hi) //���������������
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

	printf("---------------��һ����---------------------\n");


	// ���� ���������� 
	printf("����ǰ��\n");
	a.traverse(myprint); cout << endl;
	a.unsort();
	printf("���Һ�\n");
	a.traverse(myprint); cout << endl;

	//����  ���������
	printf("����ǰ��\n");
	a.traverse(myprint); cout << endl;
	a.insert(a[5]);
	printf("�����\n");
	a.traverse(myprint); cout << endl;

	//����  ������ɾ�� 
	printf("ɾ��ǰ��\n");
	a.traverse(myprint); cout << endl;
	a.remove(1, 3);
	printf("ɾ����\n");
	a.traverse(myprint); cout << endl;

	//����  ���������
	int frand = rand() % a.size();
	printf("����%d�������ڵ�λ��\n", frand);
	int result = a.find(a[frand], 0, a.size(), mycmp);
	printf("�ҵ����Ϊ%d\n", result);


	a.insert(a[0]); // ʹ�ñض��ظ� 
	//����  ������Ψһ�� (����ȥ��) 
	printf("ȥ��ǰ��\n");
	a.traverse(myprint); cout << endl;
	a.deduplicate(mycmp);
	printf("ȥ�غ�\n");
	a.traverse(myprint); cout << endl;

	cout << endl; cout << endl; cout << endl;

	printf("---------------�ڶ�����---------------------\n");
	Vector<Complex> b(a, 0, a.size());
	//����  ���������� 

	printf("ð������ǰ��\n");
	a.traverse(myprint); cout << endl;
	a.bubbleSort(0, a.size(), mycompare);
	printf("ð�������\n");
	a.traverse(myprint); cout << endl;

	printf("�鲢����ǰ��\n");
	b.traverse(myprint); cout << endl;
	b.mergeSort(0, a.size(), mycompare);
	printf("�鲢�����\n");
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

	printf("��������£�\n");
	start = clock();
	c.bubbleSort(0, c.size(), mycompare);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("ð������%lf seconds\n", s);

	start = clock();
	d.mergeSort(0, d.size(), mycompare);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("�鲢����%lf seconds\n", s);


	printf("˳������£�\n");
	start = clock();
	c.bubbleSort(0, c.size(), mycompare);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("ð������%lf seconds\n", s);

	start = clock();
	d.mergeSort(0, d.size(), mycompare);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("�鲢����%lf seconds\n", s);

	printf("��������£�\n");
	start = clock();
	c.bubbleSort(0, c.size(), mycompare2);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("ð������%lf seconds\n", s);

	start = clock();
	d.mergeSort(0, d.size(), mycompare2);
	end = clock();
	s = (double)(end - start) / ClOCKS_PER_SEC;
	printf("�鲢����%lf seconds\n", s);

	cout << endl; cout << endl; cout << endl;

	printf("---------------��������---------------------\n");
	a.mergeSort(0, a.size(), mycompare); // �� a ��Ϊԭ������������������  
	a.traverse(myprint); cout << endl;

	int m1 = 10, m2 = 200; // Ϊ��ѯ�ķ�Χ  
	printf("��ѯ���Ϊ \n");
	Vector<Complex> vecresult = partqurry(a, m1, m2);

	vecresult.traverse(myprint); cout << endl;
}


