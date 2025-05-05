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

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
#define MAX_HID_OUTPUT_REPORT_SIZE 201
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */
// Static buffer to store latest Output report
static uint8_t g_output_report_buffer[MAX_HID_OUTPUT_REPORT_SIZE];
static UINT g_output_report_length = 0;
static uint8_t g_output_report_ready = 0;
/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
static UX_SLAVE_CLASS_HID *g_hid_instance = UX_NULL;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */

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
  if (hid_event == UX_NULL || hid_event->ux_device_class_hid_event_length < 2)
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

    for (UINT i = 0; i < length; i++)
    {
      printf("Byte[%u] = 0x%02X\n", i, report[i]);
    }

    // Send the report to the host
    status = _ux_device_class_hid_event_set(hid_instance, &hid_event);

    return status;
}

VOID USBX_DEVICE_HID_CUSTOMER_Task(VOID)
{
    uint8_t report[10] = {0};
    report[0]=0x02;

    if (g_output_report_ready)
    {
        printf("Processing OUTPUT report (length = %u)\n", g_output_report_length);
        for (UINT i = 0; i < g_output_report_length; i++)
        {
            //printf("Byte[%u] = 0x%02X\n", i, g_output_report_buffer[i]);
        }

        if (g_output_report_buffer[0]==0xC4)
        {
            report[1] = 0xD4;
            printf("Reset to Default \n");
            if (g_hid_instance != UX_NULL)
            {
            	printf("Set INPUT report (length = %u) \n", sizeof(report));
                USBD_HID_Keyboard_SendReport(g_hid_instance, report, sizeof(report));
            }
        }
        if (g_output_report_buffer[0]==0xC1)
        {
            report[1] = 0xD1;
            printf("Get FW Version \n");
            if (g_hid_instance != UX_NULL)
            {
               printf("Set INPUT report (length = %u) \n", sizeof(report));
               USBD_HID_Keyboard_SendReport(g_hid_instance, report, sizeof(report));
            }
        }


        // Clear the flag after processing
        g_output_report_ready = 0;
    }
}
/* USER CODE END 1 */
