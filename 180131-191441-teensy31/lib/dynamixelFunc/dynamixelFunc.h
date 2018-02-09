void writedata(unsigned char aID, unsigned char addr, unsigned char *data, unsigned int size);
void readData();
void regwritedata(unsigned char aID, unsigned char addr, unsigned char *data, unsigned int size);
void action(unsigned char aID);
void syncWrite(unsigned char *aID, unsigned short sizeI, unsigned char *data, int el, unsigned char addr);