#include "settings_tab.h"
#include <QHBoxLayout>
#include <QPushButton>
//#include <QListWidget>
#include <QCheckBox>
#include <QLineEdit>
#include <QTextStream>
Settings::Settings(QWidget *parent) : QWidget(parent){
	QStringList setting_options = {"General","Clips", "Series","Subtitles and Audio"};
	this->resize(800,800);	
	this->setWindowFlag(Qt::Dialog);
	clipTab = new ClipSettings();
	generalTab = new GeneralSettings();
	subTab = new SubSettings();
		
	setting_options_box = new QListWidget();
	
	QHBoxLayout * settings_layout = new QHBoxLayout();
	displayed_settings = new QVBoxLayout();

	connect(setting_options_box,&QListWidget::itemClicked,this, &Settings::setting_options_clicked);

	QPushButton * quit_button = new QPushButton("Exit");
	connect(quit_button, &QPushButton::pressed, this, &Settings::exit_settings );
	displayed_settings -> addWidget(generalTab);
	displayed_settings -> addWidget(quit_button,0, Qt::AlignBottom | Qt::AlignRight);
	setting_options_box->addItems(setting_options);
	settings_layout->addWidget(setting_options_box);
	settings_layout -> addLayout(displayed_settings,2);
	setLayout(settings_layout);


}
void Settings::show_settings(){
	this -> show();
}
void Settings::exit_settings(){
	this -> close();
}


void Settings::setting_options_clicked(QListWidgetItem * option){
	QTextStream out(stdout);
	out << option -> text() <<Qt::endl;
	QString option_name = option -> text();
	if(option_name == "General"){
		update_displayed_settings(generalTab);
	}
	else if (option_name == "Clips") {
		update_displayed_settings(clipTab);	
	}
	else if(option_name == "Subtitles and Audio"){
		update_displayed_settings(subTab);
	}
}
void Settings::update_displayed_settings(QWidget * tab){
	QLayoutItem*  item = displayed_settings -> itemAt(0);
	displayed_settings -> removeItem(item);
	item ->widget() ->hide();
	displayed_settings ->insertWidget(0, tab);
	tab -> show();

}
/*QVBoxLayout * Settings::generalTabInit(){
	QVBoxLayout * box = new QVBoxLayout();
	QCheckBox *test1 = new QCheckBox("test setting 1");
	Qt::Alignment allign = Qt::AlignLeft | Qt::AlignTop;
	box -> setSpacing(0);
	box -> addWidget(test1,0,allign);	
	box -> addWidget(new QCheckBox("test 2"),0,allign);



	return box;

}

QVBoxLayout* Settings::clipTabInit(){
	QVBoxLayout *box = new QVBoxLayout();
	QCheckBox * clip_with_subs = new QCheckBox("Include Current Subtitles (if aplicable) Into Clip");
	box -> addWidget(clip_with_subs);
	
	QLineEdit * clip_dir = new QLineEdit("Clip Directory");
	box -> addWidget(clip_dir);

	QLineEdit * clip_extension = new QLineEdit("Clip Extension");
	box -> addWidget(clip_extension);
	

	


	return box;
}*/


