/*
 * enc_lib.c
 *
 *  Created on: Sep 28, 2022
 *      Author: Barcala
 */
#include "enc_lib.h"
#include "enc_ll.h"
/* variables relativas a la posición del encoder */
static volatile int32_t enc_value = 0;
static volatile int32_t enc_min = -50;
static volatile int32_t enc_max = 50;
/* definición de tipos y función para usar
 internamente en la FSM */
typedef enum {
	ENC_MIN_STATE,
	ENC_IDLE = ENC_MIN_STATE,
	ENC_CW01,
	ENC_CW00,
	ENC_CW10,
	ENC_CCW10,
	ENC_CCW00,
	ENC_CCW01,
	ENC_MAX_STATE = ENC_CCW01
} enc_state_t;
typedef enum {
	ENC_MIN_INPUT,
	ENC_00 = ENC_MIN_INPUT,
	ENC_01,
	ENC_10,
	ENC_11,
	ENC_MAX_INPUT = ENC_11
} enc_input_t;
static volatile enc_state_t enc_state = ENC_IDLE;

static void enc_fsm(enc_state_t *state, enc_input_t input) {
	if (*state < ENC_MIN_STATE || *state > ENC_MAX_STATE)
		return;
	if (input < ENC_MIN_INPUT || input > ENC_MAX_INPUT)
		return;
	switch (*state) {
	case ENC_IDLE:
		switch (input) {
		case ENC_01:
			*state = ENC_CW01;
			break;
		case ENC_10:
			*state = ENC_CCW10;
			break;
		case ENC_00:
			break;
		case ENC_11:
			break;
		}
		break;
		/*************** CW *****************/
	case ENC_CW01:
		switch (input) {
		case ENC_11:
			*state = ENC_IDLE;
			break;
		case ENC_00:
			*state = ENC_CW00;
			break;
		case ENC_01:
			break;
		case ENC_10:
			break;
		}
		break;
	case ENC_CW00:
		switch (input) {
		case ENC_11:
			*state = ENC_IDLE;
			break;
		case ENC_01:
			*state = ENC_CW01;
			break;
		case ENC_10:
			*state = ENC_CW10;
			break;
		case ENC_00:
			break;
		}
		break;
	case ENC_CW10:
		switch (input) {
		case ENC_11:
			if (enc_value < enc_max)
				enc_value++;
			*state = ENC_IDLE;
			break;
		case ENC_00:
			*state = ENC_CW00;
			break;
		case ENC_01:
			break;
		case ENC_10:
			break;
		}
		break;
		/*************** CCW *****************/
	case ENC_CCW10:
		switch (input) {
		case ENC_11:
			*state = ENC_IDLE;
			break;
		case ENC_00:
			*state = ENC_CCW00;
			break;
		case ENC_01:
			break;
		case ENC_10:
			break;
		}
		break;
	case ENC_CCW00:
		switch (input) {
		case ENC_11:
			*state = ENC_IDLE;
			break;
		case ENC_01:
			*state = ENC_CCW01;
			break;
		case ENC_10:
			*state = ENC_CCW10;
			break;
		case ENC_00:
			break;
		}
		break;
	case ENC_CCW01:
		switch (input) {
		case ENC_11:
			if (enc_value > enc_min)
				enc_value--;
			*state = ENC_IDLE;
			break;
		case ENC_00:
			*state = ENC_CCW00;
			break;
		case ENC_01:
			break;
		case ENC_10:
			break;
		}
		break;
	}
}

void enc_init(int32_t minValue, int32_t maxValue) {
	if (minValue < maxValue) {
		enc_min = enc_value = minValue;
		enc_max = maxValue;
	} else {
		enc_min = enc_max = enc_value = 0;
	}
	/* configura 2 GPIOs como entradas con pull-up
	 * se define en la capa de bajo nivel*/
	enc_gpioConfig();
	/* inicialización de la máquina de estados*/
	enc_state = ENC_IDLE;
}
void enc_process() {
	enc_input_t input;
	/* Lee los 2 GPIOs y devuelve un valor de la
	 * enumeración enc_input_t [0-3]
	 * se define en la capa de bajo nivel*/
	input = enc_getInputs();
	/* ejecuta la fsm */
	enc_fsm(&enc_state, input);
}
int32_t enc_getValue() {
	return enc_value;
}
