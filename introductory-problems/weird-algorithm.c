#include <stdio.h>
#include <stdint.h>

typedef long long int ll;

int main() {
    ll n;
    scanf("%lld", &n);

    while (n > 0 && n != 1) {
        printf("%lld ", n);
        if (n % 2 == 0) {
            n = n / 2;
        } else {
            n = n * 3 + 1;
        }
    }

    printf("1");

    return 0;
}
