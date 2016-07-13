#ifndef SPI_EXT_H
#define SPI_EXT_H

#include <libopencm3/stm32/spi.h>
#include "gpio_ext.h"

using namespace GPIO_CPP_Extension;

namespace SPI_CPP_Extension
{
	constexpr bool OK									= true;
	constexpr bool ERROR       							= false;
	constexpr uint16_t RECEIVE_BUFFER_NOT_EMPTY_MASK  	= 0x0001;
	constexpr uint16_t TRANSMIT_BUFFER_EMPTY_MASK       = 0x0002;
	constexpr uint16_t CHANEL_SIDE_MASK                 = 0x0004;
	constexpr uint16_t UNDERRUN_FLAG_MASK               = 0x0008;
	constexpr uint16_t CRC_ERROR_MASK                   = 0x0010;
	constexpr uint16_t MODE_FAULT_MASK                  = 0x0020;
	constexpr uint16_t OVERRUN_FLAG_MASK                = 0x0040;
	constexpr uint16_t BUSY_FLAG_MASK                   = 0x0080;
	constexpr uint16_t TI_FRAME_FORMAT_ERROR_MASK       = 0x0100;

    typedef struct {
        uint8_t spi_number;
		Pinout mosi_pin;
		Pinout miso_pin;
		Pinout scl_pin;
	}SPI_Conf;

	typedef enum {
		RECEIVE_BUFFER_NOT_EMPTY,
		TRANSMIT_BUFFER_EMPTY,
		CHANEL_SIDE,
		UNDERRUN_FLAG,
		CRC_ERROR,
		MODE_FAULT,
		OVERRUN_FLAG,
		BUSY_FLAG,
		TI_FRAME_FORMAT_ERROR
	}Flag;

	typedef enum : uint8_t {
		BAUDRATE_FPCLK_DIV_2   = 0x00,
		BAUDRATE_FPCLK_DIV_4   = 0x01,
		BAUDRATE_FPCLK_DIV_8   = 0x02,
		BAUDRATE_FPCLK_DIV_16  = 0x03,
		BAUDRATE_FPCLK_DIV_32  = 0x04,
		BAUDRATE_FPCLK_DIV_64  = 0x05,
		BAUDRATE_FPCLK_DIV_128 = 0x06,
		BAUDRATE_FPCLK_DIV_256 = 0x07,
	}BaudRate;

	typedef enum {
		NEXT_TX_FROM_BUFFER,
		NEXT_TX_FROM_CRC
	}NextTx;

	typedef enum {
		DFF_8BIT,
		DFF_16BIT
	}DataFrameFormat;

	typedef enum {
		DISABLE,
		ENABLE
	}State;

	typedef enum {
		LOW,
		HIGH
	}NssState;

	typedef enum {
		POLARITY_LOW,
		POLARITY_HIGH
	}Polarity;

	typedef enum {
		PHASE_LOW,
		PHASE_HIGH
	}Phase;

	typedef enum {
		MSB_FIRST,
		LSB_FIRST
	}BitPos;

	typedef enum {
		MODE_0 = 0,
		MODE_1,
		MODE_2,
		MODE_3
	}StdMode;

	class SPI_ext
	{
	public:
		SPI_ext();
		SPI_ext(SPI_Conf spi_conf);

		void reset()
		{
			spi_reset(_spi);
		}
		void enable()
		{
			spi_enable(_spi);
		}
		void disable()
		{
			spi_disable(_spi);
		}
		void clean_disable()
		{
			spi_clean_disable(_spi);
		}
		void write(uint16_t data)
		{
			spi_write(_spi, data);
		}
		void send(uint16_t data)
		{
			spi_send(_spi, data);
		}
		uint16_t read()
		{
			spi_send(_spi, 0xFF);
			return (spi_read(_spi));
		}
		uint16_t xfer(uint16_t data)
		{
			spi_xfer(_spi, data);
		}
		void set_master_mode()
		{
			spi_set_master_mode(_spi);
		}
		void set_slave_mode()
		{
			spi_set_slave_mode(_spi);
		}
		void full_duplex_mode()
		{
			spi_set_full_duplex_mode(_spi);
		}
		void set_bidirectional_mode()
		{
			spi_set_bidirectional_mode(_spi);
		}
		void set_bidirectional_transmit_only_mode()
		{
			spi_set_bidirectional_transmit_only_mode(_spi);
		}
		void set_bidirectional_receive_only_mode()
		{
			spi_set_bidirectional_receive_only_mode(_spi);
		}
		void set_unidirectional_mode()
		{
			spi_set_unidirectional_mode(_spi);
		}
		void set_receive_only_mode()
		{
			spi_set_receive_only_mode(_spi);
		}
		void enable_crc()
		{
			spi_enable_crc(_spi);
		}
		void disable_crc()
		{
			spi_disable_crc(_spi);
		}
		void set_next_tx_from(NextTx next);
		void set_data_drame_format(DataFrameFormat dff);
		void set_software_slave_management(State state);
		void set_nss(NssState nss);
		void set_bit_position(BitPos pos);
		void set_baudrate_prescaler(BaudRate baudrate)
		{
			spi_set_baudrate_prescaler(_spi, (uint8_t)baudrate);
		}
		void set_clock_polarity(Polarity polarity);
		void set_clock_phase(Phase phase);
		void enable_tx_buffer_empty_interrupt()
		{
			spi_enable_tx_buffer_empty_interrupt(_spi);
		}
		void disable_tx_buffer_empty_interrupt()
		{
			spi_disable_tx_buffer_empty_interrupt(_spi);
		}
		void enable_rx_buffer_not_empty_interrupt()
		{
			spi_enable_rx_buffer_not_empty_interrupt(_spi);
		}
		void disable_rx_buffer_not_empty_interrupt()
		{
			spi_disable_rx_buffer_not_empty_interrupt(_spi);
		}
		void enable_error_interrupt()
		{
			spi_enable_error_interrupt(_spi);
		}
		void disable_error_interrupt()
		{
			spi_disable_error_interrupt(_spi);
		}
		void enable_ss_output()
		{
			spi_enable_ss_output(_spi);
		}
		void disable_ss_output()
		{
			spi_disable_ss_output(_spi);
		}
		void enable_tx_dma()
		{
			spi_enable_tx_dma(_spi);
		}
		void disable_tx_dma()
		{
			spi_disable_tx_dma(_spi);
		}
		void enable_rx_dma()
		{
			spi_enable_rx_dma(_spi);
		}
		void disable_rx_dma()
		{
			spi_disable_rx_dma(_spi);
		}
		void set_standard_mode(StdMode mode)
		{
			spi_set_standard_mode(_spi, mode);
		}
		bool get_flag_status(Flag flag);

	private:
		uint32_t _spi;

	};
}

#endif
