#include <cppuhelper/bootstrap.hxx>
#include <com/sun/star/frame/XDesktop.hpp>

#include "officeclient.h"

OfficeClient::OfficeClient() noexcept
    : m_xMultiComponentFactory { nullptr }
    , m_xComponentContext { nullptr }
    , m_xComponentLoader { nullptr }
{
}

bool OfficeClient::initialize() noexcept
{
    bool isInitialized = false;

    try
    {
        m_xComponentContext = cppu::bootstrap();
        m_xMultiComponentFactory = m_xComponentContext->getServiceManager();

        auto xDesktop = qurey<css::frame::XDesktop>("com.sun.star.frame.Desktop");
        m_xComponentLoader = css::uno::Reference<css::frame::XComponentLoader>(xDesktop, css::uno::UNO_QUERY);

        isInitialized =  true;
    }
    catch (css::uno::Exception& e)
    {
        printf("css::uno::Exception: %s.\n", e.Message.toUtf8().getStr());
        isInitialized =  false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        isInitialized =  false;
    }

    return isInitialized;
}
