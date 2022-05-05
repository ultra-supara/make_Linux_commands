#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#define _GNU_SOURCE
//プロトタイプ宣言を取り込むために定数の定義とヘッダーファイルのインクルード

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

// struct option の配列を指す静的な変数の定義と指示したい中身の格納
#define DEFAULT_N_LINES 10
static struct option longopts[] = {
    {"lines", required_argument, NULL, 'n'},
    {"help", no_argument, NULL, 'h'},
    {0, 0, 0, 0}
};


int main(int argc, char*argv[]) {
    int operation;
    long nlines = DEFAULT_N_LINES;
    //ここでオプション解析のループ実装
    while((operation = getopt_long(argc,  argv, "n:", longopts, NULL)) != -1) {
            switch (operation){

                //-n -lines
            case 'n':
                nlines = atoi(optarg);
                break;

                //--help
            case 'h':
                fprintf(stdout, "Usage: %s [-n LINES] [FILE .....]\n", argv[0]);
                exit(0);

                //error
            case '?':
                fprintf(stderr, "Usage: %s [-n LINES] [FILE .....]\n", argv[0]);
                exit(1);
            }
        }
        //引数の受け渡し
        if(optind == argc) {
            head(stdin, nlines);
        } else {
            for(int i = optind; i < argc; i++) {
                FILE *f;

                f = fopen(argv[i], "r");
                if (f == NULL) {
                    perror(argv[i]);
                    exit(1);
                }
                head(f, nlines);
                fclose(f);
            }
        }
        return 0;

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
