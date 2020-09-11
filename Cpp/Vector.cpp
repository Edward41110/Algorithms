#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string>
using namespace std;

ostream& tab(ostream&os)		// ����һ���Ʊ�λ
{
	os << "\t";
	return os;
}

class CreateVectorFailed		// ����vector�����࣬���������Ϣ
{
public:
	CreateVectorFailed(int val) : bad_value(val) { }
	void diagnostic() { cerr << "the size " << bad_value << " is illegal to create a vector" << endl; }
private:
	int bad_value;
};

class AbnormalVector			// vectorδ��ȷ��ʼ�������࣬���������Ϣ
{
public:
	static void diagnostic() { cerr << "Array is not generated correctly, please use modify_base to revise" << endl; }
};

class VectorIndexOutOfRange		// vector�±����Խ���࣬���������Ϣ
{
public:
	VectorIndexOutOfRange(int val) : bad_value(val) { }
	void diagnostic() { cerr << "the index " << bad_value << " is out of range" << endl; }
private:
	int bad_value;
};

class OptionFailed				// ��������ʧ����
{
public:
	OptionFailed(string OptionName, int val) : bad_val1(val) { NumOfPara = 1; }
	OptionFailed(string OptionName, int val1, int val2) : bad_val1(val1), bad_val2(val2) { NumOfPara = 2; }
	void diagnostic();
private:
	string OptionName;
	int bad_val1;
	int bad_val2;
	int NumOfPara;
};

void OptionFailed::diagnostic()		// ����������Ƽ��������	
{
	if (NumOfPara == 1)
		cerr << "the input " << bad_val1 << " for the option " << OptionName <<" is illegal" << endl;
	else
		cerr << "the input " << bad_val1 << " and " << bad_val2 << " for the option " << OptionName << " is illegal" << endl;
}

class OpenFileFailed			// ���ļ�ʧ���࣬�����ʧ�ܵ��ļ���
{
public:
	OpenFileFailed(string fname) : file_name(fname) { }
	void diagnostic() { cerr << "the file " << file_name << " can't open" << endl; }
private:
	string file_name;
};

template <class T>				// ��ģ������
class vector
{
public:							// ��������
	vector(int gb = 100);		// ���캯������Ҫ����������ʼ����Ĭ��100
	vector(vector&);			// �������캯��
	~vector();					// ��������
	int size() { return this->vector_size; }				// ����vector��ǰʵ��Ԫ�ظ���
	bool empty() { return this->vector_size == 0; }			// ����vector�Ƿ�Ϊ��
	int capacity() { return this->vector_capacity; }		// ����vector��ǰ����
	int growth_base() { return this->vector_growthBase; }	// ����vector��������
	void modify_base(int gb);				// �޸�vector��������
	void resize(int new_size = 0);			// �޸�vector����
	void shrink_to_fit();					// ʹvector�����޸�Ϊ��ǰ�洢��Ԫ�ظ���

	void push_back(const T& val);			// ѹ��Ԫ�ص�vectorĩβ
	void pop_back(T& ret);					// �������һ��Ԫ�أ���������vector��ɾ��
	void front(T& ret);						// �õ�ͷԪ�أ���ɾ��
	void back(T& ret);						// �õ�βԪ�أ���ɾ��
	void at(int pos, T& ret);				// �õ�posλ�õ�Ԫ�أ���ɾ��
	void max(int& idx);						// ����vector��ǰ���ֵ���±�
	void max(T& ret, int& idx);				// ����vector��ǰ�����ֵ�����±�
	void min(int& idx);						// ����vector��ǰ��Сֵ���±�
	void min(T& ret, int& idx);				// ����vector��ǰ����Сֵ�����±�
	void clear();							// ���vector
	void insert(int pos, const T& val);		// ��posλ�ò���һ��Ԫ��
	void erase(int pos);					// ����posλ�õ�Ԫ��
	void erase(int begin, int end);			// ����begin��endλ�õ�Ԫ��
	void swap(int pos1, int pos2);			// ����pos1,pos2λ�õ�Ԫ��
	void print_all_elements();				// ��ӡvector������Ԫ��

	void BubbleSort();			// ð������ӿ�
	void SelectionSort();		// ѡ������ӿ�
	void InsertionSort();		// ��������ӿ�
	void MergeSort();			// �鲢����ӿ�
	void QuickSort();			// ��������ӿ�
	void HeapSort();			// ������ӿ�

	T& operator[](int i);		// ͨ��[]���������vector��λ�õ�����
	void save(string file_name = "data.txt");						// ��������
	void load(string file_name = "data.txt", bool isClear = 1);		// װ�����ݣ���ѡ�Ƿ���յ�ǰvector��Ĭ�����
	friend bool operator==(const vector& l1, const vector& l2);		// �Ƚ�����vector�Ƿ����
	friend bool operator!=(const vector& l1, const vector& l2);		// �Ƚ�����vector�Ƿ����
private:						// ˽�з���
	T& operator()(int i) { return (this->data)[i]; }	// ����������λ�û�����÷���������Խ�����	
	void merge(int begin, int end);					// �鲢�����ӹ���
	void MergeSortProcess(int left, int right);		// �鲢����ʵ��
	int Partition(int begin, int end);				// �����������ֹ���
	void QuickSortProcess(int begin, int end);		// ��������ʵ��
	int HeapSortProcess(int numsSize, int root);	// ������ʵ��
	void MaxHeap();									// ������󶥶ѹ���ʵ��

	bool isWorkable;		// ��־vector�Ƿ����(�Ƿ���ȷ��ʼ��)
	int vector_size;		// vector��ǰԪ�ظ���
	int vector_capacity;	// vector��ǰ����
	int vector_growthBase;	// vector��ǰ��������
	T* data;				// ���ݴ���׵�ַ
};

template <class T>
vector<T>::vector(int gb) : vector_growthBase(gb)		// ���캯��
{
	try
	{
		if (this->vector_growthBase <= 0)
			throw CreateVectorFailed(this->vector_growthBase);		// ������������<=0���׳�����ʧ���쳣
		this->isWorkable = true;
		this->vector_capacity = vector_growthBase;
		this->vector_size = 0;
		this->data = new int[this->vector_capacity];
	}
	catch (CreateVectorFailed& FailedInfo)
	{
		FailedInfo.diagnostic();
		this->isWorkable = false;			// ���vector������
		this->data = NULL;
		AbnormalVector::diagnostic();
	}
}

template <class T>					// �������캯��
vector<T>::vector(vector &l)
{
	try
	{
		if (!this->isWorkable)			// ��Դvector�����ã��׳�����vector�쳣����ͬ
			throw AbnormalVector();
		this->vector_size = l.vector_size;
		this->vector_capacity = l.vector_capacity;
		this->vector_growthBase = l.vector_growthBase;
		this->data = new int[this->vector_capacity];
		for (int i = 0;i < this->vector_size;i++)		// vector�������
			(*this)[i] = l[i];
	}
	catch (AbnormalVector& FailedInfo)	// ��׽vector�������쳣
	{
		FailedInfo.diagnostic();		// ���������Ϣ
	}
}

template <class T>
vector<T>::~vector()			// ��������
{
	if (this->data)				// ��data��Ϊ�գ�����տռ�
		delete[]this->data;
}

template <class T>
void vector<T>::modify_base(int gb)		
{
	try
	{
		if (gb <= 0)			// ��������������<=0���׳������쳣������ͬ
			throw OptionFailed("modify_base", gb);
		this->vector_growthBase = gb;
		if (!this->isWorkable)		// ��vector�������Ϊ�����ã���Ϊ����
		{
			this->isWorkable = true;
			this->resize();			// Ϊ�����򿪱ٿռ�
		}
	}
	catch (OptionFailed& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::resize(int new_capacity)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (new_capacity < 0)
			throw CreateVectorFailed(new_capacity);
		if (!new_capacity)			// �������0�����¿ռ��СΪԭ�ռ�+��������
			new_capacity = this->vector_capacity + this->vector_growthBase;
		this->vector_capacity = new_capacity;
		T* new_data = new T[this->vector_capacity];
		this->vector_size = this->vector_size < this->vector_capacity ? this->vector_size : this->vector_capacity;	// ������ݸ������ڿռ䣬���������������
		for (int i = 0;i < this->vector_size;i++)
			new_data[i] = (*this)[i];
		if (this->data)
			delete[]this->data;
		this->data = new_data;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (CreateVectorFailed& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::shrink_to_fit()
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size == 0) this->resize(this->growth_base());	// ���û�����ݣ�������������resize
		else this->resize(this->vector_size);		// ��������ݣ��������ݸ���resize
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::push_back(const T&val)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size == this->vector_capacity)		// ���vector���������Զ�����
			this->resize();
		(*this)(this->vector_size) = val;
		this->vector_size++;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::pop_back(T& ret)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size == 0)
			throw VectorIndexOutOfRange(0);
		ret = (*this)[this->vector_size - 1];
		this->vector_size--;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (VectorIndexOutOfRange& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::front(T& ret)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size == 0)
			throw VectorIndexOutOfRange(0);
		ret = (*this)[0];
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (VectorIndexOutOfRange& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::back(T& ret)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size == 0)
			throw VectorIndexOutOfRange(0);
		ret = (*this)[this->vector_size - 1];
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (VectorIndexOutOfRange& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::at(int pos, T& ret)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (pos < 0 || pos >= this->vector_size)
			throw VectorIndexOutOfRange(pos);
		ret = (*this)[pos];
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (VectorIndexOutOfRange& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::max(int&idx)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (!this->vector_size) return;
		idx = 0;
		for (int i = 1;i < this->vector_size;i++)	// �����������ֵ����¼�±�
			if ((*this)[i] > (*this)[idx])
				idx = i;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::max(T&ret, int&idx)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (!this->vector_size) return;
		this->max(idx);					// �����������غ���������ֵ�±꣬��ͬ
		ret = (*this)[idx];
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::min(int&idx)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (!this->vector_size) return;
		idx = 0;
		for (int i = 1;i < this->vector_size;i++)
			if ((*this)[i] < (*this)[idx])
				idx = i;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::min(T&ret, int&idx)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (!this->vector_size) return;
		this->min(idx);
		ret = (*this)[idx];
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::clear()
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		this->vector_size = 0;
		this->shrink_to_fit();
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::insert(int pos, const T& val)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (pos < 0 || pos > this->vector_size)
			throw VectorIndexOutOfRange(pos);
		if (this->vector_size == this->vector_capacity)
			this->resize();
		this->vector_size++;
		for (int i = this->vector_size - 1;i > pos;i--)
			(*this)[i] = (*this)[i - 1];
		(*this)[pos] = val;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (VectorIndexOutOfRange& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::erase(int pos)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (pos < 0 || pos >= this->vector_size)
			throw VectorIndexOutOfRange(pos);
		for (int i = pos + 1;i < this->vector_size - 1;i++)
			(*this)[i - 1] = (*this)[i];
		this->vector_size--;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (VectorIndexOutOfRange& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::erase(int begin, int end)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (begin < 0 || begin > end || end >= this->vector_size)
			throw OptionFailed("erase", begin, end);
		int length = end - begin + 1;
		for (int i = end + 1;i < this->vector_size;i++)
			(*this)[i - length] = (*this)[i];
		this->vector_size -= length;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (OptionFailed& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::swap(int pos1, int pos2)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (pos1 < 0 || pos1 >= this->vector_size || pos2 < 0 || pos2 >= this->vector_size)
			throw OptionFailed("swap", pos1, pos2);
		if (pos1 == pos2) return;
		T temp = (*this)[pos1];
		(*this)[pos1] = (*this)[pos2];
		(*this)[pos2] = temp;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (OptionFailed& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template<class T>
void vector<T>::print_all_elements()
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (!this->vector_size)
			cout << "the list is empty" << endl;
		for (int i = 0;i < this->vector_size;i++)
		{
			cout << (*this)[i] << tab;
			if (!((i + 1) % 5)) cout << endl;
		}
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::BubbleSort()
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size < 2) return;
		for (int i = 0;i < this->vector_size;i++)
			for (int j = 1;j < this->vector_size - i;j++)
				if ((*this)[j - 1] > (*this)[j])
					swap(j - 1, j);
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::SelectionSort()
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size < 2) return;
		for (int i = 0;i < this->vector_size;i++)
		{
			int MinIndex = i;
			for (int j = i + 1;j < this->vector_size;j++)
				if ((*this)[j] < (*this)[MinIndex])
					MinIndex = j;
			swap(i, MinIndex);
		}
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::InsertionSort()
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size < 2) return;
		int i, j, num;
		for (i = 1;i < this->vector_size;i++)
		{
			num = (*this)[i];
			for (j = i - 1;j >= 0;j--)
				if ((*this)[j] > num)
					(*this)[j + 1] = (*this)[j];
				else break;
			(*this)[j + 1] = num;
		}
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::merge(int begin, int end)
{
	if (begin == end) return;
	int mid = begin + ((end - begin) >> 1);
	int left = begin, right = mid + 1, index = 0;
	int length = end - begin + 1;
	T* help = new T[length];
	while (left <= mid && right <= end)
		help[index++] = (*this)[left] <= (*this)[right] ? (*this)[left++] : (*this)[right++];
	while (left <= mid)
		help[index++] = (*this)[left++];
	while (right <= end)
		help[index++] = (*this)[right++];
	for (index = 0;index < length;index++)
		(*this)[index + begin] = help[index];
	delete[]help;
}

template <class T>
void vector<T>::MergeSortProcess(int left, int right)
{
	if (left == right) return;
	int mid = left + ((right - left) >> 1);
	this->MergeSortProcess(left, mid);
	this->MergeSortProcess(mid + 1, right);
	this->merge(left, right);
}

template <class T>
void vector<T>::MergeSort()
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size < 2) return;
		this->MergeSortProcess(0, this->vector_size - 1);
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
int vector<T>::Partition(int begin, int end)
{
	int pivotkey = (*this)[begin];
	while (begin < end)
	{
		while (begin<end && (*this)[end] >= pivotkey)
			end--;
		swap(begin, end);
		while (begin < end && (*this)[begin] <= pivotkey)
			begin++;
		swap(begin, end);
	}
	return begin;
}

template <class T>
void vector<T>::QuickSortProcess(int begin, int end)
{
	int pivot;
	if (begin < end)
	{
		pivot = Partition(begin, end);
		QuickSortProcess(begin, pivot - 1);
		QuickSortProcess(pivot + 1, end);
	}
}

template <class T>
void vector<T>::QuickSort()
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size < 2) return;
		this->QuickSortProcess(0, this->vector_size - 1);
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
int vector<T>::HeapSortProcess(int numsSize, int root)
{
	if (root * 2 > numsSize) return 0;
	if ((root * 2 + 1) <= numsSize)
	{
		int maxChildIdx = (*this)[root * 2 - 1] >= (*this)[root * 2] ? root * 2 - 1 : root * 2;
		if ((*this)[root - 1] >= (*this)[maxChildIdx]) return 0;
		else
		{
			swap(root - 1, maxChildIdx);
			return maxChildIdx + 1;
		}
	}
	else
		if ((*this)[root - 1] >= (*this)[root * 2 - 1]);
		else swap(root - 1, root * 2 - 1);
	return 0;
}

template <class T>
void vector<T>::MaxHeap()
{
	int i, j, depth;
	for (depth = 1;1 << depth < this->vector_size + 1;depth++);
	for (i = 0;i < depth;i++)
		for (j = this->vector_size;j > 1;j -= 2)
		{
			if (j / 2 < (1 << i) - 1) break;
			HeapSortProcess(this->vector_size, j / 2);
		}
}

template <class T>
void vector<T>::HeapSort()
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (this->vector_size < 2) return;
		MaxHeap();
		for (int i = this->vector_size - 1;i > 1;i--)
		{
			int root = 1;
			swap(0, i);
			while (root = HeapSortProcess(i, root));
		}
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
T& vector<T>::operator[](int i)		// ͨ���±���Ԫ������
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		if (i < 0 || this->vector_size <= i)
			throw VectorIndexOutOfRange(i);
		return this->data[i];
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (VectorIndexOutOfRange& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
bool operator==(const vector<T>&l1, const vector<T>&l2)		// Ϲд����ȫû��ʵ����;
{
	try
	{
		if (!(l1.isWorkable && l2.isWorkable))
			throw AbnormalVector();
		if (l1.vector_size != l2.vector_size) return false;
		for (int i = 0; i < l1.vector_size;i++)
			if (l1[i] != l2[i])
				return false;
		return true;
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
bool operator!=(const vector<T>&l1, const vector<T>&l2)
{
	try
	{
		if (!(l1.isWorkable && l2.isWorkable))
			throw AbnormalVector();
		return !(l1 == l2);
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::save(string file_name)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		ofstream OF(file_name);
		if (OF.is_open())
		{
			OF << "total:" << this->vector_size << endl;	// ���ȴ���Ԫ�ظ���
			for (int i = 0;i < this->vector_size;i++)		// ��˳��д���ļ�
				OF << (*this)[i] << endl;
			OF.close();
			cout << "saved." << endl;
		}
		else
			throw OpenFileFailed(file_name);		// �ļ�δ�򿪣��׳��ļ�δ�򿪴�����ͬ
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (OpenFileFailed& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

template <class T>
void vector<T>::load(string file_name, bool isClear)
{
	try
	{
		if (!this->isWorkable)
			throw AbnormalVector();
		ifstream IF(file_name);
		if (IF.is_open())
		{
			int size;
			if (isClear)
				this->clear();				// ���
			IF.ignore(1024, ':');			// ����":"��֮ǰ����
			IF >> size;						// ����size
			T data;
			for (int i = 0;i < size;i++)	// �������vector
			{
				IF >> data;
				this->push_back(data);
			}
			IF.close();
			cout << "loaded." << endl;
		}
		else
			throw OpenFileFailed(file_name);
	}
	catch (AbnormalVector& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
	catch (OpenFileFailed& FailedInfo)
	{
		FailedInfo.diagnostic();
	}
}

int MainMenu();				// ������˵�����ȡ����

int main()					// ѭ�����Թ���
{
	int i;
	vector<int> l(1);
	int cmd = MainMenu();
	while (cmd)
	{
		switch (cmd)
		{
		case 1:  cout << l.size(); break;
		case 2:  cout << l.empty(); break;
		case 3:  cout << l.capacity(); break;
		case 4:  cout << l.growth_base(); break;
		case 5:
		{
			int gb;
			cin >> gb;
			l.modify_base(gb);
			break;
		}
		case 6:
		{
			int num;
			cin >> num;
			l.resize(num);
			break;
		}
		case 7:  l.shrink_to_fit(); break;
		case 8:
		{
			int num;
			cin >> num;
			l.push_back(num);
			break;
		}
		case 9:
		{
			l.pop_back(i);
			cout << i << endl; break;
		}
		case 10:
		{
			l.front(i);
			cout << i << endl;
			break;
		}
		case 11:
		{
			l.back(i);
			cout << i << endl;
			break;
		}
		case 12:
		{
			int pos;
			cin >> pos;
			l.at(pos, i);
			cout << i << endl;
			break;
		}
		case 13:
		{
			int pos, max;
			l.max(pos);
			l.at(pos, max);
			cout << max << tab << pos <<endl;
			break;
		}
		case 14:
		{
			int pos, max;
			l.max(max, pos);
			cout << max << tab << pos << endl;
			break;
		}
		case 15:
		{
			int pos, min;
			l.min(pos);
			l.at(pos, min);
			cout << min << tab << pos << endl;
			break;
		}
		case 16:
		{
			int pos, min;
			l.min(min, pos);
			cout << min << tab << pos << endl;
			break;
		}
		case 17: l.clear(); break;
		case 18:
		{
			int num, pos;
			cin >> pos >> num;
			l.insert(pos, num);
			break;
		}
		case 19:
		{
			int pos;
			cin >> pos;
			l.erase(pos);
			break;
		}
		case 20:
		{
			int begin, end;
			cin >> begin >> end;
			l.erase(begin, end);
			break;
		}
		case 21:
		{
			int pos1, pos2;
			cin >> pos1 >> pos2;
			l.swap(pos1, pos2);
			break;
		}
		case 22: l.print_all_elements(); break;
		case 23: l.BubbleSort(); break;
		case 24: l.SelectionSort(); break;
		case 25: l.InsertionSort(); break;
		case 26: l.MergeSort(); break;
		case 27: l.QuickSort(); break;
		case 28: l.HeapSort(); break;
		case 29: l.save(); break;
		case 30: l.load(); break;
		}
		cout << endl;
		system("pause");
		cmd = MainMenu();
	}
	return 0;
}

bool Judge()
{
	char ch;
	cout << "Y/N: ";
	cin >> ch;
	if (ch == 'Y' || ch == 'y') return true;
	else return false;
}

int MainMenu()
{
	system("cls");
	int cmd;
	cout << "<Main Menu>" << endl << endl << tab;
	cout << " 1. l.size()" << tab << tab;
	cout << " 2. l.empty()" << tab << tab;
	cout << " 3. l.capacity()" << endl << endl << tab;
	cout << " 4. l.grow_base()" << tab;
	cout << " 5. l.modify_base()" << tab;
	cout << " 6. l.resize()" << endl << endl << tab;
	cout << " 7. l.shrink_to_fit()" << tab;
	cout << " 8. l.push_back()" << tab;
	cout << " 9. l.pop_back()" << endl << endl << tab;
	cout << "10. l.front()" << tab << tab;
	cout << "11. l.back()" << tab << tab;
	cout << "12. l.at(pos)" << endl << endl << tab;
	cout << "13. l.max()" << tab << "return maxVal index" << tab << tab;
	cout << "14. l.max()" << tab << "return maxVal and its index" << endl << endl << tab;
	cout << "15. l.min()" << tab << "return minVal index" << tab << tab;
	cout << "16. l.min()" << tab << "return minVal and its index" << endl << endl << tab;
	cout << "17. l.clear()" << tab << tab;
	cout << "18. l.insert(pos, num)" << tab;
	cout << "19. l.erase(pos)" << endl << endl << tab;
	cout << "20. l.erase(pos1, pos2)" << tab;
	cout << "21. l.swap(pos1, pos2)" << tab;
	cout << "22. l.print_all_elements()" << endl << endl << tab;
	cout << "23. l.BubbleSort()" << tab;
	cout << "24. l.SelectionSort()" << tab;
	cout << "25. l.InsertionSort()" << endl << endl << tab;
	cout << "26. l.MergeSort()" << tab;
	cout << "27. l.QuickSort()" << tab;
	cout << "28. l.HeapSort()" << endl << endl << tab;
	cout << "29. l.save()" << tab << tab;
	cout << "30. l.load()" << tab << tab;
	cout << " 0. Quit" << endl << endl;
	cout << endl << "cmd: ";
	cin >> cmd;
	return cmd;
};
