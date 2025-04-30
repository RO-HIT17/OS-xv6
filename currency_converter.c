
#include "types.h"
#include "stat.h"
#include "user.h"

int currency_convert(char from_currency, char to_currency, int amount);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf(2, "Usage: currency_convert <from_currency> <to_currency> <amount>\n");
        exit();
    }

    char from_currency = argv[1][0];
    char to_currency = argv[2][0];
    int amount = atoi(argv[3]);

    int result = currency_convert(from_currency, to_currency, amount);

    if (result < 0) {
        printf(2, "Conversion failed. Invalid input.\n");
    } else {
        printf(1, "Converted amount: %d\n", result);
    }

    exit();
}
