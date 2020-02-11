//
// Created by 丙寅乙 on 2020/2/11.
//

#include <stdio.h>
#include <stdlib.h>

static int type;

static void selectHours() {
    printf("\n");
    switch (type) {
        case 49:
            printf("当前时辰排盘\n");
            break;
        case 50:
            printf("随机时辰排盘\n");
            break;
        default:
            break;
    }
}

static void usage() {
    printf("\n\t上古三式之首大六壬、排盘复杂、信息量大、专测人事\n\n");
    printf("\t输入序号方式排盘：1.当前时辰 2.随机时辰\n\t");
    type = getchar();
    if (type != 49 && type != 50) {
        exit(101);
    }
    selectHours();
}

int main() {
    usage();
    return 0;
}
