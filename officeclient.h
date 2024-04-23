#ifndef OFFICECLIENT_H
#define OFFICECLIENT_H

#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>
#include <com/sun/star/presentation/XPresentationSupplier.hpp>

class OfficeClient
{
public:
    OfficeClient() noexcept;
    OfficeClient(const OfficeClient&) = delete;
    OfficeClient& operator=(const OfficeClient &) = delete;
    OfficeClient(OfficeClient&&) noexcept = default;
    OfficeClient & operator=(OfficeClient&&) noexcept = default;

public:
    bool initialize() noexcept;
    bool loadPresentation(const char*) noexcept;
    bool start() noexcept;
    bool setFullScreen(bool) noexcept;
    bool getFullScreen(bool&) noexcept;

private:
    template <typename T>
    css::uno::Reference<T> qurey(rtl::OUString spec) noexcept
    {
        try
        {
            css::uno::Reference<T> inst(m_xMultiComponentFactory->createInstanceWithContext(spec, m_xRemoteContext),
                                        css::uno::UNO_QUERY);
            return inst;
        }
        catch (css::uno::Exception& e)
        {
            printf("css::uno::Exception: Could not create service of type. %s.\n", e.Message.toUtf8().getStr());
            return nullptr;
        }
        catch (...)
        {
            printf("Unknown exception: Could not create service of type.\n");
            return nullptr;
        }
    }

public:
    css::uno::Reference<css::lang::XMultiComponentFactory>        m_xMultiComponentFactory;
    css::uno::Reference<css::uno::XComponentContext>              m_xRemoteContext;
    css::uno::Reference<css::frame::XComponentLoader>             m_xComponentLoader;
    css::uno::Reference<css::presentation::XPresentationSupplier> m_xPresentationSupplier;
};

#endif // OFFICECLIENT_H
