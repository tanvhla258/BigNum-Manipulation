#include"Header.h"

int main(int argc,char* argv[])
{
	if (strcmp(argv[1],"-comp")==0)
	{
		cout << "Phep toan cong tru" << endl;
		string* line = NULL;	// Mảng chứa các dòng
		int math = 0;			// Số dòng
		BN* BNarr = NULL;		// Mảng chứa các số trong 1 dòng

		int node_size = atoi(argv[2]);	//Độ dài node
		int countNuminline = 1;

		LoadFileNumBer(argv[3], line, math);	// Đọc file
		fstream fout(argv[4], ios::out);		//Ghi file
		if (!fout.is_open())
		{
			cout << "Can't write";
			return 0;
		}
		fout << math;
	
		cout << "So bieu thuc: " << math<<endl;	

		int countNuminLine = 1;	//Số lượng số trên một dòng

		BN* Value = NULL;
		for (int countline = 0; countline < math; countline++)                              
		{
			SplitLine(line[countline], BNarr, countNuminLine, node_size);	//Cắt số vào mảng BNarr
			Value = new BN[countNuminLine - 1];	//mảng lưu kết quả
			
			Value[0]=DoMath(BNarr[0], BNarr[1],node_size);
		
			cout << endl;
			for (int i = 2; i < countNuminLine; i++)	// Tiến hành các phép toán
			{
				Value[i - 1] = DoMath(Value[i - 2], BNarr[i],node_size);// Phép toán cộng hay trừ đc thực hiện dựa vào sign
			}
		
			if (Value[countNuminLine-2].sign==1)	// Ghi số vào file nếu sign là dương
				printNum(fout, Value[countNuminLine-2].l, node_size);
			else
			{
				fout <<endl<< "NaN";		// Ghi NaN nếu âm
			}
			
			deleteArr(BNarr, countNuminLine);	// reset lại mảng cho dòng tiếp theo
			deleteArr(Value, countNuminLine-1);
			countNuminLine = 1;
		}
		delete[] line;
		fout.close();
	}

	if (strcmp(argv[1], "-qsort") == 0)
	{
		string* line = NULL;	// Mảng chứa các dòng
		int math = 0;			// Số dòng
		BN* BNarr = NULL;		// Mảng chứa các số trong 1 dòng

		int node_size = atoi(argv[2]);	//Độ dài node
		const int countNuminline = 1;
		LoadFileNumBer(argv[3], line, math);
		BNarr = new BN[math];	//mảng chứa các bignum

		//truyền số từ line (string) vào BN (list)
		for (int i = 0; i < math; i++)
		{
			PutNumInList(line[i], node_size, BNarr[i]);
			BNarr[i].size = line[i].size();
		}

		QuickSort(BNarr, 0, math-1); // Sắp xếp
			
		for (int i = 0; i < math; i++)		// Xuất màn hình
		{
			cout << BNarr[i].size << endl;
			printlist(BNarr[i].l);
			cout << endl;
		    
		}
		//Ghi file
		fstream fout(argv[4], ios::out);
		fout << math;
		if (!fout.is_open())
		{
			cout << "Can't Write";
			return 0;
		}
		for (int i = 0; i < math; i++)
			printNum(fout, BNarr[i].l,node_size);

		delete[] line;
		deleteArr(BNarr, math);
		fout.close();
	}

	if (strcmp(argv[1], "-msort") == 0)
	{
		string* line = NULL;	// Mảng chứa các dòng
		int math = 0;			// Số dòng
		BN* BNarr = NULL;		// Mảng chứa các số trong 1 dòng

		int node_size = atoi(argv[2]);	//Độ dài node
		const int countNuminline = 1;
		LoadFileNumBer(argv[3], line, math);
		BNarr = new BN[math];	//Tạo mảng gồm các big num

		for (int i = 0; i < math; i++) // Tạo list cho bignum và bignum size
		{
			PutNumInList(line[i], node_size, BNarr[i]);
			BNarr[i].size = line[i].size();
		}

		mergeSort(BNarr, 0, math - 1); // Sắp xếp

		for (int i = 0; i < math; i++)	// Xuất ra màn hình console
		{
			cout << BNarr[i].size << endl;
			printlist(BNarr[i].l);
			cout << endl;

		}
		//Ghi file
		fstream fout(argv[4], ios::out);
		fout << math;
		if (!fout.is_open())
		{
			cout << "Can't Write";
			return 0;
		}
		for (int i = 0; i < math; i++)
			printNum(fout, BNarr[i].l, node_size);

		delete[] line;
		deleteArr(BNarr, math);
		fout.close();
	}
	

	return 0;
}
