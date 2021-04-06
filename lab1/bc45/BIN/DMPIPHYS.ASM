	.386p
	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "DMPIPHYS.CPP"
	?debug	C E94C7689240C444D5049504859532E435050
DMPIPHYS_TEXT	segment byte public use16 'CODE'
DMPIPHYS_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:DMPIPHYS_TEXT,ds:DGROUP
_DATA	segment word public use16 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public use16 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
DMPIPHYS_TEXT	segment byte public use16 'CODE'
	?debug	C E8010C444D5049504859532E4350504C768924
	?debug	L 1
	assume	cs:DMPIPHYS_TEXT
_main	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	push	si
	push	di
	?debug	B
	?debug	L 5
 	mov	 ax,00800H
	?debug	L 6
 	mov	 cx,001f8H
	?debug	L 7
 	mov	 bx,02da2H
	?debug	L 8
 	mov	 si,16
	?debug	L 9
 	mov	 di,0
	?debug	L 10
 	int	 031H
	?debug	L 12
	inc	dx
	?debug	L 13
	dec	dx
	?debug	L 14
	pop	di
	pop	si
	pop	bp
	ret	
	?debug	C E6017804040200
	?debug	E
	?debug	E
_main	endp
	?debug	C E9
	?debug	C FA00000000
DMPIPHYS_TEXT	ends
_DATA	segment word public use16 'DATA'
s@	label	byte
_DATA	ends
DMPIPHYS_TEXT	segment byte public use16 'CODE'
DMPIPHYS_TEXT	ends
	public	_main
_s@	equ	s@
	?debug	C EA050C
	?debug	C E31800000023040400
	?debug	C EC055F6D61696E181800
	end
