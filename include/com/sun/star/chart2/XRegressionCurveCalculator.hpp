#ifndef INCLUDED_COM_SUN_STAR_CHART2_XREGRESSIONCURVECALCULATOR_HPP
#define INCLUDED_COM_SUN_STAR_CHART2_XREGRESSIONCURVECALCULATOR_HPP

#include "sal/config.h"

#include "com/sun/star/chart2/XRegressionCurveCalculator.hdl"

#include "com/sun/star/chart2/XScaling.hpp"
#include "com/sun/star/geometry/RealPoint2D.hpp"
#include "com/sun/star/uno/XInterface.hpp"
#include "com/sun/star/util/XNumberFormatsSupplier.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Sequence.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"
#include "sal/types.h"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace chart2 {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::chart2::XRegressionCurveCalculator const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_mi_interface_type_init( &the_type, "com.sun.star.chart2.XRegressionCurveCalculator", 0, 0 );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::chart2::XRegressionCurveCalculator > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::chart2::XRegressionCurveCalculator > >::get();
}

::css::uno::Type const & ::css::chart2::XRegressionCurveCalculator::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::chart2::XRegressionCurveCalculator >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::chart2::XRegressionCurveCalculator>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_CHART2_XREGRESSIONCURVECALCULATOR_HPP