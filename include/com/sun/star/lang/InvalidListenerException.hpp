#ifndef INCLUDED_COM_SUN_STAR_LANG_INVALIDLISTENEREXCEPTION_HPP
#define INCLUDED_COM_SUN_STAR_LANG_INVALIDLISTENEREXCEPTION_HPP

#include "sal/config.h"

#include "com/sun/star/lang/InvalidListenerException.hdl"

#include "com/sun/star/uno/Exception.hpp"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"

namespace com { namespace sun { namespace star { namespace lang {

inline InvalidListenerException::InvalidListenerException(
#if defined LIBO_USE_SOURCE_LOCATION
    std::experimental::source_location location
#endif
    )
    : ::css::uno::Exception(
#if defined LIBO_USE_SOURCE_LOCATION
    location
#endif
)
{ }

inline InvalidListenerException::InvalidListenerException(const ::rtl::OUString& Message_, const ::css::uno::Reference< ::css::uno::XInterface >& Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , std::experimental::source_location location
#endif
)
    : ::css::uno::Exception(Message_, Context_
#if defined LIBO_USE_SOURCE_LOCATION
    , location
#endif
)
{ }

#if !defined LIBO_INTERNAL_ONLY
InvalidListenerException::InvalidListenerException(InvalidListenerException const & the_other): ::css::uno::Exception(the_other) {}

InvalidListenerException::~InvalidListenerException() {}

InvalidListenerException & InvalidListenerException::operator =(InvalidListenerException const & the_other) {
    //TODO: Just like its implicitly-defined counterpart, this function definition is not exception-safe
    ::css::uno::Exception::operator =(the_other);
    return *this;
}
#endif

} } } }

namespace com { namespace sun { namespace star { namespace lang {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::lang::InvalidListenerException const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_static_compound_type_init( &the_type, typelib_TypeClass_EXCEPTION, "com.sun.star.lang.InvalidListenerException", * ::typelib_static_type_getByTypeClass( typelib_TypeClass_EXCEPTION ), 0,  0 );
    }
    return * reinterpret_cast< const ::css::uno::Type * >( &the_type );
}

} } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::lang::InvalidListenerException const *) {
    return ::cppu::UnoType< ::css::lang::InvalidListenerException >::get();
}

#endif // INCLUDED_COM_SUN_STAR_LANG_INVALIDLISTENEREXCEPTION_HPP
