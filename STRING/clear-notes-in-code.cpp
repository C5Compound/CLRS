/**
*
* 清除代码中的注释
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <wctype.h>

// 状态机
void ClearNotes(FILE *file, FILE *newfile)
{
    int flag = 0;
    while (!feof(file)) {
        wchar_t letter = fgetwc(file);
        switch (letter)
        {
        case L'/':
            switch (flag)
            {
            case 0:
                flag = 1;
                break;
            case 1:
                flag = 2;
                //
                //
                break;
            case 2:
                //
                flag = 0;
                break;
            case 3:
                //
                flag = 0;
                break;
            case 4:
                //
                flag = 0;
                break;
            default:
                fputwc(L'/', newfile);
                break;
            }
            break;
        case '*':
            switch (flag)
            {
            case 1:
                //
                //
                flag = 3;
                break;
            case 2:
                //
                break;
            case 3:
                //
                flag = 4;
                break;
            default:
                fputwc('*', newfile);
                break;
            }
            break;
        case L'"':
            switch (flag)
            {
            case 0:
                flag = 5;
                fputwc(L'"', newfile);
                break;
            case 2:
                //
                break;
            case 3:
                //
                break;
            case 4:
                flag = 3;
                //
                break;
            case 5:
                flag = 0;
                fputwc(L'"', newfile);
                break;
            default:
                fputwc(L'"', newfile);
                break;
            }
            break;
        case L'\'':
            switch (flag)
            {
            case 0:
                flag = 6;
                fputwc(L'\'', newfile);
                break;
            case 2:
                //
                break;
            case 3:
                //
                break;
            case 4:
                flag = 3;
                //
                break;
            case 6:
                flag = 0;
                fputwc(L'\'', newfile);
                break;
            default:
                fputwc(L'\'', newfile);
                break;
            }
            break;
        default:
            switch (flag)
            {
            case 1:
                if (letter == L' ' || letter == L'\n') {
                    fputwc(L'/', newfile);
                    fputwc(letter, newfile);
                    flag = 0;
                }
            case 2:
                if (letter == L'\n') {
                    flag = 0;
                    fputwc(L'\n', newfile);
                }
                else {
                    //
                }
                break;
            case 3:
                //
                break;
            case 4:
                flag = 3;
                //
                break;
            default:
                fputwc(letter, newfile);
                break;
            }
        }
    }
}

#define LINE_MAX 1024

// 清除空行
void ClearLine(FILE *file, FILE *newfile)
{
    wchar_t buf[LINE_MAX];
    while (!feof(file)) {
        int flag = 0;
        memset(buf, 0, LINE_MAX * sizeof(wchar_t));
        fgetws(buf, LINE_MAX, file);
        for (int i = 0; i < LINE_MAX; i++) {
            if (buf[i] != L'\n' && buf[i] != L' ' && iswprint(buf[i])) {
                flag = 1;
                break;
            }
        }
        if (flag) {
            fputws(buf, newfile);
        }
    }

}

//int main()
//{
//    FILE *fr = _wfopen(L"Alphabeta.cpp", L"rt+, ccs = UNICODE");
//    FILE *fw = _wfopen(L"extract.cpp", L"wt+, ccs = UNICODE");
//    FILE *ff = _wfopen(L"clearline.cpp", L"wt+, ccs = UNICODE");
//    ClearNotes(fr, fw);
//    rewind(fw);
//    ClearLine(fw, ff);
//    fclose(fr);
//    fclose(fw);
//}