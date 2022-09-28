/*
 * enc_ll.h
 *
 *  Created on: Sep 28, 2022
 *      Author: Barcala
 */

#ifndef INC_ENC_LL_H_
#define INC_ENC_LL_H_
#include "stm32f1xx_hal.h"
#define ENC_PORT_A GPIOA
#define ENC_PIN_A 1
#define ENC_PORT_B GPIOA
#define ENC_PIN_B 2
#define enc_getInputs() ((((ENC_PORT_B->IDR)&(1<<ENC_PIN_B)) >> ENC_PIN_B) +\
((((ENC_PORT_A->IDR)&(1<<ENC_PIN_A)) >> ENC_PIN_A)<<1))
void enc_gpioConfig();
#endif /* INC_ENC_LL_H_ */
