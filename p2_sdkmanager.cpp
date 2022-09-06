#include "p2_sdkmanager.h"
#include "./ui_p2_sdkmanager.h"
#include "QFile"
#include "QJsonDocument"
#include "changesettings.h"
#include "QFileDialog"

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
            QTextStream(stdout) << "Settings file not Found, Opening Settings\n";
            P2_SDKManager::on_actionSettings_triggered();
            P2_SDKManager::windowInitialization(ui);
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
        QString gameInfoPath = qFileDialog.directoryUrl().path().remove(0, 1);
        ui->gameInfoLabel->setText(gameInfoPath);
        changeSettings.setSettings(P2_SDKManager::settings);
        changeSettings.writeSettingValue("paths", "gameinfo", gameInfoPath);

        // Write setting JSON
        P2_SDKManager::writeJSONFile(P2_SDKManager::settingsFile, changeSettings.settings);
}

