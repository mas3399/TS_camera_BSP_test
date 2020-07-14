#include "widget.h"
#include "./ui_widget.h"
#include "utils.h"
#include <iostream>
Widget::Widget(QWidget *parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    std::string res = Utils::getCmdResult(Utils::getLinuxPCMemCmd());
    std::cout<<res<<'\n';
}

Widget::~Widget()
{
    delete ui;
}

