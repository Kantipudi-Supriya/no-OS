/***************************************************************************//**
 *   @file   common_data.c
 *   @brief  Defines data common to all examples.
 *   @author Ciprian Regus (ciprian.regus@analog.com)
********************************************************************************
 * Copyright 2023(c) Analog Devices, Inc.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of Analog Devices, Inc. nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY ANALOG DEVICES, INC. “AS IS” AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO
 * EVENT SHALL ANALOG DEVICES, INC. BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*******************************************************************************/

#include "common_data.h"
#include "maxim_gpio.h"
#include "maxim_spi.h"

#if defined(APARD32690_ADIN1110_STANDALONE_EXAMPLE)
#include "adin1110.h"
#endif

#if defined(APARD32690_ECHO_SERVER_EXAMPLE)
#include "adin1110.h"
#include "lwip_socket.h"
#include "lwip_adin1110.h"
#endif

struct max_uart_init_param uart_extra_ip = {
	.flow = MAX_UART_FLOW_DIS
};

struct no_os_uart_init_param uart_ip = {
	.device_id = 0,
	.asynchronous_rx = false,
	.baud_rate = 115200,
	.size = NO_OS_UART_CS_8,
	.parity = NO_OS_UART_PAR_NO,
	.stop = NO_OS_UART_STOP_1_BIT,
	.extra = &uart_extra_ip,
	.platform_ops = &max_uart_ops,
};

#if defined(APARD32690_ECHO_SERVER_EXAMPLE) || defined(APARD32690_ADIN1110_STANDALONE_EXAMPLE)

const struct max_spi_init_param adin1110_spi_extra = {
	.num_slaves = 1,
	.polarity = SPI_SS_POL_LOW,
	.vssel = MXC_GPIO_VSSEL_VDDIOH,
};

const struct no_os_gpio_init_param adin1110_rst_gpio_ip = {
	.port = 0,
	.number = 15,
	.pull = NO_OS_PULL_NONE,
	.platform_ops = &max_gpio_ops,
	.extra = &(struct max_gpio_init_param)
	{
		.vssel = 1
	},
};

const struct no_os_spi_init_param adin1110_spi_ip = {
	.device_id = 3,
	.max_speed_hz = 25000000,
	.bit_order = NO_OS_SPI_BIT_ORDER_MSB_FIRST,
	.mode = NO_OS_SPI_MODE_0,
	.platform_ops = &max_spi_ops,
	.chip_select = 0,
	.extra = &adin1110_spi_extra,
};

struct adin1110_init_param adin1110_ip = {
	.chip_type = ADIN1110,
	.comm_param = adin1110_spi_ip,
	.reset_param = adin1110_rst_gpio_ip,
	.mac_address = {0x00, 0x18, 0x80, 0x03, 0x25, 0x80},
	.append_crc = false,
};

#endif

#if defined(APARD32690_ECHO_SERVER_EXAMPLE)

struct lwip_network_param lwip_ip = {
	.platform_ops = &adin1110_lwip_ops,
	.mac_param = &adin1110_ip,
};
#endif
