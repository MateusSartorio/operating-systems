#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv) {
    const char* msg = "Hello World!\n";
    write(STDOUT_FILENO, msg, 13);

	return 0;
}
