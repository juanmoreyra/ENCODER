/*
 * enc_lib.h
 *
 *  Created on: Sep 28, 2022
 *      Author: Barcala
 */

#ifndef INC_ENC_LIB_H_
#define INC_ENC_LIB_H_
#include <stdint.h>
/* inicializa entradas y estado, establece posiciones límites*/
void enc_init(int32_t minValue, int32_t maxValue);
/* lee entradas y procesa según el modelado como FSM */
void enc_process();
/* devuelve la posición actual de la perilla */
int32_t enc_getValue();
#endif /* INC_ENC_LIB_H_ */
