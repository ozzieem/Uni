#ifndef _EEPROM_H
#define _EEPROM_H



void eeprom_write_enable();
void eeprom_write(unsigned int address, unsigned char data);
void eeprom_write_vector(unsigned int address, unsigned char *data, int n);
unsigned char eeprom_read(unsigned int address);
unsigned char eeprom_read_sr();

#endif
