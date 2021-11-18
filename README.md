# NoHello
A Hello World in C, except there is no Hello World

```c
#include<stdio.h>

int main(void) {
  unsigned long al = 0x726F6C6564574820,
                dx = 0x357620655410;
  while(dx) putchar(al >> (((dx>>=4) & 0xF) << 3) & 0xFF);
}
```

## TODO: How it works
