gbabook
=======

A simple gba game like a visual novel (book), Simplified Chinese Only.

* Build her with devkitPro/devkitARM (http://sourceforge.net/projects/devkitpro/).  
* Run .gba file with VisualBoyAdvance under Windows.  
* There is a bug in it (I forget what it is, maybe in graph loading), I found no method to fix it.  
* If you use newest devkitpro/devkitARM, change arm-eabi-gcc to arm-none-eabi-gcc in Makefile (see patch/Makefile).    
* My arm-eabi-gcc is in build_tool/gba.7z, I put the code under gba\home\Administrator\gbabook, execute 'make' to generate book.gba and execute 'vba book.gba'.    
