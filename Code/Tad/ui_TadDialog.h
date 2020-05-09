/********************************************************************************
** Form generated from reading UI file 'TadDialog.ui'
**
** Created: Sat May 9 10:19:17 2020
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TADDIALOG_H
#define UI_TADDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_TadDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label;
    QComboBox *mpAoi;
    QLabel *label_2;
    QDoubleSpinBox *mpEdgesInBackground;
    QLabel *label_3;
    QDoubleSpinBox *mpComponentSize;
    QLabel *label_4;
    QSpinBox *mpSampleSize;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *TadDialog)
    {
        if (TadDialog->objectName().isEmpty())
            TadDialog->setObjectName(QString::fromUtf8("TadDialog"));
        TadDialog->resize(338, 267);
        formLayout = new QFormLayout(TadDialog);
        formLayout->setContentsMargins(10, 10, 10, 10);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setHorizontalSpacing(10);
        formLayout->setVerticalSpacing(10);
        label = new QLabel(TadDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        mpAoi = new QComboBox(TadDialog);
        mpAoi->setObjectName(QString::fromUtf8("mpAoi"));

        formLayout->setWidget(0, QFormLayout::FieldRole, mpAoi);

        label_2 = new QLabel(TadDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        mpEdgesInBackground = new QDoubleSpinBox(TadDialog);
        mpEdgesInBackground->setObjectName(QString::fromUtf8("mpEdgesInBackground"));
        mpEdgesInBackground->setSingleStep(1);
        mpEdgesInBackground->setValue(10);

        formLayout->setWidget(1, QFormLayout::FieldRole, mpEdgesInBackground);

        label_3 = new QLabel(TadDialog);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        mpComponentSize = new QDoubleSpinBox(TadDialog);
        mpComponentSize->setObjectName(QString::fromUtf8("mpComponentSize"));
        mpComponentSize->setSingleStep(1);
        mpComponentSize->setValue(2);

        formLayout->setWidget(2, QFormLayout::FieldRole, mpComponentSize);

        label_4 = new QLabel(TadDialog);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        mpSampleSize = new QSpinBox(TadDialog);
        mpSampleSize->setObjectName(QString::fromUtf8("mpSampleSize"));
        mpSampleSize->setValue(10000);
        mpSampleSize->setMinimum(3);
        mpSampleSize->setMaximum(300000);
        mpSampleSize->setSingleStep(2);

        formLayout->setWidget(3, QFormLayout::FieldRole, mpSampleSize);

        buttonBox = new QDialogButtonBox(TadDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::FieldRole, buttonBox);


        retranslateUi(TadDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TadDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TadDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TadDialog);
    } // setupUi

    void retranslateUi(QDialog *TadDialog)
    {
        TadDialog->setWindowTitle(QApplication::translate("TadDialog", "TAD Detector", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("TadDialog", "Area of Interest", 0, QApplication::UnicodeUTF8));
        mpAoi->clear();
        mpAoi->insertItems(0, QStringList()
         << QApplication::translate("TadDialog", "<Entire Image>", 0, QApplication::UnicodeUTF8)
        );
        label_2->setText(QApplication::translate("TadDialog", "% Edges In Background", 0, QApplication::UnicodeUTF8));
        mpEdgesInBackground->setSuffix(QApplication::translate("TadDialog", " %", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("TadDialog", "% Component Size", 0, QApplication::UnicodeUTF8));
        mpComponentSize->setSuffix(QApplication::translate("TadDialog", " %", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("TadDialog", "Sample Size", 0, QApplication::UnicodeUTF8));
        mpSampleSize->setSuffix(QApplication::translate("TadDialog", " pixels", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TadDialog: public Ui_TadDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TADDIALOG_H
