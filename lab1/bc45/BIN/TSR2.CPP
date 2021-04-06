/* NOTE:
  This is an interrupt service routine.
  You can NOT compile this program with Test
  Stack Overflow turned on and get an
  executable file which will operate
  correctly.  Due to the nature of this
  function the formula used to compute
  the number of paragraphs may not
  necessarily work in all cases.  Use with
  care!  Terminate Stay Resident (TSR)
  programs are complex and no other support
  for them is provided.  Refer to the
  MS-DOS technical documentation
  for more information.  */

#include <dos.h>
/* The clock tick interrupt */
#define INTR 0x1C
/* Screen attribute (blue on grey) */
#define ATTR 0x7900

#ifdef __cplusplus
	#define __CPPARGS ...
#else
	#define __CPPARGS
#endif

/* reduce heaplength and stacklength to make a smaller program in memory */
//extern unsigned _heaplen = 1024;
extern unsigned _stklen  = 512U;

void interrupt ( *oldhandler)(__CPPARGS);

typedef unsigned int (far *s_arrayptr);

char myStack[10240];
char *p = &(myStack[1024]);
unsigned oSS,oSP;

void dummy()
{
   s_arrayptr screen[80];
   static int count;
	unsigned int mySS,mySP;

/* For a color screen the video memory is at B800:0000.
   For a monochrome system use B000:000 */
   screen[0] = (s_arrayptr) MK_FP(0xB800,0);

/* increase the counter and keep it within 0 to 9 */
   count++;
   count %= 10;

/* put the number on the screen */
   screen[0][79] = count + '0' + ATTR;

   asm	mov mySP,sp
   asm 	mov ax,ss
   asm	mov mySS,ax

	screen[0][1] = ((mySS>>12)&0x000f)+48+ATTR;
	screen[0][2] = ((mySS>>8)&0x000f)+48+ATTR;
	screen[0][3] = ((mySS>>4)&0x000f)+48+ATTR;
	screen[0][4] = ((mySS)&0x000f)+48+ATTR;
	screen[0][6] = ((mySP>>12)&0x000f)+48+ATTR;
	screen[0][7] = ((mySP>>8)&0x000f)+48+ATTR;
	screen[0][8] = ((mySP>>4)&0x000f)+48+ATTR;
	screen[0][9] = ((mySP)&0x000f)+48+ATTR;

/* call the old interrupt handler */
   oldhandler();

}
void interrupt handler(__CPPARGS)
{
	// you cannot switch stack and use local variable here...
	// because all local variable here will ref to old stack(and offset)
	// please switch to a new stack and use local variable
	// in next procedure call!!( so the new stack will be used.)
	asm mov ax,ss
	asm mov oSS,ax
	asm mov oSP,sp
	asm mov sp,offset p
	asm mov ax,seg p
	asm mov	ss,ax
	dummy();
	asm mov ax,oSS
	asm mov ss,oSS
	asm mov sp,oSP
}
int main(void)
{
/* get the address of the current clock
   tick interrupt */
oldhandler = getvect(INTR);

/* install the new interrupt handler */
setvect(INTR, handler);

/* _psp is the starting address of the
   program in memory.  The top of the stack
   is the end of the program.  Using mySS and
   _SP together we can get the end of the
   stack.  You may want to allow a bit of
   saftey space to insure that enough room
   is being allocated ie:
   (mySS + ((_SP + safety space)/16) - _psp)
*/
keep(0, (_SS + (_SP/16) - _psp));
return 0;
}
