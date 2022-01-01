#ifndef __UTILS_H
#define __UTILS_H

#define INFO(...)                                           \
  do                                                         \
  {                                                          \
    printf("INFO %s:%d %s ", __FILE__, __LINE__, __func__); \
    printf(__VA_ARGS__);                                     \
  } while (0)

#endif
