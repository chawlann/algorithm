/*
1、实现选择排序、冒泡排序、合并排序、快速排序、插入排序算法；
2、以待排序数组的大小n为输入规模，固定n，随机产生20组测试样本，统计不同排序算法在20个样本上的平均运行时间；
3、分别以n=1000, n=10000, n=100,000，n=1,000,000, n=10,000,000（千万规模选做）重复2的实验；
*/ 

#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

void Selection_sort(int *arr, int n){ //选择排序 arr数组 n数组元素个数
	//第i趟排序找出后n-i+1个数中最小的数并且与第i位数交换
	int min, i, j, temp;
	for(i = 0;i < n; i++) { // 共n趟排序
		min = i;
		for(j = i;j < n; j++) { // 寻找最小数
			if(arr[j] < arr[min]) {
				min = j;
			}
		}
		if(min != i) { // 若最小数不是第i位数 则交换
			temp = arr[i];
			arr[i] = arr[min];
			arr[min] = temp;
		}
	}
}

void Bubble_sort(int *arr, int n) { //冒泡排序
	// 第i趟排序将前面 n-i+1个数中最大/最小的数排在末位
	int temp, i, j;
	for(i = 0;i < n; i++) { //循环n趟
		for(j = 0;j < n - i - 1; j++) { //将最大的数移到第n-i+1的位置上
			if(arr[j] > arr[j + 1]) {
				temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}

void sort_array(int *a, int start, int middle, int end) {
	int left = start; //第一段序列下标
	int right = middle + 1; //第二段序列下标
	int *p = new int [end - start + 1]; //归并后的数组
	int i = 0; //归并后数组的下标

	while(left <= middle && right <= end) { //若两段序列中均有元素需要互相比较
		if(a[left] <= a[right]) { //将两段中较小的数放入新数组中
			p[i] = a[left];
			left ++;
			i ++;
		} else {
			p[i] = a[right];
			right ++;
			i ++;
		}
	}

	while(left <= middle) { //若第二段已没有元素  则将第一段中的所有元素顺序加入合并后的数组
		p[i] = a[left];
		left ++;
		i ++;
	}

	while(right <= end) { //若第一段已没有元素  则将第二段中的所有元素顺序加入合并后的数组
		p[i] = a[right];
		right ++;
		i ++;
	}

	int j;
	for(i = 0,j = start;j <= end;i++, j++) {
		a[j] = p[i];
	}
}

void divide_array(int *a, int start, int end) { // 将数组递归对半划分
	if(start >= end) {
		return;
	}
	int middle = (end + start) / 2;
	divide_array(a, start, middle);
	divide_array(a, middle + 1, end);
	sort_array(a, start, middle, end); // 划分完数组后开始从后往前两两合并排序
}

void Merge_sort(int *arr, int n) { //归并排序
	divide_array(arr, 0, n - 1);
}

void Insertion_sort(int *arr, int n) { //插入排序
	//从i=1开始每趟排序将小于第i-1个元素的数插入到前面i个元素中
	int i, j, temp;
	for(i = 1;i < n; i++) {
		if(arr[i] < arr[i - 1]) {
			temp = arr[i];
			for(j = i - 1;j >= 0 && arr[j] > temp; j--) {
				arr[j + 1] = arr[j];
			}
			arr[j + 1] = temp;
		}
	}
}

void Quick_sort(int *arr, int left, int right) { //快速排序
	//取一个元素作为基准将比他小的数与比他大的数分开
	int low = left;
	int high = right;
	int temp = arr[left];
	if(left < right) {
		while(low < high) {
			while(low < high && arr[high] > temp) {
				high --;
			}
			arr[low] = arr[high];
			while(low < high && arr[low] < temp) {
				low ++;
			}
			arr[high] = arr[low];
		}
		arr[low] = temp;
		Quick_sort(arr, left, low - 1);
		Quick_sort(arr, low + 1, right);
	}
	
}

int main() {
	int num; // 测试数据个数
	int times = 20; // 测试次数
	int *array; // 测试数组
	int i, j, k;
	clock_t start, end; //记录排序起始时间与结束时间
	double total_time;
	double average_time;//用于计算平均时间
	double sum = 0;
	//total_time = (double)(end-start)/CLOCKS_PER_SEC;
	cout << "Please enter the number of data should be test:" ;
	cin >> num;
	array = new int[num];

	//选择排序
	cout << "Selection sort:" << endl;
	for(k = 0;k < times; k++) {
		for(i = 0;i < num; i++) {
			array[i] = rand();
		}
		start = clock();
		Selection_sort(array, num);
		end = clock();
		total_time = (double)(end-start)/CLOCKS_PER_SEC;
		cout << total_time*1000 << "ms ";
		sum += total_time;
	}
	cout << endl;
	cout << "The average time of Selection sort is " << sum/20.0*1000 << "ms" << endl;

	//冒泡排序
	cout << endl;
	cout << "Bubble sort:" << endl;
	sum = 0;
	for(k = 0;k < times; k++) {
		for(i = 0;i < num; i++) {
			array[i] = rand();
		}
		start = clock();
		Bubble_sort(array, num);
		end = clock();
		total_time = (double)(end-start)/CLOCKS_PER_SEC;
		cout << total_time*1000 << "ms ";
		sum += total_time;
	}
	cout << endl;
	cout << "The average time of Bubble sort is " << sum/20.0*1000 << "ms" << endl;

	//归并排序
	cout << endl;
	cout << "Merge sort:" << endl;
	sum = 0;
	for(k = 0;k < times; k++) {
		for(i = 0;i < num; i++) {
			array[i] = rand();
		}
		start = clock();
		Merge_sort(array, num);
		end = clock();
		total_time = (double)(end-start)/CLOCKS_PER_SEC;
		cout << total_time*1000 << "ms ";
		sum += total_time;
	}
	cout << endl;
	cout << "The average time of Merge sort is " << sum/20.0*1000 << "ms" << endl;

	//插入排序
	cout << endl;
	cout << "Insertion sort:" << endl;
	sum = 0;
	for(k = 0;k < times; k++) {
		for(i = 0;i < num; i++) {
			array[i] = rand();
		}
		start = clock();
		Insertion_sort(array, num);
		end = clock();
		total_time = (double)(end-start)/CLOCKS_PER_SEC;
		cout << total_time*1000 << "ms ";
		sum += total_time;
	}
	cout << endl;
	cout << "The average time of Insertion sort is " << sum/20.0*1000 << "ms" << endl;

	//快速排序
	cout << endl;
	cout << "Quick sort:" << endl;
	sum = 0;
	for(k = 0;k < times; k++) {
		for(i = 0;i < num; i++) {
			array[i] = rand();
		}
		start = clock();
		Quick_sort(array, 0, num - 1);
		end = clock();
		total_time = (double)(end-start)/CLOCKS_PER_SEC;
		cout << total_time*1000 << "ms ";
		sum += total_time;
	}
	cout << endl;
	cout << "The average time of Quick sort is " << sum/20.0*1000 << "ms" << endl;

	return 0;
}
