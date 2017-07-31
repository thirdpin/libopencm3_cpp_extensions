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

#include "round_buffer.h"


namespace cm3cpp {

namespace utils {


RoundBuffer::RoundBuffer()
{
	init(ROUND_BUFFER_DEFAULT_SIZE);
}

RoundBuffer::RoundBuffer(uint32_t size)
{
	init(size);
}

uint32_t RoundBuffer::get(void *buffer, uint32_t index, uint32_t count)
{
	uint32_t cnt = get_count();
	uint32_t cnt_out = ((count + index) <= cnt) ? (count + index) : cnt;
	for( uint32_t i = index; i < cnt_out; i++)
		((uint8_t*)buffer)[i - index] = (*this)[i];
	return(cnt_out);
}

bool RoundBuffer::push(void *buffer, uint32_t count)
{
	bool result = true;

	for(uint32_t i = 0; i < count; i++)
		result = push(((uint8_t*)buffer)[i]);
	return result;
}

bool RoundBuffer::push(RoundBuffer *buffer, uint32_t count, bool withPop)
{
	bool result = true;
	uint32_t max_size = buffer->get_count();

	max_size = ((max_size<count) ? max_size : count);

	if(max_size > 0)
    {
        if(withPop)
        {
            for(uint32_t i = 0; i < max_size; i++)
                result = push(buffer->pop());
        }

        else
        {
            for(uint32_t i = 0; i < max_size; i++)
                result = push(buffer->operator[](i));
        }
    }

	return result;
}

uint32_t RoundBuffer::pop(void *buffer, uint32_t count)
{
	uint32_t cnt = get_count();
	uint32_t cnt_out = (count <= cnt) ? count : cnt;

	for(uint32_t i = 0; i < cnt_out; i++)
		((uint8_t*)buffer)[i] = pop();

	return(cnt_out);
}

uint32_t RoundBuffer::pop(uint32_t count)
{
	uint32_t cnt = get_count();
	uint32_t cnt_out = (count <= cnt) ? count : cnt;

	for(uint32_t i = 0; i < cnt_out; i++)
		pop();

	return(cnt_out);
}

int RoundBuffer::memcmp(  void *buffer, uint32_t sizebuf)
{
	uint8_t *buf = (uint8_t*)buffer;
	unsigned int cnt = get_count();

	if(!cnt || !sizebuf || (sizebuf > cnt))
		return(-1);

	uint32_t i = 0;
	while(i < sizebuf && buf[i] == (*this)[i])
		i++;
	if( i == sizebuf )
		return(0);	//???????
	return(i+1);
}

int RoundBuffer::mem_search(  void *buffer, uint32_t sizebuf)
{
	uint32_t cnt = get_count();
	if(cnt < sizebuf)
		return(-1);
	uint8_t *pbuf = (uint8_t*)buffer;
	for(uint32_t i_begin=0; i_begin<=(cnt-sizebuf); i_begin++) {
		uint32_t i_word;
		uint8_t byte;
		for(i_word=0; i_word<sizebuf; i_word++) {
			byte = (*this)[i_begin + i_word];
			if(byte != pbuf[i_word]) {
				if(i_word != 0)
					i_word = 0;
				break;
			}
		}
		if( i_word == sizebuf )
			return( i_begin);
	}
	return(-2);
}


}  // namespace utils

}  // namespace cm3ext
