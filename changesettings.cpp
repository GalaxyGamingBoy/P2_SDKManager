#include "changesettings.h"
#include "ui_changesettings.h"
#include "QFileDialog"
#include "QJsonObject"
#include "p2_sdkmanager.h"

//!
//! \brief ChangeSettings::ChangeSettings
//! \param parent
//! The ChangeSettings class
//!
ChangeSettings::ChangeSettings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeSettings)
    {
        ui->setupUi(this);
    }

//!
//! \brief ChangeSettings::~ChangeSettings
//! Deconstructor of ChangeSettings
//!
ChangeSettings::~ChangeSettings()
    {
        delete ui;
    }

//!
//! \brief ChangeSettings::setSettings
//! Sets the settings from a remote QJsonDocument to the local QJsonDocument.
//! Updates the labels of the tools to match the ones in the settings JSON.
//! \param settings The QJsonDocument to store locally.
//!
void ChangeSettings::setSettings(QJsonDocument settings)
    {
        ChangeSettings::settings = settings;
        ui->hammerBrowseLabel->setText(ChangeSettings::settings["paths"]["hammer"].toString());
        ui->facePoserBrowseLabel->setText(ChangeSettings::settings["paths"]["face_poser"].toString());
        ui->modelViewerBrowseLabel->setText(ChangeSettings::settings["paths"]["model_viewer"].toString());
    }

//!
//! \brief ChangeSettings::writeSettingValue
//! Writes a value to the settings.
//! \param section the json section to write the data.
//! \param key the key of the data.
//! \param value the value coresponding to the key.
//!
void ChangeSettings::writeSettingValue(QString section, QString key, QString value)
    {
        QJsonObject jsonObject = ChangeSettings::settings.object();
        QJsonValueRef settingRef = jsonObject.find(section).value();
        QJsonObject settingValue = settingRef.toObject();
        settingValue.insert(key, value);
        settingRef = settingValue;
        ChangeSettings::settings.setObject(jsonObject);
    }

//!
//! \brief ChangeSettings::on_save_clicked
//! Saves the JSON settings file
//!
void ChangeSettings::on_save_clicked()
{
        P2_SDKManager sdkManager;
        sdkManager.writeJSONFile(sdkManager.settingsFile, ChangeSettings::settings);
        close();
}

//!
//! \brief ChangeSettings::on_hammerBrowse_clicked
//! Opens native file explorer to select the hammer executable
//!
void ChangeSettings::on_hammerBrowse_clicked()
{
        QFileDialog qFileDialog;
        qFileDialog.setNameFilter("hammer.*");
        qFileDialog.exec();
        if (qFileDialog.selectedFiles().length() > 0)
        {
            ui->hammerBrowseLabel->setText(qFileDialog.selectedFiles()[0]);
            ChangeSettings::writeSettingValue("paths", "hammer", qFileDialog.selectedFiles()[0]);
        }
}

//!
//! \brief ChangeSettings::on_facePoserBrowse_clicked
//! Opens native file explorer to select face poser executable
//!
void ChangeSettings::on_facePoserBrowse_clicked()
{
        QFileDialog qFileDialog;
        qFileDialog.setNameFilter("hlfaceposer.*");
        qFileDialog.exec();
        if (qFileDialog.selectedFiles().length() > 0)
        {
            ui->facePoserBrowseLabel->setText(qFileDialog.selectedFiles()[0]);
            ChangeSettings::writeSettingValue("paths", "face_poser", qFileDialog.selectedFiles()[0]);
        }
}

//!
//! \brief ChangeSettings::on_modelViewerBrowse_clicked
//! Opens native file explorer to select model viewer executable
//!
void ChangeSettings::on_modelViewerBrowse_clicked()
{
        QFileDialog qFileDialog;
        qFileDialog.setNameFilter("hlmv.*");
        qFileDialog.exec();
        if (qFileDialog.selectedFiles().length() > 0)
        {
            ui->modelViewerBrowseLabel->setText(qFileDialog.selectedFiles()[0]);
            ChangeSettings::writeSettingValue("paths", "model_viewer", qFileDialog.selectedFiles()[0]);
        }
}

