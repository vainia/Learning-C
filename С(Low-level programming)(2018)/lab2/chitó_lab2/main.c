#include <8051.h>
#include <string.h>

#define WORD_SIZE 4

char buf[WORD_SIZE + 1] = {0};

char getchar(void)
{
	char znak;
	while (RI==0);
	RI=0;
	znak=SBUF;
	return znak;
} 

void putchar(char znak)
{
	SBUF=znak;
	while(TI==0);
	TI=0;
}
 
void init()
{
	TH0=0xfd;
	SCON=0x50;
	TMOD=0x20;
	PCON=0x80;
	TCON=0x40;
}

unsigned long hex2int(char *a, unsigned int len)
{
    char i;
    unsigned long val = 0;

    for(i=0;i<len;i++)
		if(a[i] <= 57)
			val += (a[i]-48)*(1<<(4*(len-1-i)));
		else
			val += (a[i]-55)*(1<<(4*(len-1-i)));

    return val;
}

int ascii2hex(char c)
{
        int num = (int) c;
        if(num < 58 && num > 47)
                return num - 48; 
        if(num < 103 && num > 96)
                return num - 87;
        return num;
}

void get_word() {
        char i = 0;
        char c;
        for(i = 0; i < WORD_SIZE; ++i) {
                c = getchar();
                if (c == ' ') break;
                buf[i] = c;
        }
        buf[i] = '\0';
}

void res (char a, char b, char c) {
        putchar(a + b - c);
}

void main (void)
{
	unsigned char a, b, c, i;
	// char znak;
	// char counter = 0;
	// char iter = 0;
	// char input[16];
	
	init();
	
	for(;;)
	{
		get_word();
		a = hex2int(buf, WORD_SIZE);
		get_word();
		b = hex2int(buf, WORD_SIZE);
		get_word();
		c = hex2int(buf, WORD_SIZE);
		res(a,b,c);
		for (i = 0; i < WORD_SIZE; ++i) putchar(buf[i]);
		// znak=getchar();
		// input[iter] = znak;
		// ++iter;
		// if((znak == ' ') && (counter < 3)) 
		// {
			// char j;
			// //char array[] = "   PROGRAM DZIALA POPRAWNIE   ";
			
			// ++counter;
			// for (j=0; j<strlen(input); ++j) putchar(input[j]);
		// }  
		// else 
		// {
			// putchar(znak);
		// }
	} 
}
