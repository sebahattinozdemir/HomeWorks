#include <stdio.h>
#include <math.h>

/*
gcc recursion.c -o recursion -lm
./recursion
*/

int factorial(int num){
    if(num==1)
        return 1;
    return num*factorial(num-1);
}

/* also uses an accumulator */
int factorial_tail(int num, int acc){
    if(num==1)
        return acc;
    return factorial_tail(num-1, num*acc);
}

int factorial_2(int num){
    return factorial_tail(num, 1);
}

int fibonacci(int i) {
   if(i < 2) 
      return i;
   return fibonacci(i-1) + fibonacci(i-2);
}

int numDigits(int number){
    if(number/10==0)
        return 1;
    return numDigits(number/10)+1;
}

/*
e = 1 + 1/1! + 1/2! + 1/3! + ...
*/
double find_e(int times){
    if(times==0)
        return 1.0;
    return 1.0/factorial(times)+find_e(times-1);

}

/* 
pi = 4 - 4/3 + 4/5 - 4/7 + 4/9 ...
need very large n to converge
*/
double calculatePI(int n){
    if(n == 0)
        return 4.0;
    else
        return (n%2 ? -1 : 1) * 4.0/(2*n+1) + calculatePI(n-1);

}

/*
153 = 1^3 + 5^3 + 3^3
compare return value to find given number is an Armstrong number or not.
*/
int armstrong(int num,int order){
    if(num/10==0)
        return pow(num,order);
    return pow(num%10,order) + armstrong(num/10,order);
}



void hanoi(int num, char from, char to, char mid){
    if (num > 0){
        hanoi(num - 1, from, mid, to);
        printf("Move disk %d from %c to %c\n", num, from, to);
        hanoi(num - 1, mid, to, from);
    }
}


int odd(int number);

int even(int number){
    if (number == 0)
        return 1;
    else
        return odd(number - 1);
}

int odd(int number){
    if (number == 0)
        return 0;
    else
        return even(number - 1);
}


int ackermann(int m, int n){
    if (m == 0) 
        return n + 1;
    else if (m > 0 && n == 0) 
        return ackermann(m - 1, 1);
    else if (m > 0 && n > 0)
        return ackermann(m - 1, ackermann(m, n - 1));
}


void printR(int a[], int n, int i){
    if (i<n){
        printf("%d ", a[i]);
        printR(a, n, i+1);
    }
}

void print(int a[], int n){
    printR(a, n, 0);
    printf("\n");
}

void printRR(int a[], int n, int i){
    if (i<n){
        printRR(a, n, i+1);
        printf("%d ", a[i]);
    }
}

void printReverse(int a[], int n){
    printRR(a, n, 0);
    printf("\n");
}

int minR(int a[], int n, int i){
    if (i==n-1){
        return a[i];
    }
    else{
        int tmp = minR(a, n, i+1);
        return a[i] < tmp ? a[i] : tmp;
    }
}

int min(int a[], int n){
    return minR(a, n, 0);
}

int main(){

    /* fibonacci */
    printf("fib 8: %d\n",fibonacci(8));
    printf("fib 5: %d\n",fibonacci(5));
    printf("fib 3: %d\n",fibonacci(3));
    printf("fib 1: %d\n",fibonacci(1));

    /* factorial */
    printf("fact 8: %d\n",factorial(8));
    printf("fact 5: %d\n",factorial(5));
    printf("fact 3: %d\n",factorial(3));
    printf("fact 1: %d\n",factorial(1));

    /* num digits */
    printf("digits 1622553: %d\n",numDigits(1622553));
    printf("digits 56739: %d\n",numDigits(56739));
    printf("digits 3: %d\n",numDigits(3));

    /* pi */
    int times = 10;
    printf("pi: %lf\n",calculatePI(times));
    times = 20;
    printf("pi: %lf\n",calculatePI(times));
    times = 30;
    printf("pi: %lf\n",calculatePI(times));

    /* e */
    times = 5;
    printf("e: %lf\n",find_e(times));

    /* Armstrong */
    int number=153, order;
    order = numDigits(number);
    if (number == armstrong(number,order))
        printf("The number is an Armstrong number.\n");
    else
        printf("The number is NOT an Armstrong number.\n");

    /* hanoi */
    hanoi(4, 'A', 'B', 'C');
    
    /* even-odd*/
    printf("%d %d\n", even(12), even(11));
    printf("%d %d\n", odd(5), odd(6));
    printf("%d %d %d %d\n", odd(0), odd(1), even(0), even(1));


    /* ackermann */
    printf("%d\n", ackermann(3,2));
    /* https://en.wikipedia.org/wiki/Ackermann_function */
    /*printf("%d\n", ackermann(4,2));*/

    /* Arrays */
    int a1[7] = {1,3,5,7,6,4,2};
    int a2[7] = {8,3,4,7,9,5,2};
    int a3[7] = {1,2,3,0,6,5,4};

    print(a1, 7);
    printReverse(a1, 7);

    print(a2, 7);
    printReverse(a2, 7);

    print(a3, 7);   
    printReverse(a3, 7);

    printf("min: %d\n", min(a1, 7));
    printf("min: %d\n", min(a2, 7));
    printf("min: %d\n", min(a3, 7));


    return 0;
}
