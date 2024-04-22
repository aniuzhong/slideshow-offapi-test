#ifndef OFFICECLIENT_H
#define OFFICECLIENT_H

#include <com/sun/star/frame/XComponentLoader.hpp>
#include <com/sun/star/lang/XMultiComponentFactory.hpp>

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

private:
    template <typename T>
    css::uno::Reference<T> qurey(rtl::OUString spec) noexcept
    {
        try
        {
            css::uno::Reference<T> inst(m_xMultiComponentFactory->createInstanceWithContext(spec, m_xComponentContext),
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

private:
    css::uno::Reference<css::lang::XMultiComponentFactory>        m_xMultiComponentFactory;
    css::uno::Reference<css::uno::XComponentContext>              m_xComponentContext;
    css::uno::Reference<css::frame::XComponentLoader>             m_xComponentLoader;
};

#endif // OFFICECLIENT_H