int func1(int a1, int a2, int a3, int a4, int a5) {
    return 0;
}

int func2() {
    return func1(1,2,3,4,5);
}

int main() {
    return func2();
}