#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    this->setMaximumSize(280,400);
    this->setMinimumSize(280,400);
    this->setWindowTitle("计算器");
    QFont f("楷体",14);
    ui->text_show->setFont(f);

    //按钮放图片
    QIcon con("E:\\qt\\calulator\\tt.png");
    ui->button_del->setIcon(con);
    //改变按钮背景色
    ui->button_equal->setStyleSheet("background-color:pink");
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_button_1_clicked()
{
    expression += "1";
    ui->text_show->setText(expression);
}

void Widget::on_button_2_clicked()
{
    expression += "2";
    ui->text_show->setText(expression);
}

void Widget::on_button_3_clicked()
{
    expression += "3";
    ui->text_show->setText(expression);
}

void Widget::on_button_4_clicked()
{
    expression += "4";
    ui->text_show->setText(expression);
}

void Widget::on_button_5_clicked()
{
    expression += "5";
    ui->text_show->setText(expression);
}

void Widget::on_button_6_clicked()
{
    expression += "6";
    ui->text_show->setText(expression);
}

void Widget::on_button_7_clicked()
{
    expression += "7";
    ui->text_show->setText(expression);
}

void Widget::on_button_8_clicked()
{
    expression += "8";
    ui->text_show->setText(expression);
}

void Widget::on_button_9_clicked()
{
    expression += "9";
    ui->text_show->setText(expression);
}

void Widget::on_button_0_clicked()
{
    expression += "0";
    ui->text_show->setText(expression);
}

void Widget::on_button_mul_clicked()
{
    expression += "*";
    ui->text_show->setText(expression);
}

void Widget::on_button_div_clicked()
{
    expression += "/";
    ui->text_show->setText(expression);
}

void Widget::on_button_left_clicked()
{
    expression += "(";
    ui->text_show->setText(expression);
}

void Widget::on_button_right_clicked()
{
    expression += ")";
    ui->text_show->setText(expression);
}

void Widget::on_button_add_clicked()
{
    expression += "+";
    ui->text_show->setText(expression);
}

void Widget::on_button_sub_clicked()
{
    expression += "-";
    ui->text_show->setText(expression);
}

void Widget::on_button_empty_clicked()
{
    expression.clear();
    ui->text_show->clear();
}

void Widget::on_button_del_clicked()
{
    expression.chop(1);
    ui->text_show->setText(expression);
}

void Widget::on_button_equal_clicked()
{
    QStack<int> s_num, s_opt;

        char opt[128] = {0};
        int i = 0, tmp = 0, num1, num2;

        //把QString转换成char *
        QByteArray ba;
        ba.append(expression);   //把QString转换成QByteArray
        strcpy(opt, ba.data());  //data可以把QByteArray转换成const char *

        while (opt[i] != '\0' || s_opt.empty() != true)
        {
            if (opt[i] >= '0' && opt[i] <= '9')
            {
                tmp = tmp * 10 + opt[i] - '0';
                i++;
                if (opt[i] < '0' || opt[i] > '9')
                {
                    s_num.push(tmp);
                    tmp = 0;
                }
            }
            else           //操作符
            {
                if (s_opt.empty() == true || Priority(opt[i]) > Priority(s_opt.top()) ||
                        (s_opt.top() == '(' && opt[i] != ')'))
                {
                    s_opt.push(opt[i]);
                    i++;
                    continue;
                }

                if (s_opt.top() == '(' && opt[i] == ')')
                {
                    s_opt.pop();
                    i++;
                    continue;
                }

                if (Priority(opt[i]) <= Priority(s_opt.top()) || (opt[i] == ')' && s_opt.top() != '(') ||
                    (opt[i] == '\0' && s_opt.empty() != true))
                {
                    char ch = s_opt.top();
                    s_opt.pop();
                    switch(ch)
                    {
                        case '+':
                            num1 = s_num.top();
                            s_num.pop();
                            num2 = s_num.top();
                            s_num.pop();
                            s_num.push(num1 + num2);
                            break;
                        case '-':
                            num1 = s_num.top();
                            s_num.pop();
                            num2 = s_num.top();
                            s_num.pop();
                            s_num.push(num1 - num2);
                            break;
                        case '*':
                            num1 = s_num.top();
                            s_num.pop();
                            num2 = s_num.top();
                            s_num.pop();
                            s_num.push(num1 * num2);
                            break;
                        case '/':
                            num1 = s_num.top();
                            s_num.pop();
                            num2 = s_num.top();
                            s_num.pop();
                            s_num.push(num1 / num2);
                            break;
                    }
                }
            }
        }
        ui->text_show->setText(QString::number(s_num.top()));
        expression = s_num.top();
}
int Widget::Priority(char ch)
{
    switch(ch)
    {
        case '(':
            return 3;
        case '*':
        case '/':
            return 2;
        case '+':
        case '-':
            return 1;
        default:
            return 0;
    }
}


