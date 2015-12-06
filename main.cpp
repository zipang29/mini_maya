#include "MainWindow.h"
#include <qapplication.h>
#include <QCommandLineParser>
#include "parser.h"
#include "Tools.h"
#include <QGLViewer/qglviewer.h>

int main(int argc, char** argv)
{
    QApplication application(argc,argv);

    QCommandLineParser args;
    args.setApplicationDescription("Mini bee : Application 3D permettant de modéliser des objets à partir d'un cube via du tracking de mouvement.");
    args.addHelpOption();

    QCommandLineOption fileOption(QStringList() << "f" << "fichier", "Utilise les données de mouvement spécifiées dans le fichier");
    args.addOption(fileOption);

    args.process(application);

    QStringList positionalArgs = args.positionalArguments();
    if (positionalArgs.size() == 0)
    {
      args.showHelp(1);
    }

    if (!args.isSet(fileOption))
      args.showHelp(0);
    else
    {
      Parser p(positionalArgs[0]);
      if (!p.parse())
          return 0;
    }

    Tools t;
    t.show();

    MainWindow * w = MainWindow::getInstance();
    w->setWindowTitle("animation");

    int width = QApplication::desktop()->screenGeometry().width();
    int height = QApplication::desktop()->screenGeometry().height();

    w->setFixedSize(width, height-250);
    w->show();

    return application.exec();
}
