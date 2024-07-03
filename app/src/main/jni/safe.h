
#ifndef HONKAI_IMPACT_3RD_MENU_MOD_SAFE_H
#define HONKAI_IMPACT_3RD_MENU_MOD_SAFE_H

void anti();
ssize_t read_one_line(int fd, char *buf, size_t len);
int openat_2(const char *path, int flag);
int api_level();

#endif //HONKAI_IMPACT_3RD_MENU_MOD_SAFE_H
