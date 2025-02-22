# CP/M Basic Input/Output System
- https://www.seasip.info/Cpm/bios.html

The BIOS is the machine-dependent part of CP/M. In theory, all you need to do is change the BIOS and CP/M will work on a different machine. The same used to be true of MSDOS...

The BIOS begins with the following jumps to service routines:

	JMP	BOOT	;-3: Cold start routine
	JMP	WBOOT	; 0: Warm boot - reload command processor
	JMP	CONST	; 3: Console status
	JMP	CONIN	; 6: Console input
	JMP	CONOUT	; 9: Console output
	JMP	LIST	;12: Printer output
	JMP	PUNCH	;15: Paper tape punch output
        JMP     READER	;18: Paper tape reader input
	JMP	HOME	;21: Move disc head to track 0
	JMP	SELDSK	;24: Select disc drive
	JMP	SETTRK	;27: Set track number
	JMP	SETSEC	;30: Set sector number
	JMP	SETDMA	;33: Set DMA address
	JMP	READ	;36: Read a sector
	JMP	WRITE	;39: Write a sector
In CP/M 2 and later, the following extra jumps appear:

	JMP	LISTST	;42: Status of list device
	JMP	SECTRAN	;45: Sector translation for skewing
In CP/M 3, a further set of jumps is present:

	JMP	CONOST	;48: Status of console output
	JMP	AUXIST	;51: Status of auxiliary input
	JMP	AUXOST	;54: Status of auxiliary output
	JMP	DEVTBL	;57: Address of devices table
	JMP	DEVINI	;60: Initialise a device
	JMP	DRVTBL	;63: Address of discs table
	JMP	MULTIO	;66: Read/write multiple sectors
	JMP	FLUSH	;69: Flush host buffers
	JMP	MOVE	;72: Move a block of memory
	JMP	TIME	;75: Real time clock
	JMP	SELMEM	;78: Select memory bank
	JMP	SETBNK	;81: Select bank for DMA operation
	JMP	XMOVE	;84: Preload banks for MOVE
	JMP	USERF	;87: System-depedent functions
	JMP	RESERV1	;90: Reserved
	JMP	RESERV2	;93: Reserved
## BOOT (function 0)
This function is completely implementation-dependent and should never be called from user code.

## WBOOT (function 1)
Reloads the command processor and (on some systems) the BDOS as well. How it does this is implementation-dependent; it may use the reserved tracks of a floppy disc or extra memory.

## CONST (function 2)
Returns its status in A; 0 if no character is ready, 0FFh if one is.

## CONIN (function 3)
Wait until the keyboard is ready to provide a character, and return it in A.

## CONOUT (function 4)
Write the character in C to the screen.

## LIST (function 5)
Write the character in C to the printer. If the printer isn't ready, wait until it is.

## PUNCH / AUXOUT (function 6)
Write the character in C to the "paper tape punch" - or whatever the current auxiliary device is. If the device isn't ready, wait until it is.

This function is called PUNCH in CP/M 2.x, AUXOUT in CP/M 3.

## READER (function 7)
Read a character from the "paper tape reader" - or whatever the current auxiliary device is. If the device isn't ready, wait until it is. The character will be returned in A. If this device isn't implemented, return character 26 (^Z).

This function is called READER in CP/M 2.x, AUXIN in CP/M 3.

## HOME (function 8)
Move the current drive to track 0.

## SELDSK (function 9)
Select the disc drive in register C (0=A:, 1=B: ...). Called with E=0 or 0FFFFh.

If bit 0 of E is 0, then the disc is logged in as if new; if the format has to be determined from the boot sector, for example, this will be done.

If bit 0 if E is 1, then the disc has been logged in before. The disc is not accessed; the DPH address (or zero) is returned immediately.

SELDSK returns the address of a Disc Parameter Header in HL. The exact format of a DPH varies between CP/M versions; note that under CP/M 3, the DPH is in memory bank 0 and probably not visible to programs. If the disc could not be selected it returns HL=0.

## SETTRK (function 10)
Set the track in BC - 0 based.

## SETSEC (function 11)
Set the sector in BC. Under CP/M 1 and 2 a sector is 128 bytes. Under CP/M 3 the sector size is given in the Disk Parameter Block.

There has been discussion in comp.os.cpm about whether the parameter to this function is a byte or a word. The conclusion (based on examining the BDOS source) was that it is a word.

## SETDMA (function 12)
The next disc operation will read its data from (or write its data to) the address given in BC.

## READ (function 13)
Read the currently set track and sector at the current DMA address. Returns A=0 for OK, 1 for unrecoverable error, 0FFh if media changed.

## WRITE (function 14)
Write the currently set track and sector. C contains a deblocking code:

C=0 - Write can be deferred
C=1 - Write must be immediate
C=2 - Write can be deferred, no pre-read is necessary.
Returns A=0 for OK, 1 for unrecoverable error, 2 if disc is readonly, 0FFh if media changed.

## LISTST (function 15)
Return status of current printer device.

Returns A=0 (not ready) or A=0FFh (ready).

## SECTRAN (function 16)
Translate sector numbers to take account of skewing.

On entry, BC=logical sector number (zero based) and DE=address of translation table. On exit, HL contains physical sector number. On a system with hardware skewing, this would normally ignore DE and return either BC or BC+1.

## CONOST (function 17)
Return status of current screen output device.

Returns A=0 (not ready) or A=0FFh (ready).

## AUXIST (function 18)
Return status of current auxiliary input device.

Returns A=0 (not ready) or A=0FFh (ready).

## AUXOST (function 19)
Return status of current auxiliary output device.

Returns A=0 (not ready) or A=0FFh (ready).

## DEVTBL (function 20)
Return in HL the address of the devices table, or 0 if the devices table isn't implemented.

The devices table will be visible to programs without the need for bank switching, ie. it will be in common memory.

The device table contains one entry for each character device. Each entry is formed:

	DEFB	'NAME  '	;Name, 6 bytes. If the first byte is zero,
				;this is the end of the table.
	DEFB	mode		;Bitmapped value:
				;Bit 0 set => can input from this device
				;Bit 1 set => can output to this device
				;Bit 2 set => can change the baud rate
				;Bit 3 set => supports XON/XOFF
				;Bit 4 set => is using XON/XOFF
				;Bits 5,6,7 set to 0.
				; Amstrad extension: If bit 7 is set, output
				;to the device does not time out. 
	DEFB	baudrate	;Coded speed, 1-15 or 0 if speed can't be
				;changed.
				;Rates are 50,75,110,134.5,150,300,600,1200,
				;         1800,2400,3600,4800,7200,9600,19200.
The maximum number of devices allowed in CP/M Plus is unclear. The documentation variously says there can be 12 or 13, while the DEVICE.COM source code suggests 15.

## DEVINI (function 21)
Reinitialise character device number C - called when the device's settings (baud rate, mode etc.) are changed.

## DRVTBL (function 22)
Return in HL the address of the drive table, or 0 (or 0FFFFh, or 0FFFEh) if the drive table isn't implemented. The drive table contains 16 pointers to the Disc Parameter Headers of the 16 disc drives A-P; if a pointer is 0 it means that the corresponding drive does not exist.

The drive table is usually (but not always) in common memory (ie accessible by user programs).

## MULTIO (function 23)
Notify the BIOS that the BDOS is intending to transfer a number of consecutive disc sectors with READ or WRITE. Entered with C = number of calls that will be made; up to 16k of data will be transferred.

The idea is that after the MULTIO call, the BIOS can choose to transfer all the data in the first READ/WRITE operation, and then not to do anything on the subsequent (n-1) operations.

## FLUSH (function 24)
Write any pending data to disc.

Returns A=0 if successful, 1 for physical disc error, 2 for drive R/O.

This function is only useful when the BIOS is doing the deblocking - ie, the physical sector size is not the size that the BIOS reports to the BDOS.

## MOVE (function 25)
Move BC bytes of memory, from the address in DE to the address in HL (the other way round from the Z80's LDIR instruction). Should return HL and DE pointing to the first addresses not copied. If XMOVE is used before this function, data are moved between two memory banks.

## TIME (function 26)
Get the current date and time into the SCB (at BOOT-0Ch). HL and DE must be preserved. If C=0FFh, then set the time from the SCB instead.

The format of the 5-byte buffer is:

	DW	day	;Day 1 is 1 Jan 1978
	DB	hour	;packed BCD
	DB	minute	;packed BCD
	DB	second	;packed BCD
## SELMEM (function 27)
Set the current bank to the number in A. Bank 1 is the bank in which user programs run (the TPA); Bank 0 and any other banks are used by CP/M for disc buffers or as a RAMdisc.

According to the DRI documentation, this function must preserve all registers except A.

## SETBNK (function 28)
Set the bank to be used for the next read/write sector operation. The bank number is passed in A. Note that the BDOS will call SETBNK after calling SETDMA; some BIOSes insist on this order, so it's safest if your programs do the same.

## XMOVE (function 29)
After XMOVE, the next call to MOVE will move data between different memory banks. Call XMOVE with C=source bank and B=destination bank. According to the CP/M Plus System Guide, the BDOS will only ever use this function to move 128 or fewer bytes in one go; some BIOSes may not support bigger moves between banks.

## USERF (function 30)
This function is reserved for the author of the BIOS to add any extra features. On Amstrad computers, for example, this call accesses the extended BIOS functions.

## RESERV1 and RESERV2 (functions 31, 32)
These calls are reserved and contain JMP 0 instructions.