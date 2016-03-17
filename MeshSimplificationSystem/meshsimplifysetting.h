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
	QPushButton *confirm_button_;                       // 确定按钮
	QPushButton *cancel_button_;                        // 取消按钮
	QRadioButton *radio_button_rate_;                   // 选择按比例缩减
	QRadioButton *radio_button_rate_vertex_;            // 按点的比例进行缩减
	QRadioButton *radio_button_rate_face_;              // 按面的比例进行缩减
	QRadioButton *radio_button_number_;                 // 按数量缩减
	QRadioButton *radio_button_number_vertex_;          // 按点的数量缩减
	QRadioButton *radio_button_number_face_;            // 按面的数量缩减
	QLineEdit *lineedit_rate_vertex_;                   // 点缩减的比例值
	QLineEdit *lineedit_rate_face_;                     // 面缩减的比例值
	QLineEdit *lineedit_number_vertex_;                 // 点缩减的数量值
	QLineEdit *lineedit_number_face_;                   // 面缩减的数量值
};

#endif // MESHSIMPLIFYSETTING_H
