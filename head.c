#include <stdio.h>
#include <stdlib.h>

static void head(FILE *f, long nlines) {
    //nlines...number of lines
    int a;
    //例外処理
    if(nlines <= 0) return;
    //headの中身の実装
    while((a = getc(f)) != EOF) {
        if(putchar(a) < 0) exit(1);
        if(a == '\n') {
            nlines--;
            if(nlines == 0) return;
        }
    }
}

int main(int argc, char*argv[]) {
    long nlines;
    //引数の例外処理
    if(argc < 2) {
        fprintf(stderr, "Usage: %s \n", argv[0]);
        exit(1);
    }
    nlines = atoi(argv[1]);
    if (argc == 2) {
        head(stdin, nlines);
    } else {
        for (int i = 2; i < argc; i++) {
            FILE *f;

            f = fopen(argv[i], "r");
            if(f == NULL) {
                perror(argv[i]);
                exit(1);
            }
            head(f, nlines);
            fclose(f);
        }
    }
    return 0;
}
