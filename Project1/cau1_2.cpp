// Mot so ham co ban cua segment tree

#include<iostream>
using namespace std;
#define MAX 1000

/////////////
//               Ghi chu
//- Moi node luu gia tri la tong 2 node con
//- Dia chi:
//     Node cha : index
//     Node con trai: index * 2
//     Node con phai: index * 2 + 1
// 
/////////////


// Tai day khai bao du lieu cua: mang, so luong mang, cay
//          0  1  2  3   4  5  6  7  8  9
int a[] = { 1, 6, 3, 10, 5, 7, 8, 4, 9, 2 };
int n = sizeof(a) / sizeof(a[0]);
int tree[MAX * 4];

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
// cap nhat 1 vi tri
void updateTree(int id, int left, int right, int index, int val) {
	if (index<left || index>right) {
		return;
	}
	if (left == right) {//Cap nhat gia tri cua a[index] va node cha cua no
		a[index] = val;
		tree[id] = a[index];
		return;
	}
	int mid = (left + right) / 2;
	updateTree(id * 2, left, mid, index, val);//Duyet ve cay con trai
	updateTree(id * 2 + 1, mid + 1, right, index, val);//Duyet ve cay con phai
	tree[id] = tree[id * 2] + tree[id * 2 + 1];
}
// gia tri lon nhat trong [u, v]
int findMax(int u, int v) {
	if (u > v) { //Neu u>v thi khong hop ly nen tra ve 0
		return 0;
	}
	if (u == v) {//Neu u=v thi tra ve gia tri cua a[u] hoac a[v]
		return a[v];
	}
	int mid = (u + v) / 2;
	int left = findMax(u, mid);     //Duyet ve cay con trai
	int right = findMax(mid + 1, v);//Duyet ve cay con phai
	return max(left, right);
}

// tong cac so tu u-v
int getSum(int id, int left, int right, int u, int v) {
	if (u > right || v < left) {
		return 0;
	}
	if (u <= left && v >= right) {
		return tree[id];
	}
	int mid = (left + right) / 2;
	int sumleft = getSum(id * 2, left, mid, u, v);
	int sumright = getSum(id * 2 + 1, mid + 1, right, u, v);
	return sumleft + sumright;
}

void viewA() { // Ham xuat mang cho truoc
	for (int i = 0; i < n; i++) {
		cout << "  " << a[i];
	}
	cout << endl;
}
void viewTree() { // Ham xuat cay phan doan
	int x;
	for (x = n * 4; x > 0; x--) {
		if (tree[x] != 0)
			break;
	}
	for (int i = 1; i <= n * 4; i++) {
		if (i <= x)
			cout << "   " << tree[i];
	}
	cout << endl;
}

void menu() {
	cout << "\n  =========Menu=========";
	cout << "\n   0. Ket thuc";
	cout << "\n   1. Duyet cau phan doan(Segment Tree) theo muc";
	cout << "\n   2. Cap nhat gia tri (LOAI 1)";
	cout << "\n   3. Gia tri lon nhat trong doan [u, v]";
	cout << "\n   4. Tong gia tri trong khoang [u, v] (LOAI 2)";
	cout << "\n  ======================";
	cout << "\n\nMang cho truoc:";
	viewA();
}
int main() {
	buildSegmentTree(1, 0, n - 1);
	menu();
	while (1) {
		int choose;
		cout << "\n\nChon: "; cin >> choose;
		system("cls");
		menu();
		cout << endl;
		if (choose == 0)
			break;
		switch (choose) {
		case 1: {
			cout << "1. Duyet cay phan doan (Segment Tree) theo muc:\n";
			viewTree();
			system("pause");
			system("cls");
			menu();
			break;
		}
		case 2: {
			cout << "2. Cap nhat gia tri: (LOAI 1)\n";
			int index, val, b;
			cout << "  Gia tri thay doi: "; cin >> val;
			cout << "  Gia tri bi thay doi: "; cin >> b;
			for (int i = 0; i < n; i++) {
				if (a[i] == b)
					index = i;
			}
			cout << "\n";
			updateTree(1, 0, n - 1, index, val);
			cout << "  Mang sau khi cap nhat:\n";
			viewA();
			system("pause");
			system("cls");
			menu();
			break;
		}
		case 3: {
			cout << "3. Gia tri lon nhat trong khoang [u, v]\n";
			cout << "  Nhap khoang [u, v]: ";
			int u, v;
			cout << "  u = "; cin >> u;
			cout << "  v = "; cin >> v;
			cout << "  Gia tri lon nhat trong khoang [" << u << ", " << v << "] :" << findMax(u, v) << endl;
			system("pause");
			system("cls");
			menu();
			break;
		}
		case 4: {
			cout << "4. Tong gia tri trong khoang [u, v] (LOAI 2)\n";
			cout << "  Nhap khoang [u, v]: ";
			int u, v;
			cout << "  u = "; cin >> u;
			cout << "  v = "; cin >> v;
			int sum = getSum(1, 0, n - 1, u, v);
			cout << "  Tong gia tri trong khoangg [" << u << ", " << v << "] :" << sum << endl;
			system("pause");
			system("cls");
			menu();
			break;
		}
		default: {
			system("cls");
			menu();
			cout << "\n\n  Chon khong hop le!!";
			cout << "\n  Moi chon lai";
		}
		}
	}
	return 0;
}
