#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <string.h>

int token;              // 当前的标识符.
char* src, *old_src;    // 这两个指针都是指向源代码的string.
int pool_size;          // 默认的test/data/stack大小
int line;               // 当前的行数.

int* text_segment;      
int* old_text_segment;
int* stack;
char* data_segment;

// 这些都时虚拟机的寄存器. 
// pc : 代表程序计数器(programe count),它存放一个内存地址，这个地址用来指向
// 下一条需要执行的计算机指令.
// bp : 基地址指针。用与指向stack的某些位置，再调用函数时会使用到它.
// sp : 指针寄存器，永远指向当前的stack top, 需要注意的是由于stack是位于高地址
// 并向底地址增长的，所以入栈时SP的值减小.
// ax : 通用寄存器, 它用于存访一条指令执行后的结果
int* pc, *bp, *sp;
int ax, cycle;

// 指令集
// IMM(num) : 将num放入寄存器ax中
// LC : 将对应的地址中的字符载入ax中，要求ax中存放地址.
// LI : 将对应地址中的整数载入ax中，要求ax中存放地址.
// SC : 将ax中的数据作为字符存入地址中，要求栈顶存放地址.
// SI : 将ax中的数据作为整数存入地址中，要求栈顶存放地址.
// PUSH : 将ax的值放入栈中.
// JMP : 无条件的将当前的PC寄存器设置位指定的addr.
// JZ : 如果ax为零就跳转.
// JNZ : 如果zx不为0就跳转
enum {
    LEA, INM, JMP, CALL, JZ, JNZ, ENT, ADJ, LEV, LI, LC, SI, SC, PUSH,
    OR, XOR, AND, EQ, NE, LT, GT, LE, GE, SHL, SHR, ADD, SUB, MUL, DIV,
    MOD, OPEN, READ, CLOS, PRTF, MALC, MSET, MCMP, EXIT
};

void get_next_token() {
    token = *src++;
}

/* 对标识符进行解析 */
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
    int op, *tmp;
    while (true) {
        switch (op) {
            case IMM:
            {
                ax = *pc++;
                break;
            }
            case LC:
            {
                ax = *(char*)ax;
                break;
            }
            case LI:
            {
                ax = *(int*)ax;
                break;
            }
            case SC:
            {
                ax = *(char*)*sp++ = ax;
                break;
            }
            case SI:
            {
                *(int*)*sp++ = ax;
                break;
            }
            case PUSH:
            {
                *--sp = ax;
                break;
            }
            case JMP:
            {
               pc = (int*)*pc; 
               break;
            }
            case JZ:
            {
                pc = ax ? pc + 1 : (int*)*pc;
                break;
            }
            case JNZ:
            {
                pc = ax ? (int*)pc : pc + 1;
                break;
            }
            
        }
    }
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

    /* 给machine分配内存 */
    if (!(text_segment = old_text_segment = malloc(pool_size))) {
        printf("could not malloc(%d) for text area\n", pool_size);
        return -1;
    }

    if (!(data_segment = malloc(pool_size))) {
        printf("could not malloc(%d) for data area\n", pool_size);
        return -1;
    }

    if (!(stack = malloc(pool_size))) {
        printf("could not malloc(%d) for stack area\n", pool_size);
        return -1;
    }
    memset(text, 0, pool_size);
    memset(data, 0, pool_size);
    memset(stack, 0, pool_size);


    program();
    return eval();
}



