#include "EDialog.h"
EDialog::EDialog(QWidget *ptr,const QString&FonUrl,const QString& Text,
                 const QList<QString>&Answers,
                 const QString& ImgUrl,EKord siz):
    QWidget(ptr)
{
    main=new QVBoxLayout;
    Fon=new EImage(FonUrl);
    Fon->setParent(this);
    Fon->setMaximumSize(this->size());
    Fon->setMinimumSize(this->size());
    Fon->resize();
    text.setText("<h4><p align=left style=color:#AFEEEE>"+Text+"</p></h4>");
    text.setMaximumSize(((QWidget*)this->parent())->size().height()*0.6,((QWidget*)this->parent())->size().width()*0.3);
    answers=new QVector<EButton*>;
    if(ImgUrl!="")
    {
        img=new EImage(ImgUrl);
        img->setMaximumSize(siz.TO_QSize());
        img->setMinimumSize(siz.TO_QSize());
        img->resize();
        main->addWidget(img);
    }else
    {
        img=NULL;
    }
     main->addWidget(&text);
     if(Answers.size()==0)
     {
         EButton*temp= new EButton("://BF","://BF","Ok",QFont("Verdana",14));
         answers->push_back(temp);
         connect(temp,SIGNAL(EClick(QWidget*)),this,SLOT(_select(QWidget*)));
         main->addWidget(temp);
     }
     else
     {
         for(QString i:Answers)
         {
             EButton*temp= new EButton("://BF","://BF",i,QFont("Verdana",14));
             answers->push_back(temp);
             connect(temp,SIGNAL(EClick(QWidget*)),this,SLOT(_select(QWidget*)));
             main->addWidget(temp);
         }
     }
     this->setLayout(main);
     show();
}
void EDialog::_select(QWidget *ptr)//vozmogen bag QWidget*!=EButton*
{
    for(int i(0);i<answers->size();i++)
        if(answers->data()[i]==ptr)
        {
            emit selected(i);
            this->close();
            ((QWidget*)this->parent())->setFocus();
            return;
        }
}
void EDialog::resize()
{
    if(img!=NULL)
    {
        float temp= (float)text.size().width()/img->width();
        img->setMaximumSize(img->width()*temp,img->height()*temp);
        img->setMinimumSize(img->width()*temp,img->height()*temp);
        img->resize();
        this->setMaximumSize(img->size().width(),img->size().height()+text.size().height()*2+answers->size()*answers->data()[0]->size().height());
        this->setMinimumSize(img->size().width(),img->size().height()+text.size().height()*2+answers->size()*answers->data()[0]->size().height());
    }else
    {
        this->setMaximumSize(text.size().width(),text.size().height()*2+answers->size()*answers->data()[0]->size().height());
        this->setMinimumSize(text.size().width(),text.size().height()*2+answers->size()*answers->data()[0]->size().height());
    }
        Fon->setMaximumSize(this->size());
    Fon->setMinimumSize(this->size());
    Fon->resize();
    this->move(((QWidget*)this->parent())->geometry().width()*0.5-size().width()/2,
               ((QWidget*)this->parent())->geometry().height()*0.5-size().height()/2);
    this->setLayout(main);

}
void EDialog::Information(QWidget *ptr, const QString text,const QString&UrlImag,const EKord& siz)
{
    QList<QString> temp;
    EDialog *dial=new EDialog(ptr,"://IF",text,temp,UrlImag,siz);
    dial->resize();
    dial->show();
    ptr->setFocus();
}
EDialog::~EDialog()
{
    disconnect(this,0,0,0);
    answers->clear();
    delete answers;
}
