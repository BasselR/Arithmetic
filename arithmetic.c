#include <stdio.h>
#include <string.h>

#define N 80

char a[N], b[N], res[N + 1];

void add(const char a[], const char b[], char res[]){

    int sizeDiff = strlen(a) - strlen(b); //Array size difference is a - b : If a is size 5 and b is size 2, sizeDiff is 3
    int smallestSize = strlen(a) < strlen(b) ? strlen(a) : strlen(b); //Determines smallest array size
    int carry = 0;

    for(int i = smallestSize - 1; i >= 0; i--){
        if(sizeDiff >= 0){   //If a >= b:
            res[i + 1 + sizeDiff] = (((a[i + sizeDiff] - 48) + (b[i] - 48) + carry) % 10) + 48;
            if(((a[i + sizeDiff] - 48) + (b[i] - 48) + carry) >= 10){
                carry = 1;
            }
            else{
                carry = 0;
            }
        }
        else{  //If a < b:
            res[(i + 1) - sizeDiff] = (((a[i] - 48) + (b[i - sizeDiff] - 48) + carry) % 10) + 48;
            if(((a[i] - 48) + (b[i - sizeDiff] - 48) + carry) >= 10){
                carry = 1;
            }
            else{
                carry = 0;
            }
        }
    }

    //Copying in rest of sum result
    if(sizeDiff >= 0){
        for(int i = sizeDiff - 1; i >= 0; i--){
            res[i + 1] = (((a[i] - 48) + carry) % 10) + 48;
            if((((a[i] - 48) + carry)) >= 10){
                carry = 1;
            }
            else{
                carry = 0;
            }
        }
    }

    else{   //if sizeDiff < 0:
        for(int i = (sizeDiff * -1); i >= 1; i--){
            res[i] = (((b[i - 1] - 48) + carry) % 10) + 48;
            if(((b[i - 1] - 48) + carry) >= 10){
                carry = 1;
            }
            else{
                carry = 0;
            }
        }
    }

    if(carry == 1){
        res[0] = '1';
    }
    else{
        if(sizeDiff >= 0){
            for(int i = 0; i < (smallestSize + sizeDiff + 1); i++){     //Push each element back one space (no leading 1)
                res[i] = res[i + 1];
            }
        }
        else{
            for(int i = 0; i < (smallestSize + (sizeDiff * -1) + 1); i++){     //Push each element back one space (no leading 1)
                res[i] = res[i + 1];
            }            
        }

    }
}

int aGreaterThanB(const char a[], const char b[], int sizeDiff, int smallestSize){  //Returns 0 if a == b, 1 if a > b, 0 if b > a
    int equal = 1;
    if(sizeDiff > 0){
        return 1;
    }
    else if(sizeDiff < 0){
        return 0;
    }
    else{
        for(int i = 0; i < smallestSize; i++){
            if(a[i] != b[i]){
                equal = 0;
                if(a[i] < b[i]){
                    return 0;
                }                
            }
        }
        if(equal == 1){
            return 2;
        }
        return 1;
    }
} 

void sub(const char a[], const char b[], char res[]){

    int sizeDiff = strlen(a) - strlen(b); //Array size difference is a - b : If a is size 5 and b is size 2, sizeDiff is 3
    int smallestSize = strlen(a) < strlen(b) ? strlen(a) : strlen(b); //Determines smallest array size
    int carry = 0;

    // a == b
    if(aGreaterThanB(a, b, sizeDiff, smallestSize) == 2){
        res[0] = '0';
    }

    // a > b
    else if(aGreaterThanB(a, b, sizeDiff, smallestSize) == 1){
        for(int i = (smallestSize + sizeDiff) - 1; i >= 0; i--){
            if(i >= sizeDiff){
                if(((a[i] - 48) - carry) - (b[i - sizeDiff] - 48) < 0){
                    res[i] = ((((a[i] - 48) - carry) + 10) - (b[i - sizeDiff] - 48)) + 48;
                    carry = 1;
                }
                else{
                    res[i] = (((a[i] - 48) - carry) - (b[i - sizeDiff] - 48)) + 48;
                    carry = 0;
                }
            }
            else{   // i < sizeDiff (done subtracting, now copying down digits)
                if(((a[i] - 48) - carry) < 0){
                    res[i] = (((a[i] - 48) + 10) - carry) + 48;
                    carry = 1;
                }
                else{
                    res[i] = ((a[i] - 48) - carry) + 48;
                    carry = 0;
                }
            }
        }
        if(res[0] == '0'){
            for(int i = 0; i < smallestSize + sizeDiff; i++){
                res[i] = res[i + 1];
            }
        }
    }

    else if(aGreaterThanB(a, b, sizeDiff, smallestSize) == 0){  // a < b; do b - a then make it negative
        for(int i = (smallestSize + (sizeDiff * -1)) - 1; i >= 0; i--){
            if(i >= (sizeDiff * -1)){
                if(((b[i] - 48) - carry) - (a[i + sizeDiff] - 48) < 0){
                    res[i] = ((((b[i] - 48) - carry) + 10) - (a[i + sizeDiff] - 48)) + 48;
                    carry = 1;
                }
                else{
                    res[i] = (((b[i] - 48) - carry) - (a[i + sizeDiff] - 48)) + 48;
                    carry = 0;
                }
            }
            else{   // i < sizeDiff (done subtracting, now copying down digits)
                if(((b[i] - 48) - carry) < 0){
                    res[i] = (((b[i] - 48) + 10) - carry) + 48;
                    carry = 1;
                }
                else{
                    res[i] = ((b[i] - 48) - carry) + 48;
                    carry = 0;
                }
            }
        }
        if(res[0] == '0'){
            res[0] = '-';
        }
        else{
            for(int i = smallestSize - sizeDiff; i >= 1; i--){
                res[i] = res[i - 1];
            }
            res[0] = '-';
        }
    }
}

int main(){
  char op;
  scanf("%s %s %c", a, b, &op);
  switch (op)
  {
  case '+':
    add(a, b, res);
    break;
  case '-':
    sub(a, b, res);
  }
  // print result
  char buf[20];
  int l1 = strlen(a), l2 = strlen(b), l3 = strlen(res);
  int m = l1 > l2 ? l1 : l2;
  m = m > l3 ? m : l3;
  sprintf(buf, "%% %ds\n%% %ds\n%% %ds\n", m, m, m);
  printf(buf, a, b, res);
}