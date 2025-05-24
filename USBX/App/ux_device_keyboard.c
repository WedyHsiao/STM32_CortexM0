/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    ux_device_keyboard.c
  * @author  MCD Application Team
  * @brief   USBX Device HID Keyboard applicative source file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "ux_device_keyboard.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "stm32u0xx.h"
#include "stm32u0xx_hal_flash.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_HID_OUTPUT_REPORT_SIZE 17

#define ADDR_FLASH_PAGE_14    ((uint32_t)0x08007000) /* Base @ of Page 14, 2 Kbytes */
#define ADDR_FLASH_PAGE_127    ((uint32_t)0x0803F800) /* Base @ of Page 127, 2 Kbytes */

#define ADDR_FLASH_PAGE_USE    ((uint32_t)0x08019000) /* Base @ of Page 50, 2 Kbytes */
#define ADDR_FLASH_PAGE_USE_END ((uint32_t)0x0803C000) /* Base @ of Page 120, 2 Kbytes */

#define FLASH_USER_START_ADDR   ADDR_FLASH_PAGE_USE   /* Start @ ADDR_FLASH_PAGE_14 of user Flash area */
#define FLASH_USER_END_ADDR     (ADDR_FLASH_PAGE_USE_END + FLASH_PAGE_SIZE - 1)   /* End @  ADDR_FLASH_PAGE_127 of user Flash area */

#define DATA_32                 ((uint32_t)0x12345678)
#define DATA_64                 ((uint64_t)0x1234567812345678)

#define FLASH_WRITE_HEADER_LEN   16
#define FLASH_WRITE_DATA_LEN   16

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// Static buffer to store latest Output report
static uint8_t g_output_report_buffer[MAX_HID_OUTPUT_REPORT_SIZE];
static UINT g_output_report_length = 0;
static uint8_t g_output_report_ready = 0;
static uint8_t Header[16] __attribute__((aligned(8))); // align Header on an 8-byte boundary:
static uint8_t Data [16] __attribute__((aligned(8))); //Data is 8-byte aligned
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
static UX_SLAVE_CLASS_HID *g_hid_instance = UX_NULL;

uint32_t FirstPage = 0, NbOfPages = 0;
uint32_t Address = 0, PageError = 0;
__IO uint32_t MemoryProgramStatus = 0;
__IO uint32_t data32 = 0;

uint16_t blocks =0;
uint8_t read_buffer[100];

static FLASH_EraseInitTypeDef EraseInitStruct; /*Variable used for Erase procedure*/

int quater_sec=0;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
static uint32_t GetPage(uint32_t Address);
/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  USBD_HID_Keyboard_Activate
  *         This function is called when insertion of a HID Keyboard device.
  * @param  hid_instance: Pointer to the hid class instance.
  * @retval none
  */
VOID USBD_HID_Keyboard_Activate(VOID *hid_instance)
{
  /* USER CODE BEGIN USBD_HID_Keyboard_Activate */
  g_hid_instance = (UX_SLAVE_CLASS_HID *)hid_instance;
  /* USER CODE END USBD_HID_Keyboard_Activate */

  return;
}

/**
  * @brief  USBD_HID_Keyboard_Deactivate
  *         This function is called when extraction of a HID Keyboard device.
  * @param  hid_instance: Pointer to the hid class instance.
  * @retval none
  */
VOID USBD_HID_Keyboard_Deactivate(VOID *hid_instance)
{
  /* USER CODE BEGIN USBD_HID_Keyboard_Deactivate */
  g_hid_instance = UX_NULL;
  /* USER CODE END USBD_HID_Keyboard_Deactivate */

  return;
}

/**
  * @brief  USBD_HID_Keyboard_SetReport
  *         This function is invoked when the host sends a HID SET_REPORT
  *         to the application over Endpoint 0.
  * @param  hid_instance: Pointer to the hid class instance.
  * @param  hid_event: Pointer to structure of the hid event.
  * @retval status
  */
UINT USBD_HID_Keyboard_SetReport(UX_SLAVE_CLASS_HID *hid_instance,
                                 UX_SLAVE_CLASS_HID_EVENT *hid_event)
{
  UINT status = UX_SUCCESS;

  /* USER CODE BEGIN USBD_HID_Keyboard_SetReport */
  UX_PARAMETER_NOT_USED(hid_instance);
  UX_PARAMETER_NOT_USED(hid_event);

  //Receive Output report from PC
  if (hid_event == UX_NULL || hid_event->ux_device_class_hid_event_length < 1)
          return UX_ERROR;

      uint8_t report_id = hid_event->ux_device_class_hid_event_buffer[0];
      uint8_t *data = &hid_event->ux_device_class_hid_event_buffer[1];
      UINT data_len = hid_event->ux_device_class_hid_event_length - 1;

      if (report_id == 0x02 && data_len <= MAX_HID_OUTPUT_REPORT_SIZE)
      {
          // Copy the data to global buffer for later processing
          memcpy(g_output_report_buffer, data, data_len);
          g_output_report_length = data_len;
          g_output_report_ready = 1;
      }
  /* USER CODE END USBD_HID_Keyboard_SetReport */

  return status;
}

/**
  * @brief  USBD_HID_Keyboard_GetReport
  *         This function is invoked when host is requesting event through
  *         control GET_REPORT request.
  * @param  hid_instance: Pointer to the hid class instance.
  * @param  hid_event: Pointer to structure of the hid event.
  * @retval status
  */
UINT USBD_HID_Keyboard_GetReport(UX_SLAVE_CLASS_HID *hid_instance,
                                 UX_SLAVE_CLASS_HID_EVENT *hid_event)
{
  UINT status = UX_SUCCESS;

  /* USER CODE BEGIN USBD_HID_Keyboard_GetReport */
  UX_PARAMETER_NOT_USED(hid_instance);
  UX_PARAMETER_NOT_USED(hid_event);
  /* USER CODE END USBD_HID_Keyboard_GetReport */

  return status;
}

/* USER CODE BEGIN 1 */
UINT USBD_HID_Keyboard_SendReport(UX_SLAVE_CLASS_HID *hid_instance, uint8_t *report, UINT length)
{
    UX_SLAVE_CLASS_HID_EVENT hid_event;
    UINT status;

    // Validate inputs
    if (hid_instance == UX_NULL || report == UX_NULL || length == 0)
        return UX_ERROR;

    // Prepare the HID event
    hid_event.ux_device_class_hid_event_report_id = 0; // Use report ID 0 for single report
    hid_event.ux_device_class_hid_event_report_type = UX_DEVICE_CLASS_HID_REPORT_TYPE_INPUT;
    hid_event.ux_device_class_hid_event_length = length;
    
    // Copy the report data to the event buffer
    memcpy(hid_event.ux_device_class_hid_event_buffer, report, length);

    printf("Set INPUT report:");
    for (UINT i = 0; i < length; i++)
    {
      printf("Byte[%u] = 0x%02X,", i, report[i]);
    }
    printf("\n");

    // Send the report to the host
    status = _ux_device_class_hid_event_set(hid_instance, &hid_event);

    return status;
}

/**
  * @brief  Gets the page of a given address
  * @param  Addr: Address of the FLASH Memory
  * @retval The page of a given address
  */
static uint32_t GetPage(uint32_t Addr)
{
  return (Addr - FLASH_BASE) / FLASH_PAGE_SIZE;;
}

void Erase_Flash_Page(void)
{
	/* Clear OPTVERR bit set on virgin samples */
	  __HAL_FLASH_CLEAR_FLAG(FLASH_FLAG_OPTVERR);

	  /* Erase the user Flash area
	    (area defined by FLASH_USER_START_ADDR and FLASH_USER_END_ADDR) ***********/

	  /* Get the 1st page to erase */
	  FirstPage = GetPage(FLASH_USER_START_ADDR);
	  printf("First Page %lu\n",FirstPage);

	  /* Get the number of pages to erase from 1st page */
	  NbOfPages = GetPage(FLASH_USER_END_ADDR) - FirstPage + 1;
	  printf("NbOfPages: %lu\n",NbOfPages);

	  /* Fill EraseInit structure*/
	  EraseInitStruct.TypeErase   = FLASH_TYPEERASE_PAGES;
	  EraseInitStruct.Page        = FirstPage;
	  EraseInitStruct.NbPages     = NbOfPages;

	  /* Note: If an erase operation in Flash memory also concerns data in the data or instruction cache,
	     you have to make sure that these data are rewritten before they are accessed during code
	     execution. If this cannot be done safely, it is recommended to flush the caches by setting the
	     DCRST and ICRST bits in the FLASH_CR register. */
	  if (HAL_FLASHEx_Erase(&EraseInitStruct, &PageError) != HAL_OK)
	  {
	    /*
	      Error occurred while page erase.
	      User can add here some code to deal with this error.
	      PageError will contain the faulty page and then to know the code error on this page,
	      user can call function 'HAL_FLASH_GetError()'
	    */
	    /* Infinite loop */
		printf("Erase Flash data failed");
	  }
}

HAL_StatusTypeDef Flash_Write64(uint32_t startAddress, const uint8_t *data, uint32_t length)
{
    if (startAddress % 8 != 0) {
        return HAL_ERROR;  // Must be 64-bit aligned
    }

    if ((uint32_t)data % 8 != 0) {
        // Optional: ensure source buffer is 8-byte aligned if using casting
        return HAL_ERROR;
    }

    HAL_StatusTypeDef status;
    uint32_t address = startAddress;

    // Number of 64-bit words
    uint32_t numDoubleWords = (length + 7) / 8;
    const uint64_t *data64 = (const uint64_t *)data;

    for (uint32_t i = 0; i < numDoubleWords; i++) {
       status = HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, address, data64[i]);
       if (status != HAL_OK) {
          printf("Write Flash data failed\n");
          HAL_FLASH_Lock();
          return status;
       }
       address += 8;
     }
     //HAL_FLASH_Lock();
   return HAL_OK;
}

void flash_read(uint32_t start_addr, uint8_t *dest_buf, size_t len)
{
    // Make sure start_addr is inside the flash memory region!
    const uint8_t *flash_ptr = (const uint8_t *)start_addr;

    // Simply copy bytes from flash to destination buffer
    memcpy(dest_buf, flash_ptr, len);
}

VOID USBX_DEVICE_HID_CUSTOMER_Task(VOID)
{
    uint8_t report[10] = {0}; // Use for input report
    report[0]=0x02; // Input Report ID = 0x02

    if (g_output_report_ready)
    {
        //printf("Processing OUTPUT report (length = %u): ", g_output_report_length);
        /*for (UINT i = 0; i < g_output_report_length; i++)
        {
        	printf("0x%02X, ", g_output_report_buffer[i]);
        }
        printf("\n");*/

        if (g_output_report_buffer[0]==0xC1)
        {
           report[1] = 0xD1;
           printf("[Get FW Version]: ");
           if (g_hid_instance != UX_NULL)
           {
              USBD_HID_Keyboard_SendReport(g_hid_instance, report, sizeof(report));
           }
        }
        if (g_output_report_buffer[0]==0xC4)
        {
            report[1] = 0xD4;
            printf("[Reset to Default]: ");
            if (g_hid_instance != UX_NULL)
            {
                USBD_HID_Keyboard_SendReport(g_hid_instance, report, sizeof(report));
            }
        }
        if (g_output_report_buffer[0]==0xE0)
        {
            printf("[Erase Data]\n");
            quater_sec=0;
            memset(Data,0xFF,16);
            memset(Header,0xFF,16);
            /* Unlock the Flash to enable the flash control register access *************/
            HAL_FLASH_Unlock();
            Erase_Flash_Page();
        }
        if (g_output_report_buffer[0]==0xE1)
        {
        	printf("[Transfer]\n");
        }
        if (g_output_report_buffer[0]==0xE2)
        {
            printf("[Finished]\n");
            HAL_FLASH_Lock();
            quater_sec=0;

            // just test for read out
            // Read 100 bytes starting from FLASH_READ_START_ADDR
            //flash_read(FLASH_USER_START_ADDR+16, read_buffer, sizeof(read_buffer));
            for (size_t num_block=0;num_block<blocks;num_block++)
            {
			flash_read(FLASH_USER_START_ADDR+16+(100*num_block), read_buffer, sizeof(read_buffer));
			printf("Block ID:");
            for (size_t i = 0; i < 3; i++) {
                printf("%02X ", read_buffer[i]);
            }
            printf("\n");
            }
        }
        if (g_output_report_buffer[0]==0x10)
        {
            printf(" Header \n");
            memcpy(Header,&g_output_report_buffer[0],16);
            for (UINT i = 0; i < sizeof(Header); i++)
            {
              printf("Key[%u] = 0x%02X,", i, Header[i]);
            }
            blocks = ((uint16_t)Header[2] << 8) | Header[3];
            printf("Num of bolcks: %u\n", blocks);
            HAL_StatusTypeDef status = Flash_Write64(ADDR_FLASH_PAGE_USE, Header, FLASH_WRITE_HEADER_LEN);
            if (status != HAL_OK) {
                printf("Flash write Header failed\n");
            }

        }
        if (g_output_report_buffer[0]==0xFF)
        {
          uint32_t offset = 16 + quater_sec * 16;
          uint32_t FlashAddress = FLASH_USER_START_ADDR + offset;
          memcpy(Data,&g_output_report_buffer[1],16);

          /*printf("Data \n");
          for (UINT i = 0; i < sizeof(Data); i++)
          {
            printf("Data[%u] = 0x%02X,", i, Data[i]);
          }*/

          HAL_StatusTypeDef status = Flash_Write64(FlashAddress, Data, FLASH_WRITE_DATA_LEN);
          if (status != HAL_OK) {
             printf("Flash write Data failed\n");
          }
          quater_sec++;
        }

        // Clear the flag after processing
        g_output_report_ready = 0;
    }
}
/* USER CODE END 1 */
