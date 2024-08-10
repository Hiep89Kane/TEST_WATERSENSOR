#include "myHeader.h"
#include "stdlib.h"

struct{
	uint32_t	*address_start; //địa chỉ bắt đầu cần lưu
	uint32_t	*address_end;	//địa chỉ kết thúc cần lưu
	uint16_t	len_data;		//độ dài dữ liệu flash cần lưu
	uint8_t		flash_enable:1;	//enable
}flash_str;

static uint8_t flash_compare(void);
static uint8_t flash_compare(void){
  for(uint16_t i = 0; i < flash_str.len_data; i += 4)
    if(flash_str.address_start[i/4] != (*(__IO uint32_t*)(FLASH_ADDRESS_START + i)))
      return 1;
  return 0;
}

///@chu y: sau bien ket thuc can luu vao flash phai trong 4byte
void flash_init_address(uint32_t *address_start, uint32_t *address_end){

  if(flash_str.flash_enable == 1)		//chi init 1 lan
    return;
  flash_str.address_start = address_start;
  flash_str.address_end = address_end;
  flash_str.len_data = (int)(address_end) - (int)(address_start) + 4;
  flash_str.flash_enable = 1;
}

void flash_read(void){
  if(flash_str.flash_enable == 1){
		for(uint16_t i = 0; i < flash_str.len_data; i += 4){
		flash_str.address_start[i/4] = (*(__IO uint32_t*)(FLASH_ADDRESS_START + i));
    }
  }
}

void flash_update(void){

  if((flash_compare() == 1) &&
      (flash_str.flash_enable == 1))
    {
    HAL_FLASH_Unlock();

    //timeout 10ms to erase
    uint32_t start_stick = HAL_GetTick();
    while(flash_erase(FLASH_ADDRESS_START,1)==0){
		if ((HAL_GetTick() - start_stick) > 10 /*ms*/)
		  return;
    }

    for(uint16_t i = 0; i < flash_str.len_data; i += _NUMBYTE){
	//timeout 10ms to write
	start_stick = HAL_GetTick();
	while(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD , FLASH_ADDRESS_START + i,  flash_str.address_start[i/4]) != HAL_OK){
	  if ((HAL_GetTick() - start_stick) > 10 /*ms*/)
	    return;
	}
    }
    HAL_FLASH_Lock();
  }
}


uint8_t flash_erase(uint32_t ADR_StartPage, uint32_t numPages){
	FLASH_EraseInitTypeDef 	EraseInitStruct;
	uint32_t PageError;

	HAL_FLASH_Unlock();
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Page = GetPage(ADR_StartPage); //=63
	EraseInitStruct.NbPages = numPages; //1 page

	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) == HAL_OK)																						//debug_msg("\n\rXoa Page %X OK",ADR_StartPage);
	  return 1;
	else
	  return 0;
}

uint8_t Flash_ReadByte(uint32_t ADR)
{
	uint8_t Value;
	Value = *(__IO uint8_t *)ADR;
	return Value;
}

uint32_t Flash_ReadWord(uint32_t ADR)
{
	uint32_t Value;
	Value = *(__IO uint32_t *)ADR;
	return Value;
}

uint64_t Flash_ReadDWord(uint32_t ADR)
{
	uint64_t Value;
	Value = *(__IO uint64_t *)ADR;
	return Value;
}

ResultStatus Flash_WriteDWord(uint64_t data64, uint32_t ADR_StartPage)
{
	FLASH_EraseInitTypeDef EraseInitStruct;
	uint32_t eraseStt;
	int8_t	result;

	HAL_FLASH_Unlock();
	// Erase this page
	EraseInitStruct.TypeErase = FLASH_TYPEERASE_PAGES;
	EraseInitStruct.Page = GetPage(ADR_StartPage); //=63
	EraseInitStruct.NbPages = 1;
	if (HAL_FLASHEx_Erase(&EraseInitStruct, &eraseStt) == HAL_OK)
	{
		/*debug_msg("\nErase OK");*/
		if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD,ADR_StartPage, data64) == HAL_OK)
			result = _TRUE;
	}
	HAL_FLASH_Lock();
	result = _FALSE;
	return result;
}

//ResultStatus Flash_Write_DWord(uint64_t data, uint32_t ADR_StartPage){
//	FLASH_EraseInitTypeDef 	EraseInitStruct;
//	uint32_t PageError;
//
//	HAL_FLASH_Unlock();
//	//Erase this page
//	EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
//	EraseInitStruct.Page        = GetPage(ADR_StartPage);	//=63
//	EraseInitStruct.NbPages     = 1;
//	if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK){ /*debug_msg("\n\rErase OK");*/}
//
//	if(HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, ADR_StartPage, data)== HAL_OK)
//		return _TRUE;
//	else
//		return _FALSE;
//
//	HAL_FLASH_Lock();
//}

/**Cách sư dụng**/
//uint32_t epprom_start=0xFF; //phải gán giá trị khác 0 , để địa chỉ các biến liền kề nhau
//uint8_t eppData1=0xFF;
//uint8_t eppData2=0xFF;
//uint8_t eppData3=0xFF;
//uint32_t epprom_end=0xFF;
//
////Hoặc khai báo 1 mảng 32
//uint32_t epprom[10];
//
////Hoặc khai báo 1 struct
//typedef struct{
//  uint32_t eppData0;	//4bytes
//
//  //2 byte liền kề nhau nhưng vẫn chiếm 4 byte địa chỉ
//  uint8_t eppData1;	//1bytes
//  uint8_t eppData2;	//1bytes
//
//  //eppData3 vẫn chiếm 4 byte địa chỉ
//  uint16_t eppData3;	//4bytes
//
//  uint32_t eppData4;	//4bytes
//
//}epprom_str;



