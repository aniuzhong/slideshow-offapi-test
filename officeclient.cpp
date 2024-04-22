#include <osl/file.hxx>
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

bool OfficeClient::loadPresentation(const rtl::OUString& aPath) noexcept
{
    bool isLoaded = false;

    try
    {
        rtl::OUString aURL;
        osl::FileBase::getFileURLFromSystemPath(aPath, aURL);

        css::uno::Sequence<css::beans::PropertyValue> loadProperties(0);
        auto xComponent = m_xComponentLoader->loadComponentFromURL(aURL, "_blank", 0, loadProperties);

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
