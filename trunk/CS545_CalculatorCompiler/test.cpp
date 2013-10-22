#include<stdio.h>

class Test {
public:
	Test(){
	printf("Object created\n");
	}
	virtual ~Test() {
	printf("Object Deleted\n");
	}
};
template <class T>
void deleteItem(void* a) {
delete (T*)a;
}

int main(int argc,char** argv) {
Test t();
}
