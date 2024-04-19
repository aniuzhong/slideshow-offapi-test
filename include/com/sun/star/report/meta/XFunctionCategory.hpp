#ifndef INCLUDED_COM_SUN_STAR_REPORT_META_XFUNCTIONCATEGORY_HPP
#define INCLUDED_COM_SUN_STAR_REPORT_META_XFUNCTIONCATEGORY_HPP

#include "sal/config.h"

#include "com/sun/star/report/meta/XFunctionCategory.hdl"

#include "com/sun/star/beans/XPropertySet.hpp"
#include "com/sun/star/container/XIndexAccess.hpp"
#include "com/sun/star/report/meta/XFunctionDescription.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace report { namespace meta {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::report::meta::XFunctionCategory const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_TypeDescriptionReference * aSuperTypes[2];
        aSuperTypes[0] = ::cppu::UnoType< const ::css::uno::Reference< ::css::beans::XPropertySet > >::get().getTypeLibType();
        aSuperTypes[1] = ::cppu::UnoType< const ::css::uno::Reference< ::css::container::XIndexAccess > >::get().getTypeLibType();
        typelib_static_mi_interface_type_init( &the_type, "com.sun.star.report.meta.XFunctionCategory", 2, aSuperTypes );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::report::meta::XFunctionCategory > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::report::meta::XFunctionCategory > >::get();
}

::css::uno::Type const & ::css::report::meta::XFunctionCategory::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::report::meta::XFunctionCategory >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::report::meta::XFunctionCategory>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_REPORT_META_XFUNCTIONCATEGORY_HPP
