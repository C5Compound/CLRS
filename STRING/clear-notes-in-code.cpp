/**
 *
 * ��������е�ע��
 *
 */

#include <stdlib.h>
#include <stdio.h>

// ״̬��
void ClearNotes(FILE *file, FILE *newfile)
{
    int flag = 0;
    while (char letter = fgetc(file) != EOF) {
        switch (letter) 
        {
        case '/':
            if (flag == 1) {
                // ��ȡ����ʣ�µ��ַ���ɾ��
                flag = 0;
            }
            else {
                flag = 1;
            }
            break;
        case '*':
            if (flag == 1) {
                // ��¼λ��
                flag = 2;
            }
            else if (flag == 2) {
                // ��ȡ��һ�����ж��Ƿ�Ϊ'/'
                if (fgetc(file) == '/') {
                    // ɾ��
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