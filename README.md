# Account Number Replacement

This program is designed to monitor the clipboard for text containing an account number, and replace it with a specific message. The replaced account number is then displayed on the console.

## Functionality

1. The `replace_account_number` function is responsible for finding the account number in the provided text and replacing it with the message "Don't copy account number!". The account number is expected to be a sequence of 26 digits.
2. The `main` function monitors the clipboard for text data using the Windows API functions.
3. If text data is available on the clipboard, it is retrieved and passed to the `replace_account_number` function.
4. The modified text is stored in a new clipboard data object, and the original clipboard is cleared.
5. The modified text is then displayed on the console using the `printf` function.
6. The program continues to monitor the clipboard, repeating the process after a 200ms delay.

## Usage

To use this program, follow these steps:

1. Compile the source code using a C compiler, ensuring the necessary Windows libraries are linked. For example:
   ```bash
   gcc -o account_replacement.exe account_replacement.c -luser32
   ```
2. Run the compiled executable:
   ```bash
   account_replacement.exe
   ```

## Notes

- The code utilizes the Windows API functions `OpenClipboard`, `IsClipboardFormatAvailable`, `GetClipboardData`, `EmptyClipboard`, `SetClipboardData`, `CloseClipboard`, and `Sleep`.
- The program only works on Windows systems due to the use of Windows-specific functions.
- The code utilizes a constant string message, "Don't copy account number!", which is used to replace the account number. The length of the account number is assumed to be 26 digits.
- The program continuously monitors the clipboard, replacing any detected account numbers until it is terminated.
- The console is cleared using the `system("cls")` command before printing the modified text.

Please exercise caution when using this program and ensure that you have the necessary permissions to access and modify the clipboard.
