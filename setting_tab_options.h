#pragma once
#include<QWidget>

#include <QCheckBox>
#include <QSettings>
#include <QLineEdit>
class GeneralSettings : public QWidget{
	Q_OBJECT
	public:
		GeneralSettings(QWidget *parent = nullptr);
};
class ClipSettings : public QWidget{
	Q_OBJECT
	public:
		ClipSettings(QWidget *parent = nullptr);
	private slots:
		void update_clip_subs();
		void update_clip_dir();
		void update_clip_ext(QString s);
	private:
		QCheckBox * clip_with_subs;
		QLineEdit * clip_dir_box;
		QLineEdit * clip_extension;
		QSettings setting;
};

class SubSettings : public QWidget{
	Q_OBJECT
	public: 
		SubSettings(QWidget *parent = nullptr);
	private: 
		QLineEdit * prefered_sub_lang;
		QLineEdit * prefered_aud_lang;
		QSettings setting;
	private slots:
		void update_prefered_subs(QString s);
		void update_prefered_aud(QString s);
};
