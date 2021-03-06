/**
 * size : 0 - 256
 */
uint8_t crc4_tablet_init(int size)
{
 uint8_t i;

 uint8_t shift = -4;             // Current byte size - 8
 uint8_t poly = 3;              // CRC-4 default poly
 uint8_t crc = 0 << shift;     
 uint8_t highbit = 1 << (4 - 1); // Calc highbit
 uint8_t mask = ((highbit - 1) << 1) | 0x1;
 uint8_t diff8 = -shift;
 uint8_t temp_data = 0x0;

  if (diff8 > 0) {
   //# enlarge temporary to fit 8 - bit
   mask = 0xFF;
   crc <<= diff8;
   shift = 0;
   highbit = 0x80;
   poly = poly << diff8;
  }

  crc ^= table_byte_value[size] << shift;                 // crc ^= *data; data++;

  for (i = 0; i < 8; ++i) {
   if (crc & highbit) {
    crc = (crc << 1) ^ poly;// 0x0C = (reverse 0x03)<<(8-4)
   } else {
    crc <<= 1;
   }
  }

 return crc;
}



/**
* 
* reflect_input = flase
* reflect_output = false
* xor_output = 0x0
*
* @param crc -> Existing CRC value before process a new one.
* @param data -> Pointer to data to be hashed with CRC
* @param len -> Size of data
* @return -> CRC value.
*/
uint8_t crc4(uint8_t crc, unsigned char *data, unsigned char len) {
 if (data == NULL)
  return 0;
 while (len--) crc = table_byte[crc ^ *data++];
 return crc >> 4;
}
