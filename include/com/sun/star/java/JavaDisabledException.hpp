#ifndef INCLUDED_COM_SUN_STAR_JAVA_JAVADISABLEDEXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_JAVA_JAVADISABLEDEXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/java/JavaDisabledException.hdl"

#include "com/sun/star/java/JavaInitializationException.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace java {

inline JavaDisabledException::JavaDisabledException(
#if defined LIBO_USE_SOURCE_LOCATION
    std::experimental::source_location location
#endif
    )
    : ::css::java::JavaInitializationException(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
{ }

inline JavaDisabledException::JavaDisabledException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , std::experimental::source_location location
#endif
)
    : ::css::java::JavaInitializationException(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
{ }

#if !defined LIBO_INTERNAL_ONLY
JavaDisabledException::JavaDisabledException(JavaDisabledException const & the_other): ::css::java::JavaInitializationException(the_other) {}

JavaDisabledException::~JavaDisabledException() {}

JavaDisabledException & JavaDisabledException::operator =(JavaDisabledException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::java::JavaInitializationException::operator =(the_other);
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace java {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::java::JavaDisabledException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        const ::css::uno::Type& rBaseType = ::cppu::UnoType< const ::css::java::JavaInitializationException >::get();

        typelib_static_compound_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.java.JavaDisabledException", rBaseType.getTypeLibType(), 0,  0 );
    }
    return * reinterpret_cast< const ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::java::JavaDisabledException const *) {
    return ::cppu::UnoType< ::css::java::JavaDisabledException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_JAVA_JAVADISABLEDEXCEPTION_HPP
