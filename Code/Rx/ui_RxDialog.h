/********************************************************************************
** Form generated from reading UI file 'RxDialog.ui'
**
** Created: Sat May 9 10:19:17 2020
**      by: Qt User Interface Compiler version 4.7.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_RXDIALOG_H
#define UI_RXDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QSpinBox>

QT_BEGIN_NAMESPACE

class Ui_RxDialog
{
public:
    QFormLayout *formLayout;
    QLabel *label_2;
    QDoubleSpinBox *mpThreshold;
    QLabel *label;
    QComboBox *mpAoi;
    QGroupBox *mpLocalGroup;
    QFormLayout *formLayout_2;
    QSpinBox *mpGroupWidth;
    QLabel *label_3;
    QSpinBox *mpGroupHeight;
    QLabel *label_4;
    QDialogButtonBox *buttonBox;
    QGroupBox *mpSubspaceGroup;
    QFormLayout *formLayout_3;
    QSpinBox *mpComponents;
    QLabel *label_5;

    void setupUi(QDialog *RxDialog)
    {
        if (RxDialog->objectName().isEmpty())
            RxDialog->setObjectName(QString::fromUtf8("RxDialog"));
        RxDialog->resize(338, 267);
        formLayout = new QFormLayout(RxDialog);
        formLayout->setContentsMargins(10, 10, 10, 10);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setHorizontalSpacing(10);
        formLayout->setVerticalSpacing(10);
        label_2 = new QLabel(RxDialog);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label_2);

        mpThreshold = new QDoubleSpinBox(RxDialog);
        mpThreshold->setObjectName(QString::fromUtf8("mpThreshold"));
        mpThreshold->setSingleStep(0.1);
        mpThreshold->setValue(2);

        formLayout->setWidget(0, QFormLayout::FieldRole, mpThreshold);

        label = new QLabel(RxDialog);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label);

        mpAoi = new QComboBox(RxDialog);
        mpAoi->setObjectName(QString::fromUtf8("mpAoi"));

        formLayout->setWidget(1, QFormLayout::FieldRole, mpAoi);

        mpLocalGroup = new QGroupBox(RxDialog);
        mpLocalGroup->setObjectName(QString::fromUtf8("mpLocalGroup"));
        mpLocalGroup->setCheckable(true);
        mpLocalGroup->setChecked(false);
        formLayout_2 = new QFormLayout(mpLocalGroup);
        formLayout_2->setContentsMargins(10, 10, 10, 10);
        formLayout_2->setObjectName(QString::fromUtf8("formLayout_2"));
        formLayout_2->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout_2->setHorizontalSpacing(5);
        formLayout_2->setVerticalSpacing(5);
        mpGroupWidth = new QSpinBox(mpLocalGroup);
        mpGroupWidth->setObjectName(QString::fromUtf8("mpGroupWidth"));
        mpGroupWidth->setMinimum(3);
        mpGroupWidth->setMaximum(100000);
        mpGroupWidth->setSingleStep(2);
        mpGroupWidth->setValue(25);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, mpGroupWidth);

        label_3 = new QLabel(mpLocalGroup);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        formLayout_2->setWidget(0, QFormLayout::LabelRole, label_3);

        mpGroupHeight = new QSpinBox(mpLocalGroup);
        mpGroupHeight->setObjectName(QString::fromUtf8("mpGroupHeight"));
        mpGroupHeight->setMinimum(3);
        mpGroupHeight->setMaximum(100000);
        mpGroupHeight->setSingleStep(2);
        mpGroupHeight->setValue(25);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, mpGroupHeight);

        label_4 = new QLabel(mpLocalGroup);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        formLayout_2->setWidget(1, QFormLayout::LabelRole, label_4);


        formLayout->setWidget(2, QFormLayout::SpanningRole, mpLocalGroup);

        buttonBox = new QDialogButtonBox(RxDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        formLayout->setWidget(4, QFormLayout::FieldRole, buttonBox);

        mpSubspaceGroup = new QGroupBox(RxDialog);
        mpSubspaceGroup->setObjectName(QString::fromUtf8("mpSubspaceGroup"));
        mpSubspaceGroup->setEnabled(true);
        mpSubspaceGroup->setCheckable(true);
        mpSubspaceGroup->setChecked(false);
        formLayout_3 = new QFormLayout(mpSubspaceGroup);
        formLayout_3->setContentsMargins(10, 10, 10, 10);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        formLayout_3->setHorizontalSpacing(5);
        formLayout_3->setVerticalSpacing(5);
        mpComponents = new QSpinBox(mpSubspaceGroup);
        mpComponents->setObjectName(QString::fromUtf8("mpComponents"));
        mpComponents->setMinimum(1);
        mpComponents->setMaximum(1000);
        mpComponents->setValue(3);

        formLayout_3->setWidget(0, QFormLayout::FieldRole, mpComponents);

        label_5 = new QLabel(mpSubspaceGroup);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        formLayout_3->setWidget(0, QFormLayout::LabelRole, label_5);


        formLayout->setWidget(3, QFormLayout::SpanningRole, mpSubspaceGroup);


        retranslateUi(RxDialog);
        QObject::connect(mpLocalGroup, SIGNAL(toggled(bool)), mpGroupHeight, SLOT(setEnabled(bool)));
        QObject::connect(mpLocalGroup, SIGNAL(toggled(bool)), mpGroupWidth, SLOT(setEnabled(bool)));
        QObject::connect(mpSubspaceGroup, SIGNAL(toggled(bool)), mpComponents, SLOT(setEnabled(bool)));
        QObject::connect(buttonBox, SIGNAL(accepted()), RxDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), RxDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(RxDialog);
    } // setupUi

    void retranslateUi(QDialog *RxDialog)
    {
        RxDialog->setWindowTitle(QApplication::translate("RxDialog", "RX Detector", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("RxDialog", "Threshold", 0, QApplication::UnicodeUTF8));
        mpThreshold->setSuffix(QApplication::translate("RxDialog", " stddev", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("RxDialog", "Area of Interest", 0, QApplication::UnicodeUTF8));
        mpAoi->clear();
        mpAoi->insertItems(0, QStringList()
         << QApplication::translate("RxDialog", "<Entire Image>", 0, QApplication::UnicodeUTF8)
        );
#ifndef QT_NO_TOOLTIP
        mpLocalGroup->setToolTip(QApplication::translate("RxDialog", "If checked, use local RX with the specified rectangular group size. If not checked, use global RX.", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mpLocalGroup->setTitle(QApplication::translate("RxDialog", "Local Group Size", 0, QApplication::UnicodeUTF8));
        mpGroupWidth->setSuffix(QApplication::translate("RxDialog", " pixels", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("RxDialog", "Width", 0, QApplication::UnicodeUTF8));
        mpGroupHeight->setSuffix(QApplication::translate("RxDialog", " pixels", 0, QApplication::UnicodeUTF8));
        label_4->setText(QApplication::translate("RxDialog", "Height", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_TOOLTIP
        mpSubspaceGroup->setToolTip(QApplication::translate("RxDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">If checked, use subspace RX by removing the specified number of principal components.</span></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_TOOLTIP
        mpSubspaceGroup->setTitle(QApplication::translate("RxDialog", "Subspace", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("RxDialog", "Number of components to remove", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class RxDialog: public Ui_RxDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_RXDIALOG_H
