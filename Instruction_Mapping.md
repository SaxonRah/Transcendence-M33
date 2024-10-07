## **Register Mapping**

Establish a mapping between the 8080's registers and the ARM Cortex-M33's registers:

- **8080 Registers:**
  - **General Purpose:** A (Accumulator), B, C, D, E, H, L
  - **Register Pairs:** BC, DE, HL
  - **Special Registers:** SP (Stack Pointer), PC (Program Counter), Flags

- **ARM Cortex-M33 Registers:**
  - **General Purpose:** R0–R12
  - **Special Registers:** R13 (SP), R14 (LR), R15 (PC), APSR (Flags)

**Basic Mapping:**

- **A → R0**
- **B → R1**
- **C → R2**
- **D → R3**
- **E → R4**
- **H → R5**
- **L → R6**
- **SP → R13 (SP)**
- **PC → R15 (PC)**
- **Flags → APSR**

---

## **Instruction Translation**

### **1. Data Transfer Instructions**

#### **MOV r1, r2**

- **8080 Instruction:**
  ```
  MOV D, E   ; D ← E
  ```
- **M33 Equivalent:**
  ```
  MOV R3, R4 ; D ← E
  ```

#### **MVI r, data**

- **8080 Instruction:**
  ```
  MVI A, #0x55 ; A ← 0x55
  ```
- **M33 Equivalent:**
  ```
  MOVS R0, #0x55 ; A ← 0x55
  ```

#### **LXI rp, data16**

- **8080 Instruction:**
  ```
  LXI H, #0x1234 ; HL ← 0x1234
  ```
- **M33 Equivalent:**
  ```
  MOVW R5, #0x1234 ; H ← 0x1234 (lower 16 bits)
  ```

#### **LDA addr**

- **8080 Instruction:**
  ```
  LDA 0x2000 ; A ← [0x2000]
  ```
- **M33 Equivalent:**
  ```
  LDR R0, =0x2000 ; Load address into R0
  LDRB R0, [R0]   ; A ← [0x2000]
  ```

#### **STA addr**

- **8080 Instruction:**
  ```
  STA 0x2000 ; [0x2000] ← A
  ```
- **M33 Equivalent:**
  ```
  LDR R1, =0x2000 ; Load address into R1
  STRB R0, [R1]   ; [0x2000] ← A
  ```

#### **LHLD addr**

- **8080 Instruction:**
  ```
  LHLD 0x2000 ; L ← [0x2000], H ← [0x2001]
  ```
- **M33 Equivalent:**
  ```
  LDR R6, =0x2000 ; Load address into R6
  LDRB R6, [R6]   ; L ← [0x2000]
  LDR R5, =0x2001
  LDRB R5, [R5]   ; H ← [0x2001]
  ```

#### **SHLD addr**

- **8080 Instruction:**
  ```
  SHLD 0x2000 ; [0x2000] ← L, [0x2001] ← H
  ```
- **M33 Equivalent:**
  ```
  LDR R7, =0x2000
  STRB R6, [R7]   ; [0x2000] ← L
  ADD R7, #1
  STRB R5, [R7]   ; [0x2001] ← H
  ```

#### **LDAX rp**

- **8080 Instruction:**
  ```
  LDAX B ; A ← [BC]
  ```
- **M33 Equivalent:**
  ```
  LSL R1, R1, #8  ; Combine B and C into R1
  ORR R1, R1, R2
  LDRB R0, [R1]   ; A ← [BC]
  ```

#### **STAX rp**

- **8080 Instruction:**
  ```
  STAX D ; [DE] ← A
  ```
- **M33 Equivalent:**
  ```
  LSL R3, R3, #8  ; Combine D and E into R3
  ORR R3, R3, R4
  STRB R0, [R3]   ; [DE] ← A
  ```

#### **XCHG**

- **8080 Instruction:**
  ```
  XCHG ; Swap HL and DE
  ```
- **M33 Equivalent:**
  ```
  MOV R7, R5 ; Temp ← H
  MOV R5, R3 ; H ← D
  MOV R3, R7 ; D ← Temp

  MOV R7, R6 ; Temp ← L
  MOV R6, R4 ; L ← E
  MOV R4, R7 ; E ← Temp
  ```

### **2. Arithmetic Instructions**

#### **ADD r**

- **8080 Instruction:**
  ```
  ADD B ; A ← A + B
  ```
- **M33 Equivalent:**
  ```
  ADDS R0, R1 ; A ← A + B
  ```

#### **ADI data**

- **8080 Instruction:**
  ```
  ADI #0x10 ; A ← A + 0x10
  ```
- **M33 Equivalent:**
  ```
  ADDS R0, #0x10 ; A ← A + 0x10
  ```

#### **ADC r**

- **8080 Instruction:**
  ```
  ADC C ; A ← A + C + CY
  ```
- **M33 Equivalent:**
  ```
  ADCS R0, R2 ; A ← A + C + Carry
  ```

#### **ACI data**

- **8080 Instruction:**
  ```
  ACI #0x10 ; A ← A + 0x10 + CY
  ```
- **M33 Equivalent:**
  ```
  ADCS R0, #0x10 ; A ← A + 0x10 + Carry
  ```

#### **SUB r**

- **8080 Instruction:**
  ```
  SUB D ; A ← A - D
  ```
- **M33 Equivalent:**
  ```
  SUBS R0, R3 ; A ← A - D
  ```

#### **SUI data**

- **8080 Instruction:**
  ```
  SUI #0x10 ; A ← A - 0x10
  ```
- **M33 Equivalent:**
  ```
  SUBS R0, #0x10 ; A ← A - 0x10
  ```

#### **INR r**

- **8080 Instruction:**
  ```
  INR B ; B ← B + 1
  ```
- **M33 Equivalent:**
  ```
  ADDS R1, #1 ; B ← B + 1
  ```

#### **DCR r**

- **8080 Instruction:**
  ```
  DCR C ; C ← C - 1
  ```
- **M33 Equivalent:**
  ```
  SUBS R2, #1 ; C ← C - 1
  ```

#### **INX rp**

- **8080 Instruction:**
  ```
  INX H ; HL ← HL + 1
  ```
- **M33 Equivalent:**
  ```
  LSL R7, R5, #8
  ORR R7, R7, R6  ; R7 ← HL
  ADDS R7, #1     ; R7 ← R7 + 1
  LSR R5, R7, #8  ; H ← High byte
  ANDS R6, R7, #0xFF ; L ← Low byte
  ```

### **3. Logical Instructions**

#### **ANA r**

- **8080 Instruction:**
  ```
  ANA D ; A ← A & D
  ```
- **M33 Equivalent:**
  ```
  ANDS R0, R3 ; A ← A & D
  ```

#### **ANI data**

- **8080 Instruction:**
  ```
  ANI #0x0F ; A ← A & 0x0F
  ```
- **M33 Equivalent:**
  ```
  ANDS R0, #0x0F ; A ← A & 0x0F
  ```

#### **ORA r**

- **8080 Instruction:**
  ```
  ORA E ; A ← A | E
  ```
- **M33 Equivalent:**
  ```
  ORRS R0, R4 ; A ← A | E
  ```

#### **ORI data**

- **8080 Instruction:**
  ```
  ORI #0x0F ; A ← A | 0x0F
  ```
- **M33 Equivalent:**
  ```
  ORRS R0, #0x0F ; A ← A | 0x0F
  ```

#### **XRA r**

- **8080 Instruction:**
  ```
  XRA H ; A ← A ^ H
  ```
- **M33 Equivalent:**
  ```
  EORS R0, R5 ; A ← A ^ H
  ```

#### **XRI data**

- **8080 Instruction:**
  ```
  XRI #0x0F ; A ← A ^ 0x0F
  ```
- **M33 Equivalent:**
  ```
  EORS R0, #0x0F ; A ← A ^ 0x0F
  ```

#### **CMP r**

- **8080 Instruction:**
  ```
  CMP L ; Compare A and L
  ```
- **M33 Equivalent:**
  ```
  CMP R0, R6 ; Set flags based on A - L
  ```

### **4. Branching Instructions**

#### **JMP addr**

- **8080 Instruction:**
  ```
  JMP 0x3000 ; PC ← 0x3000
  ```
- **M33 Equivalent:**
  ```
  LDR R15, =0x3000 ; PC ← 0x3000
  ```

#### **JZ addr**

- **8080 Instruction:**
  ```
  JZ 0x3000 ; If Z=1, PC ← 0x3000
  ```
- **M33 Equivalent:**
  ```
  BEQ label ; Branch if Zero flag is set
  ```

#### **JNZ addr**

- **8080 Instruction:**
  ```
  JNZ 0x3000 ; If Z=0, PC ← 0x3000
  ```
- **M33 Equivalent:**
  ```
  BNE label ; Branch if Zero flag is clear
  ```

#### **CALL addr**

- **8080 Instruction:**
  ```
  CALL 0x4000 ; Call subroutine at 0x4000
  ```
- **M33 Equivalent:**
  ```
  BL subroutine ; Branch with Link to subroutine
  ```

#### **RET**

- **8080 Instruction:**
  ```
  RET ; Return from subroutine
  ```
- **M33 Equivalent:**
  ```
  BX LR ; Return to address in Link Register
  ```

### **5. Stack and Machine Control Instructions**

#### **PUSH rp**

- **8080 Instruction:**
  ```
  PUSH B ; [SP-1] ← B, [SP-2] ← C, SP ← SP - 2
  ```
- **M33 Equivalent:**
  ```
  PUSH {R1, R2} ; Push B and C onto stack
  ```

#### **POP rp**

- **8080 Instruction:**
  ```
  POP D ; E ← [SP], D ← [SP+1], SP ← SP + 2
  ```
- **M33 Equivalent:**
  ```
  POP {R3, R4} ; Pop into D and E
  ```

#### **XTHL**

- **8080 Instruction:**
  ```
  XTHL ; Exchange top of stack with HL
  ```
- **M33 Equivalent:**
  ```
  LDR R7, [SP]    ; Temp ← [SP]
  STR R6, [SP]    ; [SP] ← L
  MOV R6, R7      ; L ← Temp

  LDR R7, [SP, #4]
  STR R5, [SP, #4]
  MOV R5, R7      ; H ← Temp
  ```

#### **SPHL**

- **8080 Instruction:**
  ```
  SPHL ; SP ← HL
  ```
- **M33 Equivalent:**
  ```
  LSL R7, R5, #8  ; R7 ← H << 8
  ORR R7, R7, R6  ; R7 ← H:L
  MOV SP, R7      ; SP ← HL
  ```

### **6. Input/Output Instructions**

#### **IN port**

- **8080 Instruction:**
  ```
  IN 0x10 ; A ← Input from port 0x10
  ```
- **M33 Equivalent:**
  ```
  LDR R0, =IO_PORT_0x10
  LDRB R0, [R0] ; A ← [IO_PORT_0x10]
  ```

#### **OUT port**

- **8080 Instruction:**
  ```
  OUT 0x10 ; Output A to port 0x10
  ```
- **M33 Equivalent:**
  ```
  LDR R1, =IO_PORT_0x10
  STRB R0, [R1] ; [IO_PORT_0x10] ← A
  ```

### **7. Special Instructions**

#### **NOP**

- **8080 Instruction:**
  ```
  NOP ; No operation
  ```
- **M33 Equivalent:**
  ```
  NOP ; No operation
  ```

#### **HLT**

- **8080 Instruction:**
  ```
  HLT ; Halt CPU
  ```
- **M33 Equivalent:**
  ```
  WFI ; Wait for interrupt (simulate halt)
  ```

#### **DI**

- **8080 Instruction:**
  ```
  DI ; Disable interrupts
  ```
- **M33 Equivalent:**
  ```
  CPSID i ; Disable interrupts
  ```

#### **EI**

- **8080 Instruction:**
  ```
  EI ; Enable interrupts
  ```
- **M33 Equivalent:**
  ```
  CPSIE i ; Enable interrupts
  ```

#### **RST n**

- **8080 Instruction:**
  ```
  RST 1 ; Call subroutine at n*8
  ```
- **M33 Equivalent:**
  ```
  LDR R15, =n*8 ; PC ← n*8
  ```

---

## **Additional Notes**

- **Register Pair Operations:** The 8080 often uses register pairs (e.g., HL) for 16-bit operations. In ARM, may need to combine two 8-bit values or use a single 32-bit register.
  - **Instruction_Mapping_Pairs.md** View this file for proposed pair register mapping.
- **Flag Handling:** The 8080's flags (S, Z, AC, P, CY) do not map directly to ARM's flags (N, Z, C, V). Special care is needed when translating instructions that affect or rely on flags.
  -  **TODO**
- **Memory Addressing:** The 8080 uses 16-bit addresses; ARM uses 32-bit addresses. Ensure address calculations accommodate this difference.
- **Stack Operations:** The stack grows downward in ARM architecture. Adjust stack pointer manipulations accordingly.
- **Instruction Sizes:** ARM's instructions can be 16 or 32 bits (Thumb-2). Some operations may require multiple instructions to replicate 8080 functionality.
