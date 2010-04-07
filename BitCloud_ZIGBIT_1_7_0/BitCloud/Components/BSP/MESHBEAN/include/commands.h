#ifndef _COMMANDS_H_
#define _COMMANDS_H_

#define START_SMEAS 0x6D	//!command code of single measurement (m)
#define START_CMEAS 0x63	//!command code of continuous measurement (c)
#define STOP_MEAS	0x73	//!stop measurement, prepare to power down (s)

#define GET_NR_CHAN	0x6E	//!get number of channels (n)
#define GET_DEV_ID	0x69	//!get device id (SUPPLIER_ID, FUNCTIONAL_ID, VARIANT_ID,SERIAL_NR) (i)
#define READ_DATA	0x72	//!read the result of the measurement (r)

#define SPEC_COMM	0x78	//!special command from the coordinator (x)

#endif //_COMMANDS_H_
