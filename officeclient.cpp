#include <cppuhelper/bootstrap.hxx>
#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/presentation/XPresentation2.hpp>

#include "officeclient.h"

OfficeClient::OfficeClient() noexcept
    : m_xRemoteContext { nullptr }
    , m_xMultiComponentFactory { nullptr }
    , m_xPresentationSupplier { nullptr }
{
}

bool OfficeClient::connect() noexcept
{
    try
    {
        m_xRemoteContext = cppu::bootstrap();
        m_xMultiComponentFactory = m_xRemoteContext->getServiceManager();

        return true;
    }
    catch (css::uno::Exception& e)
    {
        printf("css::uno::Exception: %s.\n", e.Message.toUtf8().getStr());
        return false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        return false;
    }
}

bool OfficeClient::isAlive() noexcept
{
    try
    {
        if (m_xRemoteContext.is())
        {
            auto xMultiComponentFactory = m_xRemoteContext->getServiceManager();
            if (xMultiComponentFactory.is())
            {
                return true;
            }
            else
            {
                return false;
            }
        }
        else
        {
            return false;
        }
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());
        return false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        return false;
    }
}

bool OfficeClient::loadPresentation(const char* szURL) noexcept
{
    bool isLoaded = false;

    try
    {
        auto aURL = rtl::OUString::createFromAscii(szURL);
        css::uno::Sequence<css::beans::PropertyValue> loadProperties(0);

        auto xDesktop = qurey<css::frame::XDesktop>("com.sun.star.frame.Desktop");
        css::uno::Reference<css::frame::XComponentLoader> xComponentLoader(xDesktop, css::uno::UNO_QUERY);

        auto xComponent = xComponentLoader->loadComponentFromURL(aURL, "_blank", 0, loadProperties);

        if (!xComponent.is())
            return isLoaded;

        m_xPresentationSupplier = css::uno::Reference<css::presentation::XPresentationSupplier>(xComponent, css::uno::UNO_QUERY);
        auto xPresentation = m_xPresentationSupplier->getPresentation();

        isLoaded = true;
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());
        isLoaded = false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        isLoaded = false;
    }

    return isLoaded;
}

bool OfficeClient::start() noexcept
{
    if (!m_xPresentationSupplier.is())
        return false;

    bool isStarted = false;

    try
    {
        auto xPresentation = m_xPresentationSupplier->getPresentation();
        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);
        xPresentation2->start();
        isStarted = true;
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());
        isStarted = false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        isStarted = false;
    }

    return isStarted;
}

bool OfficeClient::setFullScreen(bool aValue) noexcept
{
    if (!m_xPresentationSupplier.is())
        return false;

    bool isSet = false;

    try
    {
        auto xPresentation = m_xPresentationSupplier->getPresentation();

        css::uno::Reference<css::beans::XPropertySet> xPropertySet(xPresentation, css::uno::UNO_QUERY);
        xPropertySet->setPropertyValue("IsFullScreen", css::uno::Any(aValue));

        isSet = true;
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());
        isSet = false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        isSet = false;
    }

    return isSet;
}

bool OfficeClient::getFullScreen(bool& aValue) noexcept
{
    if (!m_xPresentationSupplier.is())
        return false;

    bool isGot = false;

    try
    {
        auto xPresentation = m_xPresentationSupplier->getPresentation();

        css::uno::Reference<css::beans::XPropertySet> xPropertySet(xPresentation, css::uno::UNO_QUERY);
        auto isFullScreen = xPropertySet->getPropertyValue("IsFullScreen");
        isFullScreen >>= aValue;

        isGot = true;
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());
        isGot = false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        isGot = false;
    }

    return isGot;
}
