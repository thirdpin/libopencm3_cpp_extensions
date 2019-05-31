#ifndef CM3CPP_FLASH_OTP_HPP_
#define CM3CPP_FLASH_OTP_HPP_

#include <libopencm3/stm32/flash.h>
#include <libopencmsis/core_cm3.h>

namespace cm3cpp {

namespace flash {

enum class OtpBlock : uint8_t
{
    BLOCK_0,
    BLOCK_1,
    BLOCK_2,
    BLOCK_3,
    BLOCK_4,
    BLOCK_5,
    BLOCK_6,
    BLOCK_7,
    BLOCK_8,
    BLOCK_9,
    BLOCK_10,
    BLOCK_11,
    BLOCK_12,
    BLOCK_13,
    BLOCK_14,
    BLOCK_15,
};

enum class OtpByte
{
    BYTE_0,
    BYTE_1,
    BYTE_2,
    BYTE_3,
    BYTE_4,
    BYTE_5,
    BYTE_6,
    BYTE_7,
    BYTE_8,
    BYTE_9,
    BYTE_10,
    BYTE_11,
    BYTE_12,
    BYTE_13,
    BYTE_14,
    BYTE_15,
    BYTE_16,
    BYTE_17,
    BYTE_18,
    BYTE_19,
    BYTE_20,
    BYTE_21,
    BYTE_22,
    BYTE_23,
    BYTE_24,
    BYTE_25,
    BYTE_26,
    BYTE_27,
    BYTE_28,
    BYTE_29,
    BYTE_30,
    BYTE_31,
};

enum class Flag
{
    BSY = FLASH_SR_BSY,
    PGSERR = FLASH_SR_PGSERR,
    PGPERR = FLASH_SR_PGPERR,
    PGAERR = FLASH_SR_PGAERR,
    WRPERR = FLASH_SR_WRPERR,
    OPERR = FLASH_SR_OPERR,
    EOP = FLASH_SR_EOP,
};

class FlashOtp
{
 public:
    static void write(OtpBlock block, OtpByte byte, uint8_t data)
    {
        flash_unlock();
        clear_flag(Flag::EOP);
        clear_flag(Flag::OPERR);
        clear_flag(Flag::WRPERR);
        clear_flag(Flag::PGAERR);
        clear_flag(Flag::PGPERR);
        clear_flag(Flag::PGSERR);
        flash_wait_for_last_operation();
        uint32_t address = _OTP_START_ADDR +
                           ((uint32_t)block * _OTP_BYTES_IN_BLOCK) +
                           (uint32_t)byte;
        __disable_irq();
        flash_program_byte(address, data);
        __enable_irq();
        flash_lock();
    }

    static uint8_t read(OtpBlock block, OtpByte byte)
    {
        uint32_t address = _OTP_START_ADDR +
                           ((uint32_t)block * _OTP_BYTES_IN_BLOCK) +
                           (uint32_t)byte;
        return *(uint8_t*)address;
    }

    static const uint8_t* const get_pointer(OtpBlock block, OtpByte byte)
    {
        uint32_t address = _OTP_START_ADDR +
                           ((uint32_t)block * _OTP_BYTES_IN_BLOCK) +
                           (uint32_t)byte;
        return (uint8_t*)address;
    }

    static bool get_flag(Flag flag)
    {
        uint32_t status = FLASH_SR | (uint32_t)flag;
        if (status > 0)
            return true;
        return false;
    }

    static void clear_flag(Flag flag)
    {
        if (flag == Flag::BSY)
            return;

        FLASH_SR |= (uint32_t)flag;
    }

 private:
    static constexpr uint32_t _OTP_START_ADDR = (0x1FFF7800);
    static constexpr uint32_t _OTP_LOCK_ADDR = (0x1FFF7A00);
    static constexpr uint32_t _OTP_BLOCKS = 16;
    static constexpr uint32_t _OTP_BYTES_IN_BLOCK = 32;
    static constexpr uint32_t _OTP_SIZE = (_OTP_BLOCKS * _OTP_BYTES_IN_BLOCK);
};

} /* namespace flash */

} /* namespace cm3cpp */

#endif /* CM3CPP_FLASH_OTP_HPP_ */
