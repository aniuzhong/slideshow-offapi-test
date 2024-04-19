#ifndef INCLUDED_COM_SUN_STAR_DRAWING_XMASTERPAGESSUPPLIER_HPP
#define INCLUDED_COM_SUN_STAR_DRAWING_XMASTERPAGESSUPPLIER_HPP

#include "sal/config.h"

#include "com/sun/star/drawing/XMasterPagesSupplier.hdl"

#include "com/sun/star/drawing/XDrawPages.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace drawing {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::drawing::XMasterPagesSupplier const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_mi_interface_type_init( &the_type, "com.sun.star.drawing.XMasterPagesSupplier", 0, 0 );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::drawing::XMasterPagesSupplier > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::drawing::XMasterPagesSupplier > >::get();
}

::css::uno::Type const & ::css::drawing::XMasterPagesSupplier::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::drawing::XMasterPagesSupplier >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::drawing::XMasterPagesSupplier>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_DRAWING_XMASTERPAGESSUPPLIER_HPP
