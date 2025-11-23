#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "MultiInsertToolRole.h"
#include "BasicToolRole.h"
#include "OtherToolRole.h"
#include "SomeTypeToolRole.h"
#include <QHBoxLayout>
#include <QPushButton>
#include <QToolButton>
#include <QFrame>
inline QToolButton* AssociateToolButton(QAction* action)
{
    auto b = new QToolButton(action->parentWidget());
    b->setDefaultAction(action);
    return b;
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_action = new Tool<MultiCheckableToolRole, SomeTypeToolRole, BasicToolRole, OtherToolRole>();
    ui->horizontalLayout->addWidget(AssociateToolButton(m_action));
    m_action2 = new Tool<MultiCheckableToolRole, SomeTypeToolRole> ();
    ui->horizontalLayout->addWidget(AssociateToolButton(m_action2));

    m_action3 = new Tool<MultiCheckableToolRole> ();
    ui->horizontalLayout->addWidget(AssociateToolButton(m_action3));

    m_action4 = new Tool<BasicToolRole> ();
    ui->horizontalLayout->addWidget(AssociateToolButton(m_action4));

    m_action5 = new Tool<> ();
    ui->horizontalLayout->addWidget(AssociateToolButton(m_action5));
    ui->horizontalLayout->setAlignment(Qt::AlignLeft);


//    m_action->As<QDebug>(); // test enable_if
//    m_action->As2<ITool>(); // test enable_if
//    QDebug* t ;
//    m_action->As2<QDebug>(); // test enable_if
//    m_action->f(t, 0, 0);

    m_action->setCheckable(true);
    m_action->setText("All");
    ui->menufile->addAction(m_action);


    m_action2->setCheckable(true);
    m_action2->setText("multi insert/Lowdose");
    ui->menufile->addAction(m_action2);

    m_action3->setCheckable(true);
    m_action3->setText("multi insert");
    ui->menufile->addAction(m_action3);

    m_action4->setCheckable(true);
    m_action4->setText("BasicTool");
    ui->menufile->addAction(m_action4);

    m_action5->setCheckable(true);
    m_action5->setText("Empty");
    ui->menufile->addAction(m_action5);

    connect(m_action, &QAction::triggered,
            this, &MainWindow::OnActionTriggered );
    connect(m_action2, &QAction::triggered,
            this, &MainWindow::OnActionTriggered );
    connect(m_action3, &QAction::triggered,
            this, &MainWindow::OnActionTriggered );
    connect(m_action4, &QAction::triggered,
            this, &MainWindow::OnActionTriggered );
    connect(m_action5, &QAction::triggered,
            this, &MainWindow::OnActionTriggered );

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::OnActionTriggered(bool)
{
    if (!dynamic_cast<MultiCheckableToolRole*>(sender()) || !dynamic_cast<QAction*>(sender()))
    {
        return;
    }
    qDebug().noquote() << "Is Multi insert activated for ["<< dynamic_cast<QAction*>(sender())->text()<<"]"<< dynamic_cast<MultiCheckableToolRole*>(sender())->KeepChecked();
}
