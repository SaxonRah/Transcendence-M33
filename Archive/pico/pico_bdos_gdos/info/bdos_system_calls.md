
# BDOS system calls
- https://www.seasip.info/Cpm/bdos.html

So far, this list covers CP/M 1, 2 and 3, with partial MP/M and DOSPLUS details. Some groupings I use are:

- CP/M 1.3
  - The 1975 version of CP/M available as source from the Unofficial CP/M Website. The version number of 1.3 isn't given in the source.
- CP/M 2.2
  - In addition to CP/M-80 version 2.2, this also includes CP/M-86 1.x, CP/M-68000 1.x and CP/M-Z8000 1.x.
MP/M II and above
MP/M II
- CP/M 3 (CP/M Plus)
  - multiuser 16-bit systems such as DR-MDOS and REAL/32
  - single-user 16-bit systems after CP/M-86 1.1 and before DRDOS 3.41. This covers DOSPLUS and "Personal CP/M-86 v2.0/2".
- CP/M 3 and above
    - All the above systems except MP/M II
    - CP/Net redirector
    - Any CP/Net client that allows access to drives on an MP/M server.
    - The system calls for REAL/32 (a descendent of Concurrent CP/M) used to be online at http://development.imsltd.com/calls/allcalls.htm. This site appears to be offline but some parts of its content can be retrieved by entering the above URL into the archive.org wayback machine.

How to make a call
To make a BDOS call in an 8-bit CP/M, use:

    LD  DE,parameter
    LD  C,function
    CALL    5
and in a 16-bit CP/M, use:

    MOV DX,parameter
    MOV CL,function
    INT 0E0h
In CP/M 1.x, 8-bit values are returned in A and 16-bit values in BA. In later 8-bit versions, they are also returned in L and HL respectively.
16-bit systems return 8-bit values in AL = BL and 16-bit in AX = BX.

The information in this list overlaps with the Interrupt List section on INT E0h to some extent.

DOSPLUS and DOS+
Note that DOS + is a CP/M extended BDOS. For information on "DOSPLUS 1.2" and "Personal CP/M-86 v2.0/2" see sections applicable to CP/M-86 v4; the underlying BDOS is version 4.1 in both cases.

The calls
## BDOS function 0 (P_TERMCPM) - System Reset
    - Supported by: CP/M 1, 2, 3; MP/M; Concurrent CP/M.
    - Entered with C=0. Does not return.

Quit the current program, return to command prompt. This call is hardly ever used in 8-bit CP/M since the RST 0 instruction does the same thing and saves four bytes.

## BDOS function 0 (P_TERMCPM) - System Reset
    - Supported by: Single-user CP/M-86.
    - Entered with CL=0, DL=0 or 1. Does not return.

Quit the current program, return to command prompt. If DL is 0, the memory used by the program is deallocated; if DL is 1, it remains resident.

## BDOS function 1 (C_READ) - Console input
    - Supported by: All versions
    - Entered with C=1. Returns A=L=character.

Wait for a character from the keyboard; then echo it to the screen and return it.

## BDOS function 2 (C_WRITE) - Console output
    - Supported by: All versions
    - Entered with C=2, E=ASCII character.

Send the character in E to the screen. Tabs are expanded to spaces. Output can be paused with ^S and restarted with ^Q (or any key under versions prior to CP/M 3). While the output is paused, the program can be terminated with ^C.

## BDOS function 3 (A_READ) - Auxiliary (Reader) input
    - Supported by: All CP/M versions except MP/M and Concurrent CP/M
    - Entered with C=3. Returns A=L=ASCII character

Note that this call can hang if the auxiliary input never sends data.

## BDOS function 3 - Raw console input
    - Supported by: MP/M.
    - Entered with C=3. Returns A=L=ASCII character

Reads a character from the console without checking for ^S / ^Q.

## BDOS function 4 (A_WRITE) - Auxiliary (Punch) output
    - Supported by: All versions except MP/M and Concurrent CP/M.
    - Entered with C=4, E=ASCII character.

If the device is permanently not ready, this call can hang.

## BDOS function 4 - Raw console output
    - Supported by: MP/M.
    - Entered with C=4, E=ASCII character.

Outputs the character, without expanding tabs or checking for ^S / ^Q.

## BDOS function 5 (L_WRITE) - Printer output
    - Supported by: All versions
    - Entered with C=2, E=ASCII character.

If the printer is permanently offline or busy, this call can hang.

## BDOS function 6 - Detect memory size
    - Supported by: CP/M 1.3 only
    - Entered with C=6. Returns the base address of the CCP.

## BDOS function 6 (C_RAWIO) - Direct console I/O
    - Supported by: CP/M 1.4 and later, with variations
    - Entered with C=6, E=code. Returned values (in A) vary.

    E=0FFh
    Return a character without echoing if one is waiting; zero if none is available. In MP/M 1, this works like E=0FDh below and waits for a character.
    E=0FEh
    [CP/M3, NovaDOS, Z80DOS, DOS+] Return console input status. Zero if no character is waiting, nonzero otherwise.
    E=0FDh
    [CP/M3, DOS+] Wait until a character is ready, return it without echoing.
    E=0FCh
    [DOS+] One-character lookahead - return the next character waiting but leave it in the buffer.
Values of E not supported on a particular system will output the character. Under CP/M 2 and lower, direct console functions may interact undesirably with non-direct ones, since certain buffers may be bypassed. Do not mix them.

## BDOS function 7 - Get I/O byte
    - Supported by: CP/M 2 and lookalikes. Not supported in MP/M.
    - Entered with C=7. Returns I/O byte.

Here's a description of how the IOBYTE works.

## BDOS function 7 (A_STATIN) - Auxiliary Input status
    - Supported by: CP/M 3 and above. Not supported in MP/M.
    - Entered with C=7. Returns A=0 or 0FFh.

0FFh is returned if the Auxiliary Input device has a character ready; otherwise 0 is returned.

## BDOS function 8 - Set I/O byte
    - Supported by: CP/M 2 and lookalikes. Not supported in MP/M.
    - Entered with C=8, E=I/O byte.

Here's a description of how the IOBYTE works.

## BDOS function 8 (A_STATOUT) - Auxiliary Output status
    - Supported by: CP/M 3 and above. Not supported in MP/M.
    - Entered with C=8. Returns A=0 or 0FFh.

0FFh is returned if the Auxiliary Output device is ready for characters; otherwise 0 is returned.

## BDOS function 9 (C_WRITESTR) - Output string
    - Supported by: All versions
    - Entered with C=9, DE=address of string.

Display a string of ASCII characters, terminated with the $ character. Thus the string may not contain $ characters - so, for example, the VT52 cursor positioning command ESC Y y+32 x+32 will not be able to use row 4.

Under CP/M 3 and above, the terminating character can be changed using BDOS function 110.

## BDOS function 10 (C_READSTR) - Buffered console input
    - Supported by: All versions, with variations
    - Entered with C=0Ah, DE=address or zero.

This function reads characters from the keyboard into a memory buffer until RETURN is pressed. The Delete key is handled correctly. In later versions, more features can be used at this point; ZPM3 includes a full line editor with recall of previous lines typed.

On entry, DE is the address of a buffer. If DE=0 (in CP/M-86 versions DX=0FFFFh), the DMA address is used (CP/M 3 and later) and the buffer already contains data:
    
    DE=address:                 DE=0 / DX=0FFFFh:
    buffer: DEFB    size        buffer: DEFB    size
            DEFB    ?                   DEFB    len
            DEFB    bytes               DEFB    bytes
The value at buffer+0 is the amount of bytes available in the buffer. Once the limit has been reached, no more can be added, although the line editor can still be used.
If DE=0 (in 16-bit versions, DX=0FFFFh) the next byte contains the number of bytes already in the buffer; otherwise this is ignored. On return from the function, it contains the number of bytes present in the buffer.

The bytes typed then follow. There is no end marker.

## BDOS function 11 (C_STAT) - Console status
    - Supported by: All versions
    - Entered with C=0Bh. Returns A=L=status

Returns A=0 if no characters are waiting, nonzero if a character is waiting.

## BDOS function 12 - Lift head
    - Supported by: Version 1
    - Entered with C=0Ch. Returns HL=0

Has no effect except to return HL=0.

## BDOS function 12 (S_BDOSVER) - Return version number
    - Supported by: Versions 2.0 and later
    - Entered with C=0Ch. Returns B=H=system type, A=L=version number.

The system type is subdivided into a machine type and a CP/M type. The machine type occupies the high nibble of the byte; the CP/M type is a bitmapped field stored in the low nibble.

    Machine types:   CP/M types:         Version numbers:
    0 - 8080         Bit 0 set for MP/M        00h - Version 1 (see Lift Head above)
    1 - 8086         Bit 1 set for CP/Net      20h - Version 2.0
    2 - 68000           (ie:network present)   21h - Version 2.1
    3 - Z8000        Bit 2 set in 16-bit       22h - Version 2.2 
                        multi-user OSes        25h - Version 2.5 (DOS +)
                                               28h - Version 2.8 (Personal CP/M-80)
                     For plain CP/M,           30h - Version 3.0 (MP/M II, MP/M-86)
                     the CP/M type is 0.       31h - Version 3.1 (CP/M Plus)
                                               33h - Version 3.3 (Apricot PCP/M-86)
                                               41h - Version 4.1 (DOSPLUS 1)
                                               50h - Version 5.0 (DOSPLUS 2)
Sources differ on the value returned by DOSPLUS 2. Most sources follow the Interrupt List and say 60h; my experiments on the real thing say 50h.

Confusingly, CP/M-86 v1.1 returns 0022h (ie, "8080 CP/M v2.2").

It is interesting to note that the version numbers returned by DRDOS and Novell DOS follow this system; DRDOS 3, 5 and 6 are version 6.x, Novell DOS 7 is version 7.2 and DR-OpenDOS is version 7.3. However these systems rather unsportingly fail to provide an INT 0E0h call to get the version number; you have to use INT 21h with AX=4452h.

## BDOS function 13 (DRV_ALLRESET) - Reset discs
    - Supported by: All versions.
    - Entered with C=0Dh. Returned values vary.

Resets disc drives. Logs out all discs and empties disc buffers. Sets the currently selected drive to A:. Any drives set to Read-Only in software become Read-Write; replacement BDOSses tend to leave them Read-Only.

In versions 1 and 2, logs in drive A: and returns 0FFh if there is a file present whose name begins with a $, otherwise 0. Replacement BDOSses may modify this behaviour.

In multitasking versions, returns 0 if succeeded, or 0FFh if other processes have files open on removable or read-only drives.

When the Digital Research CP/M 2 BDOS is started from cold, it is not properly initialised until this function is called; disk operations may fail or crash. Normally this is done by the CCP and other programs don't need to worry, but if you are writing an alternative CCP or a program that runs instead of the CCP, it's something to bear in mind.

## BDOS function 14 (DRV_SET) - Select disc
    - Supported by: All versions
    - Entered with C=0Eh, E=drive number. Returns L=A=0 or 0FFh.

The drive number passed to this routine is 0 for A:, 1 for B: up to 15 for P:.

Sets the currently selected drive to the drive in A; logs in the disc. Returns 0 if successful or 0FFh if error. Under MP/M II and later versions, H can contain a physical error number.

## BDOS function 15 (F_OPEN) - Open file
    - Supported by: All versions
    - Entered with C=0Fh, DE=FCB address. Returns error codes in BA and HL.

This function opens a file to read or read/write. The FCB is a 36-byte data structure, most of which is maintained by CP/M. Look here for details.

The FCB should have its DR, Fn and Tn fields filled in, and the four fields EX, S1, S2 and RC set to zero. Under CP/M 3 and later, if CR is set to 0FFh then on return CR will contain the last record byte count. Note that CR should normally be reset to zero if sequential access is to be used.

Under MP/M II, the file is normally opened exclusively - no other process can access it. Two bits in the FCB control the mode the file is opened in:

F5' - set to 1 for "unlocked" mode - other programs can use the file.
F6' - set to 1 to open the file in read-only mode - other programs can use the file read-only. If both F6' and F5' are set, F6' wins.
If the file is opened in "unlocked" mode, the file's identifier (used for record locking) will be returned at FCB+21h.

Under MP/M II and later versions, a password can be supplied to this function by pointing the DMA address at the password.

On return from this function, A is 0FFh for error, or 0-3 for success. Some versions (including CP/M 3) always return zero; others return 0-3 to indicate that an image of the directory entry is to be found at (80h+20h*A).

If A=0FFh, CP/M 3 returns a hardware error in H and B. It also sets some bits in the FCB:

F7' is set if the file is read-only because writing is password protected and no password was supplied;
F8' is set if the file is read-only because it is a User 0 system file opened from another user area.
## BDOS function 15 - Open directory
    - Supported by: CP/M-86 v4.
    - Entered with C=0Fh, DE=FCB address. Returns error codes in BA and HL.

This function is called with bit 7 of the FCB drive byte set, to distinguish it from a normal Open File call.

Byte 0Ch (Extent) of the FCB holds a subfunction code, 0-3:
    
    0 - Change current directory
    1 - Assign floating drive N: to specified directory
    2 - Assign floating drive O: to specified directory
    3 - Assign floating drive P: to specified directory
Each floating drive maps to a directory on an existing drive. I refer to the existing drive as the 'host' drive.

## BDOS function 16 (F_CLOSE) - Close file
    - Supported by: All versions
    - Entered with C=10h, DE=FCB address. Returns error codes in BA and HL.

This function closes a file, and writes any pending data. This function should always be used when a file has been written to.

On return from this function, A is 0FFh for error, or 0-3 for success. Some versions always return zero; others return 0-3 to indicate that an image of the directory entry is to be found at (80h+20h*A).

Under CP/M 3, if F5' is set to 1 then the pending data are written and the file is made consistent, but it remains open.

If A=0FFh, CP/M 3 returns a hardware error in H and B.

## BDOS function 16 - Close directory
    - Supported by: CP/M-86 v4.
    - Entered with C=10h, DE=FCB address. Returns error codes in BA and HL.

This function is called with bit 7 of the FCB drive byte set, to distinguish it from a normal Close File call.

This sets the current directory on the specified drive to the root directory.

## BDOS function 17 (F_SFIRST) - search for first
    - Supported by: All versions
    - Entered with C=11h, DE=address of FCB. Returns error codes in BA and HL.

Search for the first occurrence of the specified file; the filename should be stored in the supplied FCB. The filename can include ? marks, which match anything on disc. If the first byte of the FCB is ?, then any directory entry (including disc labels, date stamps etc.) will match. The EX byte is also checked; normally it should be set to zero, but if it is set to ? then all suitable extents are matched.

Returns A=0FFh if error (CP/M 3 returns a hardware error in H and B), or A=0-3 if successful. The value returned can be used to calculate the address of a memory image of the directory entry; it is to be found at DMA+A*32.

Under CP/M-86 v4, if the first byte of the FCB is '?' or bit 7 of the byte is set, subdirectories as well as files will be returned by this search.

## BDOS function 18 (F_SNEXT) - search for next
    - Supported by: All versions
    - Entered with C=12h, (DE=address of FCB)?. Returns error codes in BA and HL.

This function should only be executed immediately after function 17 or another invocation of function 18. No other disc access functions should have been used.

Function 18 behaves exactly as number 17, but finds the next occurrence of the specified file after the one returned last time. The FCB parameter is not documented, but Jim Lopushinsky states in LD301.DOC:

In none of the official Programmer's Guides for any version of CP/M does it say that an FCB is required for Search Next (function 18). However, if the FCB passed to Search First contains an unambiguous file reference (i.e. no question marks), then the Search Next function requires an FCB passed in reg DE (for CP/M-80) or DX (for CP/M-86).
## BDOS function 19 (F_DELETE) - delete file
    - Supported by: All versions
    - Entered with C=13h, DE=address of FCB. Returns error codes in BA and HL.

Deletes all directory entries matching the specified filename. The name can contain ? marks. Returns A=0FFh if error, otherwise 0-3 (CP/M 3 returns a hardware error in H and B).

Under CP/M 3, if bit F5' is set to 1, the file remains but any password protection is removed. If the file has any password protection at all, the DMA address must be pointing at the password when this function is called.

## BDOS function 19 - remove directory
    - Supported by: CP/M-86 v4.
    - Entered with C=13h, DE=address of FCB. Returns error codes in BA and HL.

This function is called with bit 7 of the FCB drive byte set, to distinguish it from a normal Delete File call.

If the specified subdirectory exists and is empty, removes it.

## BDOS function 20 (F_READ) - read next record
    - Entered with C=14h, DE=address of FCB. Returns error codes in BA and HL.

    - Supported by: All versions
Load a record (normally 128 bytes, but under CP/M 3 this can be a multiple of 128 bytes) at the previously specified DMA address. Values returned in A are:

    0
    OK,
    1
    end of file,
    9
    invalid FCB,
    10
    (CP/M) media changed; (MP/M) FCB checksum error,
    11
    (MP/M) unlocked file verification error,
    0FFh
    hardware error.
If on return A is not 0FFh, H contains the number of 128-byte records read before the error (MP/M II and later).
## BDOS function 21 (F_WRITE) - write next record
    - Supported by: All versions
    - Entered with C=15h, DE=address of FCB. Returns error codes in BA and HL.

Write a record (normally 128 bytes, but can be a multiple of 128 bytes) to be found at previously specified DMA address. Values returned in A are:

    0
    OK,
    1
    directory full,
    2
    disc full,
    8
    (MP/M) record locked by another process,
    9
    invalid FCB,
    10
    (CP/M) media changed; (MP/M) FCB checksum error,
    11
    (MP/M) unlocked file verification error,
    0FFh
    hardware error.
If on return A is not 0FFh, H contains the number of 128-byte records written before the error (CP/M 3 only).
## BDOS function 22 (F_MAKE) - create file
    - Supported by: All versions
    - Entered with C=16h, DE=address of FCB. Returns error codes in BA and HL.

Creates the file specified. Returns A=0FFh if the directory is full.

If the file exists already, then the default action is to return to the command prompt, but CP/M 3 may return a hardware error instead.

Under MP/M II, set F5' to open the file in "unlocked" mode.

Under MP/M II and later versions, set F6' to create the file with a password; the DMA address should point at a 9-byte buffer:

    DEFS    8   ;Password
    DEFB    1   ;Password mode
## BDOS function 22 - create directory
    - Supported by: CP/M-86 v4.
    - Entered with C=16h, DE=address of FCB. Returns error codes in BA and HL.

This function is called with bit 7 of the FCB drive byte set, to distinguish it from a normal Create File call.

Creates a new subdirectory in the current directory, with the given name.

## BDOS function 23 (F_RENAME) - Rename file
    - Supported by: All versions
    - Entered with C=17h, DE=address of FCB. Returns error codes in BA and HL.

Renames the file specified to the new name, stored at FCB+16. This function cannot rename across drives so the "drive" bytes of both filenames should be identical. Returns A=0-3 if successful; A=0FFh if error. Under CP/M 3, if H is zero then the file could not be found; if it is nonzero it contains a hardware error number.

Under Concurrent CP/M, set F5' if an extended lock on the file should be held through the rename. Otherwise the lock will be released.

## BDOS function 24 (DRV_LOGINVEC) - Return bitmap of logged-in drives
    - Supported by: All versions
    - Entered with C=18h. Returns bitmap in HL.

Bit 7 of H corresponds to P: while bit 0 of L corresponds to A:. A bit is set if the corresponding drive is logged in.

In DOSPLUS v2.1, the three top bits (for the floating drives) will mirror the status of the corresponding host drives). This does not happen in earlier DOSPLUS / Personal CP/M-86 systems.

## BDOS function 25 (DRV_GET) - Return current drive
    - Supported by: All versions
    - Entered with C=19h. Returns drive in A. Returns currently selected drive. 0 => A:, 1 => B: etc.

## BDOS function 26 (F_DMAOFF) - Set DMA address
    - Supported by: All versions
    - Entered with C=1Ah, DE=address.

Set the Direct Memory Access address; a pointer to where CP/M should read or write data. Initially used for the transfer of 128-byte records between memory and disc, but over the years has gained many more functions.

## BDOS function 27 (DRV_ALLOCVEC) - Return address of allocation map
    - Supported by: All versions, but differs in banked versions.
    - Entered with C=1Bh. Returns address in HL (16-bit versions use ES:BX).

Return the address of the allocation bitmap (which blocks are used and which are free) in HL. Under banked CP/M 3 and MP/M, this will be an address in bank 0 (the system bank) and not easily accessible.

Under previous versions, the format of the bitmap is a sequence of bytes, with bit 7 of the byte representing the lowest-numbered block on disc, and counting starting at block 0 (the directory). A bit is set if the corresponding block is in use.

Under CP/M 3, the allocation vector may be of this form (single-bit) or allocate two bits to each block (double-bit). This information is stored in the SCB.

## BDOS function 28 (DRV_SETRO) - Software write-protect current disc
    - Supported by: All versions, with differences
    - Entered with C=1Ch.

Temporarily set current drive to be read-only; attempts to write to it will fail. Under genuine CP/M systems, this continues until either call 13 (disc reset) or call 37 (selective disc reset) is called; in practice, this means that whenever a program returns to the command prompt, all drives are reset to read/write. Newer BDOS replacements only reset the drive when function 37 is called.

Under multitasking CP/Ms, this can fail (returning A=0FFh) if another process has a file open on the drive.

## BDOS function 29 (DRV_ROVEC) - Return bitmap of read-only drives
    - Supported by: All versions
    - Entered with C=1Dh. Returns bitmap in HL.

Bit 7 of H corresponds to P: while bit 0 of L corresponds to A:. A bit is set if the corresponding drive is set to read-only in software.

## BDOS function 30 - set echo mode for function 1
    - Supported by: CP/M 1.3 only
    - Entered with C=1Eh, E=echo mode (0=no echo, else echo).

## BDOS function 30 (F_ATTRIB) - set file attributes
    - Supported by: All versions
    - Entered with C=1Eh, DE=address of FCB. Returns error codes in BA and HL.

Set and reset the bits required. Standard CP/M versions allow the bits F1', F2', F3', F4', T1' (read-only), T2' (system) and T3' (archive) to be changed. Some alternative BDOSses allow F5', F6', F7' and F8' to be set, but this is not to be encouraged since setting these bits can cause CP/M 3 to behave differently.

Under Concurrent CP/M, if the F5' bit is not set and the file has an extended file lock, the lock will be released when the attributes are set. If F5' is set the lock stays.

Under CP/M 3, the Last Record Byte Count is set by storing the required value at FCB+32 (FCB+20h) and setting the F6' bit.

The code returned in A is 0-3 if the operation was successful, or 0FFh if there was an error. Under CP/M 3, if A is 0FFh and H is nonzero, H contains a hardware error.

## BDOS function 31 (DRV_DPB) - get DPB address
    - Supported by: CP/M 2 and later.
    - Entered with C=1Fh. Returns address in HL.

Returns the address of the Disc Parameter Block for the current drive. See the formats listing for details of the DPBs under various CP/M versions.

## BDOS function 32 (F_USERNUM) - get/set user number
    - Supported by: CP/M 2 and later.
    - Entered with C=20h, E=number. If E=0FFh, returns number in A.

Set current user number. E should be 0-15, or 255 to retrieve the current user number into A. Some versions can use user areas 16-31, but these should be avoided for compatibility reasons.

DOS+ returns the number set in A.

## BDOS function 33 (F_READRAND) - Random access read record
    - Supported by: CP/M 2 and later.
    - Entered with C=21h, DE=FCB address. Returns error codes in BA and HL.

Read the record specified in the random record count area of the FCB, at the DMA address. The pointers in the FCB will be updated so that the next record to read using the sequential I/O calls will be the record just read. Error numbers returned are:

    0
    OK
    1
    Reading unwritten data
    4
    Reading unwritten extent (a 16k portion of file does not exist)
    6
    Record number out of range
    9
    Invalid FCB
    10
    Media changed (CP/M); FCB checksum error (MP/M),
    11
    Unlocked file verification error (MP/M),
    0FFh
    [MP/M II, CP/M 3] hardware error in H.
## BDOS function 34 (F_WRITERAND) - Random access write record
    - Supported by: CP/M 2 and later.
    - Entered with C=22h, DE=FCB address. Returns error codes in BA and HL.

Write the record specified in the random record count area of the FCB, at the DMA address. The pointers in the FCB will be updated so that the next record to write using the sequential I/O calls will be the record just written. Error numbers returned are:

    0
    OK
    2
    Disc full
    3
    Cannot close extent
    5
    Directory full
    6
    Record number out of range
    8
    Record is locked by another process (MP/M)
    9
    Invalid FCB
    10
    Media changed (CP/M); FCB checksum error (MP/M)
    11
    Unlocked file verification error (MP/M)
    0FFh
    [MP/M II, CP/M 3] hardware error in H.
If the record indicated is beyond the end of the file, the record will be written and the file may contain a gap; attempting to read this gap may give "reading unwritten data" errors, or nonsense.
## BDOS function 35 (F_SIZE) - Compute file size
    - Supported by: CP/M 2 and later.
    - Entered with C=23h, DE=FCB address. Returns error codes in BA and HL.

Set the random record count bytes of the FCB to the number of 128-byte records in the file. Returns A=0FFh if error (file not found, or CP/M 3 hardware error); otherwise A=0.

## BDOS function 36 (F_RANDREC) - Update random access pointer
    - Supported by: CP/M 2 and later.
    - Entered with C=24h, DE=FCB address.

Set the random record count bytes of the FCB to the number of the last record read/written by the sequential I/O calls.

## BDOS function 37 (DRV_RESET) - Selectively reset disc drives
    - Supported by: CP/M 2 and later.
    - Entered with C=25h, DE=bitmap of drives to reset. Returns A=0 if OK, 0FFh if error.

Bit 7 of D corresponds to P: while bit 0 of E corresponds to A:. A bit is set if the corresponding drive should be reset. Resetting a drive removes its software read-only status.

## BDOS function 38 (DRV_ACCESS) - Access drives
    - Supported by: MP/M, Concurrent CP/M, CP/Net redirector.
    - Entered with C=26h, DE=drive bitmap.

Locks one or more disc drives. Processes will not be able to reset these drives; the effect is the same as if there were open files on the drives.

Returns A=0 if OK, and 0FFh if there is an error. If there is, H will contain the error code.

## BDOS function 39 (DRV_FREE) - Free drive
    - Supported by: MP/M, Concurrent CP/M, CP/Net redirector.
Releases locks on disc drives.

    - Entered with C=27h, DE = bitmap of drives to free.

Open files on the drives in question must be closed before this call is made, or data may be corrupted.

## BDOS function 40 (F_WRITEZF) - Write random with zero fill
    - Supported by: CP/M 2.2 and later.
    - Entered with C=28h, DE=FCB address. Returns error codes in BA and HL.

As function 34, but if the write is to a newly allocated disc block the remainder of the block is filled with zeroes.

## BDOS function 41 - Test and write record
    - Supported by: MP/M, Concurrent CP/M.
    - Entered with C=29h, DE=FCB address. Returns error codes in BA and HL.

This function compares the contents of the file with the record at the DMA address. If the comparison is successful, the data at (DMA + record size) are written to the file.

For example, if the multisector count is set to 4 records, the DMA address will have 512 bytes (4x128) to compare with the file, and then another 512 to write to the file. On return, A is:

    0
    OK
    1
    Reading unwritten data
    3
    Cannot close current extent
    4
    Seek to unwritten extent (a 16k portion of file does not exist)
    6
    Record number out of range
    7
    Records did not match
    8
    Record is locked by another process
    10
    FCB checksum error
    11
    Unlocked file verification error
    0FFh
    hardware error in H.
## BDOS function 42 (F_LOCK) - Lock record
    - Supported by: MP/M, Concurrent CP/M, CP/Net redirector.
    - Entered with C=2Ah, DE=FCB address. Returns error codes in BA and HL.

This function locks the number of records specified by function 44, starting at the record number at FCB+21h. The DMA address should point to the file ID returned by function 15. On return, A is:

    0
    OK
    1
    Reading unwritten data
    3
    Cannot close current extent
    4
    Seek to unwritten extent (a 16k portion of file does not exist)
    6
    Record number out of range
    8
    Record is locked by another process
    10
    FCB checksum error
    11
    Unlocked file verification error
    12
    No more locks available for this process
    13
    Invalid file ID
    14
    No room in the system lock list
    0FFh
    hardware error in H.
## BDOS function 43 (F_UNLOCK) - Unlock record
    - Supported by: MP/M, Concurrent CP/M, CP/Net redirector.
    - Entered with C=2Bh, DE=FCB address. Returns error codes in BA and HL.

This function behaves as function 42 above, but unlocks records rather than locking them. If a record is locked by a different process, it remains locked; but no error is returned.

Set F5' to 1 to unlock all records rather than just the ones the FCB refers to.

## BDOS function 44 (F_MULTISEC) - Set number of records to read/write at once
    - Supported by: MP/M II and later.
    - Entered with C=2Ch, E=number of records. Returns A=0 or 0FFh.

Sets the number of records that functions 14, 15, 31, 32 and 40 should attempt to read at once. E should be 1-16 in MP/M II; 1-127 in CP/M 3 and later. Returns A=0 if E was valid, 0FFh otherwise. The random access counters still operate with 128 bytes/record.

## BDOS function 45 (F_ERRMODE) - Set action on hardware error
    - Supported by: Personal CP/M, MP/M II and later, CP/Net redirector.
    - Entered with C=2Dh, E=action.

Instructs CP/M what action to take if there is a hardware error:

    E < 254
    Compatibility mode; program is terminated and an error message printed.
    E = 254
    Error code is returned in H, error message is printed.
    E = 255
    Error code is returned in H, no error message is printed.
Note that the messages (if printed) are not followed by a carriage return or linefeed.

If this function is being provided by CP/Net, then it only affects network errors.

## BDOS function 46 (DRV_SPACE) - Find free space on a drive
    - Supported by: MP/M II and later.
    - Entered with C=2Eh, E=drive. Returns error codes in BA and HL.

Sets the three bytes at the DMA address to the number of free 128-byte records on the disc, low byte first. E is the drive (0 for A:, 1 for B: etc.). If on return A=0FFh, there is a hardware error in H.

## BDOS function 47 (P_CHAIN) - Chain to program
    - Supported by: MP/M II and later; CP/M-86 v1.1
    - Entered with C=2Fh, E=chain flag. Only returns if it fails.

Execute the command line at 80h. The error return code is not changed, so the new program can discover the status returned by the previous one.

If E=255, then the currently set drive and user (as set by calls 25 and 32) become those used by the CCP; otherwise the CCP drive and user remain the same.

In MP/M II, there is no chain flag; and this call will return if the process is not attached to the screen.

## BDOS function 48 (DRV_FLUSH) - Empty disc buffers
    - Supported by: Personal CP/M; MP/M II and later; CP/M-86 v1.1
    - Entered with C=30h, E=flag. Returns error codes in BA and HL.

Forces all pending disc writes to be executed. If E=255, then all disc read buffers are emptied as well (so that information must be read from the disc - used by file verification programs).

Returns A=0FFh if there is a hardware error in H.

## BDOS function 49 - Access the System Control Block
    - Supported by: CP/M 3.
    - Entered with C=31h, DE=address of parameter area. Returned values vary.

The SCB is a 100-byte area of memory (officially) used for storing system settings. The parameter area is formed:

    pb+0:   DB  offset      ;0-99
    pb+1:   DB  command     ;0    => Read byte at offset into A, 
                            ;        and word at offset into HL.
                            ;0FEh => Write word at pb+2 to SCB at 
                            ;        offset and offset+1
                            ;0FFh => Write byte at pb+2 to SCB at offset
## BDOS function 49 - Return address of system variables
    - Supported by: CP/M-86 v1.1
    - Entered with CL=31h. Returns address in ES:BX.

More information on the System variables area in CP/M-86.

## BDOS function 49 (S_SYSVAR) - Access the system variables
    - Supported by: CP/M-86 v4.
    - Entered with CL=31h, DX=address of parameter area. Returns AX=BX=0 if variable is valid, 0FFFFh if invalid.

The BDOS 4.1 system variables contain various system settings. The parameter area is formed:

    pb+0:   DB  system variable     ;0-5
    pb+1:   DB  command             ;0    => Read the specified variable into 
                                    ;           buffer at pb+2.
                                    ;0FFh => Write data at pb+2 to specified 
                                    ;           variable.
    Variables are:
    Number  Length  Description
    0   1   screen width-1
    1   1   screen height-1
    2   1   page mode - 0 if programs like TYPE should give paged output
    3   1   system clock speed in Hz. Cannot be changed.
    4   1   temporary file drive, 0 for current or 1-16 for A: to P:
    5   5   date and time
                DW  day count, day 1 is 1/1/78
                DB  BCD hours
                DB  BCD minutes
                DB  BCD seconds
    There are also some undocumented variables with numbers between 80h and 92h.
    
    80h 1   If nonzero, an 8087 CPU is present; otherwise it is not.
    81h 1   Current process ID
    82h 26  Data area for current process:
                DB  drive
                DB  user
                DD  DMA
                DB  current BDOS disc function
                DB  ?
                DD  FCB from the last BDOS search call
                DD  ?
                DB  Error mode (set by function 45).
                DB  Multi-record count (set by function 44).
                DB  Default password (8 bytes)
    83h 1   Length of previous command (recalled by Control-W)
    84h 255 Previous command (recalled by Control-W)
    85h 2   Either the address of the CCP data segment, or a linked list
            of memory allocations. I'm not sure which.
    86h 255 CCP settings area:
                DB  CCP drive
                DB  CCP user
                DB  Cold start flag (0 if CCP has not run yet)
                DW  Address of next command in CCP data segment
                DB  Chained command flag (nonzero if a command
                        is waiting)
                DB  ?
                DB  Search order (0=CMD 1=CMD,SUB 2=SUB,CMD)
                DB  Program name display flag (1=yes 2=no)
                DS  7   ;?
                DB  pending command?
    87h 4   List of drives to search, set by SETDEF.
    88h 1   Set if process is running in the background.
    89h 1   Number of processes in system, 1-4.
    8Ah 1   Value set by SLICE - time slice to give to foreground program.
    8Bh 2   BDOS flags. Bit 7 set if ^S is in operation. Bit 9 set if ^P
            is in operation.
    8Ch 1   Nonzero if a process is using the 8087; else zero.
    8Dh 4   Address of code to run in task switch?
    8Eh 2   Pointer to array of 16 near pointers in CP/M data segment -
            addresses of current directory structures for each drive.
    8Fh 5   Multitasker settings
                DW  comsize ;Memory to give to COM files
                DW  addmem  ;Memory to give to EXE files
                DB  f8087   ;8087 enabled or disabled?
    90h 1   Drive containing COMMAND.COM?
    91h 32  DOS 2.x Country Info (see the Interrupt List, INT 21h AH=38h)
    92h 1   SwitChar (see the Interrupt List, INT 21h AH=37h). The SwitChar
            can only be changed this way.

## BDOS function 50 (S_BIOS) - Use the BIOS
    - Supported by: CP/M 3 and later; CP/M-86 v1.1
    - Entered with C=32h, DE=address of parameter area. Returned values vary.

Under CP/M 3, the BIOS should not be directly called, except possibly the character I/O and USERF calls. Instead, this function should be used. The parameter area is formed:

    pb+0:   DB  bios-function   ;0-32
    pb+1:   DB  bios-a      ;Value for A register
    pb+2:   DB  bios-c      ;Value for C register
    pb+3:   DB  bios-b      ;Value for B register
    pb+4:   DB  bios-e      ;Value for E register
    pb+5:   DB  bios-d      ;Value for D register
    pb+6:   DB  bios-l      ;Value for L register
    pb+7:   DB  bios-h      ;Value for H register
In a banked CP/M 3 system:

A successful call to function 9 (SELDSK) will return HL pointing to a copy of the Disk Parameter Header in common memory, rather than the original. This copy may be overwritten by subsequent BDOS calls, so grab it while you can.
A call to function 12 (SETDMA) will be followed by a call to function 28 (SETBNK) with A=1 (TPA bank).
For functions 16 (SECTRAN), 20 (DEVTBL) and 22 (DRVTBL), the value returned in HL and BA will be the result the BIOS returned in HL. For other functions (apart from SELDSK above) L and A will hold the value the BIOS returned in A.
Function 27 (SELMEM) will be ignored.

Under 16-bit versions, this function should be used for all BIOS calls; only character I/O BIOS calls are permitted. The parameter area is formed:

    pb+0:   DB  bios-function
    pb+1:   DB  bios-cl
    pb+2:   DB  bios-ch
    pb+3:   DB  bios-dl
    pb+4:   DB  bios-dh
## BDOS function 51 (F_DMASEG) - Set DMA segment
    - Supported by: CP/M-86 v1.1 and later.
    - Entered with CL=33h, DX=segment value.

## BDOS function 52 (F_DMAGET) - Get DMA address
    - Supported by: CP/M-86 v3+, CCP/M-86.
    - Entered with CL=34h. Returns address in ES:BX.

## BDOS function 53 (MC_MAX) - Allocate maximum memory
    - Supported by: CP/M-86 v1.1 and later.
    - Entered with CL=35h, DX=address of MCB

Set MCB_EXT to 2 if the memory should remain allocated after program termination. Set MCB_LENGTH to maximum required length.

Returns MCB_EXT=0 if no additional memory is available, 1 if there is. Sets MCB_SEGMENT and MCB_LENGTH to the values for the memory block allocated, which will be less than or equal to the size requested. Returns AX=0 if OK, 0FFFFh if error; CX=error code:

     0 OK
     2 Illegal call number
     3 Out of memory
    12 Out of descriptors
    43 Bad Parameter
## BDOS function 54 (MC_ABSMAX) - Allocate absolute maximum memory
    - Supported by: CP/M-86 v1.1 and later.
    - Entered with CL=36h, DX=address of MCB

Set MCB_EXT to 2 if the memory should remain allocated after program termination. Set MCB_LENGTH to maximum required length, and MCB_SEGMENT to the required start paragraph.

Returns MCB_EXT=0 if no additional memory is available, 1 if there is. Sets MCB_SEGMENT and MCB_LENGTH to the values for the memory block allocated, which will be less than or equal to the size requested. Returns AX=0 if OK, 0FFFFh if error; CX=error code.

Z80DOS function 54 - Get file time stamps
    - Supported by: Z80DOS, ZPM3
    - Entered with C=36h. Returns HL=address of stamp.

This returns the timestamp from the last file used by functions 15, 17 or 18. The format of a Z80DOS timestamp is:

    DW  creation date
    DW  modification date
    DB  modification time, hours,   BCD
    DB  modification time, minutes, BCD
    DW  last access date
    DB  last access time, hours, BCD
    DW  last access time, minutes, BCD
More information on Z80DOS and ZPM3.

## BDOS function 55 (MC_ALLOC) - Allocate memory
    - Supported by: CP/M-86 v1.1 and later.
    - Entered with CL=37h, DX=address of MCB

Set MCB_EXT to 2 if the memory should remain allocated after program termination. Set MCB_LENGTH to maximum required length.

Returns MCB_EXT=0 if no additional memory is available, 1 if there is. Sets MCB_SEGMENT and MCB_LENGTH to the values for the memory block allocated, which will be exactly the size requested. Returns AX=0 if OK, 0FFFFh if error; CX=error code.

Z80DOS function 55 - Use file time stamps
    - Supported by: Z80DOS, ZPM3
    - Entered with C=37h.

The next BDOS call will use the timestamp buffer returned by function 54, rather than the current time. This would normally done before creating or closing the file.

## BDOS function 56 (MC_ABSALLOC) - Allocate absolute memory
    - Supported by: CP/M-86 v1.1 and later.
    - Entered with CL=38h, DX=address of MCB

Set MCB_EXT to 2 if the memory should remain allocated after program termination. Set MCB_LENGTH to maximum required length, and MCB_SEGMENT to the required start paragraph.

Returns MCB_EXT=0 if no additional memory is available, 1 if there is. Sets MCB_SEGMENT and MCB_LENGTH to the values for the memory block allocated, which will be exactly the size requested. Returns AX=0 if OK, 0FFFFh if error; CX=error code.

In the 4.1 BDOS (and possibly earlier) it is possible to call this with MCB_EXT set to 2 on a memory block that has already been allocated; this will make the block remain after program termination if it didn't before.

## BDOS function 57 (MC_FREE) - Free memory
    - Supported by: CP/M-86 v1.1 and later.
    - Entered with CL=39h, DX=address of MCB

Set MCB_SEGMENT to start of area, MCB_LENGTH to length. It is not possible to deallocate the middle or start of an area which was allocated as one piece. Set MCB_EXT to 0 to free the specified MCB, or 0FFh to free all this program's memory. Returns AX=0 if OK, 0FFFFh if error; CX=error code.

## BDOS function 58 (MC_ALLFREE) - Free all memory
    - Supported by: CP/M-86 v1.1 and later.
    - Entered with CL=3Ah. This function is obsolete in CP/M-86 v3.x+. In CP/M-86 v1.1, it is called by the CCP to empty memory before a new program is loaded. In Concurrent CP/M, it should not be called by user programs.

## BDOS function 59 (P_LOAD) - Load overlay
    - Supported by: CP/M 3 and higher Loaders.
    - Entered with C=3Bh, DE=FCB address. Returns error code in A.

Load a program or RSX. The FCB should have been opened before making this call; the load address should be stored at FCB+21h. If the program is a PRL (Paged Relocatable), the original CP/M loader will relocate it; some replacement loaders, such as that in CCP+ need a special flag set to indicate this.

If DE=0, the Loader will not load anything, but it will remove from the RSX chain any RSXs marked as due for deletion.

Returns A=0 if OK, 0FEh if there was an error, or 0FFh if the Loader is not present.

In CP/M-86 operating systems, this will load the CMD file at the DMA address, and returns the segment of the Zero Page allocated to the program in BX.

## BDOS function 60 - Call to RSX
    - Supported by: CP/M 3 and later RSXs.
    - Entered with C=3Ch, DE=RSXPB address

This call is provided for programs to communicate with Resident System Extensions. There is a separate list of functions provided by specific RSXs. The format of the RSXPB is:

    DEFB    function, 0-127 ;(128-255 used internally by CP/M)
    DEFB    numwords    ;Number of parameter words passed to RSX.
    DEFW    parameters
A popular convention is for the first parameter word to point to a copy within the program of the name of the intended RSX; for example:

    RSXPB:  DEFB    100     ;Function
            DEFB    1       ;1 Parameter
            DEFW    RNAME   ;RSX name
    RNAME:  DEFB    'GETERL  '
This call returns BA=HL=00FFh if the requested RSX is not resident; otherwise, the values are those returned by the RSX.

## BDOS function 61 - Rename file
    - Supported by: DOS Plus v2.1
    - Entered with C=3Dh, DE=address of FCB. Returns error codes in BA and HL.

This works the same way as the normal rename function, except that it can rename a file across drives if the two drives are 'really' the same (that is, one is a floating drive and the other is its host).

## BDOS function 62 - Unknown
    - Supported by: DOS Plus v2.1
This is a function that was internal to DOS Plus 1.2 and earlier. It allocates a new current directory structure for the active process.

## BDOS function 64 - Log in
    - Supported by: CP/Net.
    - Enter with C=40h, DE=address of login record:

    DB  network ID of server
    DS  8   ;Password
Network IDs are 0-254. The server is normally number 0.

Returns A=0 if successful or already logged in; 0FFh if failed. Logging in can fail if the server does not exist, or the password was incorrect.

## BDOS function 65 - Log off
    - Supported by: CP/Net.
    - Enter with C=41h, E=network ID of server

Returns A=0 if OK, or 0FFh if not logged on to the server anyway.

## BDOS function 66 - Send message
    - Supported by: CP/Net.
    - Enter with C=42h, DE=address of message.

The format of a normal CP/Net message is:

    [--FMT--]  Format code, 1 byte. 0-7 are standard CP/Net message formats.
    [--DID--]  Destination computer's network ID; normally 1 byte.
    [--SID--]  Source computer's network ID; normally 1 byte. 
    [--FNC--]  Function code; for standard messages, BDOS function number.
               Always 1 bytes. 
    [--SIZ--]  Message size - 1; normally 1 byte.
    [--MSG--]  Message data; normally 1-256 bytes.
The 8 standard message formats are treated as bitfields:

    Bit 0: 0 for command, 1 for returned result.
    Bit 1: Message data is more than 256 bytes. The "siz" field is a word and
           the data can be up to 64k.
    Bit 2: Destination ID and source ID are words, not bytes.
Thus giving eight packet types:

    0   Command    5 bytes header  1-256 bytes data   8-bit network IDs
    1   Result     5 bytes header  1-256 bytes data   8-bit network IDs
    2   Command    6 bytes header  1-64k data         8-bit network IDs
    3   Result     6 bytes header  1-64k data         8-bit network IDs
    4       Command    7 bytes header  1-256 bytes data  16-bit network IDs
    5       Result     7 bytes header  1-256 bytes data  16-bit network IDs
    6       Command    8 bytes header  1-64k data        16-bit network IDs
    7       Result     8 bytes header  1-64k data        16-bit network IDs
In 8-bit systems, the NDOS only uses formats 0 and 1.

If the normal format is not used, the computers sending and receiving the message must have a modified NIOS (Network I/O system) so they can correctly handle the nonstandard message.

DRI also state that the format code should be greater than 128, so that the message is not mistaken for a one sent by CP/Net itself. This seems to imply that formats 128-135 should be used for messages in the 8 normal formats.

This call does not wait for a reply. Use function 67 to get a reply.

Returns BA = HL = 0FFFFh if an error occurred; else 0.

## BDOS function 67 - Receive message
    - Supported by: CP/Net.
    - Enter with C=43h, DE=address of buffer for message.

Message format is as given above.

## BDOS function 68 - Get network status
    - Supported by: CP/Net.
    - Enter with C=44h. Returns A=L=status byte.

    Bit 0 set if error transmitting data.
    Bit 1 set if error in received data.
    Bit 4 set if this computer is logged on to the network.
Bits 0 and 1 will be cleared after they have been read by this function.

## BDOS function 69 - Get configuration table address
    - Supported by: CP/Net.
    - Enter with C=45h. Returns HL = address of table.

Format of the table is:

    DB  Network status byte
    DB  Computer's network ID
    DS  32  ;Redirection status of 16 drives
    DS  2   ;Redirection status of console
    DS  2   ;Redirection status of printer
    DB  no. of characters in printer buffer
    DS  5   ;Message header for printer output
    DB  printer device number
    DS  128 ;Printer buffer
A redirection status entry is two bytes:

    DB  Bit 7 set if device is on a different machine.
        Bit 6 set for "set up in disk".
        Bits 0-3 = drive number / device number on its local machine.
    DB  Network ID of the machine containing the device.

## BDOS function 70 - Set compatibility attributes
    - Supported by: CP/Net-86, some 8-bit CP/Net versions.
    - Enter with C=46h, E=compatibility info. No return.

The compatibility attributes are used to make a network server behave more like a local drive on a single-user system, for compatibility with ill-behaved programs. They are set from the "user attributes" F1'-F4' of the current .COM file being run on the client machine.

    F1'
    Disable file locking. There is no protection against two programs writing to the same file at the same time.
    F2'
    File close operations write pending data and update the directory, but the file is not closed and can still be accessed.
    F3'
    Disable FCB checksumming for file close operations.
    F4'
    Disable FCB checksumming completely. This can cause filesystem damage.
    These attributes are passed in E:
    
    Bit 7: F1', disable locking.
    Bit 6: F2', file close is partial.
    Bit 5: F3', disable checksum on close file.
    Bit 4: F4', disable checksum on all FCB operations (also set bits 5 & 6).
## BDOS function 71 - Get server configuration
    - Supported by: CP/Net-86, some 8-bit CP/Net versions.
Enter with C=47h, E=server ID. Returns HL = address of table.

The table returned is:

    DB  server temporary file drive
    DB  server network status
    DB  server ID
    DB  max clients on this server
    DB  current no. of clients on this server
    DW  bitmap of clients logged in to the server
    DS  16  ;Requester ID table

Each call to this function uses the same buffer, so take a copy of the data if calling this repeatedly.

## BDOS function 98 - Clean up disc
    - Supported by: CP/M 3 (Internal?).
    - Entered with C=62h. Returns A=0 if OK, 0FFh if current drive is invalid

This function is called by the CCP when a program terminates. Open files are closed; buffered data are not written, so files opened for writing may be destroyed if not properly closed.

## BDOS function 99 (F_TRUNCATE) - Truncate file
    - Supported by: CP/M 3 and later.
    - Entered with C=63h, DE=FCB address. Returns error codes in BA and HL.

Set the random record count of the FCB to the required file size in records. If the file is password protected, point the DMA address at the password. Returns A=0-3 for success, 0FFh for failure; H may contain a hardware error code.

Under Concurrent CP/M, if the F5' bit is not set and the file has an extended file lock, the lock will be released when the file is truncated. If F5' is set the lock stays.

This function can't be used to extend a file, only reduce it; and if the file is sparse, then it must truncate it to a point where the last record contains actual data.

## BDOS function 100 (DRV_SETLABEL) - Set directory label
    - Supported by: MP/M II and later.
    - Entered with C=64h, DE=FCB. Returns error codes in BA and HL.

The EX byte (FCB+0Ch) of the FCB should contain a flags byte:

    Bit   Meaning if set
    ----------------------------------------
    7     Passwords enabled
    6     Stamp on access
    5     Stamp on update
    4     Stamp on creation
    0     Assign password at DMA+8 to label.
This function may need a password at the DMA address, if there is a label on the disc which has a password.
This function returns A=0 if OK, 0FFh for failure. H may contain a hardware error code.

## BDOS function 101 (DRV_GETLABEL) - Get directory label byte
    - Supported by: MP/M II and later.
    - Entered with C=65h, E=drive. Returns A=byte

The byte returned has the following bits set:

    Bit   Meaning if set
    ----------------------------------------
    7     Passwords enabled
    6     Stamp on access
    5     Stamp on update
    4     Stamp on creation
    0     Directory label exists
If bit 0 is zero, the other bits are meaningless.
If a label does exist, it can be found using functions 17 and 18 with the first 13 bytes of the FCB set to "?", and checking for a file whose user number is 32.

## BDOS function 102 (F_TIMEDATE) - Get file date and time
    - Supported by: MP/M II and later.
    - Entered with C=66h, DE=FCB address. Returns error codes in BA and HL.

Gets the file date and time stamps, and the password mode. The stamps end up at FCB+18h (create or access), FCB+1Ch (update); the password mode ends up at FCB+0Ch. This returns A=0-3 for success, or 0FFh for failure. To tell whether a stamp is for creation or access, check the directory label byte.

For information on the format of date and time stamps, see the date and time calls. The password mode is documented in the next function.

## BDOS function 103 (F_WRITEXFCB) - Set file password and protection
    - Supported by: MP/M II and later.
    - Entered with C=67h, DE=FCB address. Returns error codes in BA and HL.

Sets file password and protection mode. Set FCB+0Ch to the required password mode, and point the DMA address at the current password. The password mode byte should have the following bits set:

    Bit   Meaning if set
    ----------------------------------------
    7     Reading requires password
    6     Writing requires password
    5     Deletion requires password
    0     Assign password at DMA+8 to file.

## BDOS function 104 (T_SET) - Set date and time
    - Supported by: MP/M II and later; Z80DOS, DOS+.
    - Entered with C=68h, DE=address of time stamp.

The format of the time stamp is:

    DW  day ;Day 1 is 1 January 1978
    DB  hour    ;Packed BCD
    DB  minute  ;Packed BCD
    DB  second  ;Packed BCD; only on Z80DOS and DOS+
Under MP/M II and CP/M 3, the "seconds" counter will be reset to zero when this function is called. Under Z80DOS and DOS+, the "seconds" counter will be set from the time stamp.
## BDOS function 105 (T_GET) - Get date and time
    - Supported by: MP/M II and later; Z80DOS, DOS+.
    - Entered with C=69h, DE=address of time stamp. Returns A=seconds (packed BCD).

The format of the time stamp is:

    DW  day ;Day 1 is 1 January 1978
    DB  hour    ;Packed BCD
    DB  minute  ;Packed BCD
    DB  second  ;Packed BCD - only in Z80DOS and DOS+
Under MP/M II and later versions, the "seconds" value will be returned in A.
## BDOS function 106 (F_PASSWD) - Set default password
    - Supported by: MP/M II and above, CP/Net redirector.
    - Entered with C=6Ah, DE=address of password.

Sets the default password, used for all file operations requiring passwords when no password is given explicitly.

## BDOS function 107 (S_SERIAL) - Get serial number
    - Supported by: MP/M II and above.
    - Entered with C=6Bh, DE=address of buffer.

Stores a 6-byte serial number at the address given by DE. Usually this number will be printable ASCII.

## BDOS function 108 (P_CODE) - Get/put program return code
    - Supported by: CP/M 3 and above.
    - Entered with C=6Ch, DE=code. Returns HL=code.

If DE=0FFFFh, then the current code is returned in HL. Otherwise, it is set to the value in DE. Allowable values are:

    00000h - 0FEFFh
    No fatal error
    0FF00h - 0FF7Fh
    Fatal error
    0FF80h - 0FFFCh
    Reserved
    0FFFDh
    Program terminated because of a hardware error.
    0FFFEh
    Program terminated by Control-C.
If a program was chained by function 47, an error code stored by the previous program will be available to it. Otherwise the CCP sets the return code to zero when it executes a program (some replacement CCPs do not do this).
If the error code is 0FF00h or above, and the next command begins with the character : then it will not be run.

## BDOS function 109 (C_MODE) - Set or get console mode
    - Supported by: Personal CP/M; CP/M 3 and above
    - Entered with C=6Dh, DE=mode or 0FFFFh. Returns HL=mode.

The mode is a bitmapped value. Under CP/M 3, the significant bits are:

    0  If set, function 11 detects only ^C.
    1  If set, ^S does not pause screen output.
    2  If set, output does not expand tabs, nor is it echoed to the printer even 
       if ^P was pressed.
    3  If set, ^C does not cause the program to terminate.
    4  Behaves like bit 2. The BDOS source comments imply it also signifies 
       "escape sequence decoding" but whatever this is, it is not implemented in 
       the CP/M 3 BDOS.
    7  Under CCP/M, if set, ^O does not act as a byte bucket.
    
    8  } These form a 2-bit number controlling GET and SUBMIT:
    9  }
        0  Return "conditional" status to function 11.
                 Programs using function 11 to test for interruption (eg SID) are 
                 not interrupted, but those using it to test for input do get the
                 input. It does this by returning "false", then "true".
            1  Function 11 always returns "true".
            2  Function 11 always returns "false".
            3  Temporarily disable GET/SUBMIT, input comes from keyboard.
    Under Personal CP/M, only one bit is used:
    4  If set, tab expansion, ^S and ^P are disabled during screen output.
## BDOS function 110 (C_DELIMIT) - Get/set string delimiter
    - Supported by: Personal CP/M; CP/M 3 and above
    - Entered with C=6Eh, DE=0FFFFh or ASCII value. Returns ASCII value in A.

This function gets or sets the string delimiter (used in function 9 to mark the end of the string to print). If DE=0FFFFh, this gets the current ASCII value into A; otherwise it sets the delimiter to the value in E.

## BDOS function 111 (C_WRITEBLK) - Send block of text to console
    - Supported by: Personal CP/M; CP/M 3 and above
    - Entered with C=6Fh, DE=address of character control block.

For 8-bit CP/M, the character control block is formed:

    DW  text_begin
    DW  text_length
For 16-bit CP/M, it is formed:
    DW  text_begin_offset
    DW  text_begin_segment
    DW  text_length
## BDOS function 112 (L_WRITEBLK) - Send block of text to printer
    - Supported by: Personal CP/M; CP/M 3 and above
    - Entered with C=70h, DE=address of character control block.

Format of character control block

## BDOS function 113 - Direct screen functions
    - Supported by: Personal CP/M.
    - Entered with C=71h, DE=address of parameter block.

This function is implemented by the PCP/M BIOS. The first byte of the parameter block gives an operation code, 0-27.

## BDOS function 115 - Reserved for GSX
    - Supported by: GSX (Graphics System Extension)
    - Entered with C=73h, DE=parameter block address.

Follow this link for more information on the GSX calls.

Under CP/M-86, CX should be 0473h. Other values of CH than 4 are used for GSX-86 internal functions.

## BDOS function 116 - Set file date & time
    - Supported by: CP/M-86 v4.
    - Entered with CL=74h, DX=FCB address. Returns AX=BX=error code.

The required stamps should be put at the DMA address. Returns AL = 0-3 for success, or 0FFh for failure.

## BDOS function 117 - BDOS v4.x internal
    - Supported by: CP/M-86 v4.
    - Entered with CL=75h, DX=PB address. Returns AX=BX=error code.

This appears to make a call to the disc drivers; INT 13h calls are routed through this function. The parameter block is:

    DB  0 to read, 1 to write (2 to verify?)
    DB  drive
    DB  no. of sectors
    DB  head
    DB  sector (0 based)
    DB  cylinder
    DD  address of data
## BDOS function 124 - Byte block copy
    - Supported by: Personal CP/M.
This call is passed directly to the BIOS. On the Sharp MZ-800 version of PCP/M, it has no effect and returns with A = 0FFh.

## BDOS function 125 - Byte block alter
    - Supported by: Personal CP/M.
This call is passed directly to the BIOS. On the Sharp MZ-800 version of PCP/M, it has no effect and returns with A = 0FFh.

XDOS function 128 (M_ALLOC) - Absolute memory request
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=80h, DE=address of MPB. Returns A=0 if memory allocated, 0FFh if error.

Allocates memory at the requested address. If successful sets the MIN and MAX fields to the size allocated.

In 16-bit operating systems, this function and the next are interchangeable; they check the START field of the MPB to determine whether a fixed address is requested or not.

## BDOS function 129 (M_ALLOC) - Relocatable memory request
    - Supported by: MP/M
    - Entered with C=81h, DE=address of MPB. Returns A=0 if memory allocated, 0FFh if error.

Allocates memory. If successful sets the first word of the MPB to the allocated address, and the MIN and MAX fields to the size allocated.

## BDOS function 130 (M_FREE) - Free memory
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=82h, DE=address of Memory Free Parameter Block. Returns A=0 if memory freed, 0FFh if error.

The MFPB is formed:

        DW      address ;of memory previously allocated with M_ALLOC
        DW      0
## BDOS function 131 (DEV_POLL) - Poll I/O device
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=83h, E=device number. Returns A=0 if OK, 0FFh if error.

Blocks until the device in question is ready, polling it on every interrupt. The XIOS should call this if a process is waiting on a device that isn't interrupt driven.

## BDOS function 132 (DEV_WAITFLAG) - Wait on system flag
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=84h, E=flag number. Returns A=0 if OK, 0FFh if error.

Blocks until DEV_SETFLAG is called on the flag in question. Flags 0-3 are reserved for the BDOS; others are system dependent.

## BDOS function 133 (DEV_SETFLAG) - Set system flag
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=85h, E=flag number. Returns A=0 if OK, 0FFh if error.

Called by the XIOS interrupt handler to restart a process that's waiting on the given system flag.

## BDOS function 134 (Q_MAKE) - Create message queue
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=86h, DE=address of queue descriptor. Returns A=0 if OK, 0FFh if error.

The queue descriptor is formed:

	DW	0,0	;Reserved
	DW	flags	;Bit 0: Mutual exclusion queue
			;Bit 1: Cannot be deleted
			;Bit 2: Restricted to system processes
			;Bit 3: RSP message queue
			;Bit 4: Reserved
			;Bit 5: RPL address queue
			;Bits 6,7: Reserved
	DB	'  name  '
	DW	msglen	;Number of bytes in a message 
	DW	nmsg	;Number of messages in this queue
	DW	0,0,0,0	;Reserved
	DW	buffer	;Address of the queue buffer, which must be 
			;at least msglen * nmsg bytes long.	
## BDOS function 135 (Q_OPEN) - Open message queue
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=87h, DE=address of closed QPB. Returns A=0 if OK, 0FFh if error.

Opens the specified message queue. All 8 bits of the queue name are compared, unlike filename matches.

## BDOS function 136 (Q_DELETE) - Delete message queue
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=88h, DE=address of open QPB. Returns A=0 if OK, 0FFh if error.

Deletes the specified message queue from the system.

## BDOS function 137 (Q_READ) - Read from message queue
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=89h, DE=address of open QPB. Returns A=0 if OK, 0FFh if error.

If there's nothing to read, then the call blocks until there is something.

## BDOS function 138 (Q_CREAD) - Conditionally read from message queue
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=8Ah, DE=address of open QPB. Returns A=0 if OK, 0FFh if error or there's nothing to read.

As Q_READ, but does not block.

## BDOS function 139 (Q_WRITE) - Write to message queue
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=8Bh, DE=address of open QPB. Returns A=0 if OK, 0FFh if error.

If there's no room in the message queue buffer, the call blocks until there is.

## BDOS function 140 (Q_CWRITE) - Conditionally write to message queue
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=8Ch, DE=address of open QPB. Returns A=0 if OK, 0FFh if error or the queue buffer is full.

As Q_WRITE, but does not block.

## BDOS function 141 (P_DELAY) - Delay
    - Supported by: MP/M, Concurrent CP/M, CP/M-86 v4.
    - Entered with C=8Dh, DE=no. of ticks to wait.

Blocks the calling process for at least DE ticks of the system clock (system dependent; usually 50Hz or 60Hz). Returns A=0FFh if this function is unsupported.

## BDOS function 142 (P_DISPATCH) - Call dispatcher
    - Supported by: MP/M, Concurrent CP/M, CP/M-86 v4.
    - Entered with C=8Eh.

Relinquishes the CPU. The process restarts when its next time slice falls due. Returns A=0FFh if this function is unsupported.

## BDOS function 143 (P_TERM) - Terminate process
    - Supported by: MP/M, Concurrent CP/M, CP/M-86 v4.
    - Entered with C=8Fh, DL=termination code.

In single-user systems, behaves as function 0.

In multiuser systems, the termination code must be 0FFh to terminate a system process, or 0-0FEh to terminate a user process.

## BDOS function 144 (P_CREATE) - Create a subprocess
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=90h, DE=address of initial process descriptor.

Launches a subprocess of the current process.

The process descriptor passed in DE can be a linked list (to launch several processes at a time). If a descriptor is outside the system data segment, it will be copied into the process table.

Format of Concurrent CP/M process descriptor:

        DW      link    ; Address of next process descriptor. 
        DW      thread  ; Initialise to 0
        DB      stat    ; Initialise to 0 (runnable). Other values are 
                        ; 1=Polling device, 2=Delaying, 6=Waiting to read
                        ;  queue, 7=Waiting to write queue, 8=Waiting on
                        ;  system flag, 9=Waiting to attach device
        DB      prior   ; Priority. 200=normal, 255=worst. 1-63 are 
                        ; used by system processes, 198 by the terminal
                        ; message process.
        DW      flags   ; Bit 0 set for system process. Only system processes
                        ;       can launch system processes.
                        ; Bit 1 set if process can't be terminated. Only 
                        ;       system processes can launch interminable 
                        ;       processes.
                        ; Bit 2 set if process is part of the OS. The passed
                        ;       descriptor must be inside the OS.  
                        ; Bit 3 set if process descriptor is part of the 
                        ;       system PD table.
                        ; Bit 15 set if process uses the 8087.  
        DB      '  name  ' ; 8-byte process name.
        DW      uda     ; User data area segment. Initialise to the number of 
                        ; paragraphs from the beginning of the calling
                        ; process's data segment. 
        DB      disk    ; Current drive
        DB      user    ; Current user ID
        DW      0       ; Reserved
        DW      mem     ; Memory Segment Descriptors owned by this process.
                        ; Initialise to zero.
        DW      0,0,0   ; Reserved
        DW      parent  ; Parent process ID; initialise to 0.
        DB      cns     ; Default console number
        DB      0,0,0   ; Reserved
        DB      list    ; Default printer number
        DB      0       ; Reserved
        DW      sflag   ; Bit 0 is set if the process should block when not
                        ; in the foreground
        DW      0,0,0,0 ; Reserved 
The UDA is 256 bytes, or 352 bytes if the process uses the 8087, and it must be paragraph-aligned.

        DW      0        ; Reserved
        DW      DMA      ; Initial DMA offset in child process's DS.
        DS      28       ; Reserved, set to 0
        DW      ax       ; Initial AX value 
        DW      bx       ; Initial BX value 
        DW      cx       ; Initial CX value 
        DW      dx       ; Initial DX value 
        DW      si       ; Initial SI value 
        DW      di       ; Initial DI value 
        DW      bp       ; Initial BP value 
        DW      0,0,0    ; Reserved
        DW      sp       ; Initial SP value. The top of the stack must be set
                         ; up IP, CS, flags (so that an IRET launches the 
                         ; new process).
        DW      0        ; Reserved
        DD      int0     ; INT 0 handler; 0 to use the same as the calling
                         ; process.
        DD      int1     ; INT 1 handler; 0 to use the same as the calling
                         ; process.
        DD      0        ; Reserved
        DD      int3     ; INT 3 handler; 0 to use the same as the calling
                         ; process.
        DD      int4     ; INT 4 handler; 0 to use the same as the calling
                         ; process.
        DD      0        ; Reserved
        DW      cs       ; Initial CS value; 0 to use calling process's DS 
        DW      ds       ; Initial DS value; 0 to use calling process's DS 
        DW      es       ; Initial ES value; 0 to use calling process's DS 
        DW      ss       ; Initial SS value; 0 to use calling process's DS 
        DD      int224   ; INT 0E0h handler; 0 to use the same as the calling
                         ; process. This allows a parent process to intercept
                         ; BDOS calls made by its child.
        DD      int225   ; INT 0E1h handler; 0 to use the same as the calling
                         ; process.
All other fields must be initialised to 0, with one exception. If the process being launched uses the 8087, then the word at offset 100h must be set to 03FFh.

## BDOS function 145 (P_PRIORITY) - Set process priority
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=91h, E = priority.

The highest priority is 0; the lowest is 0FFh. Transient programs start off at priority 200.

## BDOS function 146 (C_ATTACH) - Attach console
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=92h.

Blocks the calling process until the process's default console is available. This is automatically called if any console I/O function is used while the current process is not attached to the console.

## BDOS function 147 (C_DETACH) - Detach console
    - Supported by: MP/M, Concurrent CP/M, CP/M-86 v4.
    - Entered with C=93h.

The program is disconnected from the screen and keyboard and must run in the background.

Under CP/M-86 v4, attempting to use the keyboard will cause the program to be terminated. Note that backgrounded programs cannot use the INT 2nh DOS-like calls, only the INT E0h CP/M calls. Limited screen output can be achieved using XIOS function 8 (write to status line).

Under MP/M and CCP/M, attempting to output to the screen will cause function 146 to be invoked.

## BDOS function 148 (C_SET) - Set console
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=94h, E=console number.

Sets the process's default console number. If the number is out of range, returns A=0FFh; else returns 0.

## BDOS function 149 (C_ASSIGN) - Assign console
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=95h, DE = address of assign control block. Returns A=0 if OK, 0FFh if failed.

Assigns a console device to another process. The assign control block is formed:

        DB      cns             ;Which console to assign
        DB      match           ;If 0FFh, the process must have console 
                                ;'cns' as its default console. If 0, not.
        DW      pd              ;Process ID of the process to be given the
                                ;console. Set to 0 to use the name below.
        DB      '  name  '
## BDOS function 150 (P_CLI) - Send CLI command
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=96h, DE = address of command-line buffer. Returns A=0 if OK, 0FFh if failed.

This executes a command line, either by passing it to a loaded Resident System Process or by launching a program. If the current process is attached to its default console, it will be detached and the child process (or RSP) will be given it. Before it takes the console back, it should raise its priority to less than 198, take the console, and set priority back to 200.

The format of the command-line buffer is:

        DB   0      ;Reserved
        DS   128    ;128 bytes for 0-terminated command line
        DB   0      ;Reserved
## BDOS function 151 (P_RPL) - Call resident procedure library
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=97h, DE=address of parameter. Returns HL=result from RPL, or 0001h if RPL not found.

The parameter is formed:

	DB	'  name  '
	DW	parameter
Internally, this is implemented using message queues.

## BDOS function 152 (F_PARSE) - Parse filename
    - Supported by: MP/M, CP/M 3 and higher.
    - Entered with C=98h, DE=address of PFCB. Returns codes in HL.

This parses an ASCII filename to a FCB. The format of the PFCB is:

    DEFW    ascii-address
    DEFW    fcb-address
The value returned in HL is 0FFFFh if the ASCII filename was invalid; 0 if the ASCII filename was terminated with a zero or a carriage return; and otherwise the address of the next character after the filename.
The filename can be of any form up to the full d:filename.typ;password (password only under CP/M 3 and above). When the filename is parsed, the password is copied to FCB+10h, with its length at FCB+1Ah.

Under ZPM3, the filename may be of the form du:filename.typ;password; FCB+0Dh will be 0 if no user number was specified, or 1+number otherwise. If a Z-System is loaded, ZPM3 can also parse filenames of the form dir:filename.typ;password.

BUG: ZPM3 (version N10) puts the password at FCB+0Ch rather than FCB+10h, overwriting the user number stored at FCB+0Dh. It does not zero the last four bytes of the FCB, while CP/M does.

The filename can be terminated by any of: space tab cr nul ; = > < . : , [ ] / | .

## BDOS function 153 (C_GET) - Return console number
    - Supported by: MP/M, Concurrent CP/M
    - Enter with C=99h (153). Returns A = default console number

Returns the number of the process's default console.

## BDOS function 154 (S_SYSDAT) - System data address
    - Supported by: MP/M, Concurrent CP/M, CP/M-86 v4.
    - Entered with C=9Ah. Returns HL (or ES:BX) = system data address.

CP/M-86 3.x/4.x System Data Area format  
CCP/M-86 3.1 System Data Area format  
REAL/32 System Data Area format  
## BDOS function 155 (T_SECONDS) - Get date and time
    - Supported by: MP/M, Concurrent CP/M
    - Entered with C=9Bh, DE=address of time stamp.

The format of the time stamp is:

        DW      day     ;Day 1 is 1 January 1978
        DB      hour    ;Packed BCD
        DB      minute  ;Packed BCD
        DB      second  ;Packed BCD
Note that this function fills in the "seconds" field, which function 105 does not do.

## BDOS function 156 (P_PDADR) - Return address of process descriptor
    - Supported by: MP/M 2, Concurrent CP/M
    - Entered with C=9Ch. Returns HL = address of descriptor (ES:BX in 16-bit systems).

The process descriptor is described in P_CREATE.

## BDOS function 157 (P_ABORT) - Abort a process
    - Supported by: MP/M 2, Concurrent CP/M
    - Entered with C=9Dh, DE = address of abort parameter block. Returns A=0 if OK, 0FFh if failed.

Terminates a process by force. The abort parameter block is formed:

        DW      pd              ;Process ID of the process to be
                                ;terminated. If this is zero, uses 
                                ;the 'name' and 'cns' fields for a match.
        DW      term            ;Termination code (see P_TERM)
        DB      cns             ;(if PD=0) Default console of process to be 
                                ;terminated.
        DB      0
        DB      '  name  '      ;(if PD=0) Name of process to be terminated.
The low byte of the termination code is 0FFh to abort a system process, other values to abort a user process.

## BDOS function 158 (L_ATTACH) - Attach printer
    - Supported by: MP/M 2, Concurrent CP/M
    - Entered with C=9Eh.

Blocks the calling process until the default printer is available. This is automatically called if any printer function is used while the current process is not attached to the printer.

## BDOS function 159 (L_DETACH) - Detach printer
    - Supported by: MP/M 2, Concurrent CP/M
    - Entered with C=9Fh.

Detach this process from the printer,

## BDOS function 160 (L_SET) - Select printer
    - Supported by: MP/M 2, Concurrent CP/M
    - Entered with C=0A0h, E=printer number.

Sets the process's default printer number. If the number is out of range, returns A=0FFh; else returns 0.

## BDOS function 161 (L_CATTACH) - Conditionally attach printer

  - Supported by: MP/M 2, Concurrent CP/M
  - Entered with C=0A1h.

Attempts to attach to the process's default printer without blocking. Returns 0 if succeeded, 0FFh if something else is using the printer.

## BDOS function 162 (C_CATTACH)- Conditionally attach console
  - Supported by: MP/M 2, Concurrent CP/M
  - Entered with C=0A2h.

Attempts to attach to the process's default console without blocking. Returns 0 if succeeded, 0FFh if something else is using the console.

## BDOS function 163 (S_OSVER) - Return version number
  - Supported by: DOSPLUS, MP/M 2, Concurrent CP/M
  - Entered with C=A3h.

The version number returned by this function is a "user-visible" number rather than the internal BDOS version. Numbers include:

    1012h - DOSPLUS v1.2
    1021h - DOSPLUS v2.1
    1121h - MP/M-86 v2.1
    1420h - Concurrent CP/M v2.0
    1431h - Concurrent CP/M v3.1
    1432h - Concurrent DOS v3.2
    1441h - Concurrent DOS v4.1
    1450h - Concurrent DOS v5.0
    (the high byte has the same meaning as in function 12.)

Not implemented by DOSPLUS v1.1 on the Philips :YES.

## BDOS function 164 (L_GET) - Return default printer device number
    - Supported by: MP/M 2, Concurrent CP/M
    - Enter with C=0A4h (164). Returns A = default printer number

Returns the number of the process's default printer.

## BDOS function 175 - Return real drive ID
    - Supported by: DOSPLUS v2.1
    - Entered with CL=AFh, DL=drive number (0 => A:, 1 => B: etc.)

DOSPLUS treats drive N:, O: and P: as floating drives, which can be assigned to paths on other drives (the same sort of thing as SUBST under MS-DOS).

    If DL is the number of a non-floating drive, 
        this will return AH=BH=0 and AL=BL=drive number passed in. 
        This is true even if the drive in question does not exist.

    If DL is the number of a floating drive which has not been assigned,
        this will return AH=BH=0 and AL=BL=drive number of the boot drive.  

    If DL is the number of a floating drive which has not been assigned,
        this will return AH=BH=0 and AL=BL=drive number of the host drive.  

    If DL is out of range, this will return AX=BX=0FFFFh and CX=17h.  
For example, after the command CD P:=B:\MYDIR, this call will return AX=BX=0001h (B:) if it was entered with DL=0Fh (P:). 

## P2DOS function 200 - get time
    - This has the same functionality under P2DOS as function 105 does under Z80DOS and DOS+.

    - Used by P2DOS, SUPRBDOS, NovaDOS.

## P2DOS function 201 - set time
    - This has the same functionality under P2DOS as function 104 does under Z80DOS and DOS+.

    - Used by P2DOS, SUPRBDOS, NovaDOS.

## DOS+ function 210 - Return system information
    - Supported by: DOS+
    - Entered with C=0D2h, E=number, 0-5. Returns values in BA and HL.

Suitable arguments are:

0.     Return base address for BDOS module. Used for dynamic reconfiguration.
1.     Return the current DMA setting.
2.     Flush any console input pending, emptying all buffers.  Returns 0.
3.     Returns list device status (ready/not ready)
4.     Returns punch   "     "          "
5.     Returns reader  "     "          "
Arguments 3 to 5 represent ready as 0ffh, not ready as 0. If no custom installation for punch/reader device status has been made their status is returned 0 (not ready). Other arguments return 0.

DOS+ function 211 - Print decimal number
Supported by: DOS+
Entered with C=0D3h, DE=decimal number.

Outputs the number as an unsigned 16-bit integer, with leading zero suppression.

## IOBYTE
- https://www.seasip.info/Cpm/iobyte.html

CP/M 2 Input/Output mapping
Under CP/M 2, input and output device selection are performed by the BIOS. Some BIOSes may implement a feature called the IOBYTE which allows the user to change which device the screen, printer etc. output go to.

The IOBYTE lives at address 3 (in the Zero Page) and should be changed using BDOS calls 7 and 8 (get/set IOBYTE). The value is bitmapped:

     Bits      Bits 6,7    Bits 4,5    Bits 2,3    Bits 0,1
     Device    LIST        PUNCH       READER      CONSOLE

     Value
       00      TTY:        TTY:        TTY:        TTY:
       01      CRT:        PTP:        PTR:        CRT:
       10      LPT:        UP1:        UR1:        BAT:
       11      UL1:        UP2:        UR2:        UC1:

    BAT = batch mode. Use the current Reader for console input, and he current List (printer) device as the console output.
    CRT = Standard console (keyboard and terminal screen).
    LPT = Standard line printer.
    PTP = Standard Paper Tape Punch.
    PTR = Standard Paper Tape Reader.
    TTY = Teletype device, eg a serial port.
    UC1 = User defined (ie implementation dependent) console device.
    UL1 = User defined (ie implementation dependent) printer device.
    UPn = User defined (ie implementation dependent) output device.
    URn = User defined (ie implementation dependent) input device.
