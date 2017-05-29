#ifndef _ABOUTWIDGET_H_
#define _ABOUTWIDGET_H_

#include "StandardWidget.h"

namespace Ui
{
	class AboutWidget;
}

class AboutWidget : public StandardWidget
{
Q_OBJECT
public:
	AboutWidget(Device *device, QWidget *parent = 0);
	~AboutWidget();
	
private:
	QString getIpAddress() const;

	Ui::AboutWidget *ui;
};


#endif
