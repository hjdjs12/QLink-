/********************************************************************************
** Form generated from reading UI file 'playscene.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYSCENE_H
#define UI_PLAYSCENE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayScene
{
public:

    void setupUi(QWidget *PlayScene)
    {
        if (PlayScene->objectName().isEmpty())
            PlayScene->setObjectName(QString::fromUtf8("PlayScene"));
        PlayScene->resize(800, 600);

        retranslateUi(PlayScene);

        QMetaObject::connectSlotsByName(PlayScene);
    } // setupUi

    void retranslateUi(QWidget *PlayScene)
    {
        PlayScene->setWindowTitle(QCoreApplication::translate("PlayScene", "PlayScene", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayScene: public Ui_PlayScene {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYSCENE_H
