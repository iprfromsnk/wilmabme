#include "ia_spi.h"
#include "accmtr.h"

char (*spi_byte)(char out);	

char default_spi_byte(char out)
{
	return 0;
}

inline void accmtr_select(char accmtr_idx)
{
	switch (accmtr_idx) {
		case 0: ACCMTR_0_SELECT(); break;
		case 1: ACCMTR_1_SELECT(); break;
		case 2: ACCMTR_2_SELECT(); break;
		case 3: ACCMTR_3_SELECT(); break;
		case 4: ACCMTR_4_SELECT(); break;
		default: ACCMTR_4_SELECT();
	}
}

inline void accmtr_deselect(char accmtr_idx)
{
	switch (accmtr_idx) {
		case 0: ACCMTR_0_DESELECT(); break;
		case 1: ACCMTR_1_DESELECT(); break;
		case 2: ACCMTR_2_DESELECT(); break;
		case 3: ACCMTR_3_DESELECT(); break;
		case 4: ACCMTR_4_DESELECT(); break;
		default: ACCMTR_4_DESELECT();
	}
}

inline void use_accmtr(char accmtr_idx)
{
	switch (accmtr_idx) {
		case 0: USE_ACCMTR_0(); break;
		case 1: USE_ACCMTR_1(); break;
		case 2: USE_ACCMTR_2(); break;
		case 3: USE_ACCMTR_3(); break;
		case 4: USE_ACCMTR_4(); break;
		default: USE_ACCMTR_4();
	}
}

void accmtr_bus_init(void)
{
	ia_spi_init();	

	A_SS0_DIR |= (1<<A_SS0_BIT);
	A_SS0_PORT |= (1<<A_SS0_BIT);

	A_SS1_DIR |= (1<<A_SS1_BIT);
	A_SS1_PORT |= (1<<A_SS1_BIT);

	A_SS2_DIR |= (1<<A_SS2_BIT);
	A_SS2_PORT |= (1<<A_SS2_BIT);

	A_SS3_DIR |= (1<<A_SS3_BIT);
	A_SS3_PORT |= (1<<A_SS3_BIT);

	A_SS4_DIR |= (1<<A_SS4_BIT);
	A_SS4_PORT |= (1<<A_SS4_BIT);

	A_INT0_DIR &= ~(1<<A_INT0_BIT);
	A_INT0_PORT |= (1<<A_INT0_BIT);
			
	A_INT1_DIR &= ~(1<<A_INT1_BIT);
	A_INT1_PORT |= (1<<A_INT1_BIT);
	
	A_INT2_DIR &= ~(1<<A_INT2_BIT);
	A_INT2_PORT |= (1<<A_INT2_BIT);
			
	A_INT3_DIR &= ~(1<<A_INT3_BIT);
	A_INT3_PORT |= (1<<A_INT3_BIT);
		
	A_INT4_DIR &= ~(1<<A_INT4_BIT);
	A_INT4_PORT |= (1<<A_INT4_BIT);

	PCICR |= (1<<A_INT0_IE);
}


char accmtr_present(char idx)
{
	char response;

	accmtr_select(idx);
	use_accmtr(idx);

	spi_byte(READ_NOAINC(WHO_AM_I));
	response = spi_byte(0xff);

	accmtr_deselect(idx);

	if (response == 0x3a) return 1;

	return 0;
}

char accmtr_init(char idx)
{
	//accmtr_int_init(idx);					// rendberakjuk a gym. megszakitasahoz tartozo labat

	accmtr_select(idx);					// CS-et lehuzzuk
	use_accmtr(idx);					// beallitjuk a megfelelo spi kezelot

	
	spi_byte(WRITE_NOAINC(CTRL_REG1));			// kikapcs
	spi_byte(POWER_DOWN);

	accmtr_deselect(idx);

	return 0;
}

inline void accmtr_int_enable(int idx)
{
	switch (idx) {
		case 0:
			PCMSK3 |= (1<<PCINT30);
			break;
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			
			break;
	}
}

inline void accmtr_int_disable(int idx)
{
	switch (idx) {
		case 0:
			PCMSK3 &= ~(1<<PCINT30);
			break;
		case 1:
			
			break;
		case 2:
			
			break;
		case 3:
			
			break;
		case 4:
			
			break;
	}
}

char accmtr_meas_start(char idx)
{
	char i;

	accmtr_select(idx);					// CS-et lehuzzuk
	use_accmtr(idx);					// beallitjuk a megfelelo spi kezelot
	
	spi_byte(WRITE_AINC(CTRL_REG1));			 
	spi_byte(POWER_UP | SF_40 | X_EN | Y_EN | Z_EN);	// 3 tengely 40Hz-el
	spi_byte(BDU | BOOT | DRDY);				// olvasasig nincs frissites, IT engedelyezve, kalibralt ertekek betoltese

	accmtr_deselect(idx);
	
	accmtr_int_enable(idx);

	// Ki kell olvasnunk a gyorsulasadatokat, hogy a gym. lehuzza a DRDY labat, es a kovetkezo adag adatnal legyen egy felfuto el
	accmtr_select(idx);
	spi_byte(READ_AINC(OUTX_L));
	for (i=0; i<6; i++) spi_byte(0);
	accmtr_deselect(idx);

	return 0;
}

char accmtr_meas_stop(char idx)
{
	accmtr_int_disable(idx);

	accmtr_select(idx);					// CS-et lehuzzuk
	use_accmtr(idx);					// beallitjuk a megfelelo spi kezelot
	
	spi_byte(WRITE_AINC(CTRL_REG1));			 
	spi_byte(POWER_DOWN);

	accmtr_deselect(idx);

	return 0;
}

void accmtr_read_acc_data(char idx, int16_t *XYZ)
{
	char *xyz;
	unsigned int i;

	xyz = (char *)XYZ;

	accmtr_select(idx);
	use_accmtr(idx);
	
	spi_byte(READ_AINC(OUTX_L));
	for (i=0; i<6; i++) {
		xyz[i] = spi_byte(0);
		}

	accmtr_deselect(idx);
}
