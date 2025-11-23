#pragma once

#include <QMainWindow>
#include <QFrame>
#include <QGridLayout>
#include "Tool.h"

class MultiCheckableToolRole;

class BasicToolRole;

class OtherToolRole;

class SomeTypeToolRole;


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void OnActionTriggered(bool);

private:
    Ui::MainWindow *ui;
    Tool<MultiCheckableToolRole, SomeTypeToolRole, BasicToolRole, OtherToolRole>* m_action;
    Tool<MultiCheckableToolRole, SomeTypeToolRole>* m_action2;
    Tool<MultiCheckableToolRole>* m_action3;
    Tool<BasicToolRole>* m_action4;
    Tool<>* m_action5 ;

    QFrame* f1;
    QFrame* f2;
    QFrame* f3;
};
