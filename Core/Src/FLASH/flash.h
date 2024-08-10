#ifndef INC_FLASH_H_
#define INC_FLASH_H_

#include "myHeader.h"

//#define _FLASH_64BIT

#ifdef _FLASH_64BIT
	#define	_NUMBYTE	8
#else
	#define	_NUMBYTE	4
#endif

// FLASH_PAGE_SIZE = 2k bytes
// luu y : stm32g070RB : co 64 pages , moi page 2k byte ,FLASH_PAGE_SIZE :  0x00000800U = 2048 bytes ~ 2kb
#define ADDR_FLASH_PAGE_63 	0x0801F800 /* Start @ of user Flash area =>  last byte of page 63 is 0x0801 FFFF */
#define	FLASH_ADDRESS_START 	ADDR_FLASH_PAGE_63
#define GetPage(Addr) 		((Addr - FLASH_BASE) / FLASH_PAGE_SIZE) // trả về vị trí Page của 1 địa chỉ bất kỳ

///@chu y: sau bien ket thuc can luu vao flash phai trong 4byte
void flash_init_address(uint32_t *address_start, uint32_t *address_end);
void flash_update(void);
void flash_read(void);
uint8_t flash_erase(uint32_t ADR_StartPage, uint32_t numPages);

ResultStatus Flash_WriteDWord(uint64_t data64, uint32_t ADR_StartPage);
ResultStatus Flash_Write_DWord(uint64_t data, uint32_t ADR_StartPage);
uint8_t Flash_ReadByte(uint32_t ADR);
uint32_t Flash_ReadWord(uint32_t ADR);
uint64_t Flash_ReadDWord(uint32_t ADR);

#endif /* INC_FLASH_H_ */
