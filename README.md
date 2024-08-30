# Transcendence-M33
Transcendence M33 - Translate PL/M code and Intel 8080 Assembly to M33 (ARMv8-M) Assembly. This is a retargeting of the original Transcendence M0+ repository to M33. I originally made significant progress in the now archived M0+ repository and will make efforts to align this new repository with the archived M0+ repository.

![](https://github.com/SaxonRah/Transcendence-M33/blob/main/Archive/imgs/Transcendence.gif)
## What's in a name?
Quite a bit, apparently. ***Transcendence*** has a meaning and itself is a backronym:    
***Transcendence:*** The state of assembly code which **transcends** architectures.  
***T***<sup>echnique <sup>(for)</sup></sup> ***R***<sup>etroactively</sup> ***A***<sup>dapting</sup> ***N***<sup>umerous</sup> ***S***<sup>ource</sup> ***C***<sup>ode</sup> ***E***<sup>xpressions <sup>(and)</sup></sup> ***N***<sup>avigating</sup> ***D***<sup>iverse</sup> ***E***<sup>mbedded</sup> ***N***<sup>otation</sup> ***C***<sup>ontexts</sup> ***E***<sup>fficiently</sup>

## A PL/M & Intel 8080 Assembly to Arm M33 Translation Tool.
- *__I dream of a translation tool for Assembly/Higher Level Languages to an ARM ISA:__*  
   - *__8-Bit: 8008, 8080, 8085, 6502, Z80, M6800__*  
   - *__16-Bit: 8086, Z800, Z8000, i186, i286__*  
   - *__32-Bit: Z80000, M68000, i386, i486__*
   - *__Languages: PL/M, Forth, Pascal__*

<sup>*__This is the starting point of that dream and tool.  
This is an extremely complex dream and will probably never be fully actualized.  
However I'm willing to try.__*</sup>

## Overview
Transcendence-M33 is a translation tool designed to convert Intel 8080 assembly language code into Arm M33 assembly language, targeting platforms like the Raspberry Pi RP2350. The tool also aims to transpile PL/M language code into Arm M33 assembly language, facilitating compatibility with older systems requiring CP/M operating systems or similar environments. Transcendence-M33 (for now) aims to bridge the gap between legacy various 8-Bit CPUs and PL/M codebases with modern Arm Cortex-M33 platforms like the Raspberry Pi RP2350. By providing a reliable and efficient translation mechanism, it enables the preservation and utilization of vintage software while leveraging the capabilities of contemporary hardware.  

## Features Desired
1. **Translation from Intel 8080 Assembly to Arm M33 Assembly:**
   - Convert Intel 8080 assembly language instructions to equivalent Arm M33 assembly instructions.
   - Handle differences in instruction formats, addressing modes, and operand types between the two architectures.
   - Ensure efficient translation to leverage the capabilities of the Arm M33 processor.
   
2. **Transpilation of PL/M Code to Arm M33 Assembly:**
   - Translate PL/M language constructs into Arm M33 assembly language.
   - Support a wide range of PL/M syntax and constructs, including control structures, data types, and procedures.
   - Ensure compatibility with CP/M operating system requirements and other legacy systems.

3. **Pattern Matching and Parsing:**
   - Utilize regular expressions for pattern matching Intel 8080 assembly and PL/M language constructs.
   - Parse matched patterns to construct an Abstract Syntax Tree (AST) for subsequent translation.
   - Employ tools like LEX and YACC, or alternatives like PLY or SLY, for efficient parsing and AST generation.

4. **Optimization and Code Generation:**
   - Implement optimizations to improve the efficiency and performance of translated code.
   - Generate optimized Arm M33 assembly code with consideration for resource constraints and execution speed.
   - Employ techniques such as instruction look-ahead for enhancing translation accuracy and performance.

5. **Modularity and Extensibility:**
   - Design Transcendence-M33 with a modular architecture to facilitate future enhancements and additions.
   - Allow for easy integration of new translation rules, optimizations, and target architectures.
   - Support multiple input and output formats to accommodate diverse usage scenarios.

## Motivation
Transcendence-M33 addresses the challenge of translating code between architectures with differing instruction sets and design philosophies. By enabling the conversion of legacy Intel 8080 and PL/M code to Arm M33 assembly, it facilitates the utilization of modern hardware while preserving compatibility with vintage systems.

## Target Platform
Transcendence-M33 primarily targets the Raspberry Pi RP2350, which features the Arm Cortex-M33 processor. The tool is optimized for the little-endian architecture of the RP2350, ensuring compatibility with its execution environment.

## Contribution
Contributions to Transcendence-M33 are welcome and encouraged. Interested developers can clone the project repository. Contribute enhancements. Fix Bugs. Add additional translation capabilities. Collaboration and feedback are essential for improving the tool.
