/*
 * TMS320C5505 DSP interrupt management
 * 
 * 
 **/
 
#include <csl_intc.h>
#include <csl_general.h>
#include "usbstk5505.h"
#include "aic3204.h"
#include "usbstk5505_gpio.h"
#include "common.h"

/** Interrupt Service Routine */
interrupt void spiISR(void);
interrupt void gpioISR(void);

/* Reference the start of the interrupt vector table */
/* This symbol is defined in file vectors.asm       */
extern void VECSTART(void);

static Uint8 spi_ISR_hit_cnt = 0;
static Uint8 mode_toggle = SINGLE_MODE;

void toggle_dual_mode(Uint8 mode)
{
	if (mode == SINGLE_MODE) {
		if ((IODATAOUT2 & MUX_SEL_PINS_B_A_MASK) == MOB_MUX_SEL_PINS_B_A) {
			// IN2L & IN1_L to LADC_P/RADC_P respectively, through 20 kohm			
			AIC3204_II_rset( 0, 1 );		// Select page 1
			AIC3204_II_rset( 52, 0x40 );	// Mob, Left
			AIC3204_II_rset( 55, 0x40 );	// Mob, Right
		} else if ((IODATAOUT2 & MUX_SEL_PINS_B_A_MASK) == TEL_MUX_SEL_PINS_B_A) {
			// IN2L & IN3_L to LADC_P/RADC_P respectively, through 20 kohm			
			AIC3204_II_rset( 0, 1 );		// Select page 1
			AIC3204_II_rset( 52, 0x04 );	// Tel, Left
			AIC3204_II_rset( 55, 0x04 );	// Tel, Right
		} else {
			AIC3204_II_rset( 0, 1 ); 		// Select page 1
			AIC3204_II_rset( 52, 0x10 );	// PC, left
			AIC3204_II_rset( 55, 0x10 );	// PC, Right
		}
	} else {
		if ((IODATAOUT2 & MUX_SEL_PINS_B_A_MASK) == MOB_MUX_SEL_PINS_B_A) {
			// IN2L & IN1_L to LADC_P/RADC_P respectively, through 20 kohm			
			AIC3204_II_rset( 0, 1 );		// Select page 1
			AIC3204_II_rset( 52, 0x10 );	// PC, Left
			AIC3204_II_rset( 55, 0x40 );	// Mob, Right
		} else if ((IODATAOUT2 & MUX_SEL_PINS_B_A_MASK) == TEL_MUX_SEL_PINS_B_A) {
			// IN2L & IN3_L to LADC_P/RADC_P respectively, through 20 kohm			
			AIC3204_II_rset( 0, 1 );		// Select page 1
			AIC3204_II_rset( 52, 0x10 );	// PC, Left
			AIC3204_II_rset( 55, 0x04 );	// Tel, Right
		} else {
			AIC3204_II_rset( 0, 1 ); 		// Select page 1
			AIC3204_II_rset( 52, 0x10 );	// PC, left
			AIC3204_II_rset( 55, 0x10 );	// PC, Right
		}
	}
}


void enable_irq(unsigned char eventid, IRQ_IsrPtr irq_handle)
{
	CSL_IRQ_Config irqConfig;
	Bool IntStatus;
	
	/* IRQ_config */
	irqConfig.funcAddr = irq_handle;
	IRQ_config(eventid, &irqConfig);

	/* Clear any pending Interrupt */
	IRQ_clear(eventid);
	IRQ_test(eventid, &IntStatus);
	IRQ_map(eventid);

	/* Register the ISR */
	IRQ_plug(eventid, irq_handle);

	/* Enabling Interrupt */
	IRQ_enable(eventid);
}

void c5505_register_irq(void)
{
	/* Disable interrupt */
    IRQ_globalDisable();

	/* Clear any pending interrupts */
	IRQ_clearAll();

	/* Disable all the interrupts */
	IRQ_disableAll();

    /* Initialize Interrupt Vector table */
	IRQ_setVecs((Uint32)(&VECSTART));

	/* Enable IRQ and register the interrupt handler */   
	enable_irq(GPIO_EVENT, gpioISR);
	/* We do not need the SPI ISR, the AIC codec config happens without interrupts */
	/* enable_irq(SPI_EVENT, spiISR); */

	IRQ_globalEnable();
}

interrupt void spiISR(void)
{
	/* This should be equal to number of SPI transactions with codec 2 */
	spi_ISR_hit_cnt ++;
	/* Clear SPI interrupt */		
	IFR1 = (IFR1 & ~0x0008) | (0x01 << 3);
}

interrupt void gpioISR(void)
{
	volatile Uint8 regval = 0;
	volatile unsigned long int i;	
	debug(("IFR1 = %#x\n", IFR1));
	debug(("IOINTFLG1 = %#x\n", IOINTFLG1));
	debug(("mode_toggle = %u\n", mode_toggle));
	
	/* Clear GPIO interrupt */
	IFR1 = (IFR1 & ~0x0020U) | (0x01 << 5);
	
	switch (IOINTFLG1) {
		case 0x1000: /* GPIO-12, BTN 2, PC */
			// IN2L & IN2_R to LADC_P/RADC_P respectively, through 20 kohm	
			// Route MIC back to the source
			USBSTK5505_GPIO_setOutput(GPIO16, 0 ); // 0x and 0y on ON Channels , B
			USBSTK5505_GPIO_setOutput(GPIO17, 0 ); // A
			toggle_dual_mode(mode_toggle);
			break;

		case 0x2000: /* GPIO-13, BTN 1, Mob */
			// IN1L & IN1_R to LADC_P/RADC_P respectively, through 20 kohm	
			// Route MIC back to the source
			USBSTK5505_GPIO_setOutput(GPIO16, 1 ); // 3x and 3y on ON Channels, B 
			USBSTK5505_GPIO_setOutput(GPIO17, 1 ); // A
			toggle_dual_mode(mode_toggle);			
			break;
			
		case 0x4000: /* GPIO-14, BTN 3, Tel */
			// IN3L & IN3_R to LADC_P/RADC_P respectively, through 20 kohm	
			// Route MIC back to the source
			USBSTK5505_GPIO_setOutput(GPIO16, 1 ); // 2x and 2y on ON Channels, B 
			USBSTK5505_GPIO_setOutput(GPIO17, 0 ); // A
			toggle_dual_mode(mode_toggle);
			break;
			
		case 0x8000: /* GPIO-15, Dual MODE */
			/* Toggle Dual Mode */
			USBSTK5505_waitusec(1000);
			mode_toggle = ~mode_toggle;
			toggle_dual_mode(mode_toggle);						
			break;
			
		case 0x0800: /* GPIO-11, Vol Up */
			/* Wait for Debounce  */
			USBSTK5505_waitusec(1000);
    		AIC3204_II_rset( 0, 0 );
			if (AIC3204_II_rget(65) >= VOLUME_MAX) {
				beep_generator(VOL_MAX);
			} else {
				regval = AIC3204_II_rget(65);
				AIC3204_II_rset(65, (regval + 0x01));
				//beep_generator(VOL_UP);
				debug(("R= %#x W: %#x\n", regval, regval + 0x02));
			}				
			break;
			
		case 0x0020: /* GPIO-5, Vol Down */
			/* Wait for Debounce */
			USBSTK5505_waitusec(1000);
			AIC3204_II_rset(0, 0);
			if (AIC3204_II_rget(65) <= VOLUME_MIN) {
				beep_generator(VOL_MIN);
			} else {
				regval = AIC3204_II_rget(65);
				AIC3204_II_rset(65, (regval - 0x01));
				//beep_generator(VOL_DOWN);
				debug(("R= %#x W: %#x\n", regval, regval - 0x02));
			}
			break;		 		
			
		default:
			/* Clear all Button interrupts */
			IOINTFLG1 = 0xFF;
			IOINTFLG2 = 0xFF;		 			
			break;
	}
	
	/* Clear all Button interrupts, if any */			
	USBSTK5505_GPIO_clear_interrupt();
	debug(("IOINTFLG1 = %#x\n", IOINTFLG1));

}

