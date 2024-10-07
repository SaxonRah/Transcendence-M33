## **Register Mapping**

**Intel 8080 Registers:**

- **Single-byte Registers:** A, B, C, D, E, H, L
- **Register Pairs (16-bit):** **BC**, **DE**, **HL**

**ARM Cortex-M33 Registers:**

- **General Purpose Registers:** R0–R12
- **Special Registers:** R13 (SP), R14 (LR), R15 (PC)

**Pair Mapping:**

- **A**  →  **R0**
- **B** and **C**  →  **R1** (B in bits **[15:8]**, C in bits **[7:0]**)
- **D** and **E**  →  **R2** (D in bits **[15:8]**, E in bits **[7:0]**)
- **H** and **L**  →  **R3** (H in bits **[15:8]**, L in bits **[7:0]**)
- **BC**  →  **R7** (alias or copy of R1 for 16-bit operations)
- **DE**  →  **R8** (alias or copy of R2 for 16-bit operations)
- **HL**  →  **R9** (alias or copy of R3 for 16-bit operations)
- **SP**  →  **R13** (Stack Pointer)
- **PC**  →  **R15** (Program Counter)
- **Flags**  →  **APSR**
  -  **Flags_Mapping.md** View this file to see explination.

**Notes:**

- **R1–R3** hold both the individual 8-bit registers and the 16-bit register pairs.
- **R7–R9** are used for 16-bit register pair operations to take advantage of ARM's 32-bit registers.
- When performing operations on single-byte registers within the pairs, use bit manipulation to access the correct byte.
- This mapping aims to optimize register usage while balancing complexity.

---

## **Instruction Translation with Updated Register Mapping**

### **Bit Manipulation Helper Macros**

- **Extract Lower Byte (bits 7:0):**
  ```
  AND Rtemp, Rx, #0xFF ; Rtemp = Rx[7:0]
  ```
- **Extract Upper Byte (bits 15:8):**
  ```
  LSR Rtemp, Rx, #8
  AND Rtemp, Rtemp, #0xFF ; Rtemp = Rx[15:8]
  ```
- **Set Lower Byte:**
  ```
  AND Rx, Rx, #0xFFFFFF00 ; Clear bits [7:0]
  ORR Rx, Rx, Rnew ; Set new lower byte
  ```
- **Set Upper Byte:**
  ```
  AND Rx, Rx, #0xFFFF00FF ; Clear bits [15:8]
  LSL Rnew, Rnew, #8
  ORR Rx, Rx, Rnew ; Set new upper byte
  ```

---

### **1. Data Transfer Instructions**

#### **MOV r1, r2**

- **8080 Instruction:**
  ```
  MOV D, E ; D ← E
  ```
- **M33 Equivalent:**
  ```
  ; Extract E from R2[7:0]
  AND Rtemp, R2, #0xFF ; Rtemp = E

  ; Set D in R2[15:8]
  AND R2, R2, #0xFFFF00FF ; Clear D
  LSL Rtemp, Rtemp, #8 ; Shift E to bits [15:8]
  ORR R2, R2, Rtemp ; D ← E
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

- **8080 Instruction:**
  ```
  MVI B, #0x55 ; B ← 0x55
  ```
- **M33 Equivalent:**
  ```
  ; Set B in R1[15:8]
  AND R1, R1, #0xFFFF00FF ; Clear B
  LSL Rtemp, #0x55, #8 ; Rtemp = 0x55 << 8
  ORR R1, R1, Rtemp ; B ← 0x55
  ```

#### **LXI rp, data16**

- **8080 Instruction:**
  ```
  LXI H, #0x1234 ; HL ← 0x1234
  ```
- **M33 Equivalent:**
  ```
  MOVW R3, #0x1234 ; HL ← 0x1234
  MOV R9, R3 ; Update HL pair register
  ```

#### **LDA addr**

- **8080 Instruction:**
  ```
  LDA 0x2000 ; A ← [0x2000]
  ```
- **M33 Equivalent:**
  ```
  LDR Rtemp, =0x2000 ; Load address
  LDRB R0, [Rtemp] ; A ← [0x2000]
  ```

#### **STA addr**

- **8080 Instruction:**
  ```
  STA 0x2000 ; [0x2000] ← A
  ```
- **M33 Equivalent:**
  ```
  LDR Rtemp, =0x2000 ; Load address
  STRB R0, [Rtemp] ; [0x2000] ← A
  ```

#### **LHLD addr**

- **8080 Instruction:**
  ```
  LHLD 0x2000 ; L ← [0x2000], H ← [0x2001]
  ```
- **M33 Equivalent:**
  ```
  LDR Rtemp, =0x2000
  LDRH R3, [Rtemp] ; Load 16 bits into HL
  MOV R9, R3 ; Update HL pair register
  ```

#### **SHLD addr**

- **8080 Instruction:**
  ```
  SHLD 0x2000 ; [0x2000] ← L, [0x2001] ← H
  ```
- **M33 Equivalent:**
  ```
  LDR Rtemp, =0x2000
  STRH R3, [Rtemp] ; Store 16 bits from HL
  ```

#### **LDAX rp**

- **8080 Instruction:**
  ```
  LDAX B ; A ← [BC]
  ```
- **M33 Equivalent:**
  ```
  ; BC is in R7
  LDRB R0, [R7] ; A ← [BC]
  ```

#### **STAX rp**

- **8080 Instruction:**
  ```
  STAX D ; [DE] ← A
  ```
- **M33 Equivalent:**
  ```
  ; DE is in R8
  STRB R0, [R8] ; [DE] ← A
  ```

#### **XCHG**

- **8080 Instruction:**
  ```
  XCHG ; Swap HL and DE
  ```
- **M33 Equivalent:**
  ```
  MOV Rtemp, R3 ; Rtemp ← HL
  MOV R3, R2 ; HL ← DE
  MOV R2, Rtemp ; DE ← Rtemp
  MOV R9, R3 ; Update HL pair
  MOV R8, R2 ; Update DE pair
  ```

### **2. Arithmetic Instructions**

#### **ADD r**

- **8080 Instruction:**
  ```
  ADD B ; A ← A + B
  ```
- **M33 Equivalent:**
  ```
  ; Extract B from R1[15:8]
  LSR Rtemp, R1, #8
  ADDS R0, R0, Rtemp ; A ← A + B
  ```

#### **ADI data**

- **8080 Instruction:**
  ```
  ADI #0x10 ; A ← A + 0x10
  ```
- **M33 Equivalent:**
  ```
  ADDS R0, R0, #0x10 ; A ← A + 0x10
  ```

#### **INX rp**

- **8080 Instruction:**
  ```
  INX H ; HL ← HL + 1
  ```
- **M33 Equivalent:**
  ```
  ADDS R3, R3, #1 ; HL ← HL + 1
  MOV R9, R3 ; Update HL pair register
  ```

### **3. Logical Instructions**

#### **ANA r**

- **8080 Instruction:**
  ```
  ANA D ; A ← A & D
  ```
- **M33 Equivalent:**
  ```
  ; Extract D from R2[15:8]
  LSR Rtemp, R2, #8
  ANDS R0, R0, Rtemp ; A ← A & D
  ```

#### **ANI data**

- **8080 Instruction:**
  ```
  ANI #0x0F ; A ← A & 0x0F
  ```
- **M33 Equivalent:**
  ```
  ANDS R0, R0, #0x0F ; A ← A & 0x0F
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
  BEQ label_3000 ; Branch if Zero flag is set
  ```

### **5. Stack Instructions**

#### **PUSH rp**

- **8080 Instruction:**
  ```
  PUSH B ; [SP-2] ← BC, SP ← SP - 2
  ```
- **M33 Equivalent:**
  ```
  SUB SP, SP, #4 ; Adjust stack pointer (assuming 32-bit stack)
  STR R1, [SP] ; Store BC onto stack
  ```

#### **POP rp**

- **8080 Instruction:**
  ```
  POP D ; DE ← [SP], SP ← SP + 2
  ```
- **M33 Equivalent:**
  ```
  LDR R2, [SP] ; Load DE from stack
  ADD SP, SP, #4 ; Adjust stack pointer
  MOV R8, R2 ; Update DE pair register
  ```

### **6. Input/Output Instructions**

#### **IN port**

- **8080 Instruction:**
  ```
  IN 0x10 ; A ← Input from port 0x10
  ```
- **M33 Equivalent:**
  ```
  LDR Rtemp, =IO_PORT_0x10
  LDRB R0, [Rtemp] ; A ← [IO_PORT_0x10]
  ```

#### **OUT port**

- **8080 Instruction:**
  ```
  OUT 0x10 ; Output A to port 0x10
  ```
- **M33 Equivalent:**
  ```
  LDR Rtemp, =IO_PORT_0x10
  STRB R0, [Rtemp] ; [IO_PORT_0x10] ← A
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
  WFI ; Wait for interrupt
  ```

---

## **Additional Notes**

- **Register Synchronization:** When modifying individual registers within a pair (e.g., B or C in BC), ensure that the 16-bit register pair (R7, R8, R9) is updated if necessary.
- **Endian Considerations:** ARM is typically little-endian; ensure byte order is correctly handled when performing 16-bit operations.
- **Performance Optimization:** While we utilize extra registers for register pairs, be mindful of the overhead introduced by bit manipulation.
