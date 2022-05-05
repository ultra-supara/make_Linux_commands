#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <regex.h>

static void grep(regex_t *patron, FILE *src) {
    char buf[4096];
    //grepの中核部分
    while(fgets(buf, sizeof buf, src)) {
        if(regexec(patron, buf, 0, NULL, 0) == 0) {
            fputs(buf, stdout);
        }
    }
}

int main(int argc, char *argv[]) {
    regex_t patron;
    int err;

    if(argc < 2) {
        fputs("no pattern\n", stderr);
        exit(1);
    }
    err = regcomp(&patron, argv[1], REG_EXTENDED | REG_NOSUB | REG_NEWLINE);
    if(err != 0) {
        char buf[1024];

        regerror(err, &patron, buf, sizeof buf);
        puts(buf);
        exit(1);
    }

    if(argc == 2) {
        grep(&patron, stdin);
    } else{
        for (int i = 2; i < argc; i++){
            FILE *f;

            f = fopen(argv[i], "r");
            if (f == NULL) {
                perror(argv[i]);
                exit(1);
            }
            grep(&patron, f);
            fclose(f);
        }
    }
    regfree(&patron);
    exit(0);
}
//正規表現のパターン文字列を"regex_t" に変換、入力用ストリームの準備
//参考資料　 https://qiita.com/thaladabar/items/91b1a66b1ead90b26102#regexec
