#include <qapplication.h>
#include <QCommandLineParser>

using namespace std;

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    QCommandLineParser args;
    args.setApplicationDescription("Mini bee : Application 3D permettant de modéliser des objets à partir d'un cube via du tracking de mouvement.");
    args.addHelpOption();

    QCommandLineOption fileOption(QStringList() << "f" << "fichier", "Utilise les données de mouvement spécifiées dans le fichier");
    args.addOption(fileOption);

    args.process();

    return a.exec();
}
