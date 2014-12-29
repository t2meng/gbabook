
void savebyte(unsigned short offset,unsigned char data){
	unsigned char* save=((unsigned char*)0x0e000000);
	save[offset]=data;
}
void saveshort(unsigned short offset,unsigned short data){
	unsigned char* save=((unsigned char*)0x0e000000);
	unsigned char high,low;
	high=data>>8;
	low=data&0xff;
	save[offset]=high;
	save[offset+1]=low;
}
void savelong(unsigned short offset,unsigned long data){
	unsigned char b0,b1,b2,b3; // b0 is the first 8-bit of long data
	b0=data>>24;
	b1=(data&0x00ffffff)>>16;
	b2=(data&0x0000ffff)>>8;
	b3=data&0x000000ff;
	savebyte(offset++,b0);
	savebyte(offset++,b1);
	savebyte(offset++,b2);
	savebyte(offset,b3);
}
/*unsigned char readbyte(unsigned short offset){
	unsigned char* sram=((unsigned char*)0x0e000000);
	return sram[offset];
}*/
unsigned char readbyte(unsigned short offset)
{
	//Read the value
	unsigned char* sram=((unsigned char*)0x0e000000);
	return *(unsigned char *)(sram + offset);
}
unsigned short readshort(unsigned short offset){
	unsigned char* sram=((unsigned char*)0x0e000000);
	unsigned short val;
	val=sram[offset];
	val=val<<8;
	val=val+sram[offset+1];
	return val;
}
unsigned long readlong(unsigned short offset){
	unsigned char* sram=((unsigned char*)0x0e000000);
	unsigned long val,val2;
	val2=sram[offset]; val=val2<<24;
	val2=sram[offset+1]; val=val+(val2<<16);
	val2=sram[offset+2]; val=val+(val2<<8);
	val2=sram[offset+3]; val=val+val2;
	return val;
}
