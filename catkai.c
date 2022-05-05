#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

static void die(const char *s) {
    strerror(*s);
    exit(1);
}

static void cat(const char *path) {
    int fc, n;
    unsigned char buf[2048];

    fc = open(path, O_RDONLY);
    if (fc < 0)
        die(path);
    for (;;) {
        n = read(fc, buf, sizeof buf);
        if (n < 0)
            die(path);
        if (n == 0)
            break;
        if (write(STDOUT_FILENO, buf, n) < 0)
            die(path);
    }
    if (close(fc) < 0)
        die(path);
}

int main(int argc, char *argv[]) {
    //引数の個数チェック、例外処理
    if (argc < 2) {
        fprintf(stderr, "%s: file name is not given\n", argv[0]);
        exit(1);
    }
    for (int i = 1; i < argc; i++) {
        cat(argv[i]);
    }
    return 0;
}
