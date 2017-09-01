# dx
An easily extensible intelligent disassembler for various (mostly 8-bit) processors

Supported CPUs:
 - 6502
 - 6809
 - Atari DVG - a bit specialised but I needed it

Experimental
 - 6509 - disassemble 6502 but produce equivalent 6809 code (how crazy is that!)

Known problems:
 6502
  - This engine does a pretty good job of identifying all areas of the ROM image 
    that contain code by starting with all possible vector entrypoints and
    disassembling from there, taking note of all possible destination addresses
    from all branches, jumps and jsrs it encounters along the way, and then
    disassembling from those addresses recursively. There is just one 6502 
    instruction where that's not possible - the indirect jump (opcode 6C).
 
 
