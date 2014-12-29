::get_pal.psd的作用是统一多张bmp图的调色板（然后手工用ps切割成多个256色bmp文件）
del *.c
gfx2gba.exe  -fsrc -D -c256 -t1 -pbg.pal bg01.bmp bg02.bmp bg03.bmp bg04.bmp bg05.bmp bg06.bmp bg07.bmp bg08.bmp bg09.bmp bg10.bmp bg11.bmp bg12.bmp bg13.bmp bg14.bmp bg15.bmp bg16.bmp bg17.bmp bg18.bmp bg19.bmp bg20.bmp bg21.bmp bg22.bmp
gfx2gba.exe  -fsrc -D -c256 -t1 -pcover01.pal cover01.bmp 
gfx2gba.exe  -fsrc -D -c256 -t1 -pcover02.pal cover02.bmp
pause
