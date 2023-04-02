#include <coder.h>
#include <command.h>
#include <string.h>

int main(int argc, char* argv[])
{
    if (argc != 4) {
        printf("Usage:\n");
        printf("coder encode <in-file-name> <out-file-name>\n");
        printf("coder decode <in-file-name> <out-file-name>\n");
        return error;
    }
    const char encode_command[7] = "encode";
    const char decode_command[7] = "decode";
    if (!strcmp(encode_command, argv[1])) {
        if (encode_file(argv[2], argv[3])) {
            printf("Can't encode\n");
            return error;
        }
    } else if (strcmp(decode_command, argv[2])) {
        if (decode_file(argv[2], argv[3])) {
            printf("Can't decode\n");
            return error;
        }
    } else {
        printf("Wrong command name!\n");
        printf("Usage:\n");
        printf("coder encode <in-file-name> <out-file-name>\n");
        printf("coder decode <in-file-name> <out-file-name>\n");
        return error;
    }
    return 0;
}