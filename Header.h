#pragma once
#include <iostream>
#include <string>
#include <string.h>
#include <math.h>
#include <fstream>
#include <stdlib.h>

using namespace std;

struct NODE
{
	int data;
	NODE* next;
};

struct List
{
	NODE* head;
	NODE* tail;
};

struct BigNum
{
	List l;		// List giá trị
	int sign;   // Dấu
	int size;   // Độ dài số
};
typedef BigNum BN;

// Hàm thao tác trên List
void createEmptyList(List& l);
bool emptyList(List l);
void printlist(List& l);
NODE* getNode(int n);
void addFirst(List& l, int n);
void addTail(List& l, int n);
void delHead(List& l);
void deleteList(List& l);

//Hàm để lấy dữ liệu từ input
void LoadFileNumBer(const char* filename, string*& line, int& math);
void PutNumInList(string& strNum, int node_size, BN& ListNum);
void SplitLine(string& line, BN*& BNarr, int& countNuminLine, int node_size);

//Hàm tính toán và các hàm nhỏ phục vụ cho 5 hàm chính của đề
void reverseList(List& l); // Đổi chiều list
BN add(BN& BN1, BN& BN2, int node_size); 
BN subtract(BN& BN1, BN& BN2, int node_size);
int compare(BN& BN1, BN& BN2);
BN DoMath(BN& BN1, BN& BN2, int node_size);	// Hàm thực hiện phép toán + hoặc -
int partition(BN*& BNarr, int left, int right);
void QuickSort(BN*& BNarr, int left, int right);
void merge(BN*& A, int l, int r, int m);
void mergeSort(BN*& BNarr, int l, int r);

//Hàm ghi file và giải phóng
void printNum(fstream& fout, List& l, int node_size);
void deleteArr(BN*& BNarr, int countNuminLine);
