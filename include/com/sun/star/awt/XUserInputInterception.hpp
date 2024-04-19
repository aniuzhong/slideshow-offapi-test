#ifndef INCLUDED_COM_SUN_STAR_AWT_XUSERINPUTINTERCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_AWT_XUSERINPUTINTERCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/awt/XUserInputInterception.hdl"

#include "com/sun/star/awt/XKeyHandler.hpp"
#include "com/sun/star/awt/XMouseClickHandler.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace awt {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::awt::XUserInputInterception const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_mi_interface_type_init( &the_type, "com.sun.star.awt.XUserInputInterception", 0, 0 );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::awt::XUserInputInterception > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::awt::XUserInputInterception > >::get();
}

::css::uno::Type const & ::css::awt::XUserInputInterception::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::awt::XUserInputInterception >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::awt::XUserInputInterception>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_AWT_XUSERINPUTINTERCEPTION_HPP
