# BDOS Function Summary
- https://www.seasip.info/Cpm/bdosfunc.html

CP/M 2.2, CP/M 3.0, MP/M 2.1 Compiled by Jim Lopushinsky  
Notation: .something means the address of something.
    
         /-----CP/M 2.2
         | /---CP/M 3.0
         | | /-MP/M 2.1
         | | |                              INPUT          RETURNED
    FUNC v v v FUNCTION NAME                PARAMETERS     VALUES
    
      0  X X X System Reset                 none           none
      1  X X X Console Input                none           A = char
      2  X X X Console Output               E = char       none
      3  X X - Auxiliary Input              none           A = char
      3  - - X Raw Console Input            none           A = char
      4  X X - Auxiliary Output             E = char       none
      4  - - X Raw Console Output           E = char       none
      5  X X X List Output                  E = char       none
      6  X X X Direct Console I/O           E = 0FFH/      A = char/
                                                0FEH/          status/
                                                0FDH/          none
                                                char
      7  X - - Get I/O Byte                 none           A = IOBYTE
      7  - X - Auxiliary Input Status       none           A = 00/0FFH
      8  X - - Set I/O Byte                 E = IOBYTE     none
      8  - X - Auxiliary Output Status      none           A = 00/0FFH
      9  X X X Print String                 DE = .String   none
     10  X X X Read Console Buffer          DE = .Buffer   Characters in
                                                               buffer
     11  X X X Get Console Status           none           A = 00/01
     12  X X X Return Version Number        none           HL = Version
     13  X X X Reset Disk System            none           see def
     14  X X X Select Disk                  E = Disk Number see def
     15  X X X Open File                    DE = .FCB      A = Dir Code
     16  X X X Close File                   DE = .FCB      A = Dir Code
     17  X X X Search for First             DE = .FCB      A = Dir Code
     18  X X X Search for Next              none           A = Dir Code
     19  X X X Delete File                  DE = .FCB      A = Dir Code
     20  X X X Read Sequential              DE = .FCB      A = Err Code
     21  X X X Write Sequential             DE = .FCB      A = Err Code
     22  X X X Make File                    DE = .FCB      A = Dir Code
     23  X X X Rename File                  DE = .FCB      A = Dir Code
     24  X X X Return Login Vector          none           HL= Login Vector
     25  X X X Return Current Disk          none           A = Cur Disk #
     26  X X X Set DMA Address              DE = .DMA      none
     27  X X X Get Addr (Alloc)             none           HL= .Alloc
     28  X X X Write Protect Disk           none           none
     29  X X X Get R/O Vector               none           HL= R/O Vector
     30  X X X Set File Attributes          DE = .FCB      A = Dir Code
     31  X X X Get Addr (DPB)               none           HL= .DPB
     32  X X X Set/Get User Code            E = 0FFH/      A = Curr User/
                                              user number      none
     33  X X X Read Random                  DE = .FCB      A = Err Code
     34  X X X Write Random                 DE = .FCB      A = Err Code
     35  X X X Compute File Size            DE = .FCB      r0, r1, r2
     36  X X X Set Random Record            DE = .FCB      r0, r1, r2
     37  X X X Reset Drive                  DE = Drive     A = Err Code
                                                 Vector
     38  - X X Access Drive                 DE = Drive     none
                                                 Vector
     39  - X X Free Drive                   DE = Drive     none
                                                 Vector
     40  X X X Write Random with Zero Fill  DE = .FCB      A = Err Code
     41  - - X Test and Write Record        DE = .FCB      HL= Err Code
     41  - X - Test and Write Record        DE = .FCB      A = 0FFH
     42  - X X Lock Record                  DE = .FCB      HL = Err Code
     43  - X X Unlock Record                DE = .FCB      HL = Err Code
     44  - X X Set Multi-sector Count       E = # Sectors  A = Return Code
     45  - X X Set BDOS Error Mode          E = Err Mode   none
     46  - X X Get Disk Free Space          E = Drive #    Number of Free
                                                              Sectors
     47  - X X Chain to Program             E = Chain Flg  none
     48  - X X Flush Buffers                E = Purge Flg  A = Err Flag
     49  - X - Get/Set System Control       DE = .SCB PB   A = Returned Byte
                             Block                         HL= Returned Word
     50  - X - Direct Bios Calls            DE = .BIOS PB  BIOS Return
     59  - X - Load Overlay                 DE = .FCB      A = Err Code
     60  - X - Call Resident System         DE = .RSX PB   A = Err Code
                        Extension
     98  - X - Free Blocks                  none           none
     99  - X - Truncate File                DE = .FCB      A = Dir Code
    100  - X X Set Directory Label          DE = .FCB      A = Dir Code
    101  - X X Return Directory Label Data  E = Drive      A = Label Data
    102  - X X Read File Date Stamps        DE = .FCB      A = Dir Code
                   and Password Mode
    103  - X X Write File XFCB              DE = .FCB      A = Dir Code
    104  - X X Set Date and Time            DE = .DAT      none
    105  - X X Get Date and Time            DE = .DAT      Date and Time
                                                           A = seconds
    106  - X X Set Default Password         DE = .Passwrd  none
    107  - X X Return Serial Number         DE = .Serial # Serial Number
                                                 field
    108  - X - Get/Set Program Return Code  DE = 0FFFFH/   HL= Ret Code/
                                                 Code          none
    109  - X - Get/Set Console Mode         DE = 0FFFFH/   HL= Console Mode/
                                                 Mode          none
    110  - X - Get/Set Output Delimiter     DE = 0FFFFH/   A = Output Delim/
                                            E = Delimiter      none
    111  - X - Print Block                  DE = .CCB      none
    112  - X - List Block                   DE = .CCB      none
    128  - - X Absolute Memory Request      DE = .MD       A = Err Code
    129  - - X Relocatable Memory Request   DE = .MD       A = Err Code
    130  - - X Memory Free                  DE = .MD       none
    131  - - X Poll                         E = Device     none
    132  - - X Flag Wait                    E = Flag       A = Err Code
    133  - - X Flag Set                     E = Flag       A = Err Code
    134  - - X Make Queue                   DE = .QCB      none
    135  - - X Open Queue                   DE = .UQCB     A = Err Code
    136  - - X Delete Queue                 DE = .QCB      A = Err Code
    137  - - X Read Queue                   DE = .UQCB     none
    138  - - X Conditional Read Queue       DE = .UQCB     A = Err Code
    139  - - X Write Queue                  DE = .UQCB     none
    140  - - X Conditional Write Queue      DE = .UQCB     A = Err Code
    141  - - X Delay                        DE = # ticks   none
    142  - - X Dispatch                     none           none
    143  - - X Terminate Process            E = Term. Code none
    144  - - X Create Process               DE = .PD       none
    145  - - X Set Priority                 E = Priority   none
    146  - - X Attach Console               none           none
    147  - - X Detach Console               none           none
    148  - - X Set Console                  E = Console    none
    149  - - X Assign Console               DE = .APB      A = Err Code
    150  - - X Send CLI Command             DE = .CLICMD   none
    151  - - X Call Resident Sys Proc       DE = .CPB      HL= result
    152  - X X Parse Filename               DE = .PFCB     see def
    153  - - X Get Console Number           none           A = Console #
    154  - - X System Data Address          none           HL= Sys Data Addr
    155  - - X Get Date and Time            DE = .TOD      date and time
    156  - - X Return Process Descriptor    none           HL= PD Addr
    157  - - X Abort Specified Process      DE = .ABT PB   A = Err Code
    158  - - X Attach List                  none           none
    159  - - X Detach List                  none           none
    160  - - X Set List                     E = List #     none
    161  - - X Conditional Attach List      none           A = Err Code
    162  - - X Conditional Attach Console   none           A = Err Code
    163  - - X MPM Version Number           none           HL= Version #
    164  - - X Get List Number              none           A = List #
