#ifndef MESHSIMPLIFYSETTING_H
#define MESHSIMPLIFYSETTING_H

#include <QDialog>
#include <qradiobutton.h>
#include <qlineedit.h>
#include "ui_meshsimplifysetting.h"

class MeshSimplifySetting : public QDialog
{
	Q_OBJECT

public:
	MeshSimplifySetting(QWidget *parent = 0);
	~MeshSimplifySetting();

private:
	Ui::MeshSimplifySetting ui;

public:
	QPushButton *confirm_button_;                       // ȷ����ť
	QPushButton *cancel_button_;                        // ȡ����ť
	QRadioButton *radio_button_rate_;                   // ѡ�񰴱�������
	QRadioButton *radio_button_rate_vertex_;            // ����ı�����������
	QRadioButton *radio_button_rate_face_;              // ����ı�����������
	QRadioButton *radio_button_number_;                 // ����������
	QRadioButton *radio_button_number_vertex_;          // �������������
	QRadioButton *radio_button_number_face_;            // �������������
	QLineEdit *lineedit_rate_vertex_;                   // �������ı���ֵ
	QLineEdit *lineedit_rate_face_;                     // �������ı���ֵ
	QLineEdit *lineedit_number_vertex_;                 // ������������ֵ
	QLineEdit *lineedit_number_face_;                   // ������������ֵ
};

#endif // MESHSIMPLIFYSETTING_H
