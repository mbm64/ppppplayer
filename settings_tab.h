#pragma once
#include <QMainWindow>
#include <QBoxLayout>
#include <QWidget>
#include <QListWidget>
#include "setting_tab_options.h"
class Settings : public QWidget {
	Q_OBJECT
	public:
		Settings(QWidget *parent = nullptr);
		QVBoxLayout * gen_settings_init();
	public slots:
		void show_settings();
		void exit_settings();
	private slots:
		void setting_options_clicked(QListWidgetItem * option);
	private:
		/*QVBoxLayout * generalTabInit();
		QVBoxLayout * generalTab;
		QVBoxLayout * clipTabInit();
		QVBoxLayout * clipTab;
		QVBoxLayout * seriesTabInit();
		QVBoxLayout * seriesTab;
		QVBoxLayout * subtitlesTabInit();
		QVBoxLayout * subtitlesTab;*/
		QVBoxLayout * displayed_settings;
		QListWidget * setting_options_box;	
		ClipSettings * clipTab;
		GeneralSettings * generalTab;
		SubSettings * subTab;
		ScreenshotSettings * screenshotTab;



		void update_displayed_settings(QWidget * tab);
};
