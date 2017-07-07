/*
 * This file is part of the libopencm3_cpp_extensions project.
 * hosted at http://github.com/thirdpin/libopencm3_cpp_extensions
 *
 * Copyright (C) 2016  Third Pin LLC
 * Written by Pavel Larionov <p.larionov@thirdpin.ru>
 * Written by Anastasiia Lazareva <a.lazareva@thirdpin.ru>
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
ROUND BUFFER implementation, public interface
*/

#ifndef ROUND_BUFFER_H
#define ROUND_BUFFER_H

#include <stdint.h>
#include <libopencm3_cpp_extensions/cm3cpp_config.h>
#include <libopencm3_cpp_extensions/private/assert.h>

namespace cm3cpp {

namespace utils {

constexpr uint32_t ROUND_BUFFER_DEFAULT_SIZE = 1000;

/**
@brief Initializes a new instance of the TplRoundBuffer class
       that is empty and has the specified initial size.
@param size The number of bytes that the new TplRoundBuffer can initially store.
*/
inline void init(uint32_t size);
/**
@brief Initializes a new instance of the TplRoundBuffer class
       that internally points to external buffer and has the specified initial size.
@param buffer External buffer the new TplRoundBuffer should points to.
@param size The number of bytes that the new TplRoundBuffer can initially store.
*/
inline void init(void *buffer, uint32_t size);
/**
@brief Removes all bytes from the TplRoundBuffer.
*/
inline void clear(void);
/**
@brief Removes a range of bytes from the top of the TplRoundBuffer.
@param count The number of bytes to remove.
@return flase if empty after removing; otherwise, true.
*/
inline bool remove_range(uint32_t count);
/**
@brief Gets the number of bytes actually contained in the TplRoundBuffer.
@return The number of bytes actually contained in the TplRoundBuffer.
*/
inline uint32_t get_count(void);
/**
@brief Gets two bytes starting from the specified index.
@param index The zero-based index of the first byte to get.
@return Two bytes starting from the specified index.
*/
inline uint16_t get_word_unsafe(uint32_t index);
/**
@brief Adds a byte to the end of the TplRoundBuffer.
@param byte The byte to add to the TplRoundBuffer.
@return false if overflow; otherwise, true.
*/
inline bool push(uint8_t byte);
/**
@brief Removes and returns the byte at the beginning of the TplRoundBuffer.
@return The byte at the beginning of the TplRoundBuffer.
*/
inline uint8_t pop(void);
/**
@brief Removes and returns the byte at the beginning of the TplRoundBuffer.
@return The byte at the beginning of the TplRoundBuffer.
*/
inline uint8_t pop_unsafe(void);

class RoundBuffer
{
public:
	/**
	@brief Initializes a new instance of the TplRoundBuffer class
           that is empty and has no initial size.
	*/
	RoundBuffer();

	/**
	@brief Prevent memory leak.
	*/
	CM3CPP_EXPLISIT_DESTRUCTOR(RoundBuffer) // prevent memory leak

	/**
    @brief Initializes a new instance of the TplRoundBuffer class
	that is empty and has the specified initial size.
	@param size The number of bytes that the new TplRoundBuffer can initially store.
	*/
	RoundBuffer(uint32_t size);
    /**
    @brief Gets the byte at the specified index.
    @param index The zero-based index of the byte to get.
    @return The byte at the specified index.
    */
    uint8_t operator [](uint32_t index)
    {
        uint32_t pos = _head;
        mrb_plus(&pos, index);

        return(_buffer[pos]);
    }
	/**
	@brief Copies a range of bytes from the TplRoundBuffer to the external buffer.
	@param resultBuffer The external buffer.
	@param index The zero-based starting index of the range of bytes to copy.
	@param count The number of bytes to copy.
	@return The number of actually copied bytes.
	*/
	uint32_t get(void *resultBuffer, uint32_t index, uint32_t count);

	/**
	@brief Adds a range of bytes from the top of the specified external buffer
	       to the end of the TplRoundBuffer.
	@param buffer The external buffer.
	@param count The number of bytes to add.
	@return false if overflow; otherwise, true.
	*/
    bool push(void *buffer, uint32_t count);
	/**
	@brief Adds a range of bytes from the top of the specified TplRoundBuffer
	       to the end of the current TplRoundBuffer.
	@param tplRoundBuffer The external TplRoundBuffer.
	@param count The number of bytes to add.
	@return false if overflow; otherwise, true.
	*/
	bool push(RoundBuffer *buffer, uint32_t count, bool with_pop = true);
	/**
	@brief Removes a range of bytes from the beginning of the TplRoundBuffer and adds it
	       to the specified external buffer.
	@param resultBuffer The external buffer.
	@param count The number of bytes to remove.
	@return The number of actually removed bytes.
	*/
	uint32_t pop(void *buffer, uint32_t count);
	/**
	@brief
	@param
	@param
	@return 0 if ok
	*/
	int memcmp(void *buffer, uint32_t sizebuf);
	/**
	@brief
	@param
	@param
	@return >=0 - the begin of mem; <0 - negative
	*/
	int mem_search(void *buffer, uint32_t sizebuf);

    void init(uint32_t size)
    {
        _buffer = new uint8_t[size];
        _size = size;
        clear();
    }

    void init(void *buffer, uint32_t size)
    {
    	_buffer = (uint8_t*)buffer;
        _size = size;
        clear();
    }

    void clear(void)
    {
        _tail = 0;
        _head = 0;
    }

    bool remove_range(uint32_t count)
    {
        if(count >= get_count())
        {
            clear();
            return(false);
        }
        mrb_plus(&_head, count);
        return(true);
    }

    uint32_t get_count(void)
    {
        if(_tail >= _head)
            return(_tail - _head);
        return(_size - _head + _tail);
    }

    uint16_t get_word_unsafe(uint32_t index)
    {
        if((index + 1) >= get_count())
            return(0);
        return((*this)[index] + ((uint16_t)(*this)[index + 1] << 8));
    }

    bool push(uint8_t byte)
    {
        _buffer[_tail] = byte;
        mrb_plus(&_tail, 1);

        if(_tail == _head)
        {
            mrb_plus(&_head, 1);
            return(false);
        }

        return(true);
    }

    uint8_t pop(void)
    {
        if(!get_count())
            return(0);
        uint8_t byte = _buffer[_head];
        mrb_plus(&_head, 1);
        return(byte);
    }

    uint8_t pop_unsafe(void)
    {
        uint8_t byte = _buffer[_head];
        mrb_plus(&_head, 1);
        return(byte);
    }

private:
	uint32_t _tail;
	uint32_t _head ;
	uint8_t *_buffer;
	uint32_t _size;

	void mrb_plus(uint32_t *par, int32_t plus)
	{
		if(plus<0 && (*par<(uint32_t)-plus))	{
			*par= *par + _size + plus;
			return;
		}
		*par = *par + plus;
		if(*par >=	_size)
			*par -= _size;
	}
};


}  // namespace utils

}  // namespace cm3ext

#endif
