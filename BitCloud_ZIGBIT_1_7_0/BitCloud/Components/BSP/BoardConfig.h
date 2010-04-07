#ifdef BOARD_MESHBEAN
  #define _BUTTONS_
  #define _TEMPERATURE_SENSOR_
  #define _LIGHT_SENSOR_
  #define _BATTERY_SENSOR_
  #define _LEDS_
  #define _SLIDERS_
#endif
#ifdef BOARD_RAVEN
  #define _LCD_
#endif
#ifdef BOARD_USB_DONGLE
  #define _LEDS_
#endif
#ifdef BOARD_STK600
  #define _BUTTONS_
  #define _LEDS_
#endif
#ifdef BOARD_STK500
  #define _BUTTONS_
  #define _LEDS_
#endif
#ifdef BOARD_MESHBEAN_TURBO
  #define _LEDS_
  #define _SLIDERS_
  #define _BUTTONS_
#endif
#ifdef BOARD_MESHBEAN_LAN
  #define _LEDS_
  #define _BUTTONS_
#endif
#ifdef BOARD_SAM7X_EK
  #define _LEDS_
  #define _JOYSTICK_
#endif
#ifdef BOARD_HON_IQL
  #define _LEDS_
  #define _BUTTONS_
  #define _RS485CONTROL_
#endif
#ifdef BOARD_HON_ALERTON
  #define _LEDS_
  #define _BUTTONS_
  #define _RS485CONTROL_
  #define _USBCONTROL_
#endif
#ifdef BOARD_RCB128RFA1
  #define _LEDS_
  #define _BUTTONS_
#endif
