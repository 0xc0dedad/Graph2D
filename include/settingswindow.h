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

class Tab;

enum TabType
{
    AlgorithmsTab,
    SettingsTab,
    StorageTab
};

enum AlgorithmID
{
    BFS,
    DFS,
    Unknown = -1
};

class SettingsWindow : public QDialog
{
    Q_OBJECT

public:
    explicit SettingsWindow(QDialog *parent = Q_NULLPTR);
    ~SettingsWindow();
    QSize sizeHint() const;
    static QString pathToImages();
    AlgorithmID selectedAlgorithm() const;
    Tab *getSettingsTab() const;

private:
    void layout();
    QTabWidget *createTabs(QWidget *parent, QTabWidget **tabs);
    QPushButton *createButton(QWidget *parent, QString title,
     QWidget *handler, const char *slot, QPushButton **btn);

public slots:
    void setSelectedAlgorithm(QModelIndex index);

private slots:
    void submit();

private:
    QTabWidget *m_tabs;
    QPushButton *m_ok;
    AlgorithmID m_selected_algo;
    Tab *m_settings_tab;
};

#endif // SETTINGSWINDOW_H
