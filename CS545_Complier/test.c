int func(int a, int b) {
	return a+b;
}

int func2(int x) {
	return x+5;
}

void main() {
    int c = func(4,3);	
    int d = c+5;
    func2(d);
}
