#include "Header.h"

void createEmptyList(List&l)	//Tạo danh sách rỗng
{
	l.head = NULL;
	l.tail = NULL;
}
bool emptyList(List l)	//Kiểm tra danh sách có rỗng hay k
{
	if (l.head == NULL && l.tail == NULL)
	{
		return true;
	}
	return false;
}

void printlist(List& l)			// In list
{
	NODE* p = l.head;
	if (l.head == NULL)
		cout << "List rong";
	else
	{
		while (p != l.tail) {
			cout << p->data << " -> ";
			p = p->next;
		}
		cout << p->data;
	}
	
}
NODE* getNode(int n)	//Tạo 1 node
{
	NODE* p;
	p = new NODE;
	p->data = n;
	p->next = NULL;
	return p;
}
void addFirst(List& l, int n)	// Thêm vào đầu
{
	NODE* p = getNode(n);
	if (emptyList(l) == true)
	{
		l.head = l.tail = p;
	}
	else
	{
		p->next = l.head;	// nối liên kết của node vào l.head
		l.head = p;			// chuyển node đó thành node đầu
	}
}

void addTail(List& l, int n)	// Thêm vào đuôi
{
	NODE* p = getNode(n);
	if (l.head == NULL)
	{
		l.head = l.tail = p;
	}
	else
	{
		l.tail->next = p;	// node đuôi sẽ nối liên kết vào p
		l.tail = p;			// đổi p thành đuôi
	}
}


void delHead(List& l)	//Xóa node đầu
{
	NODE* temp;
	if (l.head == l.tail)			//Danh sách còn 1 node thì xóa
	{
		delete l.head;
		l.head = l.tail = NULL;
	}
	else {
		temp = l.head;				// temp giữ head
		l.head = l.head->next;		// head bước qua
		delete temp;				// xóa temp
		temp = NULL;
	}
}

void deleteList(List& l)	//Xoa list
{
	NODE* p;
	while (l.head != l.tail)
	{
		p = l.head;
		l.head = l.head->next;
		delete p;
		if (l.head = l.tail)
			delete l.head;
		l.head = l.tail = p = NULL;
	}
}





void LoadFileNumBer(const char* filename,string* &line,int &math)		//Đọc file và chuyển từng dòng vào mảng line
{
	ifstream input(filename, ios::in);

	if (!input.is_open())
	{
		cout << "Can't Load" << endl;
		return;
	}

	cout << "Open file sucessfully"<<" ("<<filename<<")"<<endl;
	
	string temp;
	input >> math;
	getline(input, temp);

	line = new string[math];	/// Tạo mảng gồm các dòng biểu thức

	for (int i = 0; i < math; i++)
	{
		getline(input, line[i]);
	}
	
	input.close();
}

void PutNumInList(string& strNum, int node_size, BN& ListNum)	//Chuyển số vào list ( strNum là số dạng string, node_size là argv[2], BN là số dạng list)
{
	int firstNodesize = strNum.size() % node_size;	// độ dài node đầu
	string temp;
	createEmptyList(ListNum.l);


	if (firstNodesize == 0)	//TH: chia deu cac node      123 456
	{
		for (int i = 0; i <= strNum.size()-node_size; i+=node_size)	//Chạy đến hết string
		{
			temp = strNum.substr(i,node_size);
			addTail(ListNum.l, stoi(temp));
		}
	}
	else                   // TH: node dau bi thieu	12 456 78
	{
		temp = strNum.substr(0, firstNodesize);
		addTail(ListNum.l, stoi(temp));
		for (int i = firstNodesize; i <= strNum.size() - node_size; i += node_size)	// chạy đến gần cuối string, chừa lại last node
		{
			temp = strNum.substr(i, node_size);
			addTail(ListNum.l, stoi(temp));
		}
	}
}


// ( Mảng line chứa dữ liệu 1 dòng, mảng BNarr sẽ là mảng các list số, argv[2]) 
void SplitLine(string& line,BN*& BNarr, int& countNuminLine,int node_size)
{																		

	string* strNum;	// Mảng giữ các số dạng string 
	int countNumsize = 1;

	for (int i = 0; i < line.size(); i++)		//Đếm số lượng số trong line 
	{
		
		if (line[i] == '+' || line[i] == '-')
			countNuminLine++;
	}


	strNum = new string[countNuminLine]; // Tạo mảng chứa các số
	BNarr = new BN[countNuminLine];		// Tạo mảng gồm các list để giữ các số từ mảng strNum

	int temp = 0;	//temp để chạy mảng Numsize

	for (int i = 0; i < line.size(); i++)	//Đếm số lượng chữ số trong một số 
	{
		if (line[i] == ' ')	// Nếu gặp khoang trang thì độ dài số sẽ là countNumsize -1
		{
			BNarr[temp].size = countNumsize - 1;
			countNumsize = 1;
			temp++;
			i += 3;	// Nhảy qua dấu và 1 dấu cách nữa

		}
			countNumsize++;

		if (i == line.size() - 1)	// xử lí ở số cuối cùng
		{
			BNarr[temp].size = countNumsize-1;
			break;
		}
	}

	int count = 0; // chạy từng số
	int headNum = 0;	// vị trí đầu mỗi số
	while (count < countNuminLine)
	{
		strNum[count] = line.substr(headNum, BNarr[count].size);	//Cắt một số theo Numsize số đó
		headNum += BNarr[count].size +3;
		count++;
	}

	
	for (int i = 0; i < countNuminLine; i++)	// Chuyển string về list
	{
		PutNumInList(strNum[i], node_size, BNarr[i]);
	}

	BNarr[0].sign = 1;
	int findsign = 1;	// Tìm dấu
	for (int i = 0; i < line.size(); i++)
	{
		if (findsign == countNuminLine)
		{
			break;
		}

		if (line[i] == '-')
		{
			BNarr[findsign].sign = -1;
			findsign++;
		}

		if (line[i] == '+')
		{
			BNarr[findsign].sign = 1;
			findsign++;
		}
	
	}
}


void reverseList(List&l) {
	List temp;
	createEmptyList(temp);
	NODE*p = l.head;
	while (p != NULL)
	{
		addFirst(temp, p->data);
		p = p->next;
	}
	deleteList(l);
	l = temp;

}

void swap(BN& BN1,BN& BN2)
{
	BN BN3 = BN1;
	BN1 = BN2;
	BN2 = BN3;
}


BN add(BN& BN1,BN& BN2,int node_size)																		
{				 
	
	//đảo số trước khi tính toán
	reverseList(BN1.l);
	reverseList(BN2.l);
	NODE* p1 = BN1.l.head;
	NODE* p2 = BN2.l.head;

	int limit = pow(10, node_size);	//giới hạn giá trị của 1 node

	BN sum;	// Tạo một bignum kết quả
	createEmptyList(sum.l);
	sum.sign = 1;

	if (BN1.size == BN2.size)			// cùng số chữ số
	{
		sum.size = BN1.size;	// Khởi tạo số chữ số
		while (p1 != NULL)	//Tiến hành cộng các node
		{
			int temp = p1->data + p2->data;
			addTail(sum.l, temp);
			p1 = p1->next;
			p2 = p2->next;
		}
		NODE* p = sum.l.head;	//Tạo node để kiểm tra các node >limit 

		while (p != sum.l.tail)
		{
			if (p->data >= limit )	//Thực hiện thao tác nhớ 1 cho node kế bên nếu node > limit
			{
				p->data -= limit;
				p->next->data += 1;
			}
			p = p->next;
		}
		if (sum.l.tail->data >= limit)		//Nếu node cuối > limit thì thêm 1 node với data=1
			{
				sum.l.tail->data -= limit;
				addTail(sum.l, 1);
				sum.size++;
			}
		
	}

	if (BN1.size > BN2.size)		//Nếu numsize khác nhau, cho sum= số lớn hơn rồi cộng số bé
	{
		sum.size = BN1.size;
		while (p1 != NULL)			//Gán số thứ nhất cho sum
		{
			addTail(sum.l, p1->data);
			p1 = p1->next;
		}
		NODE* p = sum.l.head;
		while (p2!=NULL)			// Cộng vào số thứ 2
		{
			p->data += p2->data;
			p = p->next;
			p2 = p2->next;
		}
		p = sum.l.head;
		//Kiểm tra lại sum
		while (p != sum.l.tail)
		{
			if (p->data >= limit)	//Thực hiện thao tác nhớ 1 cho node kế bên nếu node > limit
			{
				p->data -= limit;
				p->next->data += 1;
			}
			p = p->next;
		}
		if (sum.l.tail->data >= limit)		//Nếu node cuối > limit thì thêm 1 node với data=1
		{
			sum.l.tail->data -= limit;
			addTail(sum.l, 1);
			sum.size++;
		}
		
	}

	if (BN2.size > BN1.size)		//Nếu numsize khác nhau, cho sum= số lớn hơn rồi cộng số bé
	{
		sum.size = BN2.size;
		while (p2 != NULL)			//Gán số thứ nhất cho sum
		{
			addTail(sum.l, p2->data);
			p2 = p2->next;
		}
		NODE* p = sum.l.head;
		while (p1 != NULL)			// Cộng vào số thứ 2
		{
			p->data += p1->data;
			p = p->next;
			p1 = p1->next;
		}
		p = sum.l.head;
		//Kiểm tra lại sum
		while (p != sum.l.tail)
		{
			if (p->data >= limit)	//Thực hiện thao tác nhớ 1 cho node kế bên nếu node > limit
			{
				p->data -= limit;
				p->next->data += 1;
			}
			p = p->next;
		}
		if (sum.l.tail->data >= limit)		//Nếu node cuối > limit thì thêm 1 node với data=1
		{
			sum.l.tail->data -= limit;
			addTail(sum.l, 1);
			sum.size++;
		}
	}

	//Trả lại chiều
	reverseList(BN1.l);
	reverseList(BN2.l);
	reverseList(sum.l);
	return sum;

}

int compare(BN& BN1, BN& BN2)	//Trả về 1 nếu trước lớn hơn , trả về -1 nếu sau lớn hơn , 0 nếu bằng
{
	if (BN1.size > BN2.size)	// size 1 > size2
		return 1;
	if (BN1.size < BN2.size)	// size 1 < size2
		return -1;
	if (BN1.size == BN2.size)		// size 1 = size 2 thì chạy list, phát hiện node lớn hơn thì số đó lớn hơn
	{
		NODE* p1 = BN1.l.head;
		NODE* p2 = BN2.l.head;
		while (p1 != NULL && p2 != NULL)
		{
			if (p1->data > p2->data)
			{
				return 1;
			}
			if (p2->data > p1->data)
			{
				return -1;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
	}
	return 0;
}
BN subtract(BN& BN1, BN& BN2, int node_size)	// Số thứ nhất trừ số thứ 2
{

	int limit = pow(10, node_size);	//giới hạn giá trị của 1 node

	BN sub;
	createEmptyList(sub.l);

	if (BN1.sign == -1)	// số âm trừ một số thì thực hiện cộng và đưa về dấu -
	{
		sub=add(BN1, BN2, node_size);
		sub.sign = -1;
		return sub;
	}

	//TH1 : số bị trừ > số trừ ( BN1 > BN2 )	// 123 051 126 - 4 321 506
	if (compare(BN1, BN2) == 1)		
	{
		sub.sign = 1;
		reverseList(BN1.l);
		reverseList(BN2.l);
		NODE* p1 = BN1.l.head;
		NODE* p2 = BN2.l.head;

		sub.size = 0;
		while (p1 != NULL)			//Gán số thứ nhất cho sub
		{
			addTail(sub.l, p1->data);
			p1 = p1->next;
		}

		NODE* p = sub.l.head;
		while (p2 != NULL)
		{
			p->data -= p2->data;
			if (p->data < 0)
			{
				p->data += limit;
				p->next->data -= 1;
			}
			p = p->next;
			p2 = p2->next;
		}

		//Kiểm tra lại sub
		p = sub.l.head;
		while (p != NULL)
		{
			if (p->data < 0)
			{
				p->data += limit;
				p->next -= 1;
			}
			p = p->next;
		}
		// Tính subsize bằng cách đếm
		p = sub.l.head;
		int temp = sub.l.tail->data;
		while (temp != 0)
		{
			sub.size++;
			temp /= 10;
		}

		while (p != sub.l.tail)
		{
			sub.size += node_size;
			p=p->next;
		}


	}
	//TH2: Số bị trừ < số trừ
	if (compare(BN1, BN2) == -1)
	{
		sub.sign = -1;
		reverseList(BN1.l);
		reverseList(BN2.l);
		NODE* p1 = BN1.l.head;
		NODE* p2 = BN2.l.head;

		sub.size = 0;
		while (p2 != NULL)			//Gán số thứ 2 cho sub
		{
			addTail(sub.l, p2->data);
			p2 = p2->next;
		}

		NODE* p = sub.l.head;
		while (p1 != NULL)
		{
			p->data -= p1->data;
			if (p->data < 0)
			{
				p->data += limit;
				p->next->data -= 1;
			}
			p = p->next;
			p1 = p1->next;
		}

		//Kiểm tra lại sub
		p = sub.l.head;
		while (p != NULL)
		{
			if (p->data < 0)
			{
				p->data += limit;
				p->next -= 1;
			}
			p = p->next;
		}
		// Tính subsize bằng cách đếm
		p = sub.l.head;
		int temp=sub.l.tail->data;
		while (temp != 0)
		{
			sub.size++;
			temp /= 10;
		}

		while (p != sub.l.tail)
		{
			sub.size += node_size;
			p=p->next;
		}
		
	}
	reverseList(BN1.l);
	reverseList(BN2.l);
	reverseList(sub.l);
	return sub;
}
BN DoMath(BN& BN1,BN&BN2,int node_size)
{
	BN temp;
	createEmptyList(temp.l);
	if (BN2.sign == -1)
	{
		temp = subtract(BN1, BN2, node_size);
	}
	if (BN2.sign == 1)
	{
		temp = add(BN1, BN2, node_size);
	}

	return temp;
}

int partition(BN* &BNarr, int left, int right)
{

	BN pivot = BNarr[right];	//Đặt pivot bên phải
	int i = left - 1;	// i nằm bên trái left

	//Đưa được bên trái nhỏ hơn pivot và bên phải lớn hon pivot
	for (int j = left; j < right; j++)
		if (compare(BNarr[j],pivot)<=0)	//đổi chỗ ( a[i] và a[j])
		{
			i++;
			swap(BNarr[i], BNarr[j]);
		}

	swap(BNarr[i + 1], BNarr[right]); // Đưa pivot vào giữa

	return i + 1; //trả về vị trí pivot
}

void QuickSort(BN* &BNarr, int left, int right)
{
	if (left < right)
	{
		int par = partition(BNarr, left, right);

		//Sort left
		QuickSort(BNarr, left, par - 1);

		//Sort right
		QuickSort(BNarr, par + 1, right);
	}
}

void merge(BN*& A, int l, int m, int r)
{
	int nL = m - l + 1;
	int nR = r - m;
	BN* L = new BN[nL];
	BN* R = new BN[nR];
	for (int i = 0; i < nL; i++)
		L[i] = A[l + i];
	for (int j = 0; j < nR; j++)
		R[j] = A[m + 1 + j];
	int iL = 0;
	int iR = 0;
	int iA = l;

	while (iL < nL && iR < nR)
	{
		if (compare(L[iL], R[iR]) <= 0)
			A[iA++] = L[iL++];
		else
			A[iA++] = R[iR++];
	}

	while (iL < nL)
	{

		A[iA++] = L[iL++];
	}
	while(iR < nR)
	{

		A[iA++] = R[iR++];
	}
	
}
void mergeSort(BN* &BNarr, int l, int r)
{
	if (l < r)
	{
		cout << "merge";
		int mid = l + (r - l) / 2;
		mergeSort(BNarr, l, mid);
		mergeSort(BNarr, mid + 1, r);
		merge(BNarr, l, mid, r);
	}
}

void printNum(fstream &fout,List& l,int node_size)
{
	fout << endl;
	cout <<endl<< "List need add: ";
	printlist(l);
	cout << endl;
	NODE* p = l.head;
	int limit = pow(10, node_size);

	fout << l.head->data; //Ghi node đầu trước

	p = p->next;
	while (p != NULL)
	{
		int temp = limit / 10;
		while (temp != 0)
		{
			if (p->data >= temp)
			{
				fout << p->data;
				temp = 0;
				
			}
			else
			{
				fout << 0;
				temp /= 10;
				
			}
		}
		p = p->next;

	}
	
}

void deleteArr(BN*& BNarr,int countNuminLine)
{
	for (int i = 0; i < countNuminLine; i++)
	{
		deleteList(BNarr[i].l);
		BNarr[i].sign = 0;
		BNarr[i].size = 0;
    }
}