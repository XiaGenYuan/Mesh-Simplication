#include "meshsimplifysetting.h"

MeshSimplifySetting::MeshSimplifySetting(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	this->confirm_button_ = this->ui.confirm_button;
	this->cancel_button_ = this->ui.cancel_button;
	this->radio_button_rate_ = this->ui.radio_button_rate;             
	this->radio_button_rate_vertex_ = this->ui.radio_button_rate_vertex;         
	this->radio_button_rate_face_ = this->ui.radio_button_rate_face;             
	this->radio_button_number_ = this->ui.radio_button_number;             
	this->radio_button_number_vertex_ = this->ui.radio_button_number_vertex;
	this->radio_button_number_face_ = this->ui.radio_button_number_face;    
	this->lineedit_rate_vertex_ = this->ui.lineedit_rate_vertex;
	this->lineedit_rate_face_ = this->ui.lineedit_rate_face;
	this->lineedit_number_vertex_ = this->ui.lineedit_number_vertex;
	this->lineedit_number_face_ = this->ui.lineedit_number_face;

	//connect( this->confirm_button_, SIGNAL( clicked() ), this, SLOT( accept() ) );
	connect( this->cancel_button_, SIGNAL( clicked() ), this, SLOT( close() ) );
}

MeshSimplifySetting::~MeshSimplifySetting()
{

}
