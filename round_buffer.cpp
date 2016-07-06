#include "../cpp_extensions/round_buffer.h"

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
