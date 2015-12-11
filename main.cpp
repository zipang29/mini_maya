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

    QCommandLineOption addressOption(QStringList() << "a" << "address", "Spécifie l'adresse ou doivent êtres récupérées les données de la motion capture lorsque l'on exécute le programme en mode real time");
    args.addOption(addressOption);

    args.process(application);

    QStringList positionalArgs = args.positionalArguments();

    if (!args.isSet(fileOption))
    {
        Parser p;
        if (args.isSet(addressOption))
        {
            QHostAddress * address = new QHostAddress(args.value(addressOption));
            DataMotion * data = new DataMotion(DataModes::REAL_TIME, address);
            p.setDataMotion(data);
        }
        else
        {
            args.showHelp(1);
        }
    }
    else
    {
      Parser p(positionalArgs[0]);
      if (!p.parse())
          return 0;
    }

    Tools t;
    if (!args.isSet(fileOption) && args.isSet(addressOption)) // mode REAL_TIME
        t.getGlWidget()->setAnimationPeriod(20);//5ms = 200Hz
    else // mode file
        t.getGlWidget()->setAnimationPeriod(5);//5ms = 200Hz
    t.show();

    return application.exec();
}
