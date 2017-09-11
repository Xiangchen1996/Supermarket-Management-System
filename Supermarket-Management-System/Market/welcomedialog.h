#ifndef WELCOMEDIALOG_H
#define WELCOMEDIALOG_H

#include <QDialog>

namespace Ui {
class welcomeDialog;
}

class welcomeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit welcomeDialog(QWidget *parent = 0);
    ~welcomeDialog();

private:
    Ui::welcomeDialog *ui;
};

#endif // WELCOMEDIALOG_H
