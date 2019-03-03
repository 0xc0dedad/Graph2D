#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QDialog>
#include <QTabWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QApplication>

#include "log.h"
#include "tab.h"

enum TabType
{
    AlgorithmsTab,
    SettingsTab
};

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QDialog *parent = Q_NULLPTR);
    ~SettingsWindow();
    QSize sizeHint() const;
    static QString pathToImages();

private:
    void layout();
    QTabWidget *createTabs(QWidget *parent, QTabWidget **tabs);
    QPushButton *createButton(QWidget *parent, QString title,
     QWidget *handler, const char *slot, QPushButton **btn);

private slots:
    void submit();

private:
    QTabWidget *m_tabs;
    QPushButton *m_ok;
};

#endif // SETTINGSWINDOW_H
