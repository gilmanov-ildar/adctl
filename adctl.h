#ifndef ADMOBBANNERCTL_H
#define ADMOBBANNERCTL_H

#include <QObject>
#include <QPoint>
#include <QVariant>
#include <QSize>

class IQtAdMobBanner;
class IQtAdMobInterstitial;
class QTimer;
#ifdef Q_OS_ANDROID
class QAndroidJniObject;
#endif
class GAnalytics;

class AdCtl : public QObject
{
    Q_OBJECT
    //enabled properties
    Q_PROPERTY(bool adMobBannerEnabled READ AdMobBannerEnabled WRITE setAdMobBannerEnabled)
    Q_PROPERTY(bool adMobIinterstitialEnabled READ AdMobIinterstitialEnabled WRITE setAdMobIinterstitialEnabled)
    Q_PROPERTY(bool startAdBannerEnabled READ StartAdBannerEnabled WRITE setStartAdBannerEnabled)
    Q_PROPERTY(bool gAnalyticsEnabled READ GAnalyticsEnabled WRITE setGAnalyticsEnabled)

    //AdMob width and height
    Q_PROPERTY(int adMobBannerHeight READ AdMobBannerHeight NOTIFY adMobBannerHeightChanged)
    Q_PROPERTY(int adMobBannerWidth READ AdMobBannerWidth NOTIFY adMobBannerWidthChanged)

    //StartAd width and height
    Q_PROPERTY(int startAdBannerHeight READ StartAdBannerHeight NOTIFY startAdBannerHeightChanged)
    Q_PROPERTY(int startAdBannerWidth READ StartAdBannerWidth NOTIFY startAdBannerWidthChanged)

    //AdMob position
    Q_PROPERTY(QPoint adMobBannerPosition READ AdMobBannerPosition WRITE setAdMobBannerPosition)

    //StartAd position
    Q_PROPERTY(QPoint startAdBannerPosition READ StartAdBannerPosition WRITE setStartAdBannerPosition)
    //StartAd size
    Q_PROPERTY(QSize startAdBannerSize READ StartAdBannerSize WRITE setStartAdBannerSize)

    //Get real positions
    Q_PROPERTY(int adMobBannerRealX READ adMobBannerRealX)
    Q_PROPERTY(int AdMobBannerRealY READ adMobBannerRealY)
    Q_PROPERTY(int startAdBannerRealX READ startAdBannerRealX)
    Q_PROPERTY(int startAdBannerRealY READ startAdBannerRealY)

    //ids
    Q_PROPERTY(QString bannerAdMobId WRITE setBannerAdMobId)
    Q_PROPERTY(QString interstitialAdMobId WRITE setInterstitialAdMobId)
    Q_PROPERTY(QString startAdId WRITE setStartAdId)
    Q_PROPERTY(QString gAnalyticsId WRITE setGAnalyticsId)

    //list of test devices
    Q_PROPERTY(QStringList testDevices WRITE setTestDevices)

    //gpgs
    Q_PROPERTY(bool gpgsSignedIn READ isGPGSSignedIn WRITE setGPGSSignedIn NOTIFY gpgsSignedInChanged)

public:
    explicit AdCtl(QObject *parent = 0);
    ~AdCtl();

signals:
    //StartAd and AdMob
    void  adMobBannerShowed();
    void  startAdBannerShowed();
    void  adMobBannerHeightChanged(int height);
    void  adMobBannerWidthChanged(int width);
    void  startAdBannerHeightChanged(int height);
    void  startAdBannerWidthChanged(int width);
    void  gpgsSignedInChanged(bool gpgsSignedIn);

public slots:
    //init library with ids and bool flags
    void init();

    //Timer for control, update and emit properties changes for banners
    void adctlTimerSlot();

    //AdMob banner enabled
    void setAdMobBannerEnabled(const bool AdMobBannerEnabled);
    bool AdMobBannerEnabled() const;
    bool AdMobBannerIsLoaded() const;

    //AdMob interstitial enabled
    bool AdMobIinterstitialEnabled() const;
    void setAdMobIinterstitialEnabled(bool AdMobIinterstitialEnabled);
    bool AdMobIinterstitialIsLoaded() const;

    //StartAd banner enabled
    void setStartAdBannerEnabled(const bool StartAdBannerEnabled);
    bool StartAdBannerEnabled() const;

    //GAnalytics banner enabled
    void setGAnalyticsEnabled(const bool GAnalyticsEnabled);
    bool GAnalyticsEnabled() const;

    //AdMob width and height
    int AdMobBannerHeight() const;
    int AdMobBannerWidth() const;

    //StartAd width and height
    int StartAdBannerHeight() const;
    int StartAdBannerWidth() const;

    //AdMob set position
    void setAdMobBannerPosition(const QPoint AdMobBannerPosition);
    QPoint AdMobBannerPosition() const;

    //StartAd set position
    void setStartAdBannerPosition(const QPoint StartAdBannerPosition);
    QPoint StartAdBannerPosition() const;

    //StartAd set size
    void setStartAdBannerSize(const QSize StartAdBannerSize);
    QSize StartAdBannerSize() const;

    //Get Real Positions
    int adMobBannerRealX();
    int adMobBannerRealY();
    int startAdBannerRealX();
    int startAdBannerRealY();

    //ids
    void setBannerAdMobId(const QString &BannerAdMobId);
    void setInterstitialAdMobId(const QString &InterstitialAdMobId);
    void setStartAdId(const QString &StartAdId);
    void setGAnalyticsId(const QString &GAnalyticsId);

    //test devices
    void setTestDevices(const QStringList &testDevices);

    //ctl methods
    void showAdMobBanner();
    void hideAdMobBanner();
    void showAdMobInterstitial();
    void showStartAdBanner();
    void hideStartAdBanner();

    //Google Analytics
    void sendGaAppView(const QString &screenName = QString());
    void sendGaEvent(const QString &category = QString(),
                     const QString &action = QString(),
                     const QString &label = QString(),
                     const QVariant &value = QVariant());
    void endGaSession();

    //Google Play Game Services
    bool isGPGSSignedIn();
    void setGPGSSignedIn(bool gpgsSignedIn);

    void signInGPGS();
    void submitScoreGPGS(QString leaderBoardId, int score);
    void unlockAchievementGPGS(QString achievementId);
    void showLeaderboardGPGS();
    void showAchievementsGPGS();

    //dp, pt and mm
    float dp();
    float mm();
    float pt();

protected:
    //Timer for control, update and emit properties changes for banners
    QTimer *adctlTimer;

    //Pointers
    IQtAdMobBanner *m_AdMobBanner;
    IQtAdMobInterstitial *m_AdMobInterstitial;
    GAnalytics *gAnalytics;

    //Enabled control vars
    bool m_AdMobBannerEnabled = false;
    bool m_AdMobInterstitialEnabled = false;
    bool m_StartAdBannerEnabled = false;
    bool m_GAnalyticsEnabled = false;

    //ids
    QString m_BannerAdMobId;
    QString m_InterstitialAdMobId;
    QString m_StartAdId;
    QString m_GAnalyticsId;

    //test devices
    QStringList m_testDevices;

    //initialized
    bool m_AdInitialized = false;

    //jni
#ifdef Q_OS_ANDROID
    QAndroidJniObject *m_Activity;
#endif

    //cache
    int cacheAdMobBannerHeight;
    int cacheAdMobBannerWidth;
    int cacheStartAdBannerHeight;
    int cacheStartAdBannerWidth;

    //positions and sizes
    QPoint m_AdMobBannerPosition;
    QPoint m_StartAdBannerPosition;
    QSize m_StartAdBannerSize;

    //is banners showed
    bool m_isAdMobBannerShowed = false;
    bool m_isStartAdBannerShowed = false;
    bool m_AdMobBannerShowHideTrigger = false;
    bool m_StartAdBannerShowHideTrigger = false;

    //banners alredy visible bools
    bool m_AdMobWidthAlredyGreatThanZero = false;
    bool m_StartAdWidthAlredyGreatThanZero = false;

    //Google Play Game Services
    bool m_gpgsSignedIn;
    QTimer *gpgsTimer;

    float m_dp;
    float m_pt;
    float m_mm;
};

#endif // ADMOBBANNERCTL_H
