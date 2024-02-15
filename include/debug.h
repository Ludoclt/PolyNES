#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C"
{
#endif

    void debugInit(void);
    char getChar(void);
    void sendChar(char c);
    void sendLong(unsigned long dword);
    void print(const char *s);
    void println(const char *s);
    void error(const char *s);

#ifdef __cplusplus
}
#endif

#endif