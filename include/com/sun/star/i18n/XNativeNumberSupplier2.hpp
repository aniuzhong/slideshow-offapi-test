#ifndef INCLUDED_COM_SUN_STAR_I18N_XNATIVENUMBERSUPPLIER2_HPP
#define INCLUDED_COM_SUN_STAR_I18N_XNATIVENUMBERSUPPLIER2_HPP

#include "sal/config.h"

#include "com/sun/star/i18n/XNativeNumberSupplier2.hdl"

#include "com/sun/star/i18n/XNativeNumberSupplier.hpp"
#include "com/sun/star/lang/Locale.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace i18n {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::i18n::XNativeNumberSupplier2 const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_TypeDescriptionReference * aSuperTypes[1];
        aSuperTypes[0] = ::cppu::UnoType< const ::css::uno::Reference< ::css::i18n::XNativeNumberSupplier > >::get().getTypeLibType();
        typelib_static_mi_interface_type_init( &the_type, "com.sun.star.i18n.XNativeNumberSupplier2", 1, aSuperTypes );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::i18n::XNativeNumberSupplier2 > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::i18n::XNativeNumberSupplier2 > >::get();
}

::css::uno::Type const & ::css::i18n::XNativeNumberSupplier2::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::i18n::XNativeNumberSupplier2 >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::i18n::XNativeNumberSupplier2>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_I18N_XNATIVENUMBERSUPPLIER2_HPP
