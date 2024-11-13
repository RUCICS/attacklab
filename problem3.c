#include <stdio.h>
#include <string.h>
#include<stdlib.h>
// 假设的目标函数

// 易受攻击的函数
void func1(int x){
    printf("your lucky number is %d\n",x);
    exit(0);
}
void mov_rdi(void *addr){
    __asm__("mov $0x20,%rdi\n\t"
            "ret\n\t");
}
void mov_rax(void *addr){
    __asm__("mov $0x401111,%rax\n\t"
            "ret\n\t");
}
void call_rax(void*addr){
    __asm__("call *%rax\n\t"
            "ret\n\t");
}
void jmp_x(void*addr){
    __asm__("jmp 0x7eeeeeee\n\t"
            "ret\n\t");
}
void func(char *s) {
    char buffer[32];
    memcpy(buffer, s, 0x40);
    // 未检查输入长度就复制字符串到缓冲区
    printf("Now,say your lucky number is 114!\n");
    printf("if you do that,I will give you great scores!\n");
    return ;
}

int main(int argc, char *argv[]) {
    printf("Do you like ICS?\n");
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <file>\n", argv[0]);
        return 1;
    }

    // 打开并读取文件中的内容
    FILE *file = fopen(argv[1], "r");
    if (!file) {
        perror("fopen");
        return 1;
    }

    char payload[256];
    size_t read_bytes = fread(payload, 1, sizeof(payload), file);
    if (read_bytes == 0) {
        perror("fread");
        fclose(file);
        return 1;
    }
    payload[read_bytes] = '\0';  // 确保字符串以 null 结尾

    // 关闭文件
    fclose(file);

    // 调用易受攻击的函数
    func(payload);
    // 如果没有发生异常，打印这条消息
    printf("You don't like it! You fail!\n");

    return 0;
}