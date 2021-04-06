	ifndef	??version
?debug	macro
	endm
publicdll macro	name
	public	name
	endm
	endif
	?debug	V 300h
	?debug	S "TSR2.CPP"
	?debug	C E99A6E2F2408545352322E435050
	?debug	C E91B1ACF0017453A5C545552424F435C494E434C5544455C444F53+
	?debug	C 2E48
	?debug	C E91B1ACF0019453A5C545552424F435C494E434C5544455C5F4445+
	?debug	C 46532E48
TSR2_TEXT	segment byte public 'CODE'
TSR2_TEXT	ends
DGROUP	group	_DATA,_BSS
	assume	cs:TSR2_TEXT,ds:DGROUP
_DATA	segment word public 'DATA'
d@	label	byte
d@w	label	word
_DATA	ends
_BSS	segment word public 'BSS'
b@	label	byte
b@w	label	word
_BSS	ends
_DATA	segment word public 'DATA'
__stklen	label	word
	db	0
	db	2
_DATA	ends
_BSS	segment word public 'BSS'
_oldhandler	label	dword
	db	4 dup (?)
_myStack	label	byte
	db	10240 dup (?)
_BSS	ends
_DATA	segment word public 'DATA'
_p	label	dword
	dd	DGROUP:_myStack+1024
_DATA	ends
_BSS	segment word public 'BSS'
_oSS	label	word
	db	2 dup (?)
_oSP	label	word
	db	2 dup (?)
	db	2 dup (?)
_BSS	ends
TSR2_TEXT	segment byte public 'CODE'
	?debug	C E80108545352322E4350509A6E2F24
	?debug	L 40
	assume	cs:TSR2_TEXT
@dummy$qv	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	sub	sp,324
	?debug	B
	?debug	L 48
	mov	word ptr [bp-322],-18432
	mov	word ptr [bp-324],0
	?debug	L 51
	inc	word ptr DGROUP:b@w+10248
	?debug	L 52
	mov	bx,10
	mov	ax,word ptr DGROUP:b@w+10248
	cwd	
	idiv	bx
	mov	word ptr DGROUP:b@w+10248,dx
	?debug	L 55
	mov	ax,word ptr DGROUP:b@w+10248
	add	ax,31024
	les	bx,dword ptr [bp-324]
	mov	word ptr es:[bx+158],ax
	?debug	L 57
		mov	 [bp-4],sp
	?debug	L 58
 		mov	 ax,ss
	?debug	L 59
		mov	 [bp-2],ax
	?debug	L 61
	mov	ax,word ptr [bp-2]
	mov	cl,12
	shr	ax,cl
	and	ax,15
	add	ax,31024
	les	bx,dword ptr [bp-324]
	mov	word ptr es:[bx+2],ax
	?debug	L 62
	mov	ax,word ptr [bp-2]
	mov	cl,8
	shr	ax,cl
	and	ax,15
	add	ax,31024
	les	bx,dword ptr [bp-324]
	mov	word ptr es:[bx+4],ax
	?debug	L 63
	mov	ax,word ptr [bp-2]
	mov	cl,4
	shr	ax,cl
	and	ax,15
	add	ax,31024
	les	bx,dword ptr [bp-324]
	mov	word ptr es:[bx+6],ax
	?debug	L 64
	les	bx,dword ptr [bp-324]
	mov	ax,word ptr [bp-2]
	and	ax,15
	add	ax,31024
	mov	word ptr es:[bx+8],ax
	?debug	L 65
	mov	ax,word ptr [bp-4]
	mov	cl,12
	shr	ax,cl
	and	ax,15
	add	ax,31024
	les	bx,dword ptr [bp-324]
	mov	word ptr es:[bx+12],ax
	?debug	L 66
	mov	ax,word ptr [bp-4]
	mov	cl,8
	shr	ax,cl
	and	ax,15
	add	ax,31024
	les	bx,dword ptr [bp-324]
	mov	word ptr es:[bx+14],ax
	?debug	L 67
	mov	ax,word ptr [bp-4]
	mov	cl,4
	shr	ax,cl
	and	ax,15
	add	ax,31024
	les	bx,dword ptr [bp-324]
	mov	word ptr es:[bx+16],ax
	?debug	L 68
	les	bx,dword ptr [bp-324]
	mov	ax,word ptr [bp-4]
	and	ax,15
	add	ax,31024
	mov	word ptr es:[bx+18],ax
	?debug	L 71
	pushf	
	call	dword ptr DGROUP:_oldhandler
	?debug	L 73
	mov	sp,bp
	pop	bp
	ret	
	?debug	C E319000400160A00
	?debug	C E3180040011A19
	?debug	C E6046D7953500A02FCFF00046D7953530A02FEFF+
	?debug	C 0005636F756E7404000003082800067363726565+
	?debug	C 6E1802BCFE00
	?debug	E
	?debug	E
@dummy$qv	endp
	?debug	L 74
	assume	cs:TSR2_TEXT
@handler$qve	proc	far
	?debug	B
	push	ax
	push	bx
	push	cx
	push	dx
	push	es
	push	ds
	push	si
	push	di
	push	bp
	mov	bp,DGROUP
	mov	ds,bp
	mov	bp,sp
	?debug	B
	?debug	L 76
 	mov	 ax,ss
	?debug	L 77
 	mov	 DGROUP:_oSS,ax
	?debug	L 78
 	mov	 DGROUP:_oSP,sp
	?debug	L 79
 	mov	 sp,offset DGROUP:_p
	?debug	L 80
 	mov	 ax,seg DGROUP:_p
	?debug	L 81
 	mov		ss,ax
	?debug	L 82
	push	cs
	call	near ptr @dummy$qv
	?debug	L 83
 	mov	 ax,DGROUP:_oSS
	?debug	L 84
 	mov	 ss,DGROUP:_oSS
	?debug	L 85
 	mov	 sp,DGROUP:_oSP
	?debug	L 86
	pop	bp
	pop	di
	pop	si
	pop	ds
	pop	es
	pop	dx
	pop	cx
	pop	bx
	pop	ax
	iret	
	?debug	E
	?debug	E
@handler$qve	endp
	?debug	L 87
	assume	cs:TSR2_TEXT
_main	proc	far
	?debug	B
	push	bp
	mov	bp,sp
	?debug	B
	?debug	L 91
	mov	ax,28
	push	ax
	call	far ptr _getvect
	pop	cx
	mov	word ptr DGROUP:_oldhandler+2,dx
	mov	word ptr DGROUP:_oldhandler,ax
	?debug	L 94
	mov	ax,seg @handler$qve
	push	ax
	mov	ax,offset @handler$qve
	push	ax
	mov	ax,28
	push	ax
	call	far ptr _setvect
	add	sp,6
	?debug	L 105
	mov	ax,sp
	mov	cl,4
	shr	ax,cl
	mov	dx,ss
	add	dx,ax
	sub	dx,word ptr DGROUP:__psp
	push	dx
	mov	al,0
	push	ax
	call	far ptr _keep
	pop	cx
	pop	cx
	?debug	L 106
	xor	ax,ax
	jmp	short @3@58
@3@58:
	?debug	L 107
	pop	bp
	ret	
	?debug	E
	?debug	E
_main	endp
	?debug	C E9
	?debug	C FA00000000
TSR2_TEXT	ends
_DATA	segment word public 'DATA'
s@	label	byte
_DATA	ends
TSR2_TEXT	segment byte public 'CODE'
TSR2_TEXT	ends
	public	_main
	public	@handler$qve
	public	@dummy$qv
	public	_oSP
	public	_oSS
	public	_p
	public	_myStack
	public	_oldhandler
	extrn	_setvect:far
	extrn	_getvect:far
_pokeb	equ	pokeb
_poke	equ	poke
_peekb	equ	peekb
_peek	equ	peek
	extrn	_keep:far
	public	__stklen
	extrn	__psp:word
_s@	equ	s@
	?debug	C EA050C
	?debug	C E31A00000023040400
	?debug	C EC055F6D61696E1A1800
	?debug	C E31B00000023010701
	?debug	C EC0C4068616E646C6572247176651B9800
	?debug	C E31C00000023010400
	?debug	C EC094064756D6D792471761C1800
	?debug	C EC045F6F53500A0000
	?debug	C EC045F6F53530A0000
	?debug	C E31D000400160800
	?debug	C EC025F701D0000
	?debug	C E31E0000281A08
	?debug	C EC085F6D79537461636B1E0000
	?debug	C E32000000023010701
	?debug	C E31F000400162000
	?debug	C EC0B5F6F6C6468616E646C65721F0000
	?debug	C E32100000023010400
	?debug	C EB085F736574766563742100
	?debug	C E32400000023010701
	?debug	C E323000400162400
	?debug	C E32200000023230400
	?debug	C EB085F676574766563742200
	?debug	C E32500000023010400
	?debug	C E32600000023010400
	?debug	C E32700000023080400
	?debug	C E32800000023040400
	?debug	C E32900000023010400
	?debug	C EB055F6B6565702900
	?debug	C E32A0666696E645F742B001E01
	?debug	C E32B0015001A08
	?debug	C E32C000D001A08
	?debug	C E32D056666626C6B2B001E08
	?debug	C E32E0015001A08
	?debug	C E32F000D001A08
	?debug	C E330075245475041434B14001E0F
	?debug	C E33105535245475308001E1A
	?debug	C E332045245475310001F1F
	?debug	C E33308574F52445245475310001E22
	?debug	C E33408425954455245475308001E2B
	?debug	C E33509646F73646174655F7405001E34
	?debug	C E336046461746504001E39
	?debug	C E33709646F7374696D655F7404001E3D
	?debug	C E3380474696D6504001E42
	?debug	C E3390664657668647212001E47
	?debug	C E33A0008001A08
	?debug	C E33B07666174696E666F06001E4D
	?debug	C E33C0A6469736B667265655F7408001E52
	?debug	C E33D05646672656508001E57
	?debug	C E33E08444F534552524F5205001E5C
	?debug	C E33F07434F554E54525922001E61
	?debug	C E3400005001A08
	?debug	C E3410002001A08
	?debug	C E3420002001A08
	?debug	C E3430002001A08
	?debug	C E3440002001A08
	?debug	C E3450002001A08
	?debug	C E346000A001A08
	?debug	C E34704786663622C001E6E
	?debug	C E3480005001A08
	?debug	C E3490366636225001E73
	?debug	C E34A0008001A08
	?debug	C E34B0003001A08
	?debug	C E34C000A001A08
	?debug	C EC085F5F73746B6C656E0A0000
	?debug	C EB055F5F7073700A00
	?debug	C E60A735F61727261797074721906000666696E64+
	?debug	C 5F742A0700056666626C6B2D0700075245475041+
	?debug	C 434B300700055352454753310700045245475332+
	?debug	C 070008425954455245475334070008574F524452+
	?debug	C 45475333070009646F73646174655F7435070004+
	?debug	C 6461746536070009646F7374696D655F74370700+
	?debug	C 0474696D65380700066465766864723907000766+
	?debug	C 6174696E666F3B07000A6469736B667265655F74+
	?debug	C 3C07000564667265653D070008444F534552524F+
	?debug	C 523E070007434F554E5452593F07000478666362+
	?debug	C 47070003666362490700
	?debug	F pokeb 37 24 0
	?debug	F poke 38 24 0
	?debug	F peekb 39 24 0
	?debug	F peek 40 24 0
	?debug	C E2000872657365727665642B0006617474726962+
	?debug	C 08000777725F74696D650A000777725F64617465+
	?debug	C 0A000473697A650600046E616D652CC02B000000
	?debug	C E2000B66665F72657365727665642E000966665F+
	?debug	C 61747472696208000866665F6674696D650A0008+
	?debug	C 66665F66646174650A000866665F6673697A6506+
	?debug	C 000766665F6E616D652FC02B000000
	?debug	C E20004725F61780A0004725F62780A0004725F63+
	?debug	C 780A0004725F64780A0004725F62700A0004725F+
	?debug	C 73690A0004725F64690A0004725F64730A000472+
	?debug	C 5F65730A0007725F666C6167730AC014000000
	?debug	C E2000265730A000263730A000273730A00026473+
	?debug	C 0AC008000000
	?debug	C E20001783300016834C010000000
	?debug	C E2000261780A000262780A000263780A00026478+
	?debug	C 0A000273690A000264690A000563666C61670A00+
	?debug	C 05666C6167730AC010000000
	?debug	C E20002616C0800026168080002626C0800026268+
	?debug	C 080002636C0800026368080002646C0800026468+
	?debug	C 08C008000000
	?debug	C E200036461790800056D6F6E7468080004796561+
	?debug	C 720A00096461796F667765656B08C005000000
	?debug	C E2000764615F7965617204000664615F64617908+
	?debug	C 000664615F6D6F6E08C004000000
	?debug	C E20004686F75720800066D696E75746508000673+
	?debug	C 65636F6E64080007687365636F6E6408C0040000+
	?debug	C 00
	?debug	C E2000674695F6D696E08000774695F686F757208+
	?debug	C 000774695F68756E6408000674695F73656308C0+
	?debug	C 04000000
	?debug	C E2000764685F6E65787406000764685F61747472+
	?debug	C 04000864685F73747261740A000864685F696E74+
	?debug	C 65720A000764685F6E616D653AC012000000
	?debug	C E2000866695F73636C757308000866695F666174+
	?debug	C 696408000866695F6E636C75730A000866695F62+
	?debug	C 7973656304C006000000
	?debug	C E2000E746F74616C5F636C7573746572730A000E+
	?debug	C 617661696C5F636C7573746572730A0013736563+
	?debug	C 746F72735F7065725F636C75737465720A001062+
	?debug	C 797465735F7065725F736563746F720AC0080000+
	?debug	C 00
	?debug	C E2000864665F617661696C0A000864665F746F74+
	?debug	C 616C0A000764665F627365630A000864665F7363+
	?debug	C 6C75730AC008000000
	?debug	C E2000B64655F6578746572726F7204000864655F+
	?debug	C 636C61737308000964655F616374696F6E080008+
	?debug	C 64655F6C6F63757308C005000000
	?debug	C E20007636F5F64617465040007636F5F63757272+
	?debug	C 400008636F5F7468736570410008636F5F646573+
	?debug	C 6570420008636F5F6474736570430008636F5F74+
	?debug	C 6D73657044000C636F5F637572727374796C6508+
	?debug	C 0009636F5F646967697473080007636F5F74696D+
	?debug	C 65080007636F5F63617365060008636F5F646173+
	?debug	C 6570450007636F5F66696C6C46C022000000
	?debug	C E20009786663625F666C6167080009786663625F+
	?debug	C 72657376480009786663625F6174747208000878+
	?debug	C 6663625F66636249C02C000000
	?debug	C E200096663625F64726976650800086663625F6E+
	?debug	C 616D654A00076663625F6578744B000A6663625F+
	?debug	C 637572626C6B04000B6663625F72656373697A65+
	?debug	C 04000B6663625F66696C73697A65060008666362+
	?debug	C 5F646174650400086663625F726573764C000A66+
	?debug	C 63625F63757272656308000A6663625F72616E64+
	?debug	C 6F6D06C025000000
	end
