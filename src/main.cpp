#include <qapplication.h>
#include <QCommandLineParser>
#include "Parser.h"
#include "MainWindow.h"

using namespace std;

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QCommandLineParser args;
    args.setApplicationDescription("Mini bee : Application 3D permettant de modéliser des objets à partir d'un cube via du tracking de mouvement.");
    args.addHelpOption();

    QCommandLineOption fileOption(QStringList() << "f" << "fichier", "Utilise les données de mouvement spécifiées dans le fichier");
    args.addOption(fileOption);

    args.process(a);

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
        p.parse();
    }

    MainWindow w;
    w.resize(800, 600);
    w.show();

    return a.exec();
}
