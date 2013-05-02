int func(int a, int b) {
    int c = a;
    int d = a+b;
    return c+d;
}
void main() {
int b = 5;
int i = 0;
for(i =0;i<5;i++)
{b = func(3+i,4);
printf("%d\n",b);}
int w = b+6;
}
