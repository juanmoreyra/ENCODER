/*
 * enc_ll.c
 *
 *  Created on: Sep 28, 2022
 *      Author: Barcala
 */

#include "enc_ll.h"
void enc_gpioConfig() {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	/* HABILITA CLOCK DE PUERTOS USADOS
	 * CON LAS ENTRADAS A Y B */
	switch ((uint32_t) ENC_PORT_A) {
	case (uint32_t) GPIOA:
		__HAL_RCC_GPIOA_CLK_ENABLE();
		break;
	case (uint32_t) GPIOB:
		__HAL_RCC_GPIOB_CLK_ENABLE();
		break;
	case (uint32_t) GPIOC:
		__HAL_RCC_GPIOC_CLK_ENABLE();
		break;
	case (uint32_t) GPIOD:
		__HAL_RCC_GPIOD_CLK_ENABLE();
		break;
	default:
		return;
	}
	switch ((uint32_t) ENC_PORT_B) {
	case (uint32_t) GPIOA:
		__HAL_RCC_GPIOA_CLK_ENABLE();
		break;
	case (uint32_t) GPIOB:
		__HAL_RCC_GPIOB_CLK_ENABLE();
		break;
	case (uint32_t) GPIOC:
		__HAL_RCC_GPIOC_CLK_ENABLE();
		break;
	case (uint32_t) GPIOD:
		__HAL_RCC_GPIOD_CLK_ENABLE();
		break;
	default:
		return;
	}
	/*Configura GPIO pins : ENC_A ENC_B */
	GPIO_InitStruct.Pin = (1 << ENC_PIN_A);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(ENC_PORT_A, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = (1 << ENC_PIN_B);
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(ENC_PORT_B, &GPIO_InitStruct);
}
