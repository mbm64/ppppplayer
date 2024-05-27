#include "setting_tab_options.h"
#include <QBoxLayout>
#include <QCheckBox>
#include <QLineEdit>
#include <QGridLayout>
#include <QSettings>
#include <QLabel>
#include <QPushButton>
#include <QStandardPaths>
#include <QFileDialog>
//General Settings
//{{{
GeneralSettings::GeneralSettings(QWidget *parent) : QWidget(parent){
	QVBoxLayout * box = new QVBoxLayout();
	QCheckBox *test1 = new QCheckBox("test setting 1");
	Qt::Alignment allign = Qt::AlignLeft | Qt::AlignTop;
	box -> setSpacing(0);
	box -> addWidget(test1,0,allign);	
	box -> addWidget(new QCheckBox("test 2"),0,allign);
	setLayout(box);
}
//}}}


//Clip Settings
//{{{
ClipSettings::ClipSettings(QWidget*parent) : QWidget(parent){
	
	QGridLayout * grid = new QGridLayout();
	clip_with_subs = new QCheckBox();
	//clip with subs
	grid -> addWidget(new QLabel("Clip Videos With Subtitles (If Applicable)"),0,0);
	grid -> addWidget( clip_with_subs,0,1 );
	bool sub_enabled = setting.value("clips/subs", 0).toBool();	
	clip_with_subs->setChecked(sub_enabled);
	connect(clip_with_subs,&QCheckBox::stateChanged, this, &ClipSettings::update_clip_subs);	
	
	//clip directory 
	clip_dir_box = new QLineEdit();
	QPushButton * browse_dir = new QPushButton("Browse");
	grid -> addWidget(new QLabel("Clips Directory"),1,0);
	grid -> addWidget(clip_dir_box,1,1);
	grid -> addWidget(browse_dir,1,2);
	
	QString clip_dir = setting.value("clips/dir", QStandardPaths::writableLocation(QStandardPaths::MoviesLocation)).toString();
	clip_dir_box->setText(clip_dir);
	clip_dir_box->setReadOnly(true);

	connect(browse_dir,&QPushButton::pressed, this, &ClipSettings::update_clip_dir);
	//clip extension
	QLineEdit * clip_extension = new QLineEdit();
	grid -> addWidget(new QLabel("Clip File Format"),2,0);
	grid -> addWidget(clip_extension,2,1);
	
	QString clip_ext = setting.value("clips/ext","mp4").toString();
	clip_extension->setText(clip_ext);
	connect(clip_extension, &QLineEdit::textChanged,this,&ClipSettings::update_clip_ext);

	setLayout(grid);
}
void ClipSettings::update_clip_subs(){
	setting.setValue("clips/subs", clip_with_subs->isChecked());
}
void ClipSettings::update_clip_dir(){
	QString directory = QFileDialog::getExistingDirectory(this,"Choose Clip Dir",clip_dir_box->text());
	clip_dir_box -> setText(directory);
	setting.setValue("clips/dir", directory);
	

}
void ClipSettings::update_clip_ext(QString s){
	setting.setValue("clips/ext", s);

}
//}}}

//Sub Setting 
//{{{
SubSettings::SubSettings(QWidget * parent) : QWidget(parent){
	QGridLayout * grid = new QGridLayout();

	prefered_sub_lang = new QLineEdit(this);
	grid->addWidget(new QLabel("Preferred Subtitle Languages\n(Seperate With Commas)"),0,0);
	grid -> addWidget(prefered_sub_lang,0,1);
	prefered_sub_lang->setText(setting.value("sub/preferred","").toString());	
	connect(prefered_sub_lang, &QLineEdit::textChanged, this, &SubSettings::update_prefered_subs);

	
	prefered_aud_lang = new QLineEdit(this);
	grid -> addWidget(new QLabel("Preferred Audio Languages\n(Seperate With Commas)"),1,0);
	grid -> addWidget(prefered_aud_lang,1,1);
	prefered_aud_lang->setText(setting.value("aud/preferred","").toString());	
	connect(prefered_aud_lang, &QLineEdit::textChanged,this,&SubSettings::update_prefered_aud);
	setLayout(grid);
}
void SubSettings::update_prefered_subs(QString s){
	setting.setValue("sub/preferred", s);

}
void SubSettings::update_prefered_aud(QString s){
	setting.setValue("aud/preferred",s);

}





//}}}


//ScreenShot Settings
ScreenshotSettings::ScreenshotSettings(QWidget * parent) : QWidget(parent){
	
	QGridLayout * grid = new QGridLayout();
	QLabel * dir_label = new QLabel("ScreenShot Directory");
	grid -> addWidget(dir_label,0,0);

	path = new QLineEdit();
	path->setReadOnly(true);
	QString	current_path = settings.value("screenshot/path",QStandardPaths::writableLocation(QStandardPaths::PicturesLocation)).toString();
	path -> setText(current_path);
	grid -> addWidget(path,0,1);

	QPushButton * browse = new QPushButton("Browse");
	grid -> addWidget(browse,0,2);
	connect(browse, &QPushButton::pressed, this, &ScreenshotSettings::browse_clicked);
	setLayout(grid);
}

void ScreenshotSettings::browse_clicked(){
	QString dir = QFileDialog::getExistingDirectory();
	settings.setValue("screenshot/path", dir);
	path -> setText(dir);


}
