#ifndef REVMOB_REVMOB_H
#define REVMOB_REVMOB_H

// This file generates RevMob.h from iOS/RevMob.h during rake task.

namespace revmob {

    typedef enum TestingMode {
        kTestingModeUndefined,
        kTestingModeDisabled,
        kTestingModeWithAds,
        kTestingModeWithoutAds
    } TestingMode;

    class RevMob {
    public:

        static RevMob *SharedInstance();

        virtual void StartSession(const char *pAppID){};

        virtual void SetTestingMode (revmob::TestingMode pTestingMode = kTestingModeDisabled){};
        virtual TestingMode GetTestingMode(){ return kTestingModeUndefined; };

        virtual void PrintEnvironmentInformation(){};

        virtual void ShowFullscreen(){};
        virtual void LoadFullscreen(){};
        virtual void ShowLoadedFullscreen(){};
        virtual void ShowPopup(){};
        virtual void LoadPopup(){};
        virtual void ShowLoadedPopup(){};
        virtual void ShowBanner(){};
        virtual void HideBanner(){};
        virtual void LoadBanner(){};
        virtual void ShowLoadedBanner(){};
        virtual void HideLoadedBanner(){};
        virtual void OpenLink(){};
        virtual void LoadLink(){};
        virtual void OpenLoadedLink(){};

    private:
        RevMob(RevMob const&);
        RevMob& operator=(RevMob const&);

        static RevMob *sSharedInstance;

    protected:
        RevMob();
        virtual ~RevMob();


    };
    
    
} // namespace revmob

#endif /* REVMOB_REVMOBADS_H */
