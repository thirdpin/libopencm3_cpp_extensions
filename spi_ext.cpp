#include "spi_ext.h"
using namespace SPI_CPP_Extension;

SPI_ext::SPI_ext(SPI_Conf spi_conf)
{
	switch(spi_conf.spi_number)
	{
		case 1: _spi = SPI1; break;
		case 2: _spi = SPI2; break;
		case 3: _spi = SPI3; break;
		default: break;
	}

	GPIO_ext mosi(spi_conf.mosi_pin);
	mosi.mode_setup(GPIO_CPP_Extension::Mode::ALTERNATE_FUNCTION, GPIO_CPP_Extension::PullMode::NO_PULL);
	mosi.set_output_options(GPIO_CPP_Extension::OutputType::PUSH_PULL, GPIO_CPP_Extension::Speed::FAST_50MHz);

	GPIO_ext miso(spi_conf.miso_pin);
	miso.mode_setup(GPIO_CPP_Extension::Mode::ALTERNATE_FUNCTION, GPIO_CPP_Extension::PullMode::NO_PULL);
	miso.set_output_options(GPIO_CPP_Extension::OutputType::PUSH_PULL, GPIO_CPP_Extension::Speed::FAST_50MHz);

	GPIO_ext scl(spi_conf.scl_pin);
	scl.mode_setup(GPIO_CPP_Extension::Mode::ALTERNATE_FUNCTION, GPIO_CPP_Extension::PullMode::NO_PULL);
	scl.set_output_options(GPIO_CPP_Extension::OutputType::PUSH_PULL, GPIO_CPP_Extension::Speed::FAST_50MHz);

	switch(_spi)
	{
		case SPI1:
		case SPI2:
			mosi.set_af(GPIO_CPP_Extension::AF_Number::AF5);
			miso.set_af(GPIO_CPP_Extension::AF_Number::AF5);
			scl.set_af(GPIO_CPP_Extension::AF_Number::AF5);
			break;

		case SPI3 :
			mosi.set_af(GPIO_CPP_Extension::AF_Number::AF6);
			miso.set_af(GPIO_CPP_Extension::AF_Number::AF6);
			scl.set_af(GPIO_CPP_Extension::AF_Number::AF6);
			break;

		default: break;
	}
}

void SPI_ext::set_next_tx_from(NextTx next)
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
void SPI_ext::set_data_drame_format(DataFrameFormat dff)
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
void SPI_ext::set_software_slave_management(State state)
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
void SPI_ext::set_nss(NssState nss)
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
void SPI_ext::set_bit_position(BitPos pos)
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
void SPI_ext::set_clock_polarity(Polarity polarity)
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
void SPI_ext::set_clock_phase(Phase phase)
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
bool SPI_ext::get_flag_status(Flag flag)
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
