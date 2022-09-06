#ifndef CHANGESETTINGS_H
#define CHANGESETTINGS_H

#include "qjsondocument.h"
#include <QDialog>


namespace Ui {
    class ChangeSettings;
    }

//!
//! \brief The ChangeSettings class
//!
class ChangeSettings : public QDialog
{
        Q_OBJECT

    public:
        QJsonDocument settings;
        void setSettings(QJsonDocument settings);
        void writeSettingValue(QString section, QString key, QString value);
        explicit ChangeSettings(QWidget *parent = nullptr);
        ~ChangeSettings();

    private slots:
        void on_save_clicked();

        void on_hammerBrowse_clicked();

        void on_facePoserBrowse_clicked();

        void on_modelViewerBrowse_clicked();

    private:
        Ui::ChangeSettings *ui;
};

#endif // CHANGESETTINGS_H
