/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic startup code for a Juce application.

  ==============================================================================
*/

#include "InterfaceComponent.h"

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
class BurstWalletApplication  : public JUCEApplication
{
public:
    //==============================================================================
    BurstWalletApplication()
	{
		PropertiesFile::Options options;
		options.commonToAllUsers = false;
		options.applicationName = ProjectInfo::projectName;
		options.folderName = "CryptoExtensions";
		options.filenameSuffix = "settings";
		options.osxLibrarySubFolder = "Application Support";
		options.storageFormat = PropertiesFile::storeAsXML;

		File f = options.getDefaultFile();
		bool showAbout = f.existsAsFile() == false;
		
		appProperties = new ApplicationProperties();
		appProperties->setStorageParameters(options);
	}

    const String getApplicationName() override       { return ProjectInfo::projectName; }
    const String getApplicationVersion() override    { return ProjectInfo::versionString; }
    bool moreThanOneInstanceAllowed() override       { return false; }

    //==============================================================================
    void initialise (const String& /*commandLine*/) override
    {
        if (CheckLatestVersion())
        {
            NativeMessageBox::showMessageBox(AlertWindow::InfoIcon, ProjectInfo::projectName, "Install the new version after downloading it via your browser.\nClosing " + String(ProjectInfo::projectName) + " now.");
            quit();
        }
        else mainWindow = new MainWindow (getApplicationName());
    }

    void shutdown() override
    {
        mainWindow = nullptr; // (deletes our window)
    }

    bool CheckLatestVersion()
    {
        String latestInfoStr = URL("https://api.github.com/repos/CurbShifter/BurstHotWallet/releases").readEntireTextStream(false);
        String versionTagStr = latestInfoStr.fromFirstOccurrenceOf("\"tag_name\":\"", false, true).upToFirstOccurrenceOf("\"", false, true);
        String revisionTagStr = versionTagStr.fromLastOccurrenceOf(".", false, true);

        // check if online revision is higher than local
    	if (revisionTagStr.getIntValue() > PROJECT_SVNRevisionN)
        {
            if (NativeMessageBox::showOkCancelBox(AlertWindow::WarningIcon, ProjectInfo::projectName, "A new version is available!\nDo you want to download the latest version?\n" + versionTagStr))
            {
#ifdef JUCE_WINDOWS
                juce::URL url(GITHUB_HOTWALLET_URL "releases/latest/download/BurstHotWallet.msi");
#elif JUCE_MAC
                juce::URL url(GITHUB_HOTWALLET_URL "releases/latest/download/BurstHotWallet.dmg");
#endif
                url.launchInDefaultBrowser();

                return true;
            }
        }
        return false;
    }

    //==============================================================================
    void systemRequestedQuit() override
    {
        // This is called when the app is being asked to quit: you can ignore this
        // request and let the app carry on running, or call quit() to allow the app to close.
        quit();
    }

    void anotherInstanceStarted (const String& /*commandLine*/) override
    {
        // When another instance of the app is launched while this one is running,
        // this method is invoked, and the commandLine parameter tells you what
        // the other instance's command-line arguments were.
    }

    //==============================================================================
    /*
        This class implements the desktop window that contains an instance of
        our MainContentComponent class.
    */
    class MainWindow    : public DocumentWindow
    {
    public:
        MainWindow (String name)  : DocumentWindow (name,
                                                    Colours::lightgrey,
                                                    DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar (true);
			InterfaceComponent *ic = new InterfaceComponent();
			setContentOwned(ic, true);

			juce::Rectangle<int> rMin = ic->getBounds();
			juce::Rectangle<int> rMax(rMin.withSize(1920, 1920));
			
			setResizable(true, true);
			setResizeLimits(rMin.getWidth(), rMin.getHeight(), rMax.getWidth(), rMax.getHeight());

			centreWithSize(getWidth(), getHeight());

			restoreWindowStateFromString(getAppProperties().getUserSettings()->getValue("mainWindowPos"));

            setVisible (true);
        }

		~MainWindow()
		{
			getAppProperties().getUserSettings()->setValue("mainWindowPos", getWindowStateAsString());
		}

        void closeButtonPressed() override
        {
            // This is called when the user tries to close this window. Here, we'll just
            // ask the app to quit when this happens, but you can change this to do
            // whatever you need.
            JUCEApplication::getInstance()->systemRequestedQuit();
        }

        /* Note: Be careful if you override any DocumentWindow methods - the base
           class uses a lot of them, so by overriding you might break its functionality.
           It's best to do all your work in your content component instead, but if
           you really have to override any DocumentWindow methods, make sure your
           subclass also calls the superclass's method.
        */

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MainWindow)
    };
	ScopedPointer<ApplicationProperties> appProperties;

private:
    ScopedPointer<MainWindow> mainWindow;
	TooltipWindow tooltipWindow;
};

static BurstWalletApplication& getApp()                      { return *dynamic_cast<BurstWalletApplication*>(JUCEApplication::getInstance()); }
ApplicationProperties& getAppProperties()           { return *getApp().appProperties; }


//==============================================================================
// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION (BurstWalletApplication)
