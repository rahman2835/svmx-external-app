#include "pch.h"

#include "App.h"

#include "AutolinkedNativeModules.g.h"
#include "ReactPackageProvider.h"


using namespace winrt::SVMXExternalAPP;
using namespace winrt::SVMXExternalAPP::implementation;
using namespace winrt;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Navigation;
using namespace Windows::ApplicationModel;

/// <summary>
/// Initializes the singleton application object.  This is the first line of
/// authored code executed, and as such is the logical equivalent of main() or
/// WinMain().
/// </summary>
App::App() noexcept
{
//#if BUNDLE
//    JavaScriptBundleFile(L"index.windows");
//    InstanceSettings().UseWebDebugger(false);
//    InstanceSettings().UseFastRefresh(false);
//#else
//    JavaScriptMainModuleName(L"index");
//    InstanceSettings().UseWebDebugger(true);
//    InstanceSettings().UseFastRefresh(true);
//#endif
   JavaScriptBundleFile(L"index.windows");
    InstanceSettings().UseWebDebugger(false);
    InstanceSettings().UseFastRefresh(false);
    InstanceSettings().BundleRootPath(L"ms-appx:///Assets/");
#if _DEBUG
    InstanceSettings().UseDeveloperSupport(true);
#else
    InstanceSettings().UseDeveloperSupport(false);
#endif

    RegisterAutolinkedNativeModulePackages(PackageProviders()); // Includes any autolinked modules

    PackageProviders().Append(make<ReactPackageProvider>()); // Includes all modules in this project

    InitializeComponent();
}

/// <summary>
/// Invoked when the application is launched normally by the end user.  Other entry points
/// will be used such as when the application is launched to open a specific file.
/// </summary>
/// <param name="e">Details about the launch request and process.</param>
void App::OnLaunched(activation::LaunchActivatedEventArgs const& e)
{
    super::OnLaunched(e);

    Frame rootFrame = Window::Current().Content().as<Frame>();
    rootFrame.Navigate(xaml_typename<SVMXExternalAPP::MainPage>(), box_value(e.Arguments()));
}


/// <summary>
/// Invoked when application execution is being suspended.  Application state is saved
/// without knowing whether the application will be terminated or resumed with the contents
/// of memory still intact.
/// </summary>
/// <param name="sender">The source of the suspend request.</param>
/// <param name="e">Details about the suspend request.</param>
void App::OnSuspending([[maybe_unused]] IInspectable const& sender, [[maybe_unused]] SuspendingEventArgs const& e)
{
    // Save application state and stop any background activity
}

/// <summary>
/// Invoked when Navigation to a certain page fails
/// </summary>
/// <param name="sender">The Frame which failed navigation</param>
/// <param name="e">Details about the navigation failure</param>
void App::OnNavigationFailed(IInspectable const&, NavigationFailedEventArgs const& e)
{
    throw hresult_error(E_FAIL, hstring(L"Failed to load Page ") + e.SourcePageType().Name);
}
void App::OnActivated(Windows::ApplicationModel::Activation::IActivatedEventArgs const& args)
{
    if (args.Kind() == Windows::ApplicationModel::Activation::ActivationKind::Protocol)
    {
        super::OnActivated(args);
        //auto eventArgs{ args.as<Windows::ApplicationModel::Activation::ProtocolActivatedEventArgs>() };

        // TODO: Handle URI activation.
        // The received URI is eventArgs.Uri().RawUri().
        auto protocolActivatedEventArgs{ args.as<Windows::ApplicationModel::Activation::ProtocolActivatedEventArgs>() };
        // TODO: Handle URI activation  
        auto receivedURI{ protocolActivatedEventArgs.Uri().RawUri() };
        /*auto message = "no parameters passed";
        auto queryString = protocolActivatedEventArgs.Uri().Query;
        auto absolutePath = protocolActivatedEventArgs.Uri().AbsoluteUri;
        message = "Query String: {queryString}\n AbsolutePath: {absolutePath}";*/
        Frame rootFrame = Window::Current().Content().as<Frame>();
        if (rootFrame == nullptr) {
            rootFrame = Frame();
            rootFrame.NavigationFailed({ this, &App::OnNavigationFailed });
            if (rootFrame.Content() == nullptr)
            {
                // When the navigation stack isn't restored navigate to the first page,
                // configuring the new page by passing required information as a navigation
                // parameter
                rootFrame.Navigate(xaml_typename<SVMXExternalAPP::MainPage>(), box_value(receivedURI));
            }
            // Place the frame in the current Window
            Window::Current().Content(rootFrame);
            // Ensure the current window is active
            Window::Current().Activate();
        }
        else {
            rootFrame.Navigate(xaml_typename<SVMXExternalAPP::MainPage>(), box_value(receivedURI));
            Window::Current().Activate();

        }
        //rootFrame.Navigate(xaml_typename<SVMXExternalAPP::MainPage>(), box_value(eventArgs.Uri().RawUri()));
       
    }
    else {
        Frame rootFrame = Window::Current().Content().as<Frame>();
        rootFrame.Navigate(xaml_typename<SVMXExternalAPP::MainPage>(), NULL);
        Window::Current().Activate();
    }
}
