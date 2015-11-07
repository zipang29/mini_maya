/****************************************************************************

 Copyright (C) 2002-2014 Gilles Debunne. All rights reserved.

 This file is part of the QGLViewer library version 2.6.3.

 http://www.libqglviewer.com - contact@libqglviewer.com

 This file may be used under the terms of the GNU General Public License 
 versions 2.0 or 3.0 as published by the Free Software Foundation and
 appearing in the LICENSE file included in the packaging of this file.
 In addition, as a special exception, Gilles Debunne gives you certain 
 additional rights, described in the file GPL_EXCEPTION in this package.

 libQGLViewer uses dual licensing. Commercial/proprietary software must
 purchase a libQGLViewer Commercial License.

 This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
 WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.

*****************************************************************************/

#include "MainWindow.h"
#include <qapplication.h>
#include <QCommandLineParser>
#include "parser.h"

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
      p.parse();
  }

  MainWindow w;

  w.setWindowTitle("animation");

  w.show();

  return application.exec();
}
