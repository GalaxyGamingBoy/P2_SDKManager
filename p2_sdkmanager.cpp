#include "p2_sdkmanager.h"
#include "./ui_p2_sdkmanager.h"
#include "QFile"
#include "QJsonDocument"
#include "changesettings.h"
#include "QFileDialog"
#include "QProcess"
#include "QDesktopServices"

//!
//! \brief P2_SDKManager::P2_SDKManager
//! \param parent
//! The P2_SDKManager class
//!
P2_SDKManager::P2_SDKManager(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::P2_SDKManager)
    {
        QString settingsFileLocation(P2_SDKManager::settingsFile);
        ui->setupUi(this);
        // If settings file exist, load it otherwise launch creation wizard
        if (P2_SDKManager::fileExists(settingsFileLocation))
        {
            P2_SDKManager::settings = P2_SDKManager::loadJSONFile(settingsFileLocation);
            P2_SDKManager::windowInitialization(ui);

        } else {
            QTextStream(stdout) << "Settings file not Found. Exiting...\nTemplate can be found here: https://github.com/GalaxyGamingBoy/P2_SDKManager/blob/master/settings.json\n";
            exit(1);
        }
    }

//!
//! \brief P2_SDKManager::~P2_SDKManager
//! Deconstructor of P2_SDKManager
//!
P2_SDKManager::~P2_SDKManager()
    {
        delete ui;
    }

//!
//! \brief P2_SDKManager::windowInitialization
//! \param ui
//! Runs after the settings.json file has been loaded
//!
void P2_SDKManager::windowInitialization(Ui::P2_SDKManager *ui)
    {
        QJsonDocument settings = P2_SDKManager::settings;
        ui->gameInfoLabel->setText(settings["paths"]["gameinfo"].toString());
    }

//!
//! \brief P2_SDKManager::fileExists
//! Checks if file exists
//! \param fileName the filename to check
//! \return true if exists, false if it doesn't
//!
bool P2_SDKManager::fileExists(QString fileName)
    {
        QFile fileToCheck(fileName);
        return fileToCheck.exists();
    }

//!
//! \brief P2_SDKManager::loadJSONFile
//! Loads a JSON File
//! \param fileName the filename to load
//! \return the json document ( as QJsonDocument )
//!
QJsonDocument P2_SDKManager::loadJSONFile(QString fileName)
    {
        QFile jsonFile(fileName);
        jsonFile.open(QIODevice::ReadOnly);
        QByteArray jsonFileContent = jsonFile.readAll();
        jsonFile.close();
        return QJsonDocument::fromJson(jsonFileContent);
    }

//!
//! \brief P2_SDKManager::writeJSONFile
//! Writes a JSON File
//! \param fileName the filename to write
//! \param jsonData the data to write to the json file
//!
void P2_SDKManager::writeJSONFile(QString fileName, QJsonDocument jsonData)
    {
        QFile jsonFile(fileName);
        jsonFile.open(QFile::WriteOnly | QFile::Text | QFile::Truncate);
        jsonFile.write(jsonData.toJson());
        jsonFile.close();
    }

//!
//! \brief P2_SDKManager::runProccess
//! \param executable to run
//! \param flags to append
//!
void P2_SDKManager::runProccess(QString executable, QString flags)
    {
        QProcess::startDetached(executable + " " + flags);
    }

//!
//! \brief P2_SDKManager::openWebBrowser
//! Open the native web browser
//! \param webpage the url to open
//!
void P2_SDKManager::openWebBrowser(QString webpage)
    {
        QDesktopServices::openUrl(QUrl(webpage));
    }

//!
//! \brief P2_SDKManager::on_actionSettings_triggered
//! Opens the settings menu
//!
void P2_SDKManager::on_actionSettings_triggered()
{
        ChangeSettings changeSettings;
        changeSettings.setModal(true);
        changeSettings.setSettings(P2_SDKManager::settings);
        changeSettings.exec();
        P2_SDKManager::settings = changeSettings.settings;
}

//!
//! \brief P2_SDKManager::on_gameInfoBrowse_clicked
//! Opens native file browser to pick gameinfo.txt
//!
void P2_SDKManager::on_gameInfoBrowse_clicked()
{
        // Initalizations
        ChangeSettings changeSettings;
        QFileDialog qFileDialog;

        // Open Native File Browser
        qFileDialog.setNameFilter("gameinfo.txt");
        qFileDialog.exec();

        // Get path and update settings
        if ( qFileDialog.selectedFiles().length() > 0 )
        {
            QString gameInfoPath = qFileDialog.directoryUrl().path().remove(0, 1);
            ui->gameInfoLabel->setText(gameInfoPath);
            changeSettings.setSettings(P2_SDKManager::settings);
            changeSettings.writeSettingValue("paths", "gameinfo", gameInfoPath);
        }

        // Write setting JSON
        P2_SDKManager::writeJSONFile(P2_SDKManager::settingsFile, changeSettings.settings);
}

//!
//! \brief P2_SDKManager::on_hammer_clicked
//! Runs when the Hammer button is clicked
//!
void P2_SDKManager::on_hammer_clicked()
{
        P2_SDKManager::runProccess(P2_SDKManager::settings["paths"]["hammer"].toString(), "");
}

//!
//! \brief P2_SDKManager::on_facePoser_clicked
//! Runs when the Face Poser button is clicked
//!
void P2_SDKManager::on_facePoser_clicked()
{
        P2_SDKManager::runProccess(P2_SDKManager::settings["paths"]["face_poser"].toString(), "-game \"" + P2_SDKManager::settings["paths"]["gameinfo"].toString() + "\"");
}

//!
//! \brief P2_SDKManager::on_modelViewer_clicked
//! Runs when the model viewer button is clicked
//!
void P2_SDKManager::on_modelViewer_clicked()
{
    P2_SDKManager::runProccess(P2_SDKManager::settings["paths"]["model_viewer"].toString(), "-game \"" + P2_SDKManager::settings["paths"]["gameinfo"].toString() + "\"");
}

//!
//! \brief P2_SDKManager::on_VDCP2LevelDesign_clicked
//! Opens the Valve Developer Community to the section of P2 Level Design on the native web browser
//!
void P2_SDKManager::on_VDCP2LevelDesign_clicked()
{
        P2_SDKManager::openWebBrowser("https://developer.valvesoftware.com/wiki/Category:Portal_2_Level_Design");
}

//!
//! \brief P2_SDKManager::on_ChaosWiki_clicked
//! Opens the Chaos Wiki on the native web browser
//!
void P2_SDKManager::on_ChaosWiki_clicked()
{
    P2_SDKManager::openWebBrowser("https://chaosinitiative.github.io/Wiki/");
}

//!
//! \brief P2_SDKManager::on_actionUpdate_Latest_Version_triggered
//! Updates t othe latest version
//!
void P2_SDKManager::on_actionUpdate_Latest_Version_triggered()
{
#ifdef Q_OS_WINDOWS
        QTextStream(stdout) << "Version: Windows\n";
        P2_SDKManager::runProccess("python .\\AutoUpdater.py P2_SDKManager release_p2-sdk-manager_win64 p2-sdk-manager", "");
#elif Q_OS_LINUX
        QTextStream(stdout) << "Version: Linux\n";
        P2_SDKManager::runProccess("python3 ./AutoUpdater.py P2_SDKManager release_p2-sdk-manager_gnulinux.debian-compile p2-sdk-manager", "");
#elif Q_OS_MACX
        QTextStream(stdout) << "Version: Mac\n";
        QMessageBox messageBox;
        messageBox.critical(0,"Error","AutoUpdate platform not supported. Update manually.!");
        messageBox.setFixedSize(500,200);
#else
        QTextStream(stdout) << "Version: Else\n";
        QMessageBox messageBox;
        messageBox.critical(0,"Error","AutoUpdate platform not supported. Update manually.!");
        messageBox.setFixedSize(500,200);
#endif
}

