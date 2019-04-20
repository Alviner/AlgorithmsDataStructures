#include <stdio.h>
#include <string.h>

class BloomFilter {
public:
    int filter_len;
    int filter;

    BloomFilter(int f_len) {
        this->filter_len = f_len;
        this->filter = 0;
    }

    // хэш-функции
    int hash1(char *str1) {
        int res = 0;
        for (int i = 0; i < strlen(str1); i++) {
            int code = str1[i];
            res = (17 * res + code) % this->filter_len;
        }
        return 1 << res;
    }

    int hash2(char *str1) {
        int res = 0;
        for (int i = 0; i < strlen(str1); i++) {
            int code = str1[i];
            res = (223 * res + code) % this->filter_len;
        }
        return 1 << res;
    }

    void add(char *str1) {
        this->filter |= this->hash1(str1);
        this->filter |= this->hash2(str1);
    }

    bool is_value(char *str1) {
        int res = this->hash1(str1) + this->hash2(str1);
        return (this->filter & res) == res;
    }
};