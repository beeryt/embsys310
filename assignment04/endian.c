/*
 *  File:       endian.c
 *  Author:     Carl B. Smiley
 *  Date:       Nov 11 2020
 *  Course:     Fundamentals of Embedded and Real Time Systems
 *
 * Description: displays endianness of processor over UART1
 */
#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef USE_HAL
#include <stm32l4xx_hal.h>
void init_uart();
#else
void init_uart() {}
#endif

/** The processor is big-endian if the MSB is the first byte */
bool isBigEndian() {
    volatile uint32_t storage = 0xFF000000;
    return 0xFF == *((uint8_t*)(&storage));
}

/** The processor is little-endian if the LSB is the first byte */
bool isLittleEndian() {
    volatile uint32_t storage = 0x000000FF;
    return 0xFF == *((uint8_t*)(&storage));
}

int main() {
    init_uart();
    printf("isBigEndian():      %s\n\r", isBigEndian() ? "true": "false");
    printf("isLittleEndian():   %s\n\r", isLittleEndian() ? "true": "false");
}

#ifdef USE_HAL
static UART_HandleTypeDef huart;

/** Initializes UART1 which allows for TX over USB */
void init_uart() {
    // USART1 GPIO configuration
    // PB6  ----->  USART1_TX
    // PB7  ----->  USART1_RX
    __GPIOB_CLK_ENABLE();
    GPIO_InitTypeDef gpio;
    gpio.Mode = GPIO_MODE_AF_PP;
    gpio.Pull = GPIO_PULLUP;
    gpio.Alternate = GPIO_AF7_USART1;
    gpio.Pin = GPIO_PIN_6 | GPIO_PIN_7;
    HAL_GPIO_Init(GPIOB, &gpio);

    // USART1 Peripheral configuration (115200 baud, 8 bit, no parity, 1 stop)
    __USART1_CLK_ENABLE();
    huart.Instance = USART1;
    huart.Init.Mode = UART_MODE_TX;
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    HAL_UART_Init(&huart);
}

/** Provide implementation so stdio uses UART for all file descriptors */
ssize_t _write(int fd, const void *buf, size_t count) {
    HAL_UART_Transmit(&huart, (uint8_t*)buf, count, HAL_MAX_DELAY);
    return count;
}
#endif