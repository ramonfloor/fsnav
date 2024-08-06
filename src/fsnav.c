#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <linux/limits.h>
#include <threads.h>

#include <fsnav/buffer.h>
#include <fsnav/directory.h>
#include <fsnav/io.h>


int main() {
    int return_value = EFAULT;

    thrd_t t1;
    thrd_create(&t1, (void*)listen, NULL);
    thrd_join(t1, NULL);
    return return_value;
}