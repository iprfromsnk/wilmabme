#ifndef _ACCMTR_H_
#define _ACCMTR_H_

#include "stdint.h"
#include "ia_spi.h"


#define BIT_RW			7	/* Read/Write bit */
#define BIT_MS			6	/* Address auto increment bit */

/* LIS3LV02DQ registers */

#define WHO_AM_I			0x0F
#define OFFSET_X			0x16	/* Loaded at boot */
#define OFFSET_Y			0x17	/* Loaded at boot */
#define OFFSET_Z			0x18	/* Loaded at boot */
#define GAIN_X				0x19	/* Loaded at boot */
#define GAIN_Y				0x1A	/* Loaded at boot */
#define GAIN_Z				0x1B	/* Loaded at boot */
#define CTRL_REG1			0x20
#define CTRL_REG2			0x21
#define CTRL_REG3			0x22
#define HP_FILTER_RESET		0x23	/* Dummy */
#define STATUS_REG			0x27
#define OUTX_L				0x28
#define OUTX_H				0x29
#define OUTY_L				0x2A
#define OUTY_H				0x2B
#define OUTZ_L				0x2C
#define OUTZ_H				0x2D
#define FF_WU_CFG			0x30
#define FF_WU_SRC			0x31
#define FF_WU_ACK			0x32
#define FF_WU_THS_L			0x34
#define FF_WU_THS_H			0x35
#define FF_WU_DURATION		0x36
#define DD_CFG				0x38
#define DD_SRC				0x39
#define DD_ACK				0x3A
#define DD_THSI_L			0x3C
#define DD_THSI_H			0x3D
#define DD_THSE_L			0x3E
#define DD_THSE_H			0x3F

/* register bit constants */

/* CTRL_REG1 */
#define POWER_UP	(3<<6)
#define POWER_DOWN	(0<<6)
#define SF_40		(0<<4)
#define SF_160		(1<<4)
#define SF_640		(2<<4)
#define SF_2560		(3<<4)
#define SELF_TEST 	(1<<3)
#define Z_EN		(1<<2)
#define Y_EN		(1<<1)
#define X_EN		(1<<0)

/*CTRL_REG2 */
#define FS			(1<<7)
#define BDU			(1<<6)
#define BLE			(1<<5)
#define BOOT		(1<<4)
#define IEN			(1<<3)
#define DRDY		(1<<2)
#define SIM			(1<<1)
#define DAS			(1<<0)

/* register access modes */
#define READ_NOAINC(regname)	((1<<BIT_RW) | regname)			/* read without address autoincrement */
#define READ_AINC(regname)	((1<<BIT_RW) | (1<<BIT_MS) | regname)	/* read with address autoincrement */
#define WRITE_NOAINC(regname)	(regname)				/* write without address autoincrement */
#define WRITE_AINC(regname)	((1<<BIT_MS) | regname)			/* write with address autoincrement */

// accelerometer CS pins
#define A_SS0_DIR			DDRD
#define A_SS0_PIN			PIND
#define A_SS0_PORT			PORTD
#define A_SS0_BIT			5

#define A_SS1_DIR			DDRC
#define A_SS1_PIN			PINC
#define A_SS1_PORT			PORTC
#define A_SS1_BIT			0

#define A_SS2_DIR			DDRC
#define A_SS2_PIN			PINC
#define A_SS2_PORT			PORTC
#define A_SS2_BIT			1

#define A_SS3_DIR			DDRC
#define A_SS3_PIN			PINC
#define A_SS3_PORT			PORTC
#define A_SS3_BIT			2

#define A_SS4_DIR			DDRC
#define A_SS4_PIN			PINC
#define A_SS4_PORT			PORTC
#define A_SS4_BIT			3

// accelerometer INT pins
#define A_INT0_DIR			DDRD
#define A_INT0_PIN			PIND
#define A_INT0_PORT			PORTD
#define A_INT0_BIT			6
#define A_INT0_MASK			PCMSK3
#define A_INT0_INT			PCINT30
#define A_INT0_IE			PCIE3

#define A_INT1_DIR			DDRC
#define A_INT1_PIN			PINC
#define A_INT1_PORT			PORTC
#define A_INT1_BIT			4

#define A_INT2_DIR			DDRC
#define A_INT2_PIN			PINC
#define A_INT2_PORT			PORTC
#define A_INT2_BIT			5

#define A_INT3_DIR			DDRC
#define A_INT3_PIN			PINC
#define A_INT3_PORT			PORTC
#define A_INT3_BIT			6

#define A_INT4_DIR			DDRC
#define A_INT4_PIN			PINC
#define A_INT4_PORT			PORTC
#define A_INT4_BIT			7



// Accelerometer SS defs
#define ACCMTR_0_SELECT()		A_SS0_PORT &= ~(1<<A_SS0_BIT)
#define ACCMTR_0_DESELECT()		A_SS0_PORT |= (1<<A_SS0_BIT)

#define ACCMTR_1_SELECT()		A_SS1_PORT &= ~(1<<A_SS1_BIT)
#define ACCMTR_1_DESELECT()		A_SS1_PORT |= (1<<A_SS1_BIT)

#define ACCMTR_2_SELECT()		A_SS2_PORT &= ~(1<<A_SS2_BIT)
#define ACCMTR_2_DESELECT()		A_SS2_PORT |= (1<<A_SS2_BIT)

#define ACCMTR_3_SELECT()		A_SS3_PORT &= ~(1<<A_SS3_BIT)
#define ACCMTR_3_DESELECT()		A_SS3_PORT |= (1<<A_SS3_BIT)

#define ACCMTR_4_SELECT()		A_SS4_PORT &= ~(1<<A_SS4_BIT)
#define ACCMTR_4_DESELECT()		A_SS4_PORT |= (1<<A_SS4_BIT)

// default spi handler
char default_spi_byte(char out);

// pointer to the current spi handler function
extern char (*spi_byte)(char out);	

// makrok a gyorsulasmerok spi fv-einek beallitasara
#define USE_ACCMTR_0()		spi_byte = ia_spi_byte
#define USE_ACCMTR_1()		spi_byte = default_spi_byte
#define USE_ACCMTR_2()		spi_byte = default_spi_byte
#define USE_ACCMTR_3()		spi_byte = default_spi_byte
#define USE_ACCMTR_4()		spi_byte = default_spi_byte

void accmtr_bus_init(void);

/********************************************************************
 * int accmtr_present(int accmtr_idx);
 *
 * DESCRIPTION:
 * 	Checks if the given accelerometer is connected or not
 *
 * PARAM:
 * 	accmtr_idx: accelerometer id
 *
 * RETURN:
 * 	1, if connected
 * 	0, if not connected
 *
 * NOTE:
 * 	1-4:  external sensor
 *	4:    on-board sensor
 *******************************************************************/
char accmtr_present(char accmtr_idx);


/********************************************************************
 * void accmtr_init(int accmtr_idx)
 *
 * DESCRIPTION:
 *	Switches on the accelerometer, enables all 3 channels and sets
 *	sample rate to 40 Hz
 *
 * PARAM:
 * 	accmtr_idx: accelerometer id
 *******************************************************************/
char accmtr_init(char accmtr_idx);

/* start measurement */
char accmtr_meas_start(char accmtr_idx);

/* stop measurement */
char accmtr_meas_stop(char accmtr_idx);


/********************************************************************
 * void accmtr_read_acc_data(int accmtr_idx, short int *XYZ)
 *
 * DESCRIPTION:
 * 	Reads acceleration data.
 *
 * PARAM:
 * 	accmtr_idx: accelerometer id
 * 	XYZ: array of at least 3 short ints
 *
 * OUTPUT:
 * 	XYZ: acceleration data
 *******************************************************************/
void accmtr_read_acc_data(char accmtr_idx, int16_t *XYZ);

char accmtr_get_status(char accmtr_idx);

/*
 * HOW TO USE ACCMTR.H
 *
 * accmtr_bus_init();
 * accmtr_init(0);
 * accmtr_meas_start(0);
 * accmtr_read_acc_data(0, xyz);
 * accmtr_meas_stop(0);
 */

void accmtr_select(char accmtr_idx);

#endif
