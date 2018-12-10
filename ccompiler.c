#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;              // 当前的标识符.
char* src, *old_src;    // 这两个指针都是指向源代码的string.
int pool_size;          // 默认的test/data/stack大小
int line;               // 当前的行数.

void get_next_token() {
    token = *src++;
}

void expression(int level) {
    /* do nothing. */
}

void program() {
    /* 获得下一个标识符*/
    get_next_token();
    while (token > 0) {
        printf("token is: %c\n", token);
        get_next_token();
    }
}

int eval() {
    /* do nothing yt */
    return 0;
}

int main(int argc, char* argv[]) {
    int i, fd;

    /* 跳过第一个参数，也就是跳过程序名称 */
    argc--;
    argv++;

    pool_size = 256 * 1024; 
    line = 1;

    if ((fd = open(*argv, 0)) < 0) {
        printf("Could not open %s\n", *argv);
        return -1;
    }

    if (!(src = old_src = malloc(pool_size))) {
        printf("Could not malloc %d for source area\n", pool_size);
        return -1;
    }

    /* 读取源文件 */
    if ((i = read(fd, src, pool_size - 1)) <= 0) {
        printf("read source file faild, returned %d\n", i);
        return -1;
    }
    src[i] = 0;
    close(fd);

    program();
    return eval();
}



