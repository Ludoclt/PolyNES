#ifndef DEBUG_H
#define DEBUG_H

#ifdef __cplusplus
extern "C"
{
#endif

    void ioInit(void);
    char getChar(void);
    void sendChar(char c);
    void sendString(const char *s);
    void sendInt(int number);
    void print(const char *s, ...);
    void println(const char *s, ...);

#ifdef __cplusplus
}
#endif

#endif