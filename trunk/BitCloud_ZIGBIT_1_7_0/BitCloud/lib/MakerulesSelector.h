#if !defined(BOARD_SAM7X_EK) && !defined(BOARD_RAVEN) && !defined(BOARD_USB_DONGLE) && !defined(BOARD_STK600) && !defined(BOARD_MESHBEAN) && !defined(BOARD_RCB128RFA1)
  #error unknown BOARD
#endif
#if !defined(STACK_TYPE_ALL) && !defined(STACK_TYPE_COORDINATOR) && !defined(STACK_TYPE_ROUTER) && !defined(STACK_TYPE_ENDDEVICE)
  #error unknown STACK_TYPE
#endif
#if !defined(SECURITY_MODE_NONE) && !defined(SECURITY_MODE_STANDART)
  #error unknown SECURITY_MODE
#endif
#ifdef BOARD_SAM7X_EK
  #if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
    #error unknown RFCHIP
  #endif
  #if !defined(AT91SAM7X256)
    #error unknown HAL
  #endif
  #if !defined(HAL_18d432MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_RAVEN
  #if !defined(AT86RF230B)
    #error unknown RFCHIP
  #endif
  #if !defined(ATMEGA1284)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_USB_DONGLE
  #if !defined(AT86RF230B)
    #error unknown RFCHIP
  #endif
  #if !defined(AT90USB1287)
    #error unknown HAL
  #endif
  #if !defined(HAL_8MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_STK600
  #if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
    #error unknown RFCHIP
  #endif
  #if !defined(ATXMEGA256A3) && !defined(ATXMEGA128A1)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz) && !defined(HAL_12MHz) && !defined(HAL_16MHz) && !defined(HAL_32MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_MESHBEAN
  #if !defined(AT86RF230) && !defined(AT86RF230B) && !defined(AT86RF231) && !defined(AT86RF212)
    #error unknown RFCHIP
  #endif
  #if !defined(ATMEGA1281) && !defined(ATMEGA2561)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#ifdef BOARD_RCB128RFA1
  #if !defined(ATMEGA128RFA1)
    #error unknown RFCHIP
  #endif
  #if !defined(ATMEGA128RFA1)
    #error unknown HAL
  #endif
  #if !defined(HAL_4MHz) && !defined(HAL_8MHz)
    #error unknown HAL_FREQUENCY
  #endif
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230) && defined(HAL_18d432MHz)
  #include <MakerulesBc_All_Sam7xEkRf2xx_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230B) && defined(HAL_18d432MHz)
  #include <MakerulesBc_All_Sam7xEkRf2xx_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF231) && defined(HAL_18d432MHz)
  #include <MakerulesBc_All_Sam7xEkRf2xx_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF212) && defined(HAL_18d432MHz)
  #include <MakerulesBc_All_Sam7xEkRf2xx_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230) && defined(HAL_18d432MHz)
  #include <MakerulesBc_All_Sec_Sam7xEkRf2xx_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230B) && defined(HAL_18d432MHz)
  #include <MakerulesBc_All_Sec_Sam7xEkRf2xx_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF231) && defined(HAL_18d432MHz)
  #include <MakerulesBc_All_Sec_Sam7xEkRf2xx_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF212) && defined(HAL_18d432MHz)
  #include <MakerulesBc_All_Sec_Sam7xEkRf2xx_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Coordinator_Sam7xEkRf2xx_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230B) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Coordinator_Sam7xEkRf2xx_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF231) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Coordinator_Sam7xEkRf2xx_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF212) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Coordinator_Sam7xEkRf2xx_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Coordinator_Sec_Sam7xEkRf2xx_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230B) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Coordinator_Sec_Sam7xEkRf2xx_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF231) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Coordinator_Sec_Sam7xEkRf2xx_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF212) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Coordinator_Sec_Sam7xEkRf2xx_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Router_Sam7xEkRf2xx_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230B) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Router_Sam7xEkRf2xx_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF231) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Router_Sam7xEkRf2xx_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF212) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Router_Sam7xEkRf2xx_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Router_Sec_Sam7xEkRf2xx_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230B) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Router_Sec_Sam7xEkRf2xx_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF231) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Router_Sec_Sam7xEkRf2xx_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF212) && defined(HAL_18d432MHz)
  #include <MakerulesBc_Router_Sec_Sam7xEkRf2xx_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230) && defined(HAL_18d432MHz)
  #include <MakerulesBc_EndDevice_Sam7xEkRf2xx_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230B) && defined(HAL_18d432MHz)
  #include <MakerulesBc_EndDevice_Sam7xEkRf2xx_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF231) && defined(HAL_18d432MHz)
  #include <MakerulesBc_EndDevice_Sam7xEkRf2xx_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF212) && defined(HAL_18d432MHz)
  #include <MakerulesBc_EndDevice_Sam7xEkRf2xx_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230) && defined(HAL_18d432MHz)
  #include <MakerulesBc_EndDevice_Sec_Sam7xEkRf2xx_At91sam7x256_Rf230_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF230B) && defined(HAL_18d432MHz)
  #include <MakerulesBc_EndDevice_Sec_Sam7xEkRf2xx_At91sam7x256_Rf230B_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF231) && defined(HAL_18d432MHz)
  #include <MakerulesBc_EndDevice_Sec_Sam7xEkRf2xx_At91sam7x256_Rf231_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_SAM7X_EK) && defined(AT91SAM7X256) && defined(AT86RF212) && defined(HAL_18d432MHz)
  #include <MakerulesBc_EndDevice_Sec_Sam7xEkRf2xx_At91sam7x256_Rf212_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Raven_Atmega1284_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Raven_Atmega1284_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_Raven_Atmega1284_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_Raven_Atmega1284_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Raven_Atmega1284_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Raven_Atmega1284_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_Raven_Atmega1284_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_Raven_Atmega1284_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Raven_Atmega1284_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Raven_Atmega1284_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_Raven_Atmega1284_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_Raven_Atmega1284_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Raven_Atmega1284_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Raven_Atmega1284_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_Raven_Atmega1284_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RAVEN) && defined(ATMEGA1284) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_Raven_Atmega1284_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_USB_DONGLE) && defined(AT90USB1287) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_AtmlUsbDongle_At90usb1287_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_USB_DONGLE) && defined(AT90USB1287) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_AtmlUsbDongle_At90usb1287_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_USB_DONGLE) && defined(AT90USB1287) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_AtmlUsbDongle_At90usb1287_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_USB_DONGLE) && defined(AT90USB1287) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlUsbDongle_At90usb1287_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_USB_DONGLE) && defined(AT90USB1287) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_AtmlUsbDongle_At90usb1287_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_USB_DONGLE) && defined(AT90USB1287) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_AtmlUsbDongle_At90usb1287_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_USB_DONGLE) && defined(AT90USB1287) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_AtmlUsbDongle_At90usb1287_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_USB_DONGLE) && defined(AT90USB1287) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlUsbDongle_At90usb1287_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega256a3_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_All_AtmlStk600Rf2xx_Atxmega128a1_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_All_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega256a3_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_AtmlStk600Rf2xx_Atxmega128a1_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_Coordinator_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega256a3_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_AtmlStk600Rf2xx_Atxmega128a1_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_Router_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega256a3_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_AtmlStk600Rf2xx_Atxmega128a1_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA256A3) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega256a3_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF230B) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf230B_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF231) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf231_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_12MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_12MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_16MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_16MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_STK600) && defined(ATXMEGA128A1) && defined(AT86RF212) && defined(HAL_32MHz)
  #include <MakerulesBc_EndDevice_Sec_AtmlStk600Rf2xx_Atxmega128a1_Rf212_32MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_All_ZigBit_Atmega1281_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_All_ZigBit_Atmega1281_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_ZigBit_Atmega1281_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_ZigBit_Atmega1281_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_All_ZigBit_Atmega1281_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_All_ZigBit_Atmega1281_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_All_ZigBit_Atmega1281_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_All_ZigBit_Atmega1281_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_All_ZigBit_Atmega2561_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_All_ZigBit_Atmega2561_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_ZigBit_Atmega2561_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_ZigBit_Atmega2561_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_All_ZigBit_Atmega2561_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_All_ZigBit_Atmega2561_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_All_ZigBit_Atmega2561_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_All_ZigBit_Atmega2561_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega1281_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega1281_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega1281_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega1281_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega1281_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega1281_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega1281_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega1281_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega2561_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega2561_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega2561_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega2561_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega2561_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega2561_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega2561_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_ZigBit_Atmega2561_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega1281_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega1281_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega1281_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega1281_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega1281_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega1281_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega1281_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega1281_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega2561_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega2561_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega2561_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega2561_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega2561_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega2561_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega2561_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_ZigBit_Atmega2561_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega1281_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega1281_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega1281_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega1281_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega1281_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega1281_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega1281_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega1281_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega2561_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega2561_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega2561_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega2561_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega2561_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega2561_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega2561_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_ZigBit_Atmega2561_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega1281_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega1281_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega1281_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega1281_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega1281_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega1281_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega1281_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega1281_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega2561_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega2561_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega2561_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega2561_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega2561_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega2561_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega2561_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_ZigBit_Atmega2561_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega1281_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega1281_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega1281_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega1281_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega1281_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega1281_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega1281_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega1281_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega2561_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega2561_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega2561_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega2561_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega2561_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega2561_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega2561_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_ZigBit_Atmega2561_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega1281_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega1281_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega1281_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega1281_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega1281_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega1281_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega1281_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega1281_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega2561_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega2561_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega2561_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega2561_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega2561_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega2561_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega2561_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_ZigBit_Atmega2561_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega1281_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega1281_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega1281_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega1281_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega1281_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega1281_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega1281_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA1281) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega1281_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega2561_Rf230_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega2561_Rf230_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega2561_Rf230B_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF230B) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega2561_Rf230B_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega2561_Rf231_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF231) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega2561_Rf231_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega2561_Rf212_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_MESHBEAN) && defined(ATMEGA2561) && defined(AT86RF212) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_ZigBit_Atmega2561_Rf212_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_NONE) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_4MHz)
  #include <MakerulesBc_All_Sec_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ALL) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_8MHz)
  #include <MakerulesBc_All_Sec_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_NONE) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_4MHz)
  #include <MakerulesBc_Coordinator_Sec_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_COORDINATOR) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_8MHz)
  #include <MakerulesBc_Coordinator_Sec_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_NONE) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_4MHz)
  #include <MakerulesBc_Router_Sec_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ROUTER) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_8MHz)
  #include <MakerulesBc_Router_Sec_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_NONE) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_8MHz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_4MHz)
  #include <MakerulesBc_EndDevice_Sec_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_4Mhz_Iar.h>
#endif
#if defined(STACK_TYPE_ENDDEVICE) && defined(SECURITY_MODE_STANDART) && defined(BOARD_RCB128RFA1) && defined(ATMEGA128RFA1) && defined(ATMEGA128RFA1) && defined(HAL_8MHz)
  #include <MakerulesBc_EndDevice_Sec_Atmega128rfa1_Atmega128rfa1_Atmega128rfa1_8MHz_Iar.h>
#endif
