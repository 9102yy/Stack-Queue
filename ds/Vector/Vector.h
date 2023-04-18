#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
typedef int Rank; //��
#define DEFAULT_CAPACITY  3 //Ĭ�ϵĳ�ʼ������ʵ��Ӧ���п�����Ϊ����

template <typename T> class Vector { //����ģ����
protected:
    Rank _size; Rank _capacity;  T* _elem; //��ģ��������������
    void copyFrom(T const* A, Rank lo, Rank hi) //������������A[lo, hi) A�Ѿ���һ����ַ���� 
    {
        _elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;
        while (lo < hi)
            _elem[_size++] = A[lo++];
    }
    void expand() //�ռ䲻��ʱ����
    {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T* oldelem = _elem; _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldelem[i];
        delete[] oldelem;
    }
    void shrink() //װ�����ӹ�Сʱѹ��
    {
        if (_capacity < DEFAULT_CAPACITY << 1) return;
        if (_size << 2 > _capacity) return;  // ��25%Ϊ���ޣ�
        T* oldelem = _elem; _elem = new T[_capacity >>= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldelem[i];
        delete[] oldelem;

    }
    
    Rank maxItem(Rank lo, Rank hi) //ѡȡ���Ԫ��
    {
        int max = _elem[0];
        for (int i = 1; i < _size; i++)
            if (_elem[i] > max) {
                max = _elem[i];
            }
        return max;
    }
    
    void heapSort(Rank lo, Rank hi); //�������Ժ�����ȫ�ѽ��⣩
    Rank partition(Rank lo, Rank hi); //��㹹���㷨
    void quickSort(Rank lo, Rank hi); //���������㷨
    void shellSort(Rank lo, Rank hi); //ϣ�������㷨
public:
    // ���캯��
    Vector(Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) //����Ϊc����ģΪs������Ԫ�س�ʼΪ v
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //�������帴��
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //����
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //�������帴��
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //����
 // ��������
    ~Vector() { delete[] _elem; } //�ͷ��ڲ��ռ�
 // ֻ�����ʽӿ�
    Rank size() const { return _size; } //��ģ
    bool empty() const { return !_size; } //�п�
    //Rank find(T const& e) const { return find(e, 0, _size); } //���������������
    Rank find(T const& e, Rank lo, Rank hi, bool (*pf)(T ,T )) const //���������������
    {
        while( (lo<hi--) && (!(*pf)(e , _elem[hi]) ) );
        return hi;
    }
    Rank search(T const& e) const //���������������
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi, bool (*pf)(T ,T )) const //���������������
    {
        while (lo < hi) {
            Rank mi = (lo + hi) >> 1;
            (e <= _elem[mi]) ? hi = mi : lo = mi + 1;
        }
        return --lo;
    }
    
    // ��д���ʽӿ�
    T& operator[] (Rank r)
    {
        //�����±������������������������ʽ���ø�Ԫ��
        return _elem[r];
    }
    //  const T& operator[] (Rank r) const; //����������ֵ�����ذ汾
    Vector<T>& operator= (Vector<T> const& V) //���ظ�ֵ���������Ա�ֱ�ӿ�¡����
    {
        if (_elem)
            delete[]_elem;
        copyFrom(V._elem, 0, V.size());
        return *this;
    }
    T remove(Rank r) //ɾ����Ϊr��Ԫ��
    {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }
    Rank remove(Rank lo, Rank hi) //ɾ����������[lo, hi)֮�ڵ�Ԫ��
    {
        //����³���� 
        if (lo<0 || hi>_size) { printf("Խ��\n"); return 0; }
        if (lo == hi) return 0;
        while (hi < _size) _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }
    Rank insert(Rank r, T const& e) //����Ԫ��
    {
        // ����³���� 
        if (r > _size) { printf("Խ��\n"); return -1; }
        expand();
        for (int i = _size; i > r; i--)
            _elem[i] = _elem[i - 1];
        _elem[r] = e; _size++;
        return r;
    }
    Rank insert(T const& e) { return insert(_size, e); } //Ĭ����ΪĩԪ�ز���
    
    
    
    
    void sort(Rank lo, Rank hi) //��[lo, hi)����
    {
        quickSort(lo, hi);
    }
    void sort() { sort(0, _size); } //��������

	void merge(Rank lo, Rank mi, Rank hi, bool (*pf)(T ,T )) //�鲢�㷨
    {
        T* A = _elem + lo;
        int lb = mi - lo; T* B = new T[lb];
        for (Rank i = 0; i < lb; B[i] = A[i++]);
        int lc = hi - mi; T* C = _elem + mi;
        for (Rank i = 0, j = 0, k = 0; (j < lb) || (k < lc);) {
            if ((j < lb) && (!(k < lc) || !(*pf)(B[j] , C[k]))) A[i++] = B[j++];
            if ((k < lc) && (!(j < lb) || ((*pf)( B[j], C[k] )))) A[i++] = C[k++];
        }
        delete[] B;
    }
    void mergeSort(Rank lo, Rank hi,bool (*pf)(T ,T )) //�鲢�����㷨
    {
        if (hi - lo < 2) return;
        int mi = (lo + hi) / 2;
        mergeSort(lo, mi, (*pf)); mergeSort(mi, hi, (*pf));
        merge(lo, mi, hi,(*pf));
    }

	bool bubble(Rank lo, Rank hi, bool (*pf)(T ,T ) ) //ɨ�轻��
    {
        bool sorted = true;
        while (++lo < hi)
            if ((*pf)(_elem[lo - 1] , _elem[lo]))
            {
                sorted = false;
                swap(_elem[lo - 1], _elem[lo]);
            }
        return sorted;
    }
    
    void bubbleSort(Rank lo, Rank hi,bool (*pf)(T ,T )) //���������㷨
    {
        while (!bubble(lo, hi--, (*pf)));
    }


	void selectionSort(Rank lo, Rank hi) //ѡ�������㷨
    {
        switch (rand() % 3) {
        case 1: bubbleSort(lo, hi); break;
        case 2: mergeSort(lo, hi); break;
        default: quickSort(lo, hi); break;
        }
    } 



    void unsort(Rank lo, Rank hi) //��[lo, hi)����
    {
        T* V = _elem + lo;
        for (Rank i = hi - lo; i > 0; i--)
            swap(V[i - 1], V[rand() % i]);
    }
    void unsort() { unsort(0, _size); } //��������

    Rank deduplicate( bool (*pf)(T ,T ) ) //����ȥ��
    {
        int oldSize = _size;
        Rank i = 1;
        while (i < _size)
        {
            if(find(_elem[i], 0, i,(*pf)) < 0){
            	i++;
			}else{
				remove(i);
			}
		}
        return oldSize - _size;
    }
    Rank uniquify() //����ȥ��
    {
        Rank i = 0, j = 0;
        while (++j < _size)
            if (_elem[i] != _elem[j])
                _elem[++i] = _elem[j];
        _size = ++i;
        shrink();
        return j - i;
    }

    // ����
    void traverse(void ( *visit ) ( T& )) //������ʹ�ú���ָ�룬ֻ����ֲ����޸ģ�
    {
        for (int i = 0; i < _size; i++) visit(_elem[i]);
    }
    template <typename VST> void traverse(VST& visit) //������ʹ�ú������󣬿�ȫ�����޸ģ�
    {
        for (int i = 0; i < _size; i++) visit(_elem[i]);
    }
}; //Vector

