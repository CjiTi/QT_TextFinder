#include "textfinder.h"
#include "ui_textfinder.h"
#include"qfile.h"
#include"QTextStream"

TextFinder::TextFinder(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TextFinder)
{
    ui->setupUi(this);
    loadTextFile();
}

TextFinder::~TextFinder()
{
    delete ui;
}

void TextFinder::on_findButton_clicked()
{
    QString search = ui->lineEdit->text();
    ui->textEdit->find(search, QTextDocument::FindWholeWords);

}
void TextFinder::loadTextFile()
{
    QFile File("input.txt");
    if (!File.exists()) {
        ui->textEdit->setPlainText("错误：资源文件input.txt不存在");
        return;
    }
    
    if (!File.open(QIODevice::ReadOnly)) {
        ui->textEdit->setPlainText("错误：无法打开资源文件 - " + File.errorString());
        return;
    }
    
    QTextStream in(&File);
    QString line = in.readAll();
    File.close();

    if (line.isEmpty()) {
        ui->textEdit->setPlainText("警告：文件内容为空");
    } else {
        ui->textEdit->setPlainText(line);
    }
    
    QTextCursor cursor = ui->textEdit->textCursor();
    cursor.movePosition(QTextCursor::Start, QTextCursor::MoveAnchor, 1);
}
