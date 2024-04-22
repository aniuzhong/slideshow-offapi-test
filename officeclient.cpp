#include <cppuhelper/bootstrap.hxx>
#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/presentation/XPresentation2.hpp>

#include "officeclient.h"

OfficeClient::OfficeClient() noexcept
    : m_xMultiComponentFactory { nullptr }
    , m_xComponentContext { nullptr }
    , m_xComponentLoader { nullptr }
    , m_xPresentationSupplier { nullptr }
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

bool OfficeClient::loadPresentation(const char* szURL) noexcept
{
    bool isLoaded = false;

    try
    {
        auto aURL = rtl::OUString::createFromAscii(szURL);
        css::uno::Sequence<css::beans::PropertyValue> loadProperties(0);
        auto xComponent = m_xComponentLoader->loadComponentFromURL(aURL, "_blank", 0, loadProperties);

        if (!xComponent.is())
            return isLoaded;

        m_xPresentationSupplier = css::uno::Reference<css::presentation::XPresentationSupplier>(xComponent, css::uno::UNO_QUERY);
        auto xPresentation = m_xPresentationSupplier->getPresentation();

        isLoaded = true;
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());
        isLoaded =  false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        isLoaded =  false;
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
        isStarted =  false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        isStarted =  false;
    }

    return isStarted;
}

bool OfficeClient::setFullScreen(bool value) noexcept
{
    if (!m_xPresentationSupplier.is())
        return false;

    bool isSet = false;

    try
    {
        auto xPresentation = m_xPresentationSupplier->getPresentation();

        css::uno::Reference<css::beans::XPropertySet> xPropertySet(xPresentation, css::uno::UNO_QUERY);
        xPropertySet->setPropertyValue("IsFullScreen", css::uno::Any(value));

        isSet = true;
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());
        isSet =  false;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        isSet =  false;
    }

    return isSet;
}
