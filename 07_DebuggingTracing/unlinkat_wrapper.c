#define _GNU_SOURCE
#include <fcntl.h>
#include <unistd.h>
#include <dlfcn.h>
#include <errno.h>
#include <string.h>

typedef int (* intparams)(int, const char *, int);

int unlinkat(int dirfd, const char *pathname, int flags) {
    int lastSlash = 0;
    for (int i = strlen(pathname) - 1; i >= 0; --i) {
        if (pathname[i] == '/') {
            lastSlash = i;
            break;
        }
    }
    const char *filename = &pathname[lastSlash + 1];
    if (strstr(filename, "FIX")) {
        return EPERM;
    }
    else {
        intparams true_unlinkat = dlsym(RTLD_NEXT, "unlinkat");
        return true_unlinkat(dirfd, pathname, flags);
    }
}