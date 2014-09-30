/*  This file is part of the Vc library. {{{
Copyright © 2013 Matthias Kretz <kretz@kde.org>
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.
    * Neither the names of contributing organizations nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

}}}*/

#ifndef VC_COMMON_CONST_H
#define VC_COMMON_CONST_H

#include <type_traits>
#include <Vc/global.h>

namespace Vc_VERSIONED_NAMESPACE
{
namespace Internal
{

template <int exponent> constexpr double exponentToFloat(std::integral_constant<bool, true>);
template <int exponent> constexpr double exponentToFloat(std::integral_constant<bool, false>);
template <> constexpr double exponentToFloat<0>(std::integral_constant<bool, true>)
{
    return 1.;
}
template <> constexpr double exponentToFloat<0>(std::integral_constant<bool, false>)
{
    return 1.;
}
template <> constexpr double exponentToFloat<-32>(std::integral_constant<bool, true>)
{
    return 1. / (65536. * 65536.);
}
template <> constexpr double exponentToFloat<32>(std::integral_constant<bool, false>)
{
    return 65536. * 65536.;
}
template <> constexpr double exponentToFloat<-64>(std::integral_constant<bool, true>)
{
    return 1. / (65536. * 65536. * 65536. * 65536.);
}
template <> constexpr double exponentToFloat<64>(std::integral_constant<bool, false>)
{
    return 65536. * 65536. * 65536. * 65536.;
}
template <int exponent>
constexpr double exponentToFloat(std::integral_constant<bool, false> negative)
{
    return exponentToFloat<exponent - 1>(negative) * 2.0;
}
template <int exponent>
constexpr double exponentToFloat(std::integral_constant<bool, true> negative)
{
    return exponentToFloat<exponent + 1>(negative) * 0.5;
}
template <int sign, unsigned long long mantissa, int exponent> constexpr double doubleConstant()
{
    return (static_cast<double>((mantissa & 0x000fffffffffffffull) | 0x0010000000000000ull) /
            0x0010000000000000ull) *
           exponentToFloat<exponent>(std::integral_constant<bool, (exponent < 0)>()) * sign;
}
template <int sign, unsigned int mantissa, int exponent> constexpr float floatConstant()
{
    return (static_cast<float>((mantissa & 0x007fffffu) | 0x00800000u) / 0x00800000u) *
           static_cast<float>(
               exponentToFloat<exponent>(std::integral_constant<bool, (exponent < 0)>())) *
           sign;
}

}  // namespace Internal
}  // namespace Vc

#endif // VC_COMMON_CONST_H
