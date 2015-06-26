/**
 *
 * 清除代码中的注释
 *
 */

#include <stdlib.h>
#include <stdio.h>

// 状态机
void ClearNotes(FILE *file, FILE *newfile)
{
    int flag = 0;
    while (char letter = fgetc(file) != EOF) {
        switch (letter) 
        {
        case '/':
            if (flag == 1) {
                // 读取这行剩下的字符并删除
                flag = 0;
            }
            else {
                flag = 1;
            }
            break;
        case '*':
            if (flag == 1) {
                // 记录位置
                flag = 2;
            }
            else if (flag == 2) {
                // 读取下一个，判断是否为'/'
                if (fgetc(file) == '/') {
                    // 删除
                }
            }
            break;
        case '"':
            flag = flag == 3 ? 0 : flag == 0 ? 3 : flag;
            break;
        case '\'':
            flag = flag == 4 ? 0 : flag == 0 ? 4 : flag;
            break;
        default:
            if (!flag) {
                fputc(letter, newfile);
            }
        }
    }
}