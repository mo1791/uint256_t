/**
 * @file uint256_t.cxx
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2022-07-23
 * @copyright Copyright (c) 2022
 * @details unsigned 256 bit integer type for C++
 */

#include <uint256_t.hxx>
#include <array>


//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    const uint128_t uint128_64(64);
//  ----------------------------------------------------------------------------
    const uint128_t uint128_128(128);
//  ----------------------------------------------------------------------------
    const uint128_t uint128_256(256);
//  ----------------------------------------------------------------------------
    const uint256_t uint256_0(0);
//  ----------------------------------------------------------------------------
    const uint256_t uint256_1(1);
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // CONSTRUCTORS
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t::uint256_t()
        : m_upper(uint128_0)
        , m_lower(uint128_0) 
    {}
//  ----------------------------------------------------------------------------
    uint256_t::uint256_t(const uint256_t &rhs)
        : m_upper(rhs.m_upper)
        , m_lower(rhs.m_lower)
    {}
//  ----------------------------------------------------------------------------
    uint256_t::uint256_t(uint256_t &&rhs)
        : m_upper(std::move(rhs.m_upper))
        , m_lower(std::move(rhs.m_lower))
    {
        if (this != &rhs)
        {
            rhs.m_upper = uint128_0;
            rhs.m_lower = uint128_0;
        }
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
    // ASSIGNMENT OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator=(const uint256_t &rhs)
    {
        m_upper = rhs.m_upper;
        m_lower = rhs.m_lower;
        
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator=(uint256_t &&rhs)
    {
        if (this != &rhs)
        {
            m_upper     = std::move(rhs.m_upper);
            m_lower     = std::move(rhs.m_lower);
            rhs.m_upper = uint128_0;
            rhs.m_lower = uint128_0;
        }

        return *this;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // TYPECAST OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t::operator bool() const       { return (bool)(m_upper | m_lower); }
//  ----------------------------------------------------------------------------
    uint256_t::operator uint8_t() const    { return (uint8_t)m_lower; }
//  ----------------------------------------------------------------------------
    uint256_t::operator uint16_t() const   { return (uint16_t)m_lower; }
//  ----------------------------------------------------------------------------
    uint256_t::operator uint32_t() const   { return (uint32_t)m_lower; }
//  ----------------------------------------------------------------------------
    uint256_t::operator uint64_t() const   { return (uint64_t)m_lower; }
//  ----------------------------------------------------------------------------
    uint256_t::operator uint128_t() const  { return m_lower; }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // BITWISE MEMBER OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator&(const uint128_t &rhs) const
    {
        return uint256_t(uint128_0, m_lower & rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator&(const uint256_t &rhs) const
    {
        return uint256_t(m_upper & rhs.m_upper, m_lower & rhs.m_lower);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator&=(const uint128_t &rhs)
    {
        m_upper  = uint128_0;
        m_lower &= rhs;
        
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator&=(const uint256_t &rhs)
    {
        m_upper &= rhs.m_upper;
        m_lower &= rhs.m_lower;
        
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator|(const uint128_t &rhs) const
    {
        return uint256_t(m_upper, m_lower | rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator|(const uint256_t &rhs) const
    {
        return uint256_t(m_upper | rhs.m_upper, m_lower | rhs.m_lower);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator|=(const uint128_t &rhs)
    {
        m_lower |= rhs;
        
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator|=(const uint256_t &rhs)
    {
        m_upper |= rhs.m_upper;
        m_lower |= rhs.m_lower;
    
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator^(const uint128_t &rhs) const
    {
        return uint256_t(m_upper, m_lower ^ rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator^(const uint256_t &rhs) const
    {
        return uint256_t(m_upper ^ rhs.m_upper, m_lower ^ rhs.m_lower);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator^=(const uint128_t &rhs)
    {
        m_lower ^= rhs;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator^=(const uint256_t &rhs)
    {
        m_upper ^= rhs.m_upper;
        m_lower ^= rhs.m_lower;
    
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator~() const
    { 
        return uint256_t(~m_upper, ~m_lower);
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // BITSHIFT MEMBER OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator<<(const uint128_t &rhs) const
    {
        return *this << uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator<<(const uint256_t &rhs) const
    {
        const uint128_t shift = rhs.m_lower;
    
        if ( ( (bool)rhs.m_upper ) || ( shift >= uint128_256 ) )
        {
            return uint256_0;
        } 
        else if (shift == uint128_128) 
        {
            return uint256_t(m_lower, uint128_0);
        } 
        else if (shift == uint128_0)
        {
            return *this;
        } 
        else if (shift < uint128_128)
        {
            return uint256_t((m_upper << shift) + (m_lower >> (uint128_128 - shift)),
                            ( m_lower << shift ));
        }
        else if ((uint128_256 > shift) && (shift > uint128_128))
        {
            return uint256_t(m_lower << (shift - uint128_128), uint128_0);
        } 
        else 
        {
            return uint256_0;
        }
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator<<=(const uint128_t &shift)
    {
        return *this <<= uint256_t(shift);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator<<=(const uint256_t &shift)
    {
        *this = *this << shift;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator>>(const uint128_t &rhs) const
    {
        return *this >> uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator>>(const uint256_t &rhs) const
    {
        const uint128_t shift = rhs.m_lower;

        if ( ( (bool)rhs.m_upper ) | ( shift >= uint128_256 ) )
        {
            return uint256_0;
        }
        else if (shift == uint128_128)
        {
            return uint256_t(m_upper);
        }
        else if (shift == uint128_0)
        {
            return *this;
        }
        else if (shift < uint128_128)
        {
            return uint256_t(m_upper >> shift,
                            (m_upper << (uint128_128 - shift)) + (m_lower >> shift));
        }
        else if ((uint128_256 > shift) && (shift > uint128_128))
        {
            return uint256_t(m_upper >> (shift - uint128_128));
        }
        else {
            return uint256_0;
        }
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator>>=(const uint128_t &shift)
    {
        return *this >>= uint256_t(shift);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator>>=(const uint256_t &shift)
    {
        *this = *this >> shift;
    
        return *this;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------



//  ----------------------------------------------------------------------------
    // LOGICAL MEMBER OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    bool uint256_t::operator!() const
    { 
        return not( (bool)*this );
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator&&(const uint128_t &rhs) const
    {
        return (*this && uint256_t(rhs));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator&&(const uint256_t &rhs) const
    {
        return ((bool)*this && (bool)rhs);
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator||(const uint128_t &rhs) const
    {
        return (*this || uint256_t(rhs));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator||(const uint256_t &rhs) const
    {
        return ((bool)*this || (bool)rhs);
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // COMPARAISON MEMBER OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    bool uint256_t::operator==(const uint128_t &rhs) const
    {
        return (*this == uint256_t(rhs));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator==(const uint256_t &rhs) const
    {
        return ((m_upper == rhs.m_upper) && (m_lower == rhs.m_lower));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator!=(const uint128_t &rhs) const
    {
        return (*this != uint256_t(rhs));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator!=(const uint256_t &rhs) const
    {
        return ((m_upper != rhs.m_upper) | (m_lower != rhs.m_lower));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator>(const uint128_t &rhs) const
    {
        return (*this > uint256_t(rhs));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator>(const uint256_t &rhs) const
    {
        if (m_upper == rhs.m_upper)
        {
            return (m_lower > rhs.m_lower);
        }

        if (m_upper > rhs.m_upper)
        {
            return true;
        }

        return false;
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator<(const uint128_t &rhs) const
    {
        return (*this < uint256_t(rhs));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator<(const uint256_t &rhs) const
    {
        if (m_upper == rhs.m_upper)
        {
            return (m_lower < rhs.m_lower);
        }

        if (m_upper < rhs.m_upper)
        {
            return true;
        }

        return false;
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator>=(const uint128_t &rhs) const
    {
        return (*this >= uint256_t(rhs));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator>=(const uint256_t &rhs) const
    {
        return ((*this > rhs) | (*this == rhs));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator<=(const uint128_t &rhs) const
    {
        return (*this <= uint256_t(rhs));
    }
//  ----------------------------------------------------------------------------
    bool uint256_t::operator<=(const uint256_t &rhs) const
    {
        return ((*this < rhs) | (*this == rhs));
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // ARITHMETIC MEMBER OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator+(const uint128_t &rhs) const
    {
        return *this + uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator+(const uint256_t &rhs) const
    {
        return uint256_t(
            m_upper + rhs.m_upper +
                (( (m_lower + rhs.m_lower) < m_lower ) ? uint128_1 : uint128_0 ),
            m_lower + rhs.m_lower);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator+=(const uint128_t &rhs)
    {
        return *this += uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator+=(const uint256_t &rhs)
    {
        m_upper = rhs.m_upper + m_upper + ((m_lower + rhs.m_lower) < m_lower);
        m_lower = m_lower + rhs.m_lower;
        
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator-(const uint128_t &rhs) const
    {
        return *this - uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator-(const uint256_t &rhs) const
    {
        return uint256_t(m_upper - rhs.m_upper - ((m_lower - rhs.m_lower) > m_lower),
                        m_lower - rhs.m_lower);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator-=(const uint128_t &rhs)
    {
        return *this -= uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator-=(const uint256_t &rhs)
    {
        *this = *this - rhs;

        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator*(const uint128_t &rhs) const
    {
        return *this * uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator*(const uint256_t &rhs) const
    {
        // split values into 4 64-bit parts
        std::array<uint128_t, 4> top 
        {
            m_upper.upper(),
            m_upper.lower(),
            m_lower.upper(),
            m_lower.lower()
        };

        std::array<uint128_t ,4> bottom
        {
            rhs.upper().upper(),
            rhs.upper().lower(),
            rhs.lower().upper(),
            rhs.lower().lower()
        };

        std::array<std::array<uint128_t, 4>, 4> products;

        // multiply each component of the values
        for (int y = 3; y > -1; y--)
        {
            for (int x = 3; x > -1; x--)
            {
                products[3 - y][x] = top[x] * bottom[y];
            }
        }

        // first row
        uint128_t fourth64  = uint128_t(products[0][3].lower());
        uint128_t third64   = uint128_t(products[0][2].lower()) + uint128_t(products[0][3].upper());
        uint128_t second64  = uint128_t(products[0][1].lower()) + uint128_t(products[0][2].upper());
        uint128_t first64   = uint128_t(products[0][0].lower()) + uint128_t(products[0][1].upper());

        // second row
        third64   += uint128_t(products[1][3].lower());
        second64  += uint128_t(products[1][2].lower()) + uint128_t(products[1][3].upper());
        first64   += uint128_t(products[1][1].lower()) + uint128_t(products[1][2].upper());

        // third row
        second64  += uint128_t(products[2][3].lower());
        first64   += uint128_t(products[2][2].lower()) + uint128_t(products[2][3].upper());

        // fourth row
        first64   += uint128_t(products[3][3].lower());


        // combines the values, taking care of carry over
        return uint256_t(first64 << uint128_64, uint128_0) + 
               uint256_t(third64.upper(), third64 << uint128_64) + 
               uint256_t(second64, uint128_0) + uint256_t(fourth64);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator*=(const uint128_t &rhs)
    {
        return *this *= uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator*=(const uint256_t &rhs) {
        *this = *this * rhs;

        return *this;
    }
//  ----------------------------------------------------------------------------
    std::pair<uint256_t, uint256_t> uint256_t::divmod(const uint256_t &lhs, const uint256_t &rhs) const
    {
        // Save some calculations /////////////////////
        if (rhs == uint256_0)
        {
            throw std::domain_error("Error: division or modulus by 0");
        }
        else if (rhs == uint256_1)
        {
            return std::pair<uint256_t, uint256_t>(lhs, uint256_0);
        }
        else if (lhs == rhs)
        {
            return std::pair<uint256_t, uint256_t>(uint256_1, uint256_0);
        }
        else if ((lhs == uint256_0) || (lhs < rhs))
        {
            return std::pair<uint256_t, uint256_t>(uint256_0, lhs);
        }

        std::pair<uint256_t, uint256_t> qr(uint256_0, lhs);

        uint256_t copyd = rhs << (lhs.bits() - rhs.bits());
        uint256_t adder = uint256_1 << (lhs.bits() - rhs.bits());
        
        if (copyd > qr.second)
        {
            copyd >>= uint256_1;
            adder >>= uint256_1;
        }
        
        while (qr.second >= rhs)
        {
            if (qr.second >= copyd)
            {
                qr.second -= copyd;
                qr.first  |= adder;
            }

            copyd >>= uint256_1;
            adder >>= uint256_1;
        }

        return qr;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator/(const uint128_t &rhs) const
    {
        return *this / uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator/(const uint256_t &rhs) const
    {
        return divmod(*this, rhs).first;
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator/=(const uint128_t &rhs)
    {
        return *this /= uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator/=(const uint256_t &rhs)
    {
        *this = *this / rhs;
    
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator%(const uint128_t &rhs) const
    {
        return *this % uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator%(const uint256_t &rhs) const
    {
        return *this - (rhs * (*this / rhs));
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator%=(const uint128_t &rhs)
    {
        return *this %= uint256_t(rhs);
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator%=(const uint256_t &rhs)
    {
        *this = *this % rhs;

        return *this;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // INCREMENT & DECREMENT MEMBER OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator++()
    {
        *this += uint256_1;
    
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator++(int)
    {
        uint256_t temp(*this);
        ++*this;
    
        return temp;
    }
//  ----------------------------------------------------------------------------
    uint256_t &uint256_t::operator--()
    {
        *this -= uint256_1;
    
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator--(int)
    {
        uint256_t temp(*this);
        --*this;

        return temp;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator+() const
    {
        return *this;
    }
//  ----------------------------------------------------------------------------
    uint256_t uint256_t::operator-() const
    {
        return ~*this + uint256_1;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // GETTER
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    const uint128_t &uint256_t::upper() const { return m_upper; }
//  ----------------------------------------------------------------------------
    const uint128_t &uint256_t::lower() const { return m_lower; }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint16_t uint256_t::bits() const
    {
        uint16_t out = 0;
        if (m_upper)
        {
            out          = 128;
            uint128_t up = m_upper;

            while (up)
            {
                up >>= uint128_1;
                out++;
            }
        }
        else
        {
            uint128_t low = m_lower;
           
            while (low)
            {
                low >>= uint128_1;
                out++;
            }
        }

        return out;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    std::string uint256_t::str(uint8_t base, const unsigned int &len) const
    {
        if ((base < 2) || (base > 36))
        {
            throw std::invalid_argument("Base must be in the range 2-36");
        }

        std::string out = "";
        
        if ( not(*this) )
        {
            out = std::string("0");
        }
        else
        {
            std::pair<uint256_t, uint256_t> qr(*this, uint256_0);
            
            do{

                qr = divmod(qr.first, base);
                out = "0123456789abcdefghijklmnopqrstuvwxyz"[(uint8_t)qr.second] + out;
            
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
    // BITWISE OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t operator&(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs & lhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator&=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (rhs & lhs).lower();

        return lhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator|(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs | lhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator|=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (rhs | lhs).lower();

        return lhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator^(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs ^ lhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator^=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (rhs ^ lhs).lower();

        return lhs;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // BITSHIFT OPERATOR
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const bool &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const uint8_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const uint16_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const uint32_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const uint64_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const uint128_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const int8_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const int16_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const int32_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator<<(const int64_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) << rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator<<=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (uint256_t(lhs) << rhs).lower();

        return lhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const bool &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const uint8_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const uint16_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const uint32_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const uint64_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const uint128_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const int8_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const int16_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const int32_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator>>(const int64_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) >> rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator>>=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (uint256_t(lhs) >> rhs).lower();
        
        return lhs;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // Comparison Operators
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    bool operator==(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs == lhs;
    }
//  ----------------------------------------------------------------------------
    bool operator!=(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs != lhs;
    }
//  ----------------------------------------------------------------------------
    bool operator>(const uint128_t &lhs, const uint256_t &rhs)
    { 
        return rhs < lhs;
    }
//  ----------------------------------------------------------------------------
    bool operator<(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs > lhs;
    }
//  ----------------------------------------------------------------------------
    bool operator>=(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs <= lhs;
    }
//  ----------------------------------------------------------------------------
    bool operator<=(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs >= lhs;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // Arithmetic Operators
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    uint256_t operator+(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs + lhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator+=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (rhs + lhs).lower();
       
        return lhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator-(const uint128_t &lhs, const uint256_t &rhs)
    {
        return -(rhs - lhs);
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator-=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (-(rhs - lhs)).lower();
    
        return lhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator*(const uint128_t &lhs, const uint256_t &rhs)
    {
        return rhs * lhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator*=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (rhs * lhs).lower();
    
        return lhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator/(const uint128_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) / rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator/=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (uint256_t(lhs) / rhs).lower();
    
        return lhs;
    }
//  ----------------------------------------------------------------------------
    uint256_t operator%(const uint128_t &lhs, const uint256_t &rhs)
    {
        return uint256_t(lhs) % rhs;
    }
//  ----------------------------------------------------------------------------
    uint128_t &operator%=(uint128_t &lhs, const uint256_t &rhs)
    {
        lhs = (uint256_t(lhs) % rhs).lower();
    
        return lhs;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------




//  ----------------------------------------------------------------------------
    // IO STREAM
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------
    std::ostream &operator<<(std::ostream &stream, const uint256_t &rhs)
    {
        if (stream.flags() & stream.oct)
        {
            stream << rhs.str(8);
        }
        else if (stream.flags() & stream.dec)
        {
            stream << rhs.str(10);
        }
        else if (stream.flags() & stream.hex)
        {
            stream << rhs.str(16);
        }
        
        return stream;
    }
//  ----------------------------------------------------------------------------
//  ----------------------------------------------------------------------------