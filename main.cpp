#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <windows.h>


void replace_account_number(char* text) {
    char* account_number_start = NULL;
    char* account_number_end = NULL;
    const int ACCOUNT_NUM_LENGTH = 26;
    const char* REPLACE_MSG = "Don't copy account number!";

    int text_length = strlen(text);
    if (text_length >= ACCOUNT_NUM_LENGTH) {
        for (int i = 0; i < text_length - ACCOUNT_NUM_LENGTH + 1; i++) {
            int j;
            for (j = 0; j < ACCOUNT_NUM_LENGTH; j++) {
                if (text[i + j] < '0' || text[i + j] > '9') {
                    break;
                }
            }
            if (j == ACCOUNT_NUM_LENGTH) {
                account_number_start = &text[i];
                account_number_end = &text[i + ACCOUNT_NUM_LENGTH - 1];
                break;
            }
        }

        if (account_number_start != NULL && account_number_end != NULL) {
            const int REPLACE_MSG_LENGTH = strlen(REPLACE_MSG);
            const int SPACES_TO_FILL = ACCOUNT_NUM_LENGTH - REPLACE_MSG_LENGTH;

            memset((char*)account_number_start, ' ', ACCOUNT_NUM_LENGTH);
            strncpy(account_number_start, REPLACE_MSG, REPLACE_MSG_LENGTH);
            memset(account_number_start + REPLACE_MSG_LENGTH, ' ', SPACES_TO_FILL);
        }
    }
}

// Don't copy account number!
// 
// number account 35202111090000000001234567 
int main() {
    if (!OpenClipboard(NULL)) {
        return 1;
    }

    while (1) {
        if (IsClipboardFormatAvailable(CF_TEXT)) {
            if (!OpenClipboard(NULL)) {
                printf("Failed to open clipboard.\n");
                return 1;
            }


            HGLOBAL hglbCopy = NULL;

            HGLOBAL hglb = GetClipboardData(CF_TEXT);
            if (hglb != NULL) {
                LPSTR lptstr = (char*)GlobalLock(hglb);
                if (lptstr != NULL) {
                    replace_account_number(lptstr);
                    int len = strlen(lptstr);

                    hglbCopy = GlobalAlloc(GMEM_MOVEABLE, len + 1);
                    if (hglbCopy != NULL) {
                        LPSTR lptstrCopy = (char*)GlobalLock(hglbCopy);
                        if (lptstrCopy != NULL) {
                            memcpy(lptstrCopy, lptstr, len + 1);
                            GlobalUnlock(hglbCopy);
                            EmptyClipboard();
                            SetClipboardData(CF_TEXT, hglbCopy);
                        }
                    }

                    system("cls");
                    printf("%s", lptstr);
                    GlobalUnlock(hglb);
                }
            }
            CloseClipboard();

            if (hglbCopy != NULL) {
                GlobalUnlock(hglbCopy);
                GlobalFree(hglbCopy);
            }

            Sleep(2000); // Sleep for 200ms before checking the clipboard again
        }
    }
    return 0;
}