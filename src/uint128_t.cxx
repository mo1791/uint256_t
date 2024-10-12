/******
** @file uint128_t.cxx
** @author your name (you@domain.com)
** @brief
** @version 0.1
** @date 2022-07-23
** @copyright Copyright (c) 2022
** @details An unsigned 128 bit integer type for C++
***********/

#include "source.hxx"
#include <array>


//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    const uint128_t uint128_0(0);
//  ----------------------------------------------------------------------------
    const uint128_t uint128_1(1);
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
    // constructors
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint128_t::uint128_t() noexcept
        : m_upper(0)
        , m_lower(0)
    {}
//  ----------------------------------------------------------------------------
    uint128_t::uint128_t(const uint128_t &rhs) noexcept
        : m_upper(rhs.m_upper)
        , m_lower(rhs.m_lower)
    {}
//  ----------------------------------------------------------------------------
    uint128_t::uint128_t(uint128_t &&rhs) noexcept
        : m_upper(std::exchange(rhs.m_upper, 0))
        , m_lower(std::exchange(rhs.m_lower, 0)) 
    {}
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------


//  ----------------------------------------------------------------------------
    // assignment operator
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator=(const uint128_t &rhs) noexcept
    {
        this->m_upper = rhs.m_upper;
        this->m_lower = rhs.m_lower;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator=(uint128_t &&rhs) noexcept
    {
        if (this != std::addressof(rhs))
        {
            this->m_upper = std::exchange(rhs.m_upper, 0);
            this->m_lower = std::exchange(rhs.m_lower, 0);
        }

        return *this;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------


//  ----------------------------------------------------------------------------
    // typecast operator
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint128_t::operator bool()     const noexcept { return (bool)(this->m_upper | this->m_lower); }
//  ----------------------------------------------------------------------------
    uint128_t::operator uint8_t()  const noexcept { return (uint8_t)this->m_lower; }
//  ----------------------------------------------------------------------------
    uint128_t::operator uint16_t() const noexcept { return (uint16_t)this->m_lower; }
//  ----------------------------------------------------------------------------
    uint128_t::operator uint32_t() const noexcept { return (uint32_t)this->m_lower; }
//  ----------------------------------------------------------------------------
    uint128_t::operator uint64_t() const noexcept { return (uint64_t)this->m_lower; }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator&(const uint128_t &rhs) const noexcept
    {
        return uint128_t( ( this->m_upper & rhs.m_upper ), ( this->m_lower & rhs.m_lower ) );
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------


//  ----------------------------------------------------------------------------
    // bitwise member operator
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator&=(const uint128_t &rhs) noexcept
    {
        this->m_upper &= rhs.m_upper;
        this->m_lower &= rhs.m_lower;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator|(const uint128_t &rhs) const noexcept
    {
        return uint128_t( ( this->m_upper | rhs.m_upper ), ( this->m_lower | rhs.m_lower ) );
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator|=(const uint128_t &rhs) noexcept
    {
        this->m_upper |= rhs.m_upper;
        this->m_lower |= rhs.m_lower;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator^(const uint128_t &rhs) const noexcept
    {
        return uint128_t( ( this->m_upper ^ rhs.m_upper ), ( this->m_lower ^ rhs.m_lower ) );
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator^=(const uint128_t &rhs) noexcept
    {
        this->m_upper ^= rhs.m_upper;
        this->m_lower ^= rhs.m_lower;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator~() const noexcept
    { 
        return uint128_t(~this->m_upper, ~this->m_lower);
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
    // Bit shift operator
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator<<(const uint128_t &rhs) const noexcept
    {
        const uint64_t shift = rhs.m_lower;
        
        if( ( (bool)rhs.m_upper ) || ( shift >= 128 ) )
        {
            return uint128_0;
        } 
        else if( shift == 64 )
        {
            return uint128_t(this->m_lower, 0);
        }
        else if ( shift == 0 )
        {
            return *this;
        } 
        else if (shift < 64)
        {
            return uint128_t( 
                        ( this->m_upper << shift ) + ( this->m_lower >> ( 64 - shift ) ),
                        ( this->m_lower << shift ) );
        } 
        else if ((128 > shift) && (shift > 64)) 
        {
            return uint128_t( ( this->m_lower << (shift - 64) ), 0);
        } 
        else 
        {
            return uint128_0;
        }
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator<<=(const uint128_t &rhs) noexcept
    {
        *this = *this << rhs;
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator>>(const uint128_t &rhs) const noexcept
    {
        const uint64_t shift = rhs.m_lower;

        if( ((bool)rhs.m_upper) || (shift >= 128) )
        {
            return uint128_0;
        }
        else if (shift == 64)
        {
            return uint128_t(0, this->m_upper);
        }
        else if (shift == 0)
        {
            return *this;
        }
        else if (shift < 64)
        {
            return uint128_t( ( this->m_upper >> shift ),
                              ( this->m_upper << (64 - shift) ) + (this->m_lower >> shift) );
        }
        else if ((128 > shift) && (shift > 64))
        {
            return uint128_t(0, (this->m_upper >> (shift - 64)));
        }
        else {
            return uint128_0;
        }
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator>>=(const uint128_t &rhs) noexcept
    {
        *this = *this >> rhs;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator<<(const bool &lhs, const uint128_t &rhs) noexcept
    { 
        return uint128_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator<<(const uint8_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator<<(const uint16_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator<<(const uint32_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator<<(const uint64_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator<<(const int8_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator<<(const int16_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator<<(const int32_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator<<(const int64_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator>>(const bool &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator>>(const uint8_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator>>(const uint16_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator>>(const uint32_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator>>(const uint64_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator>>(const int8_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator>>(const int16_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator>>(const int32_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t operator>>(const int64_t &lhs, const uint128_t &rhs) noexcept
    {
        return uint128_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
    // Logical operator
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    bool uint128_t::operator!() const noexcept
    { 
        return not (bool)(this->m_upper | this->m_lower);
    }
//  ----------------------------------------------------------------------------
    bool uint128_t::operator&&(const uint128_t &rhs) const noexcept
    {
        return ((bool)*this && rhs);
    }
//  ----------------------------------------------------------------------------
    bool uint128_t::operator||(const uint128_t &rhs) const noexcept
    {
        return ((bool)*this || rhs);
    }
//  ----------------------------------------------------------------------------
    bool uint128_t::operator==(const uint128_t &rhs) const noexcept
    {
        return  (this->m_upper == rhs.m_upper) &&
                (this->m_lower == rhs.m_lower);
    }
//  ----------------------------------------------------------------------------
    bool uint128_t::operator!=(const uint128_t &rhs) const noexcept
    {
        return  (this->m_upper != rhs.m_upper) |
                (this->m_lower != rhs.m_lower));
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
    // Comparaison operator
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    bool uint128_t::operator>(const uint128_t &rhs) const noexcept
    {
        if (this->m_upper == rhs.m_upper)
        {
            return this->m_lower > rhs.m_lower;
        }

        return this->m_upper > rhs.m_upper;
    }
//  ----------------------------------------------------------------------------
    bool uint128_t::operator<(const uint128_t &rhs) const noexcept
    {
        if (this->m_upper == rhs.m_upper)
        {
            return this->m_lower < rhs.m_lower;
        }

        return this->m_upper < rhs.m_upper;
    }
//  ----------------------------------------------------------------------------
    bool uint128_t::operator>=(const uint128_t &rhs) const noexcept
    {
        return (*this > rhs) | (*this == rhs);
    }
//  ----------------------------------------------------------------------------
    bool uint128_t::operator<=(const uint128_t &rhs) const noexcept
    {
        return (*this < rhs) | (*this == rhs);
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
    // Arithmetic operator
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator+(const uint128_t &rhs) const noexcept
    {
        return uint128_t(
                    this->m_upper + rhs.m_upper + ((this->m_lower + rhs.m_lower) < this->m_lower),
                    this->m_lower + rhs.m_lower);
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator+=(const uint128_t &rhs) noexcept
    {
        this->m_upper += rhs.m_upper + ((this->m_lower + rhs.m_lower) < this->m_lower);
        this->m_lower += rhs.m_lower;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator-(const uint128_t &rhs) const noexcept
    {
        return uint128_t(
                    this->m_upper - rhs.m_upper - ((this->m_lower - rhs.m_lower) > this->m_lower),
                    this->m_lower - rhs.m_lower);
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator-=(const uint128_t &rhs) noexcept
    {
        *this = *this - rhs;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator*(const uint128_t &rhs) const noexcept
    {
        // split values into 4 32-bit parts
        std::array<uint64_t, 4> top
        { 
            this->m_upper >> 32,
            this->m_upper & 0xffffffff, 
            this->m_lower >> 32,
            this->m_lower & 0xffffffff
        };
        
        std::array<uint64_t, 4> bottom
        {
            rhs.m_upper >> 32,
            rhs.m_upper & 0xffffffff,
            rhs.m_lower >> 32,
            rhs.m_lower & 0xffffffff
        };
        
        std::array<std::array<uint64_t, 4>, 4> products;


        // multiply each component of the values
        for (int y = 3; y > -1; y--)
        {
            for (int x = 3; x > -1; x--)
            {
                products[3 - x][y] = top[x] * bottom[y];
            }
        }

        // first row
        uint64_t fourth32  = (products[0][3] & 0xffffffff);
        uint64_t third32   = (products[0][2] & 0xffffffff) + (products[0][3] >> 32);
        uint64_t second32  = (products[0][1] & 0xffffffff) + (products[0][2] >> 32);
        uint64_t first32   = (products[0][0] & 0xffffffff) + (products[0][1] >> 32);

        // second row
        third32   += (products[1][3] & 0xffffffff);
        second32  += (products[1][2] & 0xffffffff) + (products[1][3] >> 32);
        first32   += (products[1][1] & 0xffffffff) + (products[1][2] >> 32);

        // third row
        second32  += (products[2][3] & 0xffffffff);
        first32   += (products[2][2] & 0xffffffff) + (products[2][3] >> 32);

        // fourth row
        first32   += (products[3][3] & 0xffffffff);

        // move carry to next digit
        third32   += fourth32 >> 32;
        second32  += third32 >> 32;
        first32   += second32 >> 32;

        // remove carry from current digit
        fourth32  &= 0xffffffff;
        third32   &= 0xffffffff;
        second32  &= 0xffffffff;
        first32   &= 0xffffffff;

        // combine components
        return uint128_t(
                    ( first32 << 32 ) | second32,
                    ( third32 << 32 ) | fourth32);
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator*=(const uint128_t &rhs) noexcept
    {
        *this = *this * rhs;

        return *this;
    }
//  ----------------------------------------------------------------------------
    std::pair<uint128_t, uint128_t> uint128_t::divmod(const uint128_t &lhs, const uint128_t &rhs) const
    {
        // Save some calculations
        if (rhs == uint128_0)
        {
            throw std::domain_error("Error: division or modulus by 0");
        }
        else if (rhs == uint128_1)
        {
            return std::pair<uint128_t, uint128_t>(lhs, uint128_0);
        }
        else if (lhs == rhs)
        {
            return std::pair<uint128_t, uint128_t>(uint128_1, uint128_0);
        }
        else if ((lhs == uint128_0) || (lhs < rhs))
        {
            return std::pair<uint128_t, uint128_t>(uint128_0, lhs);
        }

        std::pair<uint128_t, uint128_t> qr(uint128_0, uint128_0);

        for (uint8_t x = lhs.bits(); x > 0; x--)
        {
            qr.first  <<= uint128_1;
            qr.second <<= uint128_1;

            if ( ( lhs >> (x - 1U) ) & 1 )
            {
                qr.second++;
            }

            if (qr.second >= rhs)
            {
                qr.second -= rhs;
                qr.first++;
            }
        }

        return qr;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator/(const uint128_t &rhs) const
    {
        return divmod(*this, rhs).first;
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator/=(const uint128_t &rhs)
    {
        *this = *this / rhs;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator%(const uint128_t &rhs) const
    {
        return divmod(*this, rhs).second;
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator%=(const uint128_t &rhs)
    {
        *this = *this % rhs;

        return *this;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
    // Increment & Decrement operator
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator++() noexcept
    {
        return *this += uint128_1;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator++(int) noexcept
    {
        uint128_t temp(*this);
        ++(*this);

        return temp;
    }
//  ----------------------------------------------------------------------------
    uint128_t &uint128_t::operator--() noexcept
    {
        return *this -= uint128_1;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator--(int) noexcept
    {
        uint128_t temp(*this);
        --(*this);

        return temp;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator+() const noexcept
    {
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint128_t uint128_t::operator-() const noexcept
    {
        return ~(*this) + uint128_1;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
    // Getter
//  ----------------------------------------------------------------------------
//  ---------------------------------------------------------------------------- 
    const uint64_t &uint128_t::upper() const noexcept { return this->m_upper; }
//  ----------------------------------------------------------------------------
    const uint64_t &uint128_t::lower() const noexcept { return this->m_lower; }
//  ----------------------------------------------------------------------------
    uint8_t uint128_t::bits() const noexcept
    {
        uint8_t out = 0;
        
        if (this->m_upper)
        {
            out         = 64;
            uint64_t up = this->m_upper;

            while (up)
            {
                up >>= 1;
                out++;
            }
        }
        else {
            uint64_t low = this->m_lower;
            
            while (low)
            {
                low >>= 1;
                out++;
            }
        }

        return out;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------


//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    std::string uint128_t::str(uint8_t base, const unsigned int &len) const
    {
        if ((base < 2) || (base > 16))
        {
            throw std::invalid_argument("Base must be in the range [2, 16]");
        }

        std::string out = "";
        
        if ( not(*this) )
        {
            out = std::string("0");
        }
        else {
            std::pair<uint128_t, uint128_t> qr(*this, uint128_0);
            
            do {

                qr = divmod(qr.first, base);
                out = "0123456789abcdef"[(uint8_t)qr.second] + out;

            } while (qr.first);
        }

        if (out.size() < len)
        {
            out = std::string(len - out.size(), '0') + out;
        }
        
        return out;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------


//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream, const uint128_t &rhs)
    {
        if ( stream.flags() & stream.oct )
        {
            if ( stream.flags() & stream.showbase ) stream << "0";

            stream << rhs.str(8);
        }
        else if ( stream.flags() & stream.dec )
        {
            stream << rhs.str(10);
        }
        else if ( stream.flags() & stream.hex )
        {
            if ( stream.flags() & stream.showbase ) stream << "0x";

            stream << rhs.str(16);
        }
        
        return stream;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------