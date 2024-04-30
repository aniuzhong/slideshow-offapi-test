#include <cppuhelper/bootstrap.hxx>
#include <com/sun/star/frame/XDesktop.hpp>
#include <com/sun/star/util/XCloseable.hpp>
#include <com/sun/star/frame/XStorable.hpp>
#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/presentation/XPresentationSupplier.hpp>

#include "officeclient.h"

OfficeClient::OfficeClient() noexcept
    : m_xRemoteContext { nullptr }
    , m_xMultiComponentFactory { nullptr }
    , m_xComponent { nullptr }
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
    try
    {
        auto aURL = rtl::OUString::createFromAscii(szURL);
        css::uno::Sequence<css::beans::PropertyValue> loadProperties(0);

        auto xDesktop = qurey<css::frame::XDesktop>("com.sun.star.frame.Desktop");
        css::uno::Reference<css::frame::XComponentLoader> xComponentLoader(xDesktop, css::uno::UNO_QUERY);

        m_xComponent = xComponentLoader->loadComponentFromURL(aURL, "_blank", 0, loadProperties);

        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        return true;
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

void OfficeClient::closePresentation() noexcept
{
    try
    {
        if (m_xComponent.is())
        {
            css::uno::Reference<css::util::XCloseable> xCloseable(m_xComponent, css::uno::UNO_QUERY_THROW);
            xCloseable->close(false);
        }
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());

    }
    catch (...)
    {
        printf("Unknown exception.\n");
    }
}

bool OfficeClient::isPresentationAvailable() noexcept
{
    try
    {
        auto xPresentation = getXPresentation();
        return xPresentation.is();
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

bool OfficeClient::isRunning() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);

        return xPresentation2->isRunning();;
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

sal_Int32 OfficeClient::getSlideCount() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return -1;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return -1;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);

        auto xSlideShowController = xPresentation2->getController();
        if (!xSlideShowController.is())
            return -1;

        return xSlideShowController->getSlideCount();
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());
        return -1;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        return -1;
    }
}

bool OfficeClient::gotoNextEffect() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);

        if (!xPresentation2->isRunning())
            return false;

        auto xSlideShowController = xPresentation2->getController();
        if (!xSlideShowController.is())
            return false;

        xSlideShowController->gotoNextEffect();

        return true;
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

bool OfficeClient::gotoPreviousEffect() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);

        if (!xPresentation2->isRunning())
            return false;

        auto xSlideShowController = xPresentation2->getController();
        if (!xSlideShowController.is())
            return false;

        xSlideShowController->gotoPreviousEffect();

        return true;
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

bool OfficeClient::gotoFirstSlide() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);

        if (!xPresentation2->isRunning())
            return false;

        auto xSlideShowController = xPresentation2->getController();
        if (!xSlideShowController.is())
            return false;

        xSlideShowController->gotoFirstSlide();

        return true;
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

bool OfficeClient::gotoLastSlide() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);

        if (!xPresentation2->isRunning())
            return false;

        auto xSlideShowController = xPresentation2->getController();
        if (!xSlideShowController.is())
            return false;

        xSlideShowController->gotoLastSlide();

        return true;
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

bool OfficeClient::gotoNextSlide() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);

        if (!xPresentation2->isRunning())
            return false;

        auto xSlideShowController = xPresentation2->getController();
        if (!xSlideShowController.is())
            return false;

        xSlideShowController->gotoNextSlide();

        return true;
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

bool OfficeClient::gotoPreviousSlide() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);

        if (!xPresentation2->isRunning())
            return false;

        auto xSlideShowController = xPresentation2->getController();
        if (!xSlideShowController.is())
            return false;

        xSlideShowController->gotoPreviousSlide();

        return true;
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

bool OfficeClient::start() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);
        xPresentation2->start();

        return true;
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

bool OfficeClient::end() noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::presentation::XPresentation2> xPresentation2(xPresentation, css::uno::UNO_QUERY);
        xPresentation2->end();

        return true;
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

bool OfficeClient::setFullScreen(bool aValue) noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::beans::XPropertySet> xPropertySet(xPresentation, css::uno::UNO_QUERY);
        xPropertySet->setPropertyValue("IsFullScreen", css::uno::Any(aValue));

        return true;
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

bool OfficeClient::getFullScreen(bool& aValue) noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::beans::XPropertySet> xPropertySet(xPresentation, css::uno::UNO_QUERY);
        auto isFullScreen = xPropertySet->getPropertyValue("IsFullScreen");
        isFullScreen >>= aValue;

        return true;
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

bool OfficeClient::setEndless(bool aValue) noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::beans::XPropertySet> xPropertySet(xPresentation, css::uno::UNO_QUERY);
        xPropertySet->setPropertyValue("IsEndless", css::uno::Any(aValue));

        return true;
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

bool OfficeClient::getEndless(bool& aValue) noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        css::uno::Reference<css::beans::XPropertySet> xPropertySet(xPresentation, css::uno::UNO_QUERY);
        auto isEndless = xPropertySet->getPropertyValue("IsEndless");
        isEndless >>= aValue;

        return true;
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

bool OfficeClient::convertToPDF(const char* szURL) noexcept
{
    try
    {
        if (!m_xComponent.is())
            return false;

        auto xPresentation = getXPresentation();
        if (!xPresentation.is())
            return false;

        auto aURL = rtl::OUString::createFromAscii(szURL);

        css::uno::Reference<css::frame::XStorable> xStorable(m_xComponent, css::uno::UNO_QUERY_THROW);
        css::uno::Sequence<css::beans::PropertyValue> storeProps(3);
        storeProps[0].Name = "FilterName";
        storeProps[0].Value <<= rtl::OUString("impress_pdf_Export");
        storeProps[1].Name = "Overwrite";
        storeProps[1].Value <<= true;
        storeProps[2].Name = "SelectPdfVersion";
        storeProps[2].Value <<= sal_Int32(1);
        xStorable->storeToURL(aURL, storeProps);

        return true;
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

css::uno::Reference<com::sun::star::presentation::XPresentation> OfficeClient::getXPresentation()
{
    try
    {
        if (!m_xComponent.is())
            return nullptr;
        css::uno::Reference<css::presentation::XPresentationSupplier> xPresentationSupplier(m_xComponent,
                                                                                            css::uno::UNO_QUERY);
        // // Maybe not a presentation document
        // if (!xPresentationSupplier.is())
        //     return nullptr;

        auto xPresentation = xPresentationSupplier->getPresentation();
        if (!xPresentation.is())
            return nullptr;
        return xPresentation;
    }
    catch (css::uno::Exception& e)
    {
        printf("%s.\n", e.Message.toUtf8().getStr());
        return nullptr;
    }
    catch (...)
    {
        printf("Unknown exception.\n");
        return nullptr;
    }
}
