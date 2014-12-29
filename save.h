//////////////////////////////////////////////////////////////////////////
//  my functions of saving/reading data from battery ram                //
//////////////////////////////////////////////////////////////////////////

void savebyte(unsigned short offset,unsigned char data);
void saveshort(unsigned short offset,unsigned short data);
void savelong(unsigned short offset,unsigned long data);
unsigned char readbyte(unsigned short offset);
unsigned short readshort(unsigned short offset);
unsigned long readlong(unsigned short offset);
