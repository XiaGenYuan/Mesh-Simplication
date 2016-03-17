/********************************************************************************
** Form generated from reading UI file 'meshsimplifysetting.ui'
**
** Created: Fri Jan 23 11:13:03 2015
**      by: Qt User Interface Compiler version 4.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MESHSIMPLIFYSETTING_H
#define UI_MESHSIMPLIFYSETTING_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MeshSimplifySetting
{
public:
    QGroupBox *groupBox;
    QRadioButton *radio_button_rate;
    QGroupBox *groupBox_2;
    QRadioButton *radio_button_rate_vertex;
    QRadioButton *radio_button_rate_face;
    QLineEdit *lineedit_rate_vertex;
    QLineEdit *lineedit_rate_face;
    QRadioButton *radio_button_number;
    QGroupBox *groupBox_3;
    QRadioButton *radio_button_number_vertex;
    QRadioButton *radio_button_number_face;
    QLineEdit *lineedit_number_vertex;
    QLineEdit *lineedit_number_face;
    QWidget *layoutWidget;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *confirm_button;
    QPushButton *cancel_button;

    void setupUi(QDialog *MeshSimplifySetting)
    {
        if (MeshSimplifySetting->objectName().isEmpty())
            MeshSimplifySetting->setObjectName(QString::fromUtf8("MeshSimplifySetting"));
        MeshSimplifySetting->resize(410, 331);
        groupBox = new QGroupBox(MeshSimplifySetting);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(30, 30, 351, 221));
        radio_button_rate = new QRadioButton(groupBox);
        radio_button_rate->setObjectName(QString::fromUtf8("radio_button_rate"));
        radio_button_rate->setGeometry(QRect(20, 20, 89, 16));
        radio_button_rate->setChecked(true);
        groupBox_2 = new QGroupBox(groupBox);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(20, 40, 321, 71));
        radio_button_rate_vertex = new QRadioButton(groupBox_2);
        radio_button_rate_vertex->setObjectName(QString::fromUtf8("radio_button_rate_vertex"));
        radio_button_rate_vertex->setGeometry(QRect(10, 10, 111, 16));
        radio_button_rate_vertex->setChecked(true);
        radio_button_rate_face = new QRadioButton(groupBox_2);
        radio_button_rate_face->setObjectName(QString::fromUtf8("radio_button_rate_face"));
        radio_button_rate_face->setGeometry(QRect(10, 40, 111, 16));
        lineedit_rate_vertex = new QLineEdit(groupBox_2);
        lineedit_rate_vertex->setObjectName(QString::fromUtf8("lineedit_rate_vertex"));
        lineedit_rate_vertex->setGeometry(QRect(130, 10, 181, 20));
        lineedit_rate_face = new QLineEdit(groupBox_2);
        lineedit_rate_face->setObjectName(QString::fromUtf8("lineedit_rate_face"));
        lineedit_rate_face->setGeometry(QRect(130, 40, 181, 20));
        radio_button_number = new QRadioButton(groupBox);
        radio_button_number->setObjectName(QString::fromUtf8("radio_button_number"));
        radio_button_number->setGeometry(QRect(20, 120, 89, 16));
        groupBox_3 = new QGroupBox(groupBox);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(20, 139, 321, 71));
        radio_button_number_vertex = new QRadioButton(groupBox_3);
        radio_button_number_vertex->setObjectName(QString::fromUtf8("radio_button_number_vertex"));
        radio_button_number_vertex->setGeometry(QRect(10, 10, 111, 16));
        radio_button_number_vertex->setChecked(true);
        radio_button_number_face = new QRadioButton(groupBox_3);
        radio_button_number_face->setObjectName(QString::fromUtf8("radio_button_number_face"));
        radio_button_number_face->setGeometry(QRect(10, 40, 111, 16));
        lineedit_number_vertex = new QLineEdit(groupBox_3);
        lineedit_number_vertex->setObjectName(QString::fromUtf8("lineedit_number_vertex"));
        lineedit_number_vertex->setGeometry(QRect(130, 10, 181, 20));
        lineedit_number_face = new QLineEdit(groupBox_3);
        lineedit_number_face->setObjectName(QString::fromUtf8("lineedit_number_face"));
        lineedit_number_face->setGeometry(QRect(130, 40, 181, 20));
        layoutWidget = new QWidget(MeshSimplifySetting);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 270, 351, 33));
        hboxLayout = new QHBoxLayout(layoutWidget);
        hboxLayout->setSpacing(6);
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        confirm_button = new QPushButton(layoutWidget);
        confirm_button->setObjectName(QString::fromUtf8("confirm_button"));

        hboxLayout->addWidget(confirm_button);

        cancel_button = new QPushButton(layoutWidget);
        cancel_button->setObjectName(QString::fromUtf8("cancel_button"));

        hboxLayout->addWidget(cancel_button);


        retranslateUi(MeshSimplifySetting);

        QMetaObject::connectSlotsByName(MeshSimplifySetting);
    } // setupUi

    void retranslateUi(QDialog *MeshSimplifySetting)
    {
        MeshSimplifySetting->setWindowTitle(QApplication::translate("MeshSimplifySetting", "\347\256\200\345\214\226\345\217\202\346\225\260\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QString());
        radio_button_rate->setText(QApplication::translate("MeshSimplifySetting", "\347\274\251\345\207\217\346\257\224\344\276\213", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QString());
        radio_button_rate_vertex->setText(QApplication::translate("MeshSimplifySetting", "\346\214\211\347\202\271\347\232\204\346\257\224\344\276\213\347\256\200\345\214\226", 0, QApplication::UnicodeUTF8));
        radio_button_rate_face->setText(QApplication::translate("MeshSimplifySetting", "\346\214\211\351\235\242\347\232\204\346\257\224\344\276\213\347\256\200\345\214\226", 0, QApplication::UnicodeUTF8));
        lineedit_rate_vertex->setText(QApplication::translate("MeshSimplifySetting", "0.7", 0, QApplication::UnicodeUTF8));
        lineedit_rate_face->setText(QApplication::translate("MeshSimplifySetting", "0.9", 0, QApplication::UnicodeUTF8));
        radio_button_number->setText(QApplication::translate("MeshSimplifySetting", "\347\274\251\345\207\217\346\225\260\351\207\217", 0, QApplication::UnicodeUTF8));
        groupBox_3->setTitle(QString());
        radio_button_number_vertex->setText(QApplication::translate("MeshSimplifySetting", "\346\214\211\347\202\271\347\232\204\346\225\260\351\207\217\347\256\200\345\214\226", 0, QApplication::UnicodeUTF8));
        radio_button_number_face->setText(QApplication::translate("MeshSimplifySetting", "\346\214\211\351\235\242\347\232\204\346\225\260\351\207\217\347\256\200\345\214\226", 0, QApplication::UnicodeUTF8));
        confirm_button->setText(QApplication::translate("MeshSimplifySetting", "OK", 0, QApplication::UnicodeUTF8));
        cancel_button->setText(QApplication::translate("MeshSimplifySetting", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MeshSimplifySetting: public Ui_MeshSimplifySetting {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MESHSIMPLIFYSETTING_H
