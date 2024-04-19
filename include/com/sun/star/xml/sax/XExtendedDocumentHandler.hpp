#ifndef INCLUDED_COM_SUN_STAR_XML_SAX_XEXTENDEDDOCUMENTHANDLER_HPP
#define INCLUDED_COM_SUN_STAR_XML_SAX_XEXTENDEDDOCUMENTHANDLER_HPP

#include "sal/config.h"

#include "com/sun/star/xml/sax/XExtendedDocumentHandler.hdl"

#include "com/sun/star/xml/sax/XDocumentHandler.hpp"
#include "com/sun/star/uno/Reference.hxx"
#include "com/sun/star/uno/Type.hxx"
#include "cppu/unotype.hxx"
#include "rtl/ustring.hxx"

#if defined LIBO_INTERNAL_ONLY
#include <type_traits>
#endif

namespace com { namespace sun { namespace star { namespace xml { namespace sax {

inline ::css::uno::Type const & cppu_detail_getUnoType(SAL_UNUSED_PARAMETER ::css::xml::sax::XExtendedDocumentHandler const *) {
    static typelib_TypeDescriptionReference * the_type = 0;
    if ( !the_type )
    {
        typelib_TypeDescriptionReference * aSuperTypes[1];
        aSuperTypes[0] = ::cppu::UnoType< const ::css::uno::Reference< ::css::xml::sax::XDocumentHandler > >::get().getTypeLibType();
        typelib_static_mi_interface_type_init( &the_type, "com.sun.star.xml.sax.XExtendedDocumentHandler", 1, aSuperTypes );
    }
    return * reinterpret_cast< ::css::uno::Type * >( &the_type );
}

} } } } }

SAL_DEPRECATED("use cppu::UnoType") inline ::css::uno::Type const & SAL_CALL getCppuType(SAL_UNUSED_PARAMETER ::css::uno::Reference< ::css::xml::sax::XExtendedDocumentHandler > const *) {
    return ::cppu::UnoType< ::css::uno::Reference< ::css::xml::sax::XExtendedDocumentHandler > >::get();
}

::css::uno::Type const & ::css::xml::sax::XExtendedDocumentHandler::static_type(SAL_UNUSED_PARAMETER void *) {
    return ::cppu::UnoType< ::css::xml::sax::XExtendedDocumentHandler >::get();
}

#if defined LIBO_INTERNAL_ONLY
namespace cppu::detail {
template<> struct IsUnoInterfaceType<::css::xml::sax::XExtendedDocumentHandler>: ::std::true_type {};
}
#endif

#endif // INCLUDED_COM_SUN_STAR_XML_SAX_XEXTENDEDDOCUMENTHANDLER_HPP
