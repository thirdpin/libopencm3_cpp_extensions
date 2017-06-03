/*
 * This file is part of the libopencm3_cpp_extensions project.
 * hosted at http://github.com/thirdpin/libopencm3_cpp_extensions
 *
 * Copyright (C) 2016  Third Pin LLC
 * Written by Anastasiia Lazareva <a.lazareva@thirdpin.ru>
 * Written by Maxim Ambrosevich
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

/* 
SPI C++ Wrapper of libopencm3 library for STM32F2, STM32F4 
*/

#include <spi_ext.h>

namespace cm3ext {

namespace spi {


Spi::Spi(Config spi_conf)
{
	switch(spi_conf.spi_number)
	{
		case 1: _spi = SPI1; break;
		case 2: _spi = SPI2; break;
		case 3: _spi = SPI3; break;
		default: break;
	}

	gpio::Gpio mosi(spi_conf.mosi_pin);
	mosi.mode_setup(gpio::Mode::ALTERNATE_FUNCTION, gpio::PullMode::NO_PULL);
	mosi.set_output_options(gpio::OutputType::PUSH_PULL, gpio::Speed::HIGH_SPEED_100MHz);

	gpio::Gpio miso(spi_conf.miso_pin);
	miso.mode_setup(gpio::Mode::ALTERNATE_FUNCTION, gpio::PullMode::NO_PULL);
	miso.set_output_options(gpio::OutputType::PUSH_PULL, gpio::Speed::HIGH_SPEED_100MHz);

	gpio::Gpio scl(spi_conf.scl_pin);
	scl.mode_setup(gpio::Mode::ALTERNATE_FUNCTION, gpio::PullMode::NO_PULL);
	scl.set_output_options(gpio::OutputType::PUSH_PULL, gpio::Speed::HIGH_SPEED_100MHz);

	switch(_spi)
	{
		case SPI1:
		case SPI2:
			mosi.set_af(gpio::AltFuncNumber::AF5);
			miso.set_af(gpio::AltFuncNumber::AF5);
			scl.set_af(gpio::AltFuncNumber::AF5);
			break;

		case SPI3 :
			mosi.set_af(gpio::AltFuncNumber::AF6);
			miso.set_af(gpio::AltFuncNumber::AF6);
			scl.set_af(gpio::AltFuncNumber::AF6);
			break;

		default: break;
	}
}

void Spi::set_next_tx_from(NextTx next)
{
	switch(next)
	{
		case NEXT_TX_FROM_BUFFER :
			spi_set_next_tx_from_buffer(_spi);
			break;
		case NEXT_TX_FROM_CRC :
			spi_set_next_tx_from_crc(_spi);
			break;
	}
}

void Spi::set_data_drame_format(DataFrameFormat dff)
{
	switch(dff)
	{
		case DFF_8BIT :
			spi_set_dff_8bit(_spi);
			break;
		case DFF_16BIT :
			spi_set_dff_16bit(_spi);
			break;

	}
}

void Spi::set_software_slave_management(State state)
{
	switch(state)
	{
		case DISABLE :
			spi_disable_software_slave_management(_spi);
			break;
		case ENABLE :
			spi_enable_software_slave_management(_spi);
			break;
	}
}

void Spi::set_nss(NssState nss)
{
	switch(nss)
	{
		case LOW :
			spi_set_nss_low(_spi);
			break;
		case HIGH :
			spi_set_nss_high(_spi);
			break;
	}
}

void Spi::set_bit_position(BitPos pos)
{
	switch(pos)
	{
		case MSB_FIRST :
            spi_send_msb_first(_spi);
            break;
		case LSB_FIRST :
			spi_send_lsb_first(_spi);
			break;
	}
}

void Spi::set_clock_polarity(Polarity polarity)
{
	switch(polarity)
	{
		case POLARITY_LOW :
			spi_set_clock_polarity_0(_spi);
			break;
		case POLARITY_HIGH :
			spi_set_clock_polarity_1(_spi);
			break;
	}
}

void Spi::set_clock_phase(Phase phase)
{
	switch(phase)
	{
		case PHASE_LOW :
			spi_set_clock_phase_0(_spi);
			break;
		case PHASE_HIGH :
			spi_set_clock_phase_1(_spi);
			break;
	}
}

bool Spi::get_flag_status(Flag flag)
{
	bool result = ERROR;
	uint32_t reg_sr = SPI_SR(_spi);

	switch (flag)
	{
		case RECEIVE_BUFFER_NOT_EMPTY :
			if ((reg_sr & RECEIVE_BUFFER_NOT_EMPTY_MASK) ==
					         RECEIVE_BUFFER_NOT_EMPTY_MASK) {
				result = OK;
			}
			break;
		case TRANSMIT_BUFFER_EMPTY :
			if ((reg_sr & TRANSMIT_BUFFER_EMPTY_MASK) ==
					         TRANSMIT_BUFFER_EMPTY_MASK) {
				result = OK;
			}
			break;
		case CHANEL_SIDE :
			if ((reg_sr & CHANEL_SIDE_MASK) ==
					         CHANEL_SIDE_MASK) {
				result = OK;
			}
			break;
		case UNDERRUN_FLAG :
			if ((reg_sr & UNDERRUN_FLAG_MASK) ==
					         UNDERRUN_FLAG_MASK) {
				result = OK;
			}
			break;
		case CRC_ERROR :
			if ((reg_sr & CRC_ERROR_MASK) ==
					         CRC_ERROR_MASK) {
				result = OK;
			}
			break;
		case MODE_FAULT :
			if ((reg_sr & MODE_FAULT_MASK) ==
					         MODE_FAULT_MASK) {
				result = OK;
			}
			break;
		case OVERRUN_FLAG :
			if ((reg_sr & OVERRUN_FLAG_MASK) ==
					         OVERRUN_FLAG_MASK) {
				result = OK;
			}
			break;
		case BUSY_FLAG :
			if ((reg_sr & BUSY_FLAG_MASK) ==
							 BUSY_FLAG_MASK) {
				result = OK;
			}
			break;
		case TI_FRAME_FORMAT_ERROR :
			if ((reg_sr & TI_FRAME_FORMAT_ERROR_MASK) ==
							 TI_FRAME_FORMAT_ERROR_MASK) {
				result = OK;
			}
			break;
	}
	return (result);
}


} // namespace spi

} // namespace cm3ext
