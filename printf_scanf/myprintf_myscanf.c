#include <stdio.h>
#include <stdarg.h>

struct point_t {
    int x;
    int y;
};

double pow_10(int a) {
    if(a == 0) {
        return 1;
    }
    return 10 * pow_10(a-1);
}

void print_int(int num, int* wr) {
    if(num < 0) {
        putchar('-');
        *wr += 1;
        num = -num;
    }

    if(num > 9) {
        print_int(num / 10, wr);
    }
    char c = (char)((num%10) + '0');
    putchar(c);
    *wr += 1;
}

void print_llu(unsigned long long num, int* pr , int* wr) {
    if(num > 9 && *pr < 5) {
        print_llu(num / 10, pr, wr);
    }
    char c = (char)((num%10) + '0');
    putchar(c);
    *pr += 1;
    *wr += 1;
}

void print_float(double num, int* wr) {
    if(num < 0) {
        putchar('-');
        *wr += 1;
        num *= -1;
    }
    int pr = -1000000000;
    unsigned long long tmp = (unsigned long long)num;
    print_llu(tmp, &pr, wr);
    pr = 0;
    putchar('.');
    *wr += 1;
    num -= tmp;
    num *= 100000;
    while(num < 10000 && num != 0) {
        putchar('0');
        pr++;
        *wr += 1;
        num *= 10;
    }
    num /= pow_10(pr);
    tmp = (unsigned long long)(num+0.5);
    print_llu(tmp, &pr, wr);
    for(int i=pr; i<5; i++) {
        putchar('0');
        *wr += 1;
    }
}

void print_str(const char *str, int* wr) {
    int i=0;
    while(1) {
        if(*(str+i) == '\0') {
            return;
        }
        putchar(*(str + i));
        *wr += 1;
        i++;
    }
}

void print_point(struct point_t p, int *wr) {
    putchar('(');
    print_int(p.x, wr);
    putchar(' ');
    print_int(p.y, wr);
    putchar(')');
    *wr += 3;
}

int my_printf(char *str,...) {
    va_list ap;
    va_start(ap,str);
    int chars_written=0;
    int i=0;
    while(1) {
        if(*(str+i) == '\0') {
            return chars_written;
        }
        if(*(str+i) == '%') {
            if(*(str+i+1) == 'd') {
                int num = va_arg(ap,int);
                print_int(num, &chars_written);
                i++;
            }
            else if(*(str+i+1) == 'f') {
                double num = va_arg(ap,double);
                print_float(num, &chars_written);
                i++;
            }
            else if(*(str+i+1) == 's') {
                char *str2 = va_arg(ap,char *);
                print_str(str2, &chars_written);
                i++;
            }
            else if(*(str+i+1) == 'p') {
                struct point_t p = va_arg(ap,struct point_t);
                print_point(p, &chars_written);
                i++;
            }
            else {
                putchar(*(str+i));
            }
        }
        else {
            putchar(*(str+i));
            chars_written++;
        }
        i++;
    }
}

int my_getchar(int peek) {
    static int buf;
    int c;
    if(peek) {
        if(buf == 0) {
            c = getchar();
            buf = c;
            return c;
        }
        else {
            return buf;
        }
    }
    else {
        if(buf == 0) {
            return getchar();
        }
        else {
            int tmp=buf;
            buf=0;
            return tmp;
        }
    }
}

int scan_int(int *num, int *sc) {
    if(num == NULL || sc == NULL) {
        return 0;
    }
    *num = 0;
    int ch = 1;
    if(my_getchar(1) == '-') {
        my_getchar(0);
        ch = -1;
    }
    int c = my_getchar(1);
    if(c > '9' || c < '0') {
        return 0;
    }
    while(1) {
        c = my_getchar(1);
        if((c > '9' || c < '0')) {
            break;
        }
        my_getchar(0);
        *num *= 10;
        *num += c - '0';
    }
    *num *= ch;
    *sc += 1;
    return 1;
}

double scan_float(double *num, int *sc) {
    if(num == NULL || sc == NULL) {
        return 0;
    }
    *num = 0;
    int ch = 1;
    int div=0;
    int flag=0;
    if(my_getchar(1) == '-') {
        my_getchar(0);
        ch = -1;
    }
    int c = my_getchar(1);
    if(c > '9' || c < '0') {
        return 0;
    }
    while(1) {
        c = my_getchar(1);
        if((c > '9' || c < '0') && (c != '.' || flag)) {
            break;
        }
        my_getchar(0);
        if(c == '.') {
            flag = 1;
            continue;
        }
        if(flag) {
            div++;
        }
        *num *= 10;
        *num += c - '0';
    }
    *num *= ch;
    if(div) {
        *num /= pow_10(div);
    }
    *sc += 1;
    return 1;
}

int scan_point(struct point_t *num, int *sc) {
    if(num == NULL || sc == NULL) {
        return 0;
    }
    if(my_getchar(0) != '(') {
        return 0;
    }
    num->x = 0;
    scan_int(&num->x,sc);
    int c = my_getchar(0);
    if(c != ' ') {
        *sc -= 1;
        num->x=0;
        return 0;
    }
    num->y = 0;
    scan_int(&num->y,sc);
    if(my_getchar(0) != ')') {
        return 0;
    }
    return 1;
}

int my_scanf(char *str,...) {
    va_list ap;
    va_start(ap, str);
    int scanned = 0;
    int i = 0;
    while(1) {
        if (*(str + i) == '\0') {
            return scanned;
        }
        if(*(str+i) == '%') {
            if(*(str+i+1) == 'd') {
                int *num = va_arg(ap,int *);
                if(!scan_int(num,&scanned)) {
                    return scanned;
                }
                i++;
            }
            else if(*(str+i+1) == 'f') {
                double *num = va_arg(ap,double *);
                if(!scan_float(num,&scanned)) {
                    return scanned;
                }
                i++;
            }
            else if(*(str+i+1) == 'p') {
                struct point_t *p = va_arg(ap,struct point_t *);
                if(!scan_point(p,&scanned)) {
                    return scanned;
                }
                i++;
            }
        }
        else {
            int c = my_getchar(0);
            if(*(str+i) != c) {
                return scanned;
            }
        }
        i++;
    }
}


int main() {
    return 0;
}
