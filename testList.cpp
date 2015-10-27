#include "ListArray.h"
#include "ListLinked.h"
#include <chrono>
#define N 10000

template<class T>
void benchMark(ListLinked<T> linkedList, ListArray<T> arrayList, int n) {
	std::chrono::steady_clock::time_point begin;
	std::chrono::steady_clock::time_point end;

	begin = std::chrono::steady_clock::now();
	for(int i = 0; i < n; i++) {
		arrayList.insert((arrayList.getLength()-1)/2, i);
	}
	end = std::chrono::steady_clock::now();
	int arrayTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();

	begin = std::chrono::steady_clock::now();
	for(int i = 0; i < n; i++) {
		linkedList.insert((linkedList.getLength()-1)/2, i);
	}
	end = std::chrono::steady_clock::now();
	int listTime = chrono::duration_cast<chrono::microseconds>(end - begin).count();

	cout << "Array List time for " << n << " inserts: " << arrayTime << endl;
	cout << "Linked List time for " << n << " inserts: " << listTime << endl;

}
int main() {

	ListLinked<int> listInts = ListLinked<int>();
	ListArray<int> arrayInts = ListArray<int>();

	int inserts[] = {2000, 4000, 6000, 8000, 10000};

	/*for (int insert : inserts) {
		benchMark(listInts, arrayInts, insert);
	}*/

	//cout << listInts.getLength() << " " << arrayInts.getLength() << endl;

	/*listInts.insert(0,0);
	listInts.insert(0,1);
	listInts.insert(2,2);
	listInts.insert(1,3);
	
	/*listInts.remove(0);
	listInts.remove(2);
	listInts.remove(0);
	listInts.remove(0);*/

	/*listInts.set(0, 100);
	listInts.set(3, 400);
	listInts.set(1, 200);
	listInts.set(2, 300);
	for (int i = 0; i < listInts.getLength(); i++) {
		int h = listInts.get(i);
		cout << h << endl;
	}

	cout << listInts << endl;*/

	for(int i = 0; i < 20; i++) {
		arrayInts.insert(arrayInts.getLength()/2, i);
	}
	for(int i = 0; i < 10; i++) {
		arrayInts.remove(i);
	}

	arrayInts.remove(0);
	arrayInts.remove(arrayInts.getLength()-1);

	arrayInts.remove(arrayInts.getLength()/2-1);
	cout << arrayInts << endl;

	arrayInts.set(0, 10000);
	arrayInts.set(arrayInts.getLength()-1, 50000);
	arrayInts.set(arrayInts.getLength()/2, 25000);

	cout << arrayInts << endl;
	int first = arrayInts.get(0);
	int last = arrayInts.get(arrayInts.getLength()-1);
	int middle = arrayInts.get(arrayInts.getLength()/2);

	cout << first << " " << last << " " << middle << endl;
	return 0;
}

