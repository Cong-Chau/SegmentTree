#include<iostream>
using namespace std;
#define MAX 1000

int a[] = { 1, 6, 3, 10, 5, 7, 8, 4, 9, 2 };
int tree[MAX * 4];
int n = sizeof(a) / sizeof(a[0]);
void buildSegmentTree(int id, int left, int right) {
	if (left == right) {
		tree[id] = a[left];
		return;
	}
	int mid = (left + right) / 2;
	buildSegmentTree(id * 2, left, mid);//Duyet ve cay con trai
	buildSegmentTree(id * 2 + 1, mid + 1, right);//Duyet ve cay con phai
	tree[id] = tree[id * 2] + tree[id * 2 + 1];
}