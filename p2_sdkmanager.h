#ifndef P2_SDKMANAGER_H
#define P2_SDKMANAGER_H

#include "qjsondocument.h"
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class P2_SDKManager; }
QT_END_NAMESPACE

//!
//! \brief The P2_SDKManager class
//!
class P2_SDKManager : public QMainWindow
{
        Q_OBJECT

    public:
        QString settingsFile = "settings.json";
        QJsonDocument settings;
        QJsonDocument loadJSONFile(QString fileName);
        bool fileExists(QString fileName);
        void writeJSONFile(QString fileName, QJsonDocument jsonData);
        void reloadSettings();
        void runProccess(QString executable, QString flags);
        void openWebBrowser(QString webpage);
        P2_SDKManager(QWidget *parent = nullptr);
        ~P2_SDKManager();

    private slots:
        void on_actionSettings_triggered();

        void on_gameInfoBrowse_clicked();

        void on_hammer_clicked();

        void on_facePoser_clicked();

        void on_modelViewer_clicked();

        void on_VDCP2LevelDesign_clicked();

        void on_ChaosWiki_clicked();

    private:
        Ui::P2_SDKManager *ui;
        void windowInitialization(Ui::P2_SDKManager *ui);

};
#endif // P2_SDKMANAGER_H
