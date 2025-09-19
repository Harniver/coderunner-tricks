#ifndef __TESTER_H
#define __TESTER_H

#include <stddef.h>
#include <stdlib.h>
#include <stdarg.h>

void* student_malloc(size_t size);

void student_free(void* ptr);

int student_vprintf(const char *restrict format, va_list ap);

int student_vfprintf(void *stream, const char *restrict format, va_list ap) {
    return student_vprintf(format, ap);
}

int student_vdprintf(int fd, const char *restrict format, va_list ap) {
    return student_vprintf(format, ap);
}

int student_printf(const char *restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    int r = student_vprintf(format, ap);
    va_end(ap);
    return r;
}

int student_fprintf(void *stream, const char *restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    int r = student_vprintf(format, ap);
    va_end(ap);
    return r;
}

int student_dprintf(int fd, const char *restrict format, ...) {
    va_list ap;
    va_start(ap, format);
    int r = student_vprintf(format, ap);
    va_end(ap);
    return r;
}

#endif

#define malloc student_malloc
#define free student_free
