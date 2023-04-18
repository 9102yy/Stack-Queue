#include<iostream>
#include<math.h>
#include<algorithm>
using namespace std;
typedef int Rank; //秩
#define DEFAULT_CAPACITY  3 //默认的初始容量（实际应用中可设置为更大）

template <typename T> class Vector { //向量模板类
protected:
    Rank _size; Rank _capacity;  T* _elem; //规模、容量、数据区
    void copyFrom(T const* A, Rank lo, Rank hi) //复制数组区间A[lo, hi) A已经是一个地址名称 
    {
        _elem = new T[_capacity = 2 * (hi - lo)]; _size = 0;
        while (lo < hi)
            _elem[_size++] = A[lo++];
    }
    void expand() //空间不足时扩容
    {
        if (_size < _capacity) return;
        if (_capacity < DEFAULT_CAPACITY) _capacity = DEFAULT_CAPACITY;
        T* oldelem = _elem; _elem = new T[_capacity <<= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldelem[i];
        delete[] oldelem;
    }
    void shrink() //装填因子过小时压缩
    {
        if (_capacity < DEFAULT_CAPACITY << 1) return;
        if (_size << 2 > _capacity) return;  // 以25%为界限，
        T* oldelem = _elem; _elem = new T[_capacity >>= 1];
        for (int i = 0; i < _size; i++)
            _elem[i] = oldelem[i];
        delete[] oldelem;

    }
    
    Rank maxItem(Rank lo, Rank hi) //选取最大元素
    {
        int max = _elem[0];
        for (int i = 1; i < _size; i++)
            if (_elem[i] > max) {
                max = _elem[i];
            }
        return max;
    }
    
    void heapSort(Rank lo, Rank hi); //堆排序（稍后结合完全堆讲解）
    Rank partition(Rank lo, Rank hi); //轴点构造算法
    void quickSort(Rank lo, Rank hi); //快速排序算法
    void shellSort(Rank lo, Rank hi); //希尔排序算法
public:
    // 构造函数
    Vector(Rank c = DEFAULT_CAPACITY, Rank s = 0, T v = 0) //容量为c、规模为s、所有元素初始为 v
    {
        _elem = new T[_capacity = c]; for (_size = 0; _size < s; _elem[_size++] = v);
    } //s<=c
    
    Vector(T const* A, Rank n) { copyFrom(A, 0, n); } //数组整体复制
    Vector(T const* A, Rank lo, Rank hi) { copyFrom(A, lo, hi); } //区间
    Vector(Vector<T> const& V) { copyFrom(V._elem, 0, V._size); } //向量整体复制
    Vector(Vector<T> const& V, Rank lo, Rank hi) { copyFrom(V._elem, lo, hi); } //区间
 // 析构函数
    ~Vector() { delete[] _elem; } //释放内部空间
 // 只读访问接口
    Rank size() const { return _size; } //规模
    bool empty() const { return !_size; } //判空
    //Rank find(T const& e) const { return find(e, 0, _size); } //无序向量整体查找
    Rank find(T const& e, Rank lo, Rank hi, bool (*pf)(T ,T )) const //无序向量区间查找
    {
        while( (lo<hi--) && (!(*pf)(e , _elem[hi]) ) );
        return hi;
    }
    Rank search(T const& e) const //有序向量整体查找
    {
        return (0 >= _size) ? -1 : search(e, 0, _size);
    }
    Rank search(T const& e, Rank lo, Rank hi, bool (*pf)(T ,T )) const //有序向量区间查找
    {
        while (lo < hi) {
            Rank mi = (lo + hi) >> 1;
            (e <= _elem[mi]) ? hi = mi : lo = mi + 1;
        }
        return --lo;
    }
    
    // 可写访问接口
    T& operator[] (Rank r)
    {
        //重载下标操作符，可以类似于数组形式引用各元素
        return _elem[r];
    }
    //  const T& operator[] (Rank r) const; //仅限于做右值的重载版本
    Vector<T>& operator= (Vector<T> const& V) //重载赋值操作符，以便直接克隆向量
    {
        if (_elem)
            delete[]_elem;
        copyFrom(V._elem, 0, V.size());
        return *this;
    }
    T remove(Rank r) //删除秩为r的元素
    {
        T e = _elem[r];
        remove(r, r + 1);
        return e;
    }
    Rank remove(Rank lo, Rank hi) //删除秩在区间[lo, hi)之内的元素
    {
        //考虑鲁棒性 
        if (lo<0 || hi>_size) { printf("越界\n"); return 0; }
        if (lo == hi) return 0;
        while (hi < _size) _elem[lo++] = _elem[hi++];
        _size = lo;
        shrink();
        return hi - lo;
    }
    Rank insert(Rank r, T const& e) //插入元素
    {
        // 考虑鲁棒性 
        if (r > _size) { printf("越界\n"); return -1; }
        expand();
        for (int i = _size; i > r; i--)
            _elem[i] = _elem[i - 1];
        _elem[r] = e; _size++;
        return r;
    }
    Rank insert(T const& e) { return insert(_size, e); } //默认作为末元素插入
    
    
    
    
    void sort(Rank lo, Rank hi) //对[lo, hi)排序
    {
        quickSort(lo, hi);
    }
    void sort() { sort(0, _size); } //整体排序

	void merge(Rank lo, Rank mi, Rank hi, bool (*pf)(T ,T )) //归并算法
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
    void mergeSort(Rank lo, Rank hi,bool (*pf)(T ,T )) //归并排序算法
    {
        if (hi - lo < 2) return;
        int mi = (lo + hi) / 2;
        mergeSort(lo, mi, (*pf)); mergeSort(mi, hi, (*pf));
        merge(lo, mi, hi,(*pf));
    }

	bool bubble(Rank lo, Rank hi, bool (*pf)(T ,T ) ) //扫描交换
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
    
    void bubbleSort(Rank lo, Rank hi,bool (*pf)(T ,T )) //起泡排序算法
    {
        while (!bubble(lo, hi--, (*pf)));
    }


	void selectionSort(Rank lo, Rank hi) //选择排序算法
    {
        switch (rand() % 3) {
        case 1: bubbleSort(lo, hi); break;
        case 2: mergeSort(lo, hi); break;
        default: quickSort(lo, hi); break;
        }
    } 



    void unsort(Rank lo, Rank hi) //对[lo, hi)置乱
    {
        T* V = _elem + lo;
        for (Rank i = hi - lo; i > 0; i--)
            swap(V[i - 1], V[rand() % i]);
    }
    void unsort() { unsort(0, _size); } //整体置乱

    Rank deduplicate( bool (*pf)(T ,T ) ) //无序去重
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
    Rank uniquify() //有序去重
    {
        Rank i = 0, j = 0;
        while (++j < _size)
            if (_elem[i] != _elem[j])
                _elem[++i] = _elem[j];
        _size = ++i;
        shrink();
        return j - i;
    }

    // 遍历
    void traverse(void ( *visit ) ( T& )) //遍历（使用函数指针，只读或局部性修改）
    {
        for (int i = 0; i < _size; i++) visit(_elem[i]);
    }
    template <typename VST> void traverse(VST& visit) //遍历（使用函数对象，可全局性修改）
    {
        for (int i = 0; i < _size; i++) visit(_elem[i]);
    }
}; //Vector

