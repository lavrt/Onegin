#ifndef HELPER_H
#define HELPER_H

#define FREE(ptr_) \
    do { free(ptr_); ptr_ = NULL; } while (0)
#define FCLOSE(file_) \
    do { fclose(file_); file_ = NULL; } while (0)

#endif // HELPER_H
