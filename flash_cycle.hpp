#ifndef FLASH_CYCLE_H
#define FLASH_CYCLE_H

#include <libopencm3/cm3/common.h>
#include <libopencm3/stm32/f2/flash.h>
#include <libopencmsis/core_cm3.h>

namespace cm3cpp {

namespace flash {


enum FlashSector : uint32_t {
	SECTOR_0 = 0x08000000,
	SECTOR_1 = 0x08004000,
	SECTOR_2 = 0x08008000,
	SECTOR_3 = 0x0800C000,
	SECTOR_4 = 0x08010000,
	SECTOR_5 = 0x08020000,
};

constexpr uint32_t USER_FLASH_END_ADDRESS = 0x080FFFFF;

template <typename T>
class FlashCycle
{
public:
	FlashCycle(FlashSector sector)
	{
		_error = false;
		_ifexist = false;
		_flashSector = sector;
		_startAddr = 0;
		_endAddr = 0;
		_getSectorAddrs();
		_pLastContainer = _searchLastContainer();
	}

	bool write(T* newContainer)
	{
		if(_error) {
			return(false);
		}

		uint32_t writeTo;

		flash_unlock();

		if( !_ifexist)
		{
			writeTo = _startAddr;
			_ifexist = true;
		}
		else if((uint32_t)_pLastContainer >= (_endAddr-sizeof(T)))
		{
			__disable_irq();
			flash_erase_sector(5, 2);
			__enable_irq();
			writeTo = _startAddr;
		}
		else {
			writeTo = (uint32_t)(_pLastContainer + 1);
		}

		uint8_t *pContainer = (uint8_t*)newContainer;

		for(int i = 0; i < sizeof(T); i++)
		{
			__disable_irq();
			flash_program_byte(writeTo++, pContainer[i]);
			__enable_irq();
		}

		flash_lock();
		_pLastContainer=(T*)(writeTo - sizeof(T));
		return(true);
	}

	T* get(void)
	{
		return(_pLastContainer);
	}

	bool is_exist(void)
	{
		return(_ifexist);
	}

private:
	bool _error;
	bool _ifexist;
	FlashSector _flashSector;
	uint32_t _startAddr;
	uint32_t _endAddr;
	T* _pLastContainer;

	static constexpr uint8_t NUM_SECTORS = 6;

	void _getSectorAddrs(void)
	{
		_startAddr = (uint32_t)_flashSector;

		if (_flashSector == FlashSector::SECTOR_1)
			_endAddr = (uint32_t)FlashSector::SECTOR_2;
		else if (_flashSector == FlashSector::SECTOR_2)
			_endAddr = (uint32_t)FlashSector::SECTOR_3;
		else if (_flashSector == FlashSector::SECTOR_3)
			_endAddr = (uint32_t)FlashSector::SECTOR_4;
		else if (_flashSector == FlashSector::SECTOR_4)
			_endAddr = (uint32_t)FlashSector::SECTOR_5;
		else if(_flashSector == FlashSector::SECTOR_5)
			_endAddr = USER_FLASH_END_ADDRESS + 1;

		if(!_startAddr)
			_error = true;
	}

	T *_searchLastContainer(void)
	{
		if(_error) {
			return(0);
		}

		T* addr = (T*)_startAddr;
		_ifexist = true;
		while((uint32_t)addr <= (_endAddr - sizeof(T)))
		{
			if( *(((uint8_t*)addr)) == 0xFF)
			{
				if(addr == (T*)_startAddr)
				{
					_ifexist = false;
					return(addr);
					//addr = 0;
				}

				break;
			}

			addr += 1;
		}

		return(addr - 1);
	}
};


}  // namespace flash

}  // namespace cm3ext

#endif
