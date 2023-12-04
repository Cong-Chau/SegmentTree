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
int a[] = { 14, 2, 5, 12, 7, 3, 13, 1, 4, 6, 15, 9, 8, 10, 11 };
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
	if (u <= left && v >= right) {//Neu [left, right] nam trong [u, v] tra ve gia tri cua node do
		return tree[id];
	}
	int mid = (left + right) / 2;
	int sumleft = getSum(id * 2, left, mid, u, v);//Tong phia ben trai
	int sumright = getSum(id * 2 + 1, mid + 1, right, u, v);//Tong phia ben phai
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
void updateU_V(int id, int u, int v, int value) {
	if (u > v)
		return;//neu khoang can update gia tri nam ngoai khoang ta dang xet thi bo qua node id nay
	if (u == v) {//doan 1 phan tu khong co nut con
		a[u] += value;
		tree[id] = a[u];
		return;
	}
	int mid = (u + v) / 2;
	updateU_V(id * 2, u, mid, value);//duyet sang cay con trai
	updateU_V(id * 2 + 1, mid + 1, v, value);//duyet sang cay con phai
	tree[id] = tree[id * 2] + tree[id * 2 + 1];//cap nhat node cha bang tong 2 node con
}

void menu() {
	cout << "\n  =========Menu=========";
	cout << "\n   0. Ket thuc";
	cout << "\n   1. Duyet cau phan doan(Segment Tree) theo muc";
	cout << "\n   2. Cap nhat khoang [u, v] len x don vi";
	cout << "\n   3. Cap nhat gia tri (LOAI 1)";
	cout << "\n   4. Gia tri lon nhat trong doan [u, v]";
	cout << "\n   5. Tong gia tri trong khoang [u, v] (LOAI 2)";
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
			cout << "2. Cap nhat khoang [u, v] len x don vi\n";
			cout << "  Nhap khoang [u, v]: \n";
			int u, v;
			cout << "  u = "; cin >> u;
			cout << "  v = "; cin >> v;
			int x;
			cout << "  x = "; cin >> x;
			updateU_V(1, u, v, x);
			cout << "  Mang sau khi cap nhat:\n";
			viewA();
			cout << endl;
			cout << "  Cay sau khi cap nhat:\n";
			viewTree();
			cout << endl;
			system("pause");
			system("cls");
			menu();
			break;
		}
		case 3: {
			cout << "3. Cap nhat gia tri: (LOAI 1)\n";
			int index = -1, val, b;
			cout << "  Gia tri can bi thay doi: "; cin >> b;
			cout << "  Gia tri thay doi: "; cin >> val;
			for (int i = 0; i < n; i++) {
				if (a[i] == b)
					index = i;
			}
			cout << "\n";
			if (index == -1) {
				cout << "  Khong tim thay gia tri can bi thay doi!!!\n";
				system("pause");
				system("cls");
				menu();
				break;
			}
			updateTree(1, 0, n - 1, index, val);
			cout << "  Mang sau khi cap nhat:\n";
			viewA();
			cout << endl;
			cout << "  Cay sau khi cap nhat:\n";
			viewTree();
			cout << endl;
			system("pause");
			system("cls");
			menu();
			break;
		}
		case 4: {
			cout << "4. Gia tri lon nhat trong khoang [u, v]\n";
			cout << "  Nhap khoang [u, v]: \n";
			int u, v;
			cout << "  u = "; cin >> u;
			cout << "  v = "; cin >> v;
			cout << "  Gia tri lon nhat trong khoang [" << u << ", " << v << "] :" << findMax(u, v) << endl;
			system("pause");
			system("cls");
			menu();
			break;
		}
		case 5: {
			cout << "5. Tong gia tri trong khoang [u, v] (LOAI 2)\n";
			cout << "  Nhap khoang [u, v]: \n";
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
