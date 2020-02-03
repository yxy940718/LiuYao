//
// Created by turaiiao on 2020/2/2.
//

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/**
 * 随机数的最大和最小范围
 */
#define MAX_NUMBER 999
#define MIN_NUMBER 100

static int* hexagramNumbers;

static void usage() {
    printf("\n\t一念皆有一乾坤，请默念你想要摇卦的事情，单击回车键以开始！\n");
}

static void end() {
    printf("\n\tQQ：1171840237 微信: MCMenjoy 带盘解卦\n");
    printf("\n\t单击任意键退出\n");
    getchar();
}

/**
 * 每个卦的参数结构
 */
typedef struct {
    // 第一爻
    int a;
    // 第二爻
    int b;
    // 第三爻
    int c;
    // 阴阳
    int yang;
    // 卦名
    char* name;
    // 上卦第上爻地支
    char* x1;
    // 上卦第五爻地支
    char* y1;
    // 上卦第四爻地支
    char* z1;
    // 下卦第三爻地支
    char* x2;
    // 下卦第二爻地支
    char* y2;
    // 下卦初爻地支
    char* z2;
} DiagramRule;

static DiagramRule eightDiagramRules[] = {
    {1, 1, 1, 1, "乾", "戌", "申", "午", "辰", "寅", "子"},
    {0, 1, 1, 0, "兑", "未", "酉", "亥", "丑", "卯", "巳"},
    {1, 0, 1, 0, "离", "巳", "未", "酉", "亥", "丑", "卯"},
    {0, 0, 1, 1, "震", "戌", "申", "午", "辰", "寅", "子"},
    {1, 1, 0, 0, "巽", "卯", "巳", "未", "酉", "亥", "丑"},
    {0, 1, 0, 1, "坎", "子", "戌", "申", "午", "辰", "寅"},
    {1, 0, 0, 1, "艮", "寅", "子", "戌", "申", "午", "辰"},
    {0, 0, 0, 0, "坤", "酉", "亥", "丑", "卯", "巳", "未"}
};

/**
 * 根据爻数返回卦名
 *
 * @param a 第一爻
 * @param b 第二爻
 * @param c 第三爻
 * @return  卦名
 */
static char* searchDiagramRule(int a, int b, int c) {
    for (int i = 0; i < 8; i ++) {
        DiagramRule rule = eightDiagramRules[i];
        // 三个爻的阴阳相等
        if (rule.a == a && rule.b == b && rule.c == c) {
            return rule.name;
        }
    }
    return "NULL";
}

/**
 * 根据卦名返回卦的参数位置
 *
 * @param name 卦名
 * @return     卦的参数的位置
 */
static int searchDiagramRuleIndexByName(const char* name) {
    for (int i = 0; i < 8; i ++) {
        DiagramRule rule = eightDiagramRules[i];
        // 卦名相等即返回
        if (rule.name == name) {
            return i;
        }
    }
    return -1;
}

static void initRandomHexagramNumbers();
static void displayContentDiagram();

int main() {
    usage();

    if (getchar() == 10) {
        initRandomHexagramNumbers();
    }
    return 0;
}

/**
 * 生成六个爻数，先生成六个 100 -> 999 的随机数，后根据偶数设置阴阳爻
 */
static void initRandomHexagramNumbers() {
    hexagramNumbers = (int *) malloc(6);
    // 随机当前时间盐
    srand((int) time(NULL));

    for (int i = 0; i < 6; i ++) {
        // 100 -> 999
        int x = rand() % (MAX_NUMBER - MIN_NUMBER) + MIN_NUMBER;

        for (int j = 1; j <= 6; j ++) {
            hexagramNumbers[i - 1] = (int) (x / j) % 2 == 0 ? 1 : 0;
        }
    }

    displayContentDiagram();
}

/**
 * 主要输出体卦函数
 */
static void displayContentDiagram() {
    // 上卦
    const char* a = searchDiagramRule(hexagramNumbers[0], hexagramNumbers[1], hexagramNumbers[2]);
    // 下卦
    const char* b = searchDiagramRule(hexagramNumbers[3], hexagramNumbers[4], hexagramNumbers[5]);
    // 上卦的参数
    DiagramRule x = eightDiagramRules[searchDiagramRuleIndexByName(a)];
    // 下卦的参数
    DiagramRule y = eightDiagramRules[searchDiagramRuleIndexByName(b)];
    // 输出爻数
    for (int i = 0; i < 6; i ++) {
        switch (i) {
            case 0: printf("\t上爻 "); break;
            case 1: printf("\t五爻 "); break;
            case 2: printf("\t四爻 "); break;
            case 3: printf("\t三爻 "); break;
            case 4: printf("\t二爻 "); break;
            case 5: printf("\t初爻 "); break;
            default:
                break;
        }

        // 输出阴阳爻
        printf("%1s", hexagramNumbers[i] == 1 ? "---" : "- -");
        // 在第五爻和第二爻输出卦名
        if (i == 1) printf(" %s", a);
        if (i == 4) printf(" %s", b);

        // 输出每一爻的干支
        switch (i) {
            case 0: printf("%7s", x.x1); break;
            case 1: printf(" %s", x.y1); break;
            case 2: printf("%7s", x.z1); break;
            case 3: printf("%7s", y.x2); break;
            case 4: printf(" %s", y.y2); break;
            case 5: printf("%7s", y.z2); break;
            default:
                break;
        }

        printf("\n");
    }

    end();
}
