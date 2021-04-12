main()
{
	int x;

	asm mov ax,0x0800
	asm mov cx,0x01f8
	asm mov bx,0x2da2
	asm mov si,16
	asm mov di,0
	asm int 0x31

	x++;
	x--;
}